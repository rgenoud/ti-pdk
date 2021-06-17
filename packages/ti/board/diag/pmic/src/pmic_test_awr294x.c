/*
 * Copyright (C) 2014-2021 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 *  \file   pmic_test.c
 *
 *  \brief  PMIC diagnostic test file
 *
 *  Implements the test for validating the PMIC access and voltage control
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(SOC_TPR12) || defined(SOC_AWR294X)
#include <ti/drv/mibspi/MIBSPI.h>
#include <ti/drv/mibspi/soc/MIBSPI_soc.h>
#endif

#include <ti/drv/i2c/I2C.h>
#include <ti/drv/i2c/soc/I2C_soc.h>
#include <ti/drv/uart/UART_stdio.h>

#include "board.h"
#include "board_cfg.h"

#if defined(SOC_J721E) || defined(SOC_J7200) || defined(SOC_TPR12) || defined(SOC_AWR294X)
#include <ti/csl/soc.h>
#include "board_utils.h"
#include "diag_common_cfg.h"
#endif

#include <ti/drv/edma/edma.h>

typedef struct pmic_data
{
    uint8_t   slaveSelect;
    uint8_t   devInstance;
    uint8_t   pmicIdReg;
    uint8_t   pmicIdPage;
    uint8_t   pmicReg;
    uint8_t   pmicVoltVal;
    uint8_t   pwdProtReg;
    uint8_t   pmicDevCtrl;
}pmic_data_t;

#if defined(SOC_J721E) || defined(SOC_J7200)
Board_I2cInitCfg_t boardI2cInitCfg = {0, BOARD_SOC_DOMAIN_WKUP, false};
#endif
int32_t numPmic = 1;
pmic_data_t *gDualPmicData;

/*********************************  *************************************
 ************************** Internal functions ************************
 **********************************************************************/

pmic_data_t* Get_PmicData(char *pBoardName);
 
extern I2C_config_list I2C_config;

/* Board specific definitions */
#define I2C_INSTANCE                       (0U)

#define SPI_INSTANCE                       (1U)  /* MIBSPI_INST_ID_MSS_SPIB */
#define PMIC_RDID_CMD                      (0x02U)
#define PMIC_RD_REVID_CMD                   (0X01U)

#if defined(SOC_J721E) || defined(SOC_J7200)
#define BOARD_NAME_LENGTH                  (16)
#else
#define BOARD_NAME_LENGTH                  (8)
#endif

/* TPS659037 Register values. */
#define TPS659037_I2C_SLAVE_ADDR           (0x59U)
#define TPS659037_PMICID_REG               (0x4FU)
#define TPS659037_PMIC_PAGEID              (0x02U)
#define TPS659037_PMIC_REG                 (0x23U)
#define TPS659037_PMIC_VOLTAGE_VAL         (0x44U)

/* TPS65910 Register values. */
#define TPS65910_I2C_SLAVE_ADDR            (0x2D)
#define TPS65910_PMICID_REG                (0x80)
#define TPS65910_PMIC_PAGEID               (0x00U)
#define TPS65910_PMIC_REG                  (0x22U)
#define TPS65910_PMIC_VOLTAGE_VAL          (0x27U)
#define TPS65910_PMIC_DEV_CTRL             (0x3F)

#define PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL             (0x10u)
#define PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL_SHIFT       (0x04u)
#define PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL_SR_I2C      (0x0u)
#define PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL_CTL_I2C     (0x1u)

/* TPS65218 Register values. */
#define TPS65218_I2C_SLAVE_ADDR            (0x24)
#define TPS65218_PMICID_REG                (0x00U)
#define TPS65218_PMIC_PAGEID               (0x00U)
#define TPS65218_PMIC_REG                  (0x16U)
#define TPS65218_PMIC_VOLTAGE_VAL          (0x19U)
#define TPS65218_PWD_REG                   (0x10)

#define TPS65218_PROT_PWD                  (0x7DU)

/* TPS65917 Register value. */
#define TPS65917_I2C_SLAVE_ADDR            (0x58U)
#define TPS65917_PMICID_REG                (0x4FU)
#define TPS65917_PMIC_PAGEID               (0x02U)
#define TPS65917_PMIC_REG                  (0x23U)
#define TPS65917_PMIC_VOLTAGE_VAL          (0x44U)

/* TPS65941 Register value */
#define TPS65941_PMICID_REG                (0x01U)

