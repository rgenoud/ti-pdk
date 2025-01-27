/**
 *  \file   main_console.c
 *
 *  \brief  Example application main file. This application demonstrates
 *          the file operations on FAT formatted MMCSD device.
 *
 */

/*
 * Copyright (C) 2019-2022 Texas Instruments Incorporated - http://www.ti.com/
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

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "ti/osal/osal.h"
#include "ti/osal/TaskP.h"

/* RTOS Header files */
#include <ti/csl/cslr_device.h>
#include "FATFS_log.h"
#include <ti/fs/fatfs/diskio.h>
#include <ti/fs/fatfs/FATFS.h>
#include <ti/drv/mmcsd/MMCSD.h>
#include <ti/fs/fatfs/example/console/src/fs_shell_app_utils.h>
#include <ti/board/board.h>

/* GPIO is used to check the pin (SDCD) whether the SD Card is inserted
 * or not. However in case of AM65XX there is no GPIO pin to check the
 * SDCD. Hence this feature , i.e using GPIO to check the SD card insert
 * is disabled. Same is the case with J7 and Simulator (J7). Here the demo
 * assumes that the SD card is inserted */
#if !(defined(SOC_J721E) || defined(SIMULATOR) || defined(SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4))
#define FATFS_GPIO_ENABLED 1

#ifndef SIMULATOR
#include <ti/drv/gpio/GPIO.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>
#endif

#endif

#ifndef FATFS_GPIO_ENABLED
#ifndef GPIO_PIN_MMC_SDCD_ACTIVE_STATE
#define GPIO_PIN_MMC_SDCD_ACTIVE_STATE 1
#endif
#endif

/**********************************************************************
 ************************** Macros ************************************
 **********************************************************************/
#define MMCSD_INSTANCE_MMCSD            (0U)
#ifdef CONSOLE_EMMC
#define MMCSD_INSTANCE_EMMC             (1U)

#define GPIO_PIN_VAL_LOW                (0U)
#define GPIO_PIN_VAL_HIGH               (1U)
#endif

/**********************************************************************
 ************************** Internal functions ************************
 **********************************************************************/
#ifdef MULTI_PARTITION
#ifdef CONSOLE_EMMC
static void EmmcsReset(void);
static void delay(unsigned int delayValue);
#endif

static int16_t mainMenu();
#endif
/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/
#define APP_TSK_STACK_MAIN (16U * 1024U)
static uint8_t gAppTskStackMain[APP_TSK_STACK_MAIN] __attribute__((aligned(32)));

#ifdef MULTI_PARTITION
extern PARTITION VolToPart[];
#endif

/* ON Board LED pins which are connected to GPIO pins. */
typedef enum GPIO_PIN {
    GPIO_PIN_MMC_SDCD      = 0U,
#ifdef CONSOLE_EMMC
    GPIO_PIN_EMMC_RST,
#endif
    GPIO_PIN_COUNT
}GPIO_PIN;

#ifdef FATFS_GPIO_ENABLED
/* GPIO Driver board specific pin configuration structure */
GPIO_PinConfig gpioPinConfigs[] = {
    /* Output pin : AM335X_ICE V2_LD_PIN */
    GPIO_DEVICE_CONFIG(GPIO_MMC_SDCD_PORT_NUM, GPIO_MMC_SDCD_PIN_NUM) |
    GPIO_CFG_IN_INT_BOTH_EDGES | GPIO_CFG_INPUT,
#ifdef CONSOLE_EMMC
    GPIO_DEVICE_CONFIG(GPIO_EMMC_RST_PORT_NUM, GPIO_EMMC_RST_PIN_NUM) | GPIO_CFG_OUTPUT,
#endif
};

/* GPIO Driver call back functions */
GPIO_CallbackFxn gpioCallbackFunctions[] = {
    NULL,
};

#if (defined(SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4))
GPIO_v0_Config GPIO_v0_config = {
    gpioPinConfigs,
    gpioCallbackFunctions,
    sizeof(gpioPinConfigs) / sizeof(GPIO_PinConfig),
    sizeof(gpioCallbackFunctions) / sizeof(GPIO_CallbackFxn),
    0,
};
#else
/* GPIO Driver configuration structure */
GPIO_v1_Config GPIO_v1_config = {
    gpioPinConfigs,
    gpioCallbackFunctions,
    sizeof(gpioPinConfigs) / sizeof(GPIO_PinConfig),
    sizeof(gpioCallbackFunctions) / sizeof(GPIO_CallbackFxn),
    0,
};
#endif
#endif

