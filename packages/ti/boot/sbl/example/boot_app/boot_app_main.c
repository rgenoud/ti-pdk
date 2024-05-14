/*
 *  Copyright (c) Texas Instruments Incorporated 2024
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \file boot_app_main.c
 *
 *  \brief File containing main function implementation for boot app
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/sciclient/sciserver_tirtos.h>
#include "boot_app_priv.h"
#if defined(BOOT_MMCSD)
#include "boot_app_mmcsd.h"
#elif defined(BOOT_OSPI)
#include "boot_app_ospi.h"
#if defined(CAN_RESP_TASK_ENABLED)
#include <ti/boot/sbl/soc/k3/sbl_qos.h>
#include "boot_app_can.h"
#endif
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Test application stack size */
#define BOOT_APP_TASK_STACK               (10U * 1024U)

/* Task Priority Levels, CAN Task has higher priority so that CAN Response happens 
 * first followed by the Boot Task */
#define BOOT_APP_CAN_TASK_PRIORITY        (4)
#define BOOT_APP_BOOT_TASK_PRIORITY       (2)

/* Uncomment the following for debug logs */
/* #define UART_PRINT_DEBUG */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Stack for the CAN response task */
#if defined(CAN_RESP_TASK_ENABLED)
static uint8_t gBootAppCanStack[BOOT_APP_TASK_STACK] __attribute__((aligned(32)));
TaskP_Handle gBootAppCanTask;
#endif

/* Stack for the Boot task */
static uint8_t gBootAppTaskStack[BOOT_APP_TASK_STACK] __attribute__((aligned(32)));
TaskP_Handle gBootAppTask;
static uint64_t gBootAppTimeStart, gBootAppTimeFinish;

/* ========================================================================== */
/*                  Internal/Private Function Declarations                    */
/* ========================================================================== */

/**
 * \brief  This function initializes SCI Server to process RM/PM Requests by other cores
 *
 * \param  None
 *
 * \return CSL_PASS for success, CSL_EFAIL for failure
 */
static uint32_t BootApp_setupSciServer(void);

/**
 * \brief  Function to set board muxes for Ethernet firmware if needed
 *
 * \param  None
 *
 * \return None
 */
static void BootApp_ethMuxConfig(void);

/**
 * \brief  This function initializes PMU counter
 *
 * \param  None
 *
 * \return None
 */
static void BootApp_armR5PmuCntrInit(void);

/**
 * \brief  This function calculates Time in Microseconds
 *
 * \param pmuCntrVal PMU counter value
 *
 * \return Time in microseconds
 */
static uint32_t BootApp_getTimeInMicroSec(uint32_t pmuCntrVal);

/**
 * \brief  Function to load boot images and boot cores
 *
 * \param  None
 *
 * \return None
 */
static uint32_t BootApp_loadImg(void);

/**
 * \brief  Function to request stage cores
 *
 * \param  stageNum stage number for which cores are requested
 *
 * \return CSL_PASS for success, CSL_EFAIL for failure
 */
static int32_t BootApp_requestCores(uint8_t stageNum);

/**
 * \brief  Function to release stage cores
 *
 * \param  stageNum stage number for which cores are released
 *
 * \return CSL_PASS for success, CSL_EFAIL for failure
 */
static int32_t BootApp_releaseCores(uint8_t stageNum);

/**
 * \brief  Boot App Task Function
 *
 * \param  None
 *
 * \return None
 */
static void BootApp_bootTaskFxn(void* a0, void* a1);

#if defined(CAN_RESP_TASK_ENABLED)
/**
 * \brief  CAN Response Task Function
 *
 * \param  None
 *
 * \return None
 */
static void BootApp_canTaskFxn(void* a0, void* a1);

/**
 * \brief  Function to initialize Board Cfgs, PLLs, Module Clock for Main Domain and DDR 
 *
 * \param  None
 *
 * \return None
 */
static void BootApp_mainDomainSetup(void);
#endif