#define TPS65941_PMICA_I2C_SLAVE_ADDR      (0x48U)
#define TPS65941_PMICA_REG                 (0x16U)/* BUCK5 */
#define TPS65941_PMICA_VOLTAGE_VAL         (0xADU)/* 1.7V */

#define TPS65941_PMICB_I2C_SLAVE_ADDR      (0x4CU)
#define TPS65941_PMICB_REG                 (0x0EU)/* BUCK1 */
#define TPS65941_PMICB_VOLTAGE_VAL         (0x41U)/* 0.8V */

/* LP8764 Register value */
#define LP8764_PMICB_I2C_SLAVE_ADDR        (0x4CU)
#define LP8764_PMICID_REG                  (0x01U)
#define LP8764_PMIC_REG                    (0x14U)/* BUCK4 */
#define LP8764_PMIC_VOLTAGE_VAL            (0xADU)/* 1.7V */

/* TPS65313 Register value */
#define TPS65313_PMIC_SPI_CS               (0x00U)
#define TPS65313_PMICID_REG                (0x02U)
#define TPS65313_PMIC_REG                  (0x0EU) //TODO: Need to update regitser value for tpr12_evm
#define TPS65313_PMIC_VOLTAGE_VAL          (0x41U) //TODO: Need to update regitser voltage value for tpr12_evm

/* LP8762 Register value */
#define LP8762_PMIC_SPI_CS                 (0x0U)
#define LP8762_PMICID_REG                  (0x01U)
#define LP8762_PMIC_REG                    (0x3AU)
#define LP8762_PMIC_VOLTAGE_VAL            (0xADU)

/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/

pmic_data_t tps65910 = {
    TPS65910_I2C_SLAVE_ADDR,
    I2C_INSTANCE,
    TPS65910_PMICID_REG,
    TPS65910_PMIC_PAGEID,
    TPS65910_PMIC_REG,
    TPS65910_PMIC_VOLTAGE_VAL,
    0U,
    TPS65910_PMIC_DEV_CTRL
};

pmic_data_t tps65218 = {
    TPS65218_I2C_SLAVE_ADDR,
    I2C_INSTANCE,
    TPS65218_PMICID_REG,
    TPS65218_PMIC_PAGEID,
    TPS65218_PMIC_REG,
    TPS65218_PMIC_VOLTAGE_VAL,
    TPS65218_PWD_REG,
    0U
};

pmic_data_t tps659037 = {
    TPS659037_I2C_SLAVE_ADDR,
    I2C_INSTANCE,
    TPS659037_PMICID_REG,
    TPS659037_PMIC_PAGEID,
    TPS659037_PMIC_REG,
    TPS659037_PMIC_VOLTAGE_VAL,
    0U,
    0U
};

pmic_data_t tps65917 = {
    TPS65917_I2C_SLAVE_ADDR,
    I2C_INSTANCE,
    TPS65917_PMICID_REG,
    TPS65917_PMIC_PAGEID,
    TPS65917_PMIC_REG,
    TPS65917_PMIC_VOLTAGE_VAL,
    0U,
    0U
};

pmic_data_t tps65941_pmicA = {
    TPS65941_PMICA_I2C_SLAVE_ADDR,
    I2C_INSTANCE,
    TPS65941_PMICID_REG,
    0U,
    TPS65941_PMICA_REG,
    TPS65941_PMICA_VOLTAGE_VAL,
    0U,
    0U
};

pmic_data_t tps65941_pmicB = {
    TPS65941_PMICB_I2C_SLAVE_ADDR,
    I2C_INSTANCE,
    TPS65941_PMICID_REG,
    0U,
    TPS65941_PMICB_REG,
    TPS65941_PMICB_VOLTAGE_VAL,
    0U,
    0U
};

pmic_data_t lp8764 = {
    LP8764_PMICB_I2C_SLAVE_ADDR,
    I2C_INSTANCE,
    LP8764_PMICID_REG,
    0U,
    LP8764_PMIC_REG,
    LP8764_PMIC_VOLTAGE_VAL,
    0U,
    0U
};

pmic_data_t tps65313 = {
    TPS65313_PMIC_SPI_CS,
    MIBSPI_INST_ID_MSS_SPIB,
    TPS65313_PMICID_REG,
    0U,
    TPS65313_PMIC_REG,
    TPS65313_PMIC_VOLTAGE_VAL,
    0U,
    0U
};