/* MMCSD function table for MMCSD implementation */
FATFS_DrvFxnTable FATFS_drvFxnTable = {
    MMCSD_close,
    MMCSD_control,
    MMCSD_init,
    MMCSD_open,
    MMCSD_write,
    MMCSD_read
};

/* FATFS configuration structure */
FATFS_HwAttrs FATFS_initCfg[_VOLUMES] =
{
#if defined (SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)
    { 
        1U
    },
#else
    {
        0U
    },
#endif
    {
        1U
    },
    {
        2U
    },
    {
        3U
    }
};

/* FATFS objects */
FATFS_Object FATFS_objects[_VOLUMES];

/* FATFS configuration structure */
const FATFSConfigList FATFS_config = {
    {
        &FATFS_drvFxnTable,
        &FATFS_objects[0],
        &FATFS_initCfg[0]
    },

    {
         &FATFS_drvFxnTable,
         &FATFS_objects[1],
         &FATFS_initCfg[1]
    },

    {
         &FATFS_drvFxnTable,
         &FATFS_objects[2],
         &FATFS_initCfg[2]
    },

    {NULL, NULL, NULL},

    {NULL, NULL, NULL}
};

FATFS_Handle fatfsHandle = NULL;

#ifdef CONSOLE_EMMC
FATFS_Handle eMMCFatfsHandle = NULL;
#endif

Uint32 fatfsShellProcessFlag = UFALSE;
Uint32 fs_media_needs_initialization = UFALSE;
Uint32 fs_media_needs_close = UFALSE;

#ifdef MULTI_PARTITION
/* Main Menu Function */
static int16_t mainMenu()
{
    int16_t i = 0,drive_partition = 5;
    while(UTRUE)
    {
        for(i = 0; (FATFS_DFLT_VOLUME_PD != VolToPart[i].pd) && (i < FATFS_NUM_OF_PARTITIONS); i++)
        {
            FATFS_log("\n%x:/",i);
        }

        FATFS_log("\r\nSelect drive : ");
        /* Get drive_partition */
        UART_scanFmt("%d\n",&drive_partition);

        if (drive_partition < 4)
        {
            return drive_partition;
        }
        else
        {
            FATFS_log("\r\nEnter Valid drive_partition\r\n");
        }
   }
}
#endif

/* Callback function */
void AppGpioCallbackFxn(void);

/*
 *  ======== test function ========
 */
void fatfs_console(void* a0, void* a1)
{
#ifdef MULTI_PARTITION
    int16_t option = 0;
    char drivePath[3];
#endif

#ifdef FATFS_GPIO_ENABLED
    /* GPIO initialization */
    GPIO_init();

    /* Set the callback function */
    GPIO_setCallback(GPIO_PIN_MMC_SDCD, AppGpioCallbackFxn);

    /* Enable GPIO interrupt on the specific gpio pin */
    GPIO_enableInt(GPIO_PIN_MMC_SDCD);
#endif

#ifdef CONSOLE_EMMC
    EmmcsReset();
#endif

    /* MMCSD FATFS initialization */
    FATFS_init();

#if !defined(FATFS_GPIO_ENABLED)
    FATFS_log ("\nPlease ensure SD card is inserted before running this demo\r\n");
    fs_is_media_inserted = UTRUE;
    if(UTRUE)
#else
    if (GPIO_PIN_MMC_SDCD_ACTIVE_STATE == GPIO_read(GPIO_PIN_MMC_SDCD))
#endif
    {
        FATFS_open(MMCSD_INSTANCE_MMCSD, NULL, &fatfsHandle);
        fatfsShellProcessFlag = UTRUE;
        fs_is_media_inserted = UTRUE;

    }
    else
    {
        FATFS_log ("\nPlease insert card.\r\n");
        fs_is_media_inserted = UFALSE;
    }

#ifdef CONSOLE_EMMC
    if(FATFS_OK != FATFS_open(MMCSD_INSTANCE_EMMC, NULL, &eMMCFatfsHandle))
    {
        FATFS_log("\n eMMC Fails to open \n");
    }
#endif
    while(BTRUE)
    {
        /* Check for any media state changes and initialize/close FATFS accordingly.
         * Please note that this is checked*/

        if(fs_media_needs_initialization) {

            FATFS_log("\nMedia Inserted..Initializing..\n");
            FATFS_open(MMCSD_INSTANCE_MMCSD, NULL, &fatfsHandle);
            fatfsShellProcessFlag = UTRUE;
            fs_media_needs_initialization = UFALSE;
        }

        if(fs_media_needs_close) {
            FATFS_close(fatfsHandle);
            fatfsShellProcessFlag = UFALSE;
            fs_media_needs_close = UFALSE;
            FATFS_log("\nMedia Removed..Please insert media..\n");
        }

        if (UFALSE != fatfsShellProcessFlag)
        {
#ifdef MULTI_PARTITION
            option = mainMenu();
            snprintf(drivePath, 3, "%d:", option);
            FSShellAppUtilsProcess(drivePath);
#else
            FSShellAppUtilsProcess();
            fatfsShellProcessFlag = UFALSE;
#endif

        }
    }
}