/* Function Pointer used while reading data from the storage. */
extern int32_t  (*fp_readData)(void *dstAddr, void *srcAddr, uint32_t length);
extern void     (*fp_seek)(void *srcAddr, uint32_t location);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t main(void)
{
    Board_initCfg boardCfg;
    uint32_t ret = CSL_PASS;
    TaskP_Params bootTaskParams;

#if defined(CAN_RESP_TASK_ENABLED)
    TaskP_Params canRespTaskParams;
    /* Take MCAN transceivers out of STB mode to the NORMAL Mode */
    BootApp_canEnableTransceivers();
#endif

    boardCfg = BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_UART_STDIO;
    Board_init(boardCfg);
    OS_init();

    ret = BootApp_setupSciServer();
    if(ret != CSL_PASS)
    {
        UART_printf("Failed to setup sciserver for boot app\r\n");
        OS_stop();
    }
    else
    {
        BootApp_armR5PmuCntrInit();

        UART_printf("MCU R5F App started at %d usecs\r\n", BootApp_getTimeInMicroSec(CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM)));

    #if defined(CAN_RESP_TASK_ENABLED) 
        /* Initialize the task params */
        TaskP_Params_init(&canRespTaskParams);
        canRespTaskParams.priority    = BOOT_APP_CAN_TASK_PRIORITY;
        canRespTaskParams.stack       = gBootAppCanStack;
        canRespTaskParams.stacksize   = sizeof (gBootAppCanStack);

        gBootAppCanTask = TaskP_create(&BootApp_canTaskFxn, &canRespTaskParams);
        if(NULL == gBootAppCanTask)
        {
            UART_printf("Can Response Task creation failed\r\n");
            OS_stop();
        }
    #endif

        /* Initialize the task params */
        TaskP_Params_init(&bootTaskParams);
        bootTaskParams.priority       = BOOT_APP_BOOT_TASK_PRIORITY;
        bootTaskParams.stack          = gBootAppTaskStack;
        bootTaskParams.stacksize      = sizeof (gBootAppTaskStack);

        gBootAppTask = TaskP_create(&BootApp_bootTaskFxn, &bootTaskParams);
        if (NULL == gBootAppTask)
        {
            UART_printf("Boot Task creation failed\r\n");
            OS_stop();
        }

        OS_start();    /* Does not return */
    }
    return(0);
}

#if defined(MPU1_HLOS_BOOT_ENABLED)
/* Function to clean the MCU R5 cache for a given start address and given memory size */
void BootApp_McuDCacheClean(void *addr, uint32_t size)
{
    /* Invalidate by MVA */
    CSL_armR5CacheWbInv((const void *)addr, uint32_to_int32(size), BTRUE);
    return;
}
#endif

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

static uint32_t BootApp_setupSciServer(void)
{
    Sciserver_TirtosCfgPrms_t appPrms;
    Sciclient_ConfigPrms_t clientPrms;
    uint32_t ret = CSL_PASS;

    appPrms.taskPriority[SCISERVER_TASK_USER_LO] = 1;
    appPrms.taskPriority[SCISERVER_TASK_USER_HI] = 4;

    /* Sciclient needs to be initialized before Sciserver. Sciserver depends on
     * Sciclient API to execute message forwarding */
    ret = Sciclient_configPrmsInit(&clientPrms);
    if (ret == CSL_PASS)
    {
        ret = Sciclient_init(&clientPrms);
    }

    if (ret == CSL_PASS)
    {
        ret = Sciserver_tirtosInit(&appPrms);
    }

    if (ret == CSL_PASS)
    {
        UART_printf("Starting Sciserver..... PASSED\r\n");
    }
    else
    {
        UART_printf("Starting Sciserver..... FAILED\r\n");
    }

    return ret;
}

static void BootApp_armR5PmuCntrInit(void)
{
    uint32_t val;

    /* Configure PMU with User mode access */
    CSL_armR5PmuCfg(0, 0, 1);
    
    /* Read and clear the cycle counter overflow */
    val = CSL_armR5PmuReadCntrOverflowStatus();
    val &= 0x80000000; /* Bitwise AND with Mask */
    CSL_armR5PmuClearCntrOverflowStatus(val);
    
    /* Configure PMU Cycle Counter */
    CSL_armR5PmuCfgCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM, CSL_ARM_R5_PMU_EVENT_TYPE_CYCLE_CNT);
    
    /* Enable PMU counter */
    CSL_armR5PmuEnableAllCntrs(1);
    CSL_armR5PmuEnableCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM, 1);
    
    return;
}