pmic_data_t lp8762 = {
    LP8762_PMIC_SPI_CS,
    MIBSPI_INST_ID_MSS_SPIB,
    LP8762_PMICID_REG,
    0U,
    LP8762_PMIC_REG,
    LP8762_PMIC_VOLTAGE_VAL,
    0U,
    0U
};

void setPmicVoltage(void *h, pmic_data_t *pPmicData, uint8_t val)
{
    uint8_t tx[3];
#if defined(SOC_TPR12) || defined(SOC_AWR294X)
    /*TODO: Need to add write command */
    MIBSPI_Handle handle;
    handle = (MIBSPI_Handle )h;
    MIBSPI_Transaction transaction;

    memset(&transaction, 0, sizeof(transaction));

    /* Configure Data Transfer */
    transaction.count = 2;
    transaction.txBuf = tx;
    transaction.rxBuf = NULL;
    transaction.slaveIndex = 0;
    tx[0] = pPmicData->pmicReg;
    tx[1] = val;
    /* Start Data Transfer */
    MIBSPI_transfer(handle, &transaction);

#else
    I2C_Handle handle;
    handle = (I2C_Handle)h;

    I2C_Transaction t;

    memset(&t, 0, sizeof(t));
    t.slaveAddress = pPmicData->slaveSelect;
    t.writeBuf = tx;
    #if defined (SOC_AM437x)
        /* Unlock the password protected register. */
        tx[0] = pPmicData->pwdProtReg;
        tx[1] = (pPmicData->pmicReg ^ TPS65218_PROT_PWD);
        t.writeCount = 2;
        I2C_transfer(handle, &t);
        /* Write the actual value. */
        tx[0] = pPmicData->pmicReg;
        tx[1] = val;
        I2C_transfer(handle, &t);
    #else
    t.writeCount = 2;
    t.readCount = 0;
    tx[0] = pPmicData->pmicReg;
    tx[1] = val;
    I2C_transfer(handle, &t);
    #endif
#endif
}

void writePmicReg(void *h, pmic_data_t *pPmicData, uint8_t reg, uint8_t val)
{
    uint8_t tx[4];
#if defined(SOC_TPR12) || defined(SOC_AWR294X)
    /*TODO: Need to add write command */
    MIBSPI_Handle handle;
    handle = (MIBSPI_Handle )h;
    MIBSPI_Transaction transaction;

    memset(&transaction, 0, sizeof(transaction));

    /* Configure Data Transfer */
    transaction.count = 3;
    transaction.txBuf = tx;
    transaction.rxBuf = NULL;
    transaction.slaveIndex = 0;
    tx[0] = reg;
    tx[1] = 0;
    tx[2] = val;
    CacheP_wbInv((void *) tx, 3);
    /* Start Data Transfer */
    MIBSPI_transfer(handle, &transaction);

#else
    I2C_Handle handle;
    handle = (I2C_Handle)h;

    I2C_Transaction t;

    memset(&t, 0, sizeof(t));
    t.slaveAddress = pPmicData->slaveSelect;
    t.writeBuf = tx;
    #if defined (SOC_AM437x)
        /* Unlock the password protected register. */
        tx[0] = pPmicData->pwdProtReg;
        tx[1] = (pPmicData->pmicReg ^ TPS65218_PROT_PWD);
        t.writeCount = 2;
        I2C_transfer(handle, &t);
        /* Write the actual value. */
        tx[0] = pPmicData->pmicReg;
        tx[1] = val;
        I2C_transfer(handle, &t);
    #else
    t.writeCount = 2;
    t.readCount = 0;
    tx[0] = pPmicData->pmicReg;
    tx[1] = val;
    I2C_transfer(handle, &t);
    #endif
#endif
}