#ifndef BARE_METAL
#if (defined(SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)) && (defined(BUILD_MPU) || defined (BUILD_C7X))
extern void Osal_initMmuDefault(void);
void InitMmu(void)
{
    Osal_initMmuDefault();
}
#endif
#endif

/*
 *  ======== main ========
 */
int main(void)
{
	TaskP_Handle task;
	TaskP_Params taskParams;
    /* Call board init functions */
    Board_initCfg boardCfg;
    boardCfg = BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_UART_STDIO | BOARD_INIT_MODULE_CLOCK;

#if (defined(SOC_J721E) || defined (SOC_J7200) || defined(SOC_J721S2) || defined(SOC_J784S4)) &&  ((__ARM_ARCH == 7) && (__ARM_ARCH_PROFILE == 'R'))
    /* Clear it until the issue is resolved */
    boardCfg &= ~(BOARD_INIT_MODULE_CLOCK);
#endif

    Board_init(boardCfg);

    OS_init();

    TaskP_Params_init(&taskParams);
    taskParams.stack = gAppTskStackMain;
    taskParams.stacksize = sizeof (gAppTskStackMain);

    task = TaskP_create(&fatfs_console, &taskParams);
    if (NULL == task) {
        OS_stop();
    }

    /* Start OS */
    OS_start(); /* does not return */

    return (0);
}


void media_open()
{
    FATFS_open(MMCSD_INSTANCE_MMCSD, NULL, &fatfsHandle);
    fatfsShellProcessFlag = UTRUE;
}
void media_close()
{
    FATFS_close(fatfsHandle);
    fatfsShellProcessFlag = UFALSE;
}

#ifdef FATFS_GPIO_ENABLED
/*
 *  ======== Callback function ========
 */
void AppGpioCallbackFxn(void)
{
    if (GPIO_PIN_MMC_SDCD_ACTIVE_STATE == GPIO_read(GPIO_PIN_MMC_SDCD))
    {
        fs_is_media_inserted = UTRUE; /* The media has been inserted now */
        fs_media_needs_initialization = UTRUE; /* Need to initialize FATFS with the media */
    }
    else
    {
        fs_is_media_inserted = UFALSE;/*  The media has been ejected now */
        fs_media_needs_close = UTRUE; /* Need to close FATFS with the media */
    }
}
#endif

#ifdef CONSOLE_EMMC
static void EmmcsReset(void)
{
    /* EMMC reset */
    GPIO_write(GPIO_PIN_EMMC_RST, GPIO_PIN_VAL_LOW);
    delay(100);
    GPIO_write(GPIO_PIN_EMMC_RST, GPIO_PIN_VAL_HIGH);
    delay(100);
}

/*
 *  ======== Delay function ========
 */
static void delay(unsigned int delayValue)
{
    volatile uint32_t delay1 = delayValue*10000;
    while (delay1--) ;
}
#endif