static uint32_t BootApp_getTimeInMicroSec(uint32_t pmuCntrVal)
{
    uint64_t mcu_clk_freq = SBL_MCU1_CPU0_FREQ_HZ;
    uint32_t cycles_per_usec = (mcu_clk_freq / 1000000);
    return (pmuCntrVal/cycles_per_usec);
}

#if defined(CAN_RESP_TASK_ENABLED)
static void BootApp_canTaskFxn(void* a0, void* a1)
{
    BootApp_canResponseTest();
    return;
}

static void BootApp_mainDomainSetup()
{
    uint32_t       retVal;
    Sciclient_DefaultBoardCfgInfo_t boardCfgInfo;
    Board_initCfg  boardCfg;

    /* Sciclient Board Cfg set up for Main Domain */
    retVal = Sciclient_getDefaultBoardCfgInfo(&boardCfgInfo);
    if(CSL_PASS != retVal)
    {
        UART_printf("Sciclient get default Board Cfg... FAILED\r\n");
    }

    Sciclient_BoardCfgPrms_t bootAppBoardCfgPrms    = {
                                                       .boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLow,
                                                       .boardConfigHigh = 0,
                                                       .boardConfigSize = boardCfgInfo.boardCfgLowSize,
                                                       .devGrp = DEVGRP_01
                                                      };
    Sciclient_BoardCfgPrms_t bootAppBoardCfgPmPrms  = {
                                                       .boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowPm,
                                                       .boardConfigHigh = 0,
                                                       .boardConfigSize = boardCfgInfo.boardCfgLowPmSize,
                                                       .devGrp = DEVGRP_01
                                                      };
    Sciclient_BoardCfgPrms_t bootAppBoardCfgRmPrms  = {
                                                       .boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowRm,
                                                       .boardConfigHigh = 0,
                                                       .boardConfigSize = boardCfgInfo.boardCfgLowRmSize,
                                                       .devGrp = DEVGRP_01
                                                      };
    Sciclient_BoardCfgPrms_t bootAppBoardCfgSecPrms = {
                                                       .boardConfigLow = (uint32_t)boardCfgInfo.boardCfgLowSec,
                                                       .boardConfigHigh = 0,
                                                       .boardConfigSize = boardCfgInfo.boardCfgLowSecSize,
                                                       .devGrp = DEVGRP_01
                                                      };

    retVal = Sciclient_boardCfg(&bootAppBoardCfgPrms);
    if (retVal != CSL_PASS)
    {
         UART_printf("Sciclient_boardCfg() failed.\r\n");
    }
    retVal = Sciclient_boardCfgPm(&bootAppBoardCfgPmPrms);
    if (retVal != CSL_PASS)
    {
         UART_printf( "Sciclient_boardCfgPm() failed.\r\n");
    }
    retVal = Sciclient_boardCfgRm(&bootAppBoardCfgRmPrms);
    if (retVal != CSL_PASS)
    {
         UART_printf("Sciclient_boardCfgRm() failed.\r\n");
    }
    retVal = Sciclient_boardCfgSec(&bootAppBoardCfgSecPrms);
    if (retVal != CSL_PASS)
    {
         UART_printf("Sciclient_boardCfgSec() failed.\r\n");
    }

    /* Initialize PLLs, Clock for Main Domain and DDR */
    boardCfg = BOARD_INIT_PLL_MAIN | BOARD_INIT_MODULE_CLOCK_MAIN | BOARD_INIT_DDR;
    Board_init(boardCfg);

    /* SBL implements the SBL_SetQoS only for J721S2, J721E, J784S4. */
    #if !defined (SOC_J7200)
    SBL_SetQoS();
    #endif

    return;
}
#endif

static void BootApp_bootTaskFxn(void* a0, void* a1)
{
    gBootAppTimeStart = BootApp_getTimeInMicroSec(CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM));

    BootApp_loadImg();

    gBootAppTimeFinish = BootApp_getTimeInMicroSec(CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM));

    UART_printf("MCU Boot Task started at %d usecs and finished at %d usecs\r\n", (uint32_t)gBootAppTimeStart, (uint32_t)gBootAppTimeFinish);

    return;
}