uint8_t readPmicVoltage(void *h, uint8_t slaveSelect, uint8_t regOffset)
{
    uint8_t tx[8];
    uint8_t rx[8];
#if defined(SOC_TPR12) || defined(SOC_AWR294X)
    /*TODO: Need to add read ID command */
    MIBSPI_Handle handle;
    handle = (MIBSPI_Handle)h;
    MIBSPI_Transaction transaction;

    memset(&transaction, 0, sizeof(transaction));

    /* Configure Data Transfer */
    transaction.count = 3;
    transaction.txBuf = tx;
    transaction.rxBuf = rx;
    transaction.slaveIndex = 0;
    tx[0] = regOffset;
    tx[1] = 0x10;
    tx[2] = 0;
    /* Start Data Transfer */
    MIBSPI_transfer(handle, &transaction);
#else
    I2C_Handle handle;
    handle = (I2C_Handle)h;
    I2C_Transaction t;

    memset(&t, 0, sizeof(t));

    t.slaveAddress = slaveSelect;
    t.writeBuf = tx;
    t.writeCount = 1;
    t.readBuf = rx;
    t.readCount = 1;
    tx[0] = regOffset;
    I2C_transfer(handle, &t);
#endif
    return rx[2];
}

#if (defined (SOC_AM572x)) || (defined (SOC_AM571x)) || defined (SOC_AM574x)
uint32_t getPmicId(I2C_Handle h, pmic_data_t *pPmicData)
{
    uint32_t val = 0;
    uint8_t tx[2];
    uint8_t rx[1];
    uint8_t reg = pPmicData->pmicIdReg;
    I2C_Transaction t;

    memset(&t, 0, sizeof(t));

    t.slaveAddress = pPmicData->slaveSelect;
    t.writeBuf = tx;
    t.writeCount = 2;
    t.readBuf = rx;
    t.readCount = 1;
    tx[0] = reg;
    tx[1] = pPmicData->pmicIdPage;
    I2C_transfer(h, &t);
    val |= (rx[0] << 24);
    tx[0] = (reg + 1);
    tx[1] = pPmicData->pmicIdPage;
    I2C_transfer(h, &t);
    val |= (rx[0] << 16);
    tx[0] = (reg + 2);
    tx[1] = pPmicData->pmicIdPage;
    I2C_transfer(h, &t);
    val |= (rx[0] << 8);
    tx[0] = (reg + 3);
    tx[1] = pPmicData->pmicIdPage;
    I2C_transfer(h, &t);
    val |= (rx[0] << 0);
    return val;
}
#endif

#if (defined (SOC_AM437x)) || (defined (SOC_AM335x)) || (defined (SOC_TPR12) || defined(SOC_AWR294X))
uint32_t getPmicId(void *h, pmic_data_t *pPmicData)
{
#if (defined(SOC_TPR12) || defined(SOC_AWR294X))
    uint8_t tx[2] = {0, 0};
    uint8_t rx[2];
    //uint8_t status = 0;

    MIBSPI_Handle handle;
    handle = (MIBSPI_Handle)h;
    MIBSPI_Transaction transaction;

    memset(&transaction, 0, sizeof(transaction));

    UART_printf("Reading revision ID.. \n");
    /* Read revision ID */
    tx[0] = PMIC_RD_REVID_CMD;
    tx[1] = 0x01;
    /* Read Device ID in rx buffer */
    transaction.txBuf = tx;
    transaction.rxBuf = rx;
    transaction.count = 2;
    transaction.slaveIndex = 0;
    MIBSPI_transfer(handle, &transaction);

    UART_printf("PMIC Revision ID = 0x%08x\n\n", rx[0]);

    UART_printf("Reading PMIC Device ID.. \n");

    tx[0] = PMIC_RDID_CMD;
    tx[1] = pPmicData->pmicIdReg;

    /* Transfer Deivce ID read Command */
    transaction.txBuf = tx;
    transaction.rxBuf = rx;
    transaction.count = 2;
    transaction.slaveIndex = 0;
    MIBSPI_transfer(handle, &transaction);

    /* return read ID command*/
    return rx[0];

#else
    uint8_t tx[2] = {0, 0};
    uint8_t rx = 0;
    I2C_Handle handle;
    handle = (I2C_Handle)h;
    I2C_Transaction t;

    memset(&t, 0, sizeof(t));

    t.slaveAddress = pPmicData->slaveSelect;
    t.writeBuf = tx;
    t.readBuf = &rx;
    t.writeCount = 1;
    t.readCount = 0;

    /* Enable I2C access to the functional registers. */
    #if defined (SOC_AM335x)
    tx[0] = pPmicData->pmicDevCtrl;
    rx = readPmicVoltage(handle, pPmicData->slaveSelect, pPmicData->pmicDevCtrl);
    rx |= (PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL_CTL_I2C << PMIC_DEVCTRL_REG_SR_CTL_I2C_SEL_SHIFT);
    tx[1] = rx;
    t.writeCount = 2;
    rx = 0;
    I2C_transfer(handle, &t);
    #endif

    /* Read the PMIC ID register. */
    tx[0] = pPmicData->pmicIdReg;
    t.writeCount = 1;
    t.readCount = 1;
    I2C_transfer(handle, &t);
    return rx;
#endif

}
#endif

#if defined(SOC_J721E) || defined(SOC_J7200)
uint32_t getPmicId(I2C_Handle h, pmic_data_t *pPmicData)
{
    uint32_t val = 0;
    uint8_t tx[1];
    uint8_t rx[1];
    uint8_t reg = pPmicData->pmicIdReg;
    I2C_Transaction t;

    memset(&t, 0, sizeof(t));

    if(pPmicData->slaveSelect == TPS65917_I2C_SLAVE_ADDR)
    {
        t.slaveAddress = (pPmicData->slaveSelect + 1);
    }
    else /* TPS65941 */
    {
        t.slaveAddress = pPmicData->slaveSelect;
    }
    t.writeBuf = tx;
    t.writeCount = 1;
    t.readBuf = rx;
    t.readCount = 1;
    tx[0] = reg;
    I2C_transfer(h, &t);
    val |= (rx[0] << 24);

    if(pPmicData->slaveSelect == TPS65917_I2C_SLAVE_ADDR)
    {
        tx[0] = (reg + 1);
        I2C_transfer(h, &t);
        val |= (rx[0] << 16);
        tx[0] = (reg + 2);
        I2C_transfer(h, &t);
        val |= (rx[0] << 8);
        tx[0] = (reg + 3);
        I2C_transfer(h, &t);
        val |= (rx[0] << 0);
    }
    return val;
}
#endif

EDMA_Handle gDmaHandle;
int32_t edma_open(uint8_t devInstance)
{
    EDMA_instanceInfo_t instanceInfo;
    int32_t errorCode;
    MibSpi_HwCfg cfg;
    int32_t         retVal = 0;

    retVal = MIBSPI_socGetInitCfg((enum MibSpi_InstanceId)devInstance, &cfg);

    gDmaHandle = EDMA_getHandle(cfg.edmaCCId, &instanceInfo);
    if(gDmaHandle == NULL)
    {
        EDMA3CCInitParams 	initParam;

        EDMA3CCInitParams_init(&initParam);
        initParam.initParamSet = TRUE;
        if (EDMA_init(cfg.edmaCCId, &initParam) != EDMA_NO_ERROR)
        {
            printf("EDMA_init failed \n");
            return -1;
        }
        /* Open DMA driver instance 0 for SPI test */
        gDmaHandle = EDMA_open(cfg.edmaCCId, &errorCode, &instanceInfo);
    }

    if(gDmaHandle == NULL)
    {
        printf("Open DMA driver failed with error=%d\n", retVal);
        return -1;
    }

    return 0;
}

void *Board_PmicInit(uint8_t devInstance)
{

#if (defined(SOC_TPR12) || defined(SOC_AWR294X))
    MIBSPI_Params     params;
    MIBSPI_Handle     handle;

    if(edma_open(devInstance))
    {
        UART_printf("DMA Open Failied\n");
        return NULL;
    }

    /* Initialize the SPI */
    MIBSPI_init();

    /* Setup the default SPI Parameters */
    MIBSPI_Params_init(&params);

    /* Disble DMA */
    params.dmaEnable = 1;
    params.dmaHandle = gDmaHandle;

    /* Set SPI in master mode */
    params.mode = MIBSPI_MASTER;
    params.u.masterParams.bitRate = 1000000U;
    params.pinMode = MIBSPI_PINMODE_4PIN_CS;
    params.dataSize = 8U;
    params.frameFormat = MIBSPI_POL0_PHA1;
    params.csHold = 1;

    params.u.masterParams.numSlaves = 1U;
    params.u.masterParams.t2cDelay  = 0x5,                   /* t2cDelay */
    params.u.masterParams.c2tDelay  = 0x5,                /* c2tDelay */
    params.u.masterParams.wDelay    = 0,                   /* wDelay */
    params.u.masterParams.slaveProf[0].chipSelect = 0U;
    params.u.masterParams.slaveProf[0].ramBufLen = MIBSPI_RAM_MAX_ELEM;
    params.u.masterParams.slaveProf[0].dmaReqLine = 0U;

    /* Open the SPI Instance for MibSpi */
    handle = MIBSPI_open((enum MibSpi_InstanceId)devInstance, &params);
#else
    int i;
    I2C_Params i2cParams;
    I2C_Handle handle = NULL;
#if defined(SOC_J721E) || defined(SOC_J7200)
    enableI2C(CSL_WKUP_I2C0_CFG_BASE);
#endif
    for (i=0; I2C_config[i].fxnTablePtr != NULL; i++)
    {
        ((I2C_HwAttrs *)I2C_config[i].hwAttrs)->enableIntr = false;
    }

    I2C_init();

    I2C_Params_init(&i2cParams);

    handle = I2C_open(devInstance, &i2cParams);

#endif
    return (void *)handle;
}