static uint32_t BootApp_loadImg(void)
{
    uint32_t       retVal;
    cpu_core_id_t  core_id;
    cpu_core_id_t  booted_core_ids[DSP2_C7X_ID];
    uint8_t        i, j;
    cpu_core_id_t *boot_array;
    uint8_t        num_cores_to_boot;
    uint8_t        num_booted_cores = 0;
    uint64_t       time_boot_core_finish[DSP2_C7X_ID];

#if defined(BOOT_OSPI)
#if defined(CAN_RESP_TASK_ENABLED)
    /* To measure CAN response, sbl_boot_perf_cust_img is used which doesn't setup the Main Domain
     * and doesn't inialtize DDR for faster Boot time. 
     * So, initializing Board Cfgs, PLLs and Module Clock for Main Domain and DDR */
    BootApp_mainDomainSetup();
#endif
    SBL_SPI_init();
    SBL_ospiInit(&boardHandle);
#endif

    /* Configure Muxes for Ethernet Firmware, if needed */
    BootApp_ethMuxConfig();

#if defined(BOOT_MMCSD)
    retVal = BootApp_mmcBootImageInit();
    if (retVal != CSL_PASS)
    {
        UART_printf("Failure during BootApp_mmcBootImageInit\r\n");
    }
#endif

    /* Initialize the entry point array to SBL_INVALID_ENTRY_ADDR */
    for (core_id = MPU1_CPU0_ID; core_id < NUM_CORES; core_id ++)
    {
        (&gK3xx_evmEntry)->CpuEntryPoint[core_id] = SBL_INVALID_ENTRY_ADDR;
    }

    for (j = 0; j < NUM_BOOT_STAGES; j++)
    {

        retVal = BootApp_requestCores(j);

        if (retVal != CSL_PASS)
        {
            UART_printf("Failed to request all late cores in Stage %d\r\n", j);
            BootApp_releaseCores(j);
        } 
        else
        {
            UART_printf("Loading BootImage\r\n");

            #if defined(BOOT_MMCSD)
                retVal = BootApp_mmcsdBootStageImage(&gK3xx_evmEntry, mmcsd_main_domain_rtos_image_name[j]);
            #endif

            #if defined(BOOT_OSPI)
                retVal = BootApp_ospiBootStageImage(&gK3xx_evmEntry, ospi_main_domain_flash_rtos_images[j]);
            #endif

            UART_printf("BootImage completed, status = %d\r\n", retVal);

            if (retVal != CSL_PASS)
            {
                UART_printf("Failure during image copy and parsing\r\n");
            }
            else
            {
                retVal = BootApp_releaseCores(j);
                if (retVal != CSL_PASS)
                {
                    UART_printf("Failed to release all late cores\r\n");
                }
            }
        } /* if (retVal != CSL_PASS) */

        if (retVal == CSL_PASS)
        {
            /* Start the individual cores for the boot stage */
            num_cores_to_boot = num_cores_per_boot_stage[j];
            boot_array        = boot_array_stage[j];
            for (i = 0; i < num_cores_to_boot; i++)
            {
                core_id = boot_array[i];
                
                /* Try booting all cores other than the cluster running the SBL */
                if ((gK3xx_evmEntry.CpuEntryPoint[core_id] != SBL_INVALID_ENTRY_ADDR) &&
                    ((core_id != MCU1_CPU1_ID) && (core_id != MCU1_CPU0_ID)))
                {
                    SBL_SlaveCoreBoot(core_id, 0, &gK3xx_evmEntry, SBL_REQUEST_CORE);
                    UART_printf("SBL_SlaveCoreBoot completed for Core ID#%d, Entry point is 0x%x\r\n",
                                    core_id, gK3xx_evmEntry.CpuEntryPoint[core_id]);
                    booted_core_ids[num_booted_cores] = core_id;
                    time_boot_core_finish[num_booted_cores] = BootApp_getTimeInMicroSec(CSL_armR5PmuReadCntr(CSL_ARM_R5_PMU_CYCLE_COUNTER_NUM));
                    num_booted_cores++;
                }
            }
        } /* if (retVal == CSL_PASS) */
    } /* for (j = 0; j < NUM_BOOT_STAGES; j++) */

#if defined(BOOT_MMCSD)
    BootApp_mmcBootImageDeInit();
#endif

#if defined(BOOT_OSPI)
    SBL_ospiClose(&boardHandle);

    BootApp_ospiLeaveConfigSPI();
#endif

    /* Delay print out of boot log to avoid prints by other tasks */
    TaskP_sleep(4000);

    if (retVal == CSL_PASS)
    {
        /* Print boot log, including all gathered timestamps */
        UART_printf("Boot App: Started at %d usec\r\n", (uint32_t)gBootAppTimeStart);

        UART_printf("Boot App: Total Num booted cores = %d\r\n", num_booted_cores);

        for (core_id = 0; core_id < num_booted_cores; core_id++)
        {
            UART_printf("Boot App: Booted Core ID #%d at %d usecs\r\n", booted_core_ids[core_id], (uint32_t)time_boot_core_finish[core_id]);
        }
    } /* if (retVal == CSL_PASS) */
    else
    {
        UART_printf("Boot App: Failure occurred in boot sequence\r\n");
    }

    return (retVal);
}