void Board_PmicDeinit(void* h)
{
#if (defined(SOC_TPR12) || defined(SOC_AWR294X))
    MIBSPI_Handle handle;
    handle = (MIBSPI_Handle)h;
    MIBSPI_close(handle);
#else
    I2C_Handle handle;
    handle = (I2C_Handle)h;
    I2C_close(handle);
#endif
}

int pmic_test()
{
    int ret = 0;
    uint8_t voltage, regVal, val;
/* TODO: Need to update it for tpr12 after getting register details*/
#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
    uint8_t voltage, val;
#endif
    void* handle = NULL;
#if defined(SOC_J721E) || defined(SOC_J7200)
    Board_IDInfo_v2 info = {0};
#else
    Board_IDInfo boardInfo;
#endif
    pmic_data_t *pPmicData;
    int32_t stat = BOARD_SOK;

#if defined(SOC_J721E) || defined(SOC_J7200)
    Board_setI2cInitConfig(&boardI2cInitCfg);
    stat = Board_getIDInfo_v2(&info, BOARD_I2C_EEPROM_ADDR);
#else
    stat = Board_getIDInfo(&boardInfo);
#endif

/* TODO: Need to update it for tpr12 */
#if (defined(SOC_TPR12) || defined(SOC_AWR294X))
    stat = BOARD_SOK;
#endif

    if(stat == BOARD_SOK)
    {
#if defined(SOC_J721E) || defined(SOC_J7200)
        pPmicData = Get_PmicData(info.boardInfo.boardName);
#else

/* TODO : Need to update this after Flashing board id details */
#if defined(SOC_AWR294X)
        pPmicData = &lp8762;
        numPmic = 1;
#else
        pPmicData = Get_PmicData(boardInfo.boardName);
#endif
#endif
        handle = (void *)Board_PmicInit(pPmicData->devInstance);

        UART_printf("\n*********************************************\n"); 
        UART_printf  ("*                PMIC Test                  *\n");
        UART_printf  ("*********************************************\n");

        while(numPmic)
        {
#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
            val = pPmicData->pmicVoltVal;
#endif
            UART_printf("Testing PMIC module... \n");
            numPmic--;

            regVal = 0x3D;
            voltage = readPmicVoltage(handle, pPmicData->slaveSelect, regVal);
            UART_printf("GPIO OUTPUT register Default Value = 0x%x\n", voltage);

            UART_printf("Setting GPIO1 Output to High\n");
            val    = voltage | 0x1;
            BOARD_delay(10000);
            writePmicReg(handle, pPmicData, regVal, val);

            voltage = readPmicVoltage(handle, pPmicData->slaveSelect, regVal);
            UART_printf("GPIO OUTPUT register Updated Value = 0x%x\n", voltage);
            if((voltage & 0x1) == 0x1)
            {
                UART_printf("Setting GPIO1 Output to High Successful!\n");
            }
            else
            {
                UART_printf("Setting GPIO1 Output to High Failed!!\n");
            }

#if !(defined(SOC_TPR12) || defined(SOC_AWR294X))
            voltage = readPmicVoltage(handle, pPmicData->slaveSelect, pPmicData->pmicReg);
            UART_printf("Initial PMIC voltage = 0x%x\n", voltage);
            UART_printf("Setting PMIC voltage to 0x%x\n", val);
            setPmicVoltage(handle, pPmicData, val);
            UART_printf("done!\n");
            UART_printf("PMIC voltage after = 0x%x\n", readPmicVoltage(handle, pPmicData->slaveSelect, pPmicData->pmicReg));
            UART_printf("Setting PMIC voltage to original value\n");
            setPmicVoltage(handle, pPmicData, voltage);
            UART_printf("Final voltage value = 0x%x\n", readPmicVoltage(handle, pPmicData->slaveSelect, pPmicData->pmicReg));
            numPmic--;

            if(numPmic)
            {
                pPmicData = gDualPmicData;
            }
#endif
        }

        UART_printf("Test PASSED!\n");

        Board_PmicDeinit(handle);
    }
    return ret;
}

/* Fetch the PMIC data structure. */
pmic_data_t* Get_PmicData(char *pBoardName)
{
    pmic_data_t *pPmicData = NULL;

    /* Check if the board is GPEVM by comparing the string read from EEPROM. */
    if (strncmp("AM572PM_", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps659037;
    }
    /* Check if the board is AM572xIDK by comparing the string read from EEPROM. */
    else if (strncmp("AM572IDK", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps659037;
    }
    /* Check if the board is AM574xIDK by comparing the string read from EEPROM. */
    else if (strncmp("AM574IDK", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps659037;
    }
    /* Check if the board is AM571xIDK by comparing the string read from EEPROM. */
    else if (strncmp("AM571IDK", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps659037;
    }
    /* Check if the board is AM437x GPEVM by comparing the string read from EEPROM. */
    else if (strncmp("AM43__GP", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps65218;
    }
    /* Check if the board is AM437x HSEVM by comparing the string read from EEPROM. */
    else if (strncmp("AM43XXHS", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps65218;
    }
    /* Check if the board is SKAM437x by comparing the string read from EEPROM. */
    else if (strncmp("AM43__SK", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps65218;
    }
    /* Check if the board is AM335x GPEVM by comparing the string read from EEPROM. */
    else if (strncmp("A33515BB", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps65910;
    }
    /* Check if the board is BBBAM335x by comparing the string read from EEPROM. */
    else if (strncmp("A335BNLT", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps65910;
    }
    /* Check if the board is ICEV2AM335x by comparing the string read from EEPROM. */
    else if (strncmp("A335_ICE", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps65910;
    }
    /* Check if the board is SKAM335x by comparing the string read from EEPROM. */
    else if (strncmp("A335X_SK", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps65910;
    }
    /* Check if the board is J721E SoM with Alt PMIC by comparing the string read from EEPROM. */
    else if (strncmp("J721EX-PM1-SOM", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps65917;
        numPmic = 1;
    }
    /* Check if the board is J721E SoM with Dual PMIC by comparing the string read from EEPROM. */
    else if ((strncmp("J721EX-PM2-SOM", pBoardName, BOARD_NAME_LENGTH) == 0U) ||
             (strncmp("J7200X-PM1-SOM", pBoardName, BOARD_NAME_LENGTH) == 0U))
    {
        pPmicData     = &tps65941_pmicA;
        gDualPmicData = &tps65941_pmicB;
        numPmic = 2;
    }
    /* Check if the board is J7200 SoM with Dual PMIC by comparing the string read from EEPROM. */
    else if (strncmp("J7200X-PM2-SOM", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData     = &tps65941_pmicA;
        gDualPmicData = &lp8764;
        numPmic = 2;
    }
    /* Check if the board is TPR12_EVM by comparing the string read from EEPROM. */
    else if (strncmp("TPR_EVM", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &tps65313;
    }
    /* Check if the board is AWR294x_EVM by comparing the string read from EEPROM. */
    else if (strncmp("AWR294X_EVM", pBoardName, BOARD_NAME_LENGTH) == 0U)
    {
        pPmicData = &lp8762;
    }
    else
    {
        /* If the board is not one of these, then the PmicData returns NULL. */
    }

    return pPmicData;
}

/*
 *  ======== main ========
 */
int main(void)
{
    Board_initCfg boardCfg;
#ifdef PDK_RAW_BOOT
    boardCfg = BOARD_INIT_PINMUX_CONFIG | 
        BOARD_INIT_UART_STDIO;
#else
    boardCfg = BOARD_INIT_UART_STDIO | BOARD_INIT_PINMUX_CONFIG;
#endif
    Board_init(boardCfg);
    
    return pmic_test();
}

void AppDelay(uint32_t delayVal)
{
    uint32_t cnt = 0;
    while(cnt < delayVal)
    {
        asm("");
        cnt++;
    }
}