static void BootApp_ethMuxConfig(void)
{
#if defined(SOC_J721E)
    Board_STATUS status;

    /* Ethernet config: set proper board muxes for J712E Eth. firmware
     * Set IO Expander to use RMII on GESI board */
    status = Board_control(BOARD_CTRL_CMD_SET_RMII_DATA_MUX, NULL);
    
    if (status != BOARD_SOK)
    {
        UART_printf("Board_control failed to configure RMII pins\r\n");
    }
    
    /* Enable CPSW9G MDIO mux */
    status = Board_control(BOARD_CTRL_CMD_SET_GESI_CPSW_MDIO_MUX, NULL);
    
    if (status != BOARD_SOK)
    {
        UART_printf("Board_control failed to configure CPSW9G MDIO mux\r\n");
    }
#endif
    return;
}

static int32_t BootApp_requestCores(uint8_t stageNum)
{
    uint32_t i;
    int32_t  status = CSL_EFAIL;
    uint8_t  stage  = stageNum;

    for (i = 0; i < MAX_CORES_PER_STAGE; i++)
    {
        if (sbl_late_slave_core_stages_info[stage][i].tisci_proc_id != SBL_INVALID_ID)
        {
            #if defined(UART_PRINT_DEBUG)
                UART_printf("Calling Sciclient_procBootRequestProcessor, ProcId 0x%x... \r\n",
                            sbl_late_slave_core_stages_info[stage][i].tisci_proc_id);
            #endif
            status = Sciclient_procBootRequestProcessor(sbl_late_slave_core_stages_info[stage][i].tisci_proc_id,
                                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status != CSL_PASS)
            {
                #if defined(UART_PRINT_DEBUG)
                    UART_printf("Sciclient_procBootRequestProcessor, ProcId 0x%x...FAILED \r\n",
                                        sbl_late_slave_core_stages_info[stage][i].tisci_proc_id);
                #endif
                break;
            }
        }
    }

    return (status);
}

static int32_t BootApp_releaseCores(uint8_t stageNum)
{
    uint32_t i;
    int32_t  status = CSL_EFAIL;
    uint8_t  stage  = stageNum;

    for (i = 0; i < MAX_CORES_PER_STAGE; i++)
    {
        if (sbl_late_slave_core_stages_info[stage][i].tisci_proc_id != SBL_INVALID_ID)
        {
            #if defined(UART_PRINT_DEBUG)
                UART_printf("Sciclient_procBootReleaseProcessor, ProcId 0x%x...\r\n",
                            sbl_late_slave_core_stages_info[stage][i].tisci_proc_id);
            #endif
            status = Sciclient_procBootReleaseProcessor(sbl_late_slave_core_stages_info[stage][i].tisci_proc_id,
                                                        TISCI_MSG_FLAG_AOP,
                                                        SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status != CSL_PASS)
            {
                UART_printf("Sciclient_procBootReleaseProcessor, ProcId 0x%x...FAILED \r\n",
                            sbl_late_slave_core_stages_info[stage][i].tisci_proc_id);
                break;
            }
        }
    }

    return (status);
}