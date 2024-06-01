/*
 *  Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com/
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
 *
 */

 /**
  *  \file  sciclient_extended_ut_main.c
  *
  *  \brief Implementation of Sciclient Extended Unit Test application
  *
  */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <ti/csl/csl_psilcfg.h>
#include <ti/drv/sciclient/src/sciclient/sciclient_priv.h>
#include <ti/drv/sciclient/src/sciclient/sciclient_rm_priv.h>
#include <ti/drv/sciclient/examples/common/sci_app_common.h>
#include <ti/drv/sciclient/examples/sciclient_extended_unit_testapp/sciclient_extended_ut_tests.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined (SOC_J721E)
#define TISCI_DEV_NAVSS0_MODSS_INTAGG     TISCI_DEV_NAVSS0_MODSS_INTAGGR_0
#define TISCI_DEV_NAVSS0_INTR             TISCI_DEV_NAVSS0_INTR_ROUTER_0
#define TISCI_DEV_NAVSS0_MAILBOX          TISCI_DEV_NAVSS0_MAILBOX_0
#define TISCI_DEV_MCU_NAVSS0_INTR         TISCI_DEV_MCU_NAVSS0_INTR_0
#define TISCI_DEV_NAVSS0_MODSS_INTAGG1    TISCI_DEV_NAVSS0_MODSS_INTAGGR_1
#define TISCI_DEV_NAVSS0_UDMASS_INTAGG    TISCI_DEV_NAVSS0_UDMASS_INTAGGR_0
#elif defined (SOC_J7200)
#define TISCI_DEV_NAVSS0_MODSS_INTAGG     TISCI_DEV_NAVSS0_MODSS_INTA_0
#define TISCI_DEV_NAVSS0_INTR             TISCI_DEV_NAVSS0_INTR_ROUTER_0
#define TISCI_DEV_NAVSS0_MAILBOX          TISCI_DEV_NAVSS0_MAILBOX_0
#define TISCI_DEV_MCU_NAVSS0_INTR         TISCI_DEV_MCU_NAVSS0_INTR_0
#define TISCI_DEV_NAVSS0_MODSS_INTAGG1    TISCI_DEV_NAVSS0_MODSS_INTA_1 
#define TISCI_DEV_NAVSS0_UDMASS_INTAGG    TISCI_DEV_NAVSS0_UDMASS_INTA_0
#elif defined (SOC_J721S2) || defined (SOC_J784S4)
#define TISCI_DEV_NAVSS0_MODSS_INTAGG     TISCI_DEV_NAVSS0_MODSS_INTA_0
#define TISCI_DEV_NAVSS0_INTR             TISCI_DEV_NAVSS0_INTR_0
#define TISCI_DEV_NAVSS0_MAILBOX          TISCI_DEV_NAVSS0_MAILBOX1_0
#define TISCI_DEV_MCU_NAVSS0_INTR         TISCI_DEV_MCU_NAVSS0_INTR_ROUTER_0
#define TISCI_DEV_NAVSS0_MODSS_INTAGG1    TISCI_DEV_NAVSS0_MODSS_INTA_1
#define TISCI_DEV_NAVSS0_UDMASS_INTAGG    TISCI_DEV_NAVSS0_UDMASS_INTA_0
#endif
#define SCICLIENT_APP_DRAM_FWL_ID         (1280U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

extern Sciclient_ServiceHandle_t gSciclientHandle;
extern CSL_SecProxyCfg *pSciclient_secProxyCfg;

/* For SafeRTOS on R5F with FFI Support, task stack should be aligned to the stack size */
/* IMPORTANT NOTE: For C7x,
 * - stack size and stack ptr MUST be 8KB aligned
 * - AND min stack size MUST be 32KB
 * - AND stack assigned for task context is "size - 8KB"
 *       - 8KB chunk for the stack area is used for interrupt handling in this task context
 */
#if defined(SAFERTOS) && defined (BUILD_MCU)
static uint8_t  gSciclientAppTskStackMain[32*1024] __attribute__((aligned(32*1024))) = { 0 };
#else
static uint8_t  gSciclientAppTskStackMain[32*1024] __attribute__((aligned(8192)));
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

struct SciApp_RangeOfLines {
    uint16_t src_start;
    uint16_t src_end;
    uint16_t dst_start;
    uint16_t dst_end;
};

/* ========================================================================== */
/*                         Function Declarations                              */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                        Internal Function Declarations                      */
/* ========================================================================== */

static void mainTask(void* arg0, void* arg1);
#if defined (BUILD_MCU1_0)
static int32_t SciclientApp_pmMessageTest(void);
static int32_t SciclientApp_directNegTest(void);
static int32_t SciclientApp_pmMessageNegTest(void);
static int32_t SciclientApp_boardCfgTest(void);
static int32_t SciclientApp_directFuncTest(void);
static int32_t SciclientApp_rmUdmapRingPsilProxyPositiveTest(void);
static int32_t SciclientApp_rmUnmappedVintRouteCreatePositiveTest(void);
static int32_t SciclientApp_secureProxyNegTest(void);
static int32_t SciclientApp_rmIrqVintDeleteNegTest(void);
static int32_t SciclientApp_rmIaValidateEvtTest(void);
static int32_t SciclientApp_dkekTest(void);
#endif
static int32_t SciclientApp_msmcQueryNegTest(void);
static int32_t SciclientApp_otpProcessKeyCfgNegTest(void);
static int32_t SciclientApp_firewallNegTest(void);
static int32_t SciclientApp_prepareHeaderNegTest(void);
#if defined (SOC_J784S4)
static int32_t SciclientApp_contextNegTest(void);
#endif
static int32_t SciclientApp_initTest(void);
static int32_t SciclientApp_rmPsilNegTest(void);
static int32_t SciclientApp_rmRingCfgNegTest(void);
static int32_t SciclientApp_rmRingMonCfgNegTest(void);
static int32_t SciclientApp_rmUdmapNegTest(void);
static int32_t SciclientApp_rmSetProxyNegTest(void);
static int32_t SciclientApp_procbootNegTest(void);
static int32_t SciclientApp_rmNegTest(void);
static int32_t SciclientApp_procbootPositiveTest(void);
static int32_t SciclientApp_rmIrqValidParamsNegTest(void);
static int32_t SciclientApp_rmIrqCfgIsUnmappedVintDirectEventNegTest(void);
static int32_t SciclientApp_rmIrqCfgIsEventToVintMappingOnlyNegTest(void);
static int32_t SciclientApp_rmIrqCfgIsOesOnlyNegTest(void);
static int32_t SciclientApp_rmIrqCfgIsDirectEventTest(void);
static int32_t SciclientApp_rmIrqCfgIsDirectNonEventTest(void);
static int32_t SciclientApp_rmTranslateIntOutputTest(void);
static int32_t SciclientApp_rmTranslateIrqInputTest(void);
static void SciclientApp_getResoureRange(uint16_t src_id, uint16_t dst_dev_id, uint16_t dst_host_id, struct SciApp_RangeOfLines *range);
static int32_t SciclientApp_rmClearInterruptRouteTest(void);
static int32_t SciclientApp_rmProgramInterruptRouteTest(void);
static int32_t SciclientApp_rmIrqUnmappedVintRouteDeleteNegTest(void);
static int32_t SciclientApp_rmIrqFindRouteNegTest(void);
static int32_t SciclientApp_rmIaVintGetInfoNegTest(void);
static int32_t SciclientApp_rmIrqIsVintRouteSetNegTest(void);
static int32_t SciclientApp_firewallPositiveTest(void);
static int32_t SciclientApp_sciclientMcdcTest(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int main(void)
{
    TaskP_Handle task;
    TaskP_Params taskParams;

    uint32_t retVal = CSL_PASS;

    /*  This should be called before any other OS calls (like Task creation, OS_start, etc..) */
    OS_init();

    memset(gSciclientAppTskStackMain, 0xFF, sizeof(gSciclientAppTskStackMain));
    TaskP_Params_init(&taskParams);
    taskParams.priority     = 2;
    taskParams.stack        = gSciclientAppTskStackMain;
    taskParams.stacksize    = sizeof(gSciclientAppTskStackMain);
    task = TaskP_create(&mainTask, &taskParams);
    if(task == NULL)
    {
        OS_stop();
    }

    OS_start();

    return retVal;
}

uint32_t SciApp_getNumTests(void)
{
    return SCICLIENT_NUM_TESTCASES;
}

int32_t SciApp_testMain(SciApp_TestParams_t *testParams)
{
    switch (testParams->testcaseId)
    {
#if defined (BUILD_MCU1_0)
        case 1:
            testParams->testResult = SciclientApp_pmMessageTest();
            break;
#endif
        case 2:
            testParams->testResult = SciclientApp_msmcQueryNegTest();
            break;
        case 3:
            testParams->testResult = SciclientApp_otpProcessKeyCfgNegTest();
            break;
#if defined (BUILD_MCU1_0)
        case 4:
            testParams->testResult = SciclientApp_dkekTest();
            break;
#endif
        case 5:
            testParams->testResult = SciclientApp_firewallNegTest();
            break;
        case 6:
            testParams->testResult =  SciclientApp_prepareHeaderNegTest();
            break;
#if defined (SOC_J784S4)
        case 7:
            testParams->testResult =  SciclientApp_contextNegTest();
            break;
#endif
        case 8:
            testParams->testResult =  SciclientApp_initTest();
            break;
        case 9:
            testParams->testResult = SciclientApp_rmPsilNegTest();
            break;
        case 10:
            testParams->testResult = SciclientApp_rmRingCfgNegTest();
            break;
        case 11:
            testParams->testResult = SciclientApp_rmRingMonCfgNegTest();
            break;
        case 12:
            testParams->testResult = SciclientApp_rmUdmapNegTest();
            break;
        case 13:
            testParams->testResult = SciclientApp_rmSetProxyNegTest();
            break;
#if defined (BUILD_MCU1_0)
        case 14:
            testParams->testResult = SciclientApp_directNegTest();
            break;
        case 15:
            testParams->testResult = SciclientApp_pmMessageNegTest();
            break;
#endif
        case 16:
            testParams->testResult = SciclientApp_procbootNegTest();
            break;
        case 17:
            testParams->testResult = SciclientApp_rmNegTest();
            break;     
        case 18:
            testParams->testResult = SciclientApp_procbootPositiveTest();
            break;
#if defined (BUILD_MCU1_0)
        case 19:
            testParams->testResult = SciclientApp_boardCfgTest();
            break;
#endif
        case 20:
            testParams->testResult = SciclientApp_rmIrqValidParamsNegTest();
            break;
        case 21:
            testParams->testResult = SciclientApp_rmTranslateIntOutputTest();
            break;
        case 22:
            testParams->testResult = SciclientApp_rmTranslateIrqInputTest();
            break;
        case 23:  
            testParams->testResult = SciclientApp_rmClearInterruptRouteTest();
            break;   
        case 24:  
            testParams->testResult = SciclientApp_rmProgramInterruptRouteTest();
            break;    
        case 25:
            testParams->testResult =  SciclientApp_rmIrqUnmappedVintRouteDeleteNegTest();
            break;
        case 26:
            testParams->testResult =  SciclientApp_rmIrqFindRouteNegTest();
            break;
#if defined (BUILD_MCU1_0)
        case 27:
            testParams->testResult =  SciclientApp_directFuncTest();
            break;
        case 28:
            testParams->testResult =  SciclientApp_rmUdmapRingPsilProxyPositiveTest();
            break;
        case 29:
            testParams->testResult =  SciclientApp_rmUnmappedVintRouteCreatePositiveTest();
            break;
        case 30:
            testParams->testResult =  SciclientApp_secureProxyNegTest();
            break;        
        case 31:
             testParams->testResult = SciclientApp_rmIrqVintDeleteNegTest();
             break;
        case 32:
             testParams->testResult = SciclientApp_rmIaValidateEvtTest();
             break;
#endif
        case 33:
             testParams->testResult = SciclientApp_rmIaVintGetInfoNegTest();
             break;
        case 34:
             testParams->testResult = SciclientApp_rmIrqIsVintRouteSetNegTest();
             break;
        case 35:
            testParams->testResult =  SciclientApp_firewallPositiveTest();
            break;
        case 36:
            testParams->testResult =  SciclientApp_sciclientMcdcTest();
            break;
        default:
            break;
    }
    
    return 0;
}

/* ========================================================================== */
/*                          Internal Function Definitions                     */
/* ========================================================================== */

static void mainTask(void* arg0, void* arg1)
{
    /*To suppress unused variable warning*/
    (void)arg0;
    (void)arg1;

    volatile uint32_t loopForever = 1U;

    SciApp_parser();

    while(loopForever);
}

#if defined (BUILD_MCU1_0)
static int32_t SciclientApp_pmMessageTest(void)
{
    int32_t   status               = CSL_PASS;
    int32_t   sciclientInitStatus  = CSL_PASS;
    int32_t   pmMessageTestStatus  = CSL_PASS;
    uint64_t  reqFreq              = 164UL;
    uint64_t  respFreq             = 0UL;
    uint32_t  clockStatus          = 1U;
#if defined(SOC_J721S2) || defined(SOC_J784S4)
    uint32_t  parentStatus         = 0U;
    uint32_t  numParents           = 0U;
#endif
    uint64_t  freq                 = 0UL;
    uint32_t  moduleState          = 0U;
    uint32_t  resetState           = 0U;
    uint32_t  contextLossState     = 0U;
    uint32_t  reqFlag              = 0U;
    Sciclient_ConfigPrms_t  config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
        NULL,
        1U,
        0U,
        TRUE
    };

    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if (status == CSL_PASS)
    {
        SciApp_printf("Sciclient_Init Passed.\n");
        status = Sciclient_pmQueryModuleClkFreq(TISCI_DEV_UART1,
                                                TISCI_DEV_UART1_FCLK_CLK,
                                                reqFreq,
                                                &respFreq,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmQueryModuleClkFreq Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmQueryModuleClkFreq Test Failed.\n");
        }

        status = Sciclient_pmModuleGetClkStatus(TISCI_DEV_UART1,
                                                TISCI_DEV_UART1_FCLK_CLK,
                                                &clockStatus,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmModuleGetClkStatus Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmModuleGetClkStatus Test Failed.\n");
        }

        status = Sciclient_pmModuleClkRequest(TISCI_DEV_UART1,
                                              TISCI_DEV_UART1_FCLK_CLK,
                                              TISCI_MSG_VALUE_CLOCK_HW_STATE_READY,
                                              0U,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmModuleClkRequest Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmModuleClkRequest Test Failed.\n");
        }

#if defined(SOC_J721S2) || defined(SOC_J784S4)
       status = Sciclient_pmSetModuleClkParent(TISCI_DEV_MCSPI1,
                                               TISCI_DEV_MCSPI1_IO_CLKSPII_CLK,
                                               TISCI_DEV_MCSPI1_IO_CLKSPII_CLK_PARENT_BOARD_0_SPI1_CLK_OUT,
                                               SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmSetModuleClkParent Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmSetModuleClkParent Test Failed.\n");
        }

        status = Sciclient_pmGetModuleClkParent(TISCI_DEV_MCSPI1,
                                                TISCI_DEV_MCSPI1_IO_CLKSPII_CLK,
                                                &parentStatus,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if ((status == CSL_PASS) && (parentStatus == TISCI_DEV_MCSPI1_IO_CLKSPII_CLK_PARENT_BOARD_0_SPI1_CLK_OUT))
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmGetModuleClkParent Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmGetModuleClkParent Test Failed.\n");
        }

        status = Sciclient_pmGetModuleClkNumParent(TISCI_DEV_MCSPI1,
                                                  TISCI_DEV_MCSPI1_IO_CLKSPII_CLK,
                                                  &numParents,
                                                  SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmGetModuleClkNumParent Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmGetModuleClkNumParent Test Failed.\n");
        }
#endif

        status = Sciclient_pmSetModuleClkFreq(TISCI_DEV_UART1,
                                              TISCI_DEV_UART1_FCLK_CLK,
                                              reqFreq,
                                              TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmSetModuleClkFreq Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmSetModuleClkFreq Test Failed.\n");
        }

        status = Sciclient_pmGetModuleClkFreq(TISCI_DEV_UART1,
                                              TISCI_DEV_UART1_FCLK_CLK,
                                              &freq,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmGetModuleClkFreq Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmGetModuleClkFreq Test Failed.\n");
        }

        status = Sciclient_pmSetModuleState(SCICLIENT_DEV_MCU_R5FSS0_CORE0,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            0U,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmSetModuleState: SCICLIENT_DEV_MCU_R5FSS0_CORE0 Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmSetModuleState: SCICLIENT_DEV_MCU_R5FSS0_CORE0 Test Failed.\n");
        }

        status = Sciclient_pmSetModuleState(SCICLIENT_DEV_MCU_R5FSS0_CORE1,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            0U,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmSetModuleState: SCICLIENT_DEV_MCU_R5FSS0_CORE1 Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmSetModuleState: SCICLIENT_DEV_MCU_R5FSS0_CORE1 Test Failed.\n");
        }

        status = Sciclient_pmSetModuleState(TISCI_DEV_BOARD0,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            TISCI_MSG_FLAG_AOP,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("TISCI_DEV_BOARD0 TISCI_MSG_VALUE_DEVICE_SW_STATE_ON Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("TISCI_DEV_BOARD0 TISCI_MSG_VALUE_DEVICE_SW_STATE_ON Test Failed.\n");
        }

        status = Sciclient_pmGetModuleState(SCICLIENT_DEV_MCU_R5FSS0_CORE0,
                                            &moduleState,
                                            &resetState,
                                            &contextLossState,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("SCICLIENT_DEV_MCU_R5FSS0_CORE0 States: \n");
            SciApp_printf("ModuleState: %d\n", moduleState);
            SciApp_printf("ResetState: %d\n", resetState);
            SciApp_printf("ContextLossState: %d\n", contextLossState);
            SciApp_printf("Sciclient_pmGetModuleState Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmGetModuleState Test Failed.\n");
        }
        
        //Reset TISCI_DEV_LED0 module
        status = Sciclient_pmSetModuleRst(TISCI_DEV_LED0,
                                          1U,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmSetModuleRst Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmSetModuleRst Test Failed.\n");
        }
        
        //SetModuleRst_flags for TISCI_DEV_LED0
        reqFlag = TISCI_MSG_FLAG_ACK;
        status = Sciclient_pmSetModuleRst_flags(TISCI_DEV_LED0, 0U, reqFlag, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmSetModuleRst_flags Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmSetModuleRst_flags Test Failed.\n");
        }
        
        //set ClkFreq for TISCI_DEV_UART1 module
        reqFreq = 100U;
        status = Sciclient_pmSetModuleClkFreq(TISCI_DEV_UART1,
                                              TISCI_DEV_UART1_FCLK_CLK,
                                              reqFreq,
                                              TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmSetModuleClkFreq Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmSetModuleClkFreq Test Failed.\n");
        }
        
        //QueryModuleClkFreq for TISCI_DEV_UART1 module
        reqFreq = 100U;
        status = Sciclient_pmQueryModuleClkFreq(TISCI_DEV_UART1,
                                                TISCI_DEV_UART1_FCLK_CLK,
                                                reqFreq,
                                                &respFreq,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_pmQueryModuleClkFreq Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_pmQueryModuleClkFreq Test Failed.\n");
        }
        
        //Reset domain group DOMGRP_02
        status = Sciclient_pmDomainReset(DOMGRP_02, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmDomainReset Negative Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmDomainReset Negative Test Failed.\n");
        }
        
        //Check whether TISCI_DEV_UART1 module is valid or not
        status = Sciclient_pmIsModuleValid(TISCI_DEV_UART1);
        if (status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmIsModuleValid Test Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmIsModuleValid Test Failed.\n");
        }
    }
    else
    {
        pmMessageTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_Init Failed.\n");
    }

    if (sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            pmMessageTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit Passed.\n");
        }
        else
        {
            pmMessageTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit Failed.\n");
        }
    }

  return pmMessageTestStatus;
}
#endif

static int32_t SciclientApp_msmcQueryNegTest(void)
{
    int32_t status                 = CSL_PASS;
    int32_t sciclientInitStatus    = CSL_PASS;
    int32_t msmcQueryTestStatus    = CSL_PASS;
    struct  tisci_query_msmc_resp resp;
    Sciclient_ConfigPrms_t  config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
        NULL,
        0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        status = Sciclient_msmcQuery(NULL, &resp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
           msmcQueryTestStatus += CSL_PASS;
           SciApp_printf("Sciclient_msmcQuery: Negative Arg Test Passed.\n");
        }
        else
        {
           msmcQueryTestStatus += CSL_EFAIL;
           SciApp_printf("Sciclient_msmcQuery: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        msmcQueryTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            msmcQueryTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            msmcQueryTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return msmcQueryTestStatus;
}

static int32_t SciclientApp_otpProcessKeyCfgNegTest(void)
{
    int32_t   status                  = CSL_PASS;
    int32_t   sciclientInitStatus     = CSL_PASS;
    int32_t   otpProcessKeyTestStatus = CSL_PASS;
    uint32_t  resp                    = 0U;
    Sciclient_ConfigPrms_t  config    =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
        SciApp_printf("Sciclient_init PASSED.\n");
        status = Sciclient_otpProcessKeyCfg(NULL, SCICLIENT_SERVICE_WAIT_FOREVER, &resp);
        if (status == CSL_EFAIL)
        {
            otpProcessKeyTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_otpProcessKeyCfg: Negative Arg Test Passed.\n");
        }
        else
        {
           otpProcessKeyTestStatus += CSL_EFAIL;
           SciApp_printf("Sciclient_otpProcessKeyCfg: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        otpProcessKeyTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            otpProcessKeyTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            otpProcessKeyTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return otpProcessKeyTestStatus;
}

#if defined (BUILD_MCU1_0)
static int32_t SciclientApp_dkekTest(void)
{
    int32_t status                = CSL_PASS;
    int32_t sciclientInitStatus   = CSL_PASS;
    int32_t dkekTestStatus        = CSL_PASS;
    struct tisci_msg_sa2ul_set_dkek_req setDkekReq;
    struct tisci_msg_sa2ul_set_dkek_resp setDkekResp;
    struct tisci_msg_sa2ul_get_dkek_req getDkekReq;
    struct tisci_msg_sa2ul_get_dkek_resp getDkekResp;
    struct tisci_msg_sa2ul_release_dkek_req releaseDkekReq;
    struct tisci_msg_sa2ul_release_dkek_resp releaseDkekResp;

    Sciclient_ConfigPrms_t config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
        SciApp_printf("Sciclient_init PASSED.\n");
        status = Sciclient_setDKEK(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            dkekTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_setDKEK: Negative Arg Test Passed.\n");
        }
        else
        {
           dkekTestStatus += CSL_EFAIL;
           SciApp_printf("Sciclient_setDKEK: Negative Arg Test Failed.\n");
        }

        status = Sciclient_releaseDKEK(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            dkekTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_releaseDKEK: Negative Arg Test Passed.\n");
        }
        else
        {
           dkekTestStatus += CSL_EFAIL;
           SciApp_printf("Sciclient_releaseDKEK: Negative Arg Test Failed.\n");
        }

        status = Sciclient_getDKEK(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            dkekTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_getDKEK: Negative Arg Test Passed.\n");
        }
        else
        {
           dkekTestStatus += CSL_EFAIL;
           SciApp_printf("Sciclient_getDKEK: Negative Arg Test Failed.\n");
        }

        /* Passing valid setDkekReq parameters to cover Sciclient_setDKEK */
        setDkekReq.sa2ul_instance  = 0;
        setDkekReq.kdf_label_len   = 16;
        setDkekReq.kdf_context_len = 16;
        status = Sciclient_setDKEK(&setDkekReq, &setDkekResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            dkekTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_setDKEK: Positive Arg Test Passed.\n");
        }
        else
        {
            dkekTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_setDKEK: Positive Arg Test Failed.\n");
        }

        /* Passing valid getDkekReq parameters to cover Sciclient_getDKEK */
        getDkekReq.sa2ul_instance  = 0;
        getDkekReq.kdf_label_len   = 16;
        getDkekReq.kdf_context_len = 16;
        status = Sciclient_getDKEK(&getDkekReq, &getDkekResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            dkekTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_getDKEK: Positive Arg Test Passed.\n");
        }
        else
        {
            dkekTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_getDKEK: Positive Arg Test Failed.\n");
        }

        /* Passing valid releaseDkekReq parameters to cover Sciclient_releaseDKEK */
        releaseDkekReq.sa2ul_instance = 0;
        status = Sciclient_releaseDKEK(&releaseDkekReq, &releaseDkekResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            dkekTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_releaseDKEK: Positive Arg Test Passed.\n");
        }
        else
        {
            dkekTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_releaseDKEK: Positive Arg Test Failed.\n");
        }
    }
    else
    {
        dkekTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            dkekTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            dkekTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return dkekTestStatus;
}
#endif

static int32_t SciclientApp_firewallNegTest(void)
{
    int32_t status                = CSL_PASS;
    int32_t sciclientInitStatus   = CSL_PASS;
    int32_t firewallNegTestStatus = CSL_PASS;
    
    Sciclient_ConfigPrms_t SciApp_Config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0U)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&SciApp_Config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf ("Sciclient_init PASSED.\n");

        status = Sciclient_firewallChangeOwnerInfo(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            firewallNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_firewallChangeOwnerInfo: Negative Arg Test Passed.\n");
        }
        else
        {
            firewallNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_firewallChangeOwnerInfo: Negative Arg Test Failed.\n");
        }

        status = Sciclient_firewallSetRegion(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            firewallNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_firewallSetRegion: Negative Arg Test Passed.\n");
        }
        else
        {
            firewallNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_firewallSetRegion: Negative Arg Test Failed.\n");
        }

        status = Sciclient_firewallGetRegion(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            firewallNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_firewallGetRegion: Negative Arg Test Passed.\n");
        }
        else
        {
            firewallNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_firewallGetRegion: Negative Arg Test Failed.\n");
        }
     }
     else
     {
         firewallNegTestStatus += CSL_EFAIL;
         SciApp_printf ("Sciclient_init FAILED.\n");
     }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            firewallNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_deinit PASSED.\n");
        }
        else
        {
            firewallNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_deinit FAILED.\n");
        }
    }

   return firewallNegTestStatus;
}

static int32_t SciclientApp_prepareHeaderNegTest(void)
{
    int32_t  status              = CSL_PASS;
    int32_t  sciclientInitStatus = CSL_PASS;
    int32_t  sciclientTestStatus = CSL_PASS;
    const Sciclient_ReqPrm_t SciApp_ReqPrm = {};
    Sciclient_ConfigPrms_t   SciApp_Config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0U)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&SciApp_Config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
          SciApp_printf("Sciclient_init PASSED.\n");
          status = Sciclient_servicePrepareHeader(NULL, NULL, SCICLIENT_CONTEXT_R5_NONSEC_0, NULL);
          if (status == CSL_EBADARGS)
          {
               sciclientTestStatus += CSL_PASS;
               SciApp_printf("Sciclient_servicePrepareHeader: Negative Arg Test Passed.\n");
          }
          else
          {
               sciclientTestStatus += CSL_EFAIL;
               SciApp_printf("Sciclient_servicePrepareHeader: Negative Arg Test Failed.\n");
          }

          status = Sciclient_servicePrepareHeader(&SciApp_ReqPrm, NULL, SCICLIENT_CONTEXT_MAX_NUM, NULL);
          if (status == CSL_EBADARGS)
          {
               sciclientTestStatus += CSL_PASS;
               SciApp_printf("Sciclient_servicePrepareHeader: Negative Arg Test Passed.\n");
          }
          else
          {
               sciclientTestStatus += CSL_EFAIL;
               SciApp_printf("Sciclient_servicePrepareHeader: Negative Arg Test Failed.\n");
          }
    }
    else
    {
        sciclientInitStatus += CSL_EFAIL;
        SciApp_printf ("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            sciclientTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            sciclientTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return sciclientTestStatus;
}

#if defined (SOC_J784S4)
static int32_t SciclientApp_contextNegTest(void)
{
    int32_t  status              = CSL_PASS;
    int32_t  sciclientInitStatus = CSL_PASS;
    int32_t  sciclientTestStatus = CSL_PASS;
    uint32_t IntrNum1            = CSLR_MCU_R5FSS0_CORE0_INTR_MCU_NAVSS0_INTR_ROUTER_0_OUTL_INTR_1;
    uint32_t IntrNum2            = CSLR_MCU_R5FSS0_CORE0_INTR_MCU_MCAN0_MCANSS_MCAN_LVL_INT_0;
    uint32_t IntrNum3            = CSLR_MCU_R5FSS0_CORE0_INTR_MCU_CPSW0_EVNT_PEND_0;
    uint16_t messagetype[4]      = {TISCI_MSG_BOOT_NOTIFICATION, 
                                    TISCI_MSG_BOARD_CONFIG, 
                                    TISCI_MSG_BOARD_CONFIG_SECURITY
                                    };
    int8_t   num;
    Sciclient_ConfigPrms_t SciApp_Config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0U)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&SciApp_Config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
          SciApp_printf("Sciclient_init PASSED.\n");
        /* Passing different interrupt numbers to check proxy map context id for 'gSciclientMap' */
          status = Sciclient_contextIdFromIntrNum(IntrNum1);
          if (status == 0U)
          {
               sciclientTestStatus += CSL_PASS;
               SciApp_printf("Sciclient_contextIdFromIntrNum initial condition Test Passed.\n");
          }
          else
          {
               sciclientTestStatus += CSL_EFAIL;
               SciApp_printf("Sciclient_contextIdFromIntrNum initial condition Test Failed.\n");
          }

          status = Sciclient_contextIdFromIntrNum(IntrNum2);
          if (status != CSL_EFAIL)
          {
               sciclientTestStatus += CSL_PASS;
               SciApp_printf("Sciclient_contextIdFromIntrNum: IntrNum2 Arg Test Passed.\n");
          }
          else
          {
               sciclientTestStatus += CSL_EFAIL;
               SciApp_printf("Sciclient_contextIdFromIntrNum: IntrNum2 Arg Test Failed.\n");
          }

          status = Sciclient_contextIdFromIntrNum(IntrNum3);
          if (status == CSL_EFAIL)
          {
               sciclientTestStatus += CSL_PASS;
               SciApp_printf("Sciclient_contextIdFromIntrNum: Negative Arg Test Passed.\n");
          }
          else
          {
               sciclientTestStatus += CSL_EFAIL;
               SciApp_printf("Sciclient_contextIdFromIntrNum: Negative Arg Test Failed.\n");
          }

          /* Passing different message types to determine the which context to be used.*/
          for(num = 0; num < 3; num++)
          {
            status = Sciclient_getCurrentContext(messagetype[num]);
            if (status == SCICLIENT_CONTEXT_SEC)
            {
                sciclientTestStatus += CSL_PASS;
                SciApp_printf("Sciclient_getCurrentContext: Secure Arg Test Passed.\n");
            }
            else
            {
                sciclientTestStatus += CSL_EFAIL;
                SciApp_printf("Sciclient_getCurrentContext: Secure Arg Test Failed.\n");
            }
          }
    }
    else
    {
        sciclientInitStatus += CSL_EFAIL;
        SciApp_printf ("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            sciclientTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            sciclientTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return sciclientTestStatus;
}
#endif

static int32_t SciclientApp_initTest(void)
{
    int32_t status              = CSL_PASS;
    int32_t sciclientInitStatus = CSL_PASS;
    Sciclient_ConfigPrms_t SciApp_Config =
    {
       2,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

    Sciclient_ConfigPrms_t SciApp_ConfigIntrMode =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       2 /* isSecure = 0 un secured for all cores */
    };

    status = Sciclient_init(&SciApp_Config);
    if (status == CSL_EBADARGS)
    {
        sciclientInitStatus += CSL_PASS;
        SciApp_printf("Sciclient_init: Negative Arg Test Passed.\n");
    }
    else
    {
        sciclientInitStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init: Negative Arg Test Failed.\n");
    }

    Sciclient_deinit();
    status = Sciclient_init(&SciApp_ConfigIntrMode);
    if (status == CSL_EBADARGS)
    {
        sciclientInitStatus += CSL_PASS;
        SciApp_printf("Sciclient_init: Negative Arg Test Passed.\n");
    }
    else
    {
        sciclientInitStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init: Negative Arg Test Failed.\n");
    }

    status = Sciclient_deinit();
    if(status == CSL_PASS)
    {
        sciclientInitStatus += CSL_PASS;
        SciApp_printf("Sciclient_deinit PASSED.\n");
    }
    else
    {
        sciclientInitStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_deinit FAILED.\n");
    }

    return sciclientInitStatus;
}

static int32_t SciclientApp_rmPsilNegTest(void)
{
    int32_t  status              = CSL_PASS;
    int32_t  sciclientInitStatus = CSL_PASS;
    int32_t  rmPsilTestStatus    = CSL_PASS;
    const struct tisci_msg_rm_psil_pair_req SciApp_RmPsilPairReq     = {0};
    const struct tisci_msg_rm_psil_unpair_req SciApp_RmPsilUnpairReq = {0};
    const struct tisci_msg_rm_psil_read_req SciApp_RmPsilReadReq     = {0};
    const struct tisci_msg_rm_psil_write_req SciApp_RmPsilWriteReq   = {0};
    struct tisci_msg_rm_psil_read_resp SciApp_RmPsilReadResp;
    Sciclient_ConfigPrms_t SciApp_Config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
        NULL,
        0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0U)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&SciApp_Config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf ("Sciclient_init PASSED.\n");
      /* Passing a zero request parameter, sciclient_service function will return pass but response flag will be NAK */
        status = Sciclient_rmPsilPair(&SciApp_RmPsilPairReq, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmPsilTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmPsilPair: Negative Arg Test Passed.\n");
        }
        else
        {
            rmPsilTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmPsilPair: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmPsilUnpair(&SciApp_RmPsilUnpairReq, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmPsilTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmPsilUnpair: Negative Arg Test Passed.\n");
        }
        else
        {
            rmPsilTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmPsilUnpair: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmPsilRead(&SciApp_RmPsilReadReq, &SciApp_RmPsilReadResp,
                                      SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmPsilTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmPsilRead: Negative Arg Test Passed.\n");
        }
        else
        {
            rmPsilTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmPsilRead: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmPsilWrite(&SciApp_RmPsilWriteReq, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmPsilTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmPsilWrite: Negative Arg Test Passed.\n");
        }
        else
        {
            rmPsilTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmPsilWrite: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmPsilTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmPsilTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmPsilTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

     return rmPsilTestStatus;
}

static int32_t SciclientApp_rmRingCfgNegTest(void)
{
    int32_t  status              = CSL_PASS;
    int32_t  sciclientInitStatus = CSL_PASS;
    int32_t  rmRingCfgTestStatus = CSL_PASS;
    const struct tisci_msg_rm_ring_cfg_req SciApp_RmRingCfgReq = {0};
    struct tisci_msg_rm_ring_cfg_resp SciApp_RmRingCfgResp;
    Sciclient_ConfigPrms_t SciApp_Config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
        NULL,
        0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0U)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&SciApp_Config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf ("Sciclient_init PASSED.\n");
      /* Passing a zero request parameter, sciclient_service function will return pass but response flag will be NAK */
        status = Sciclient_rmRingCfg(&SciApp_RmRingCfgReq, &SciApp_RmRingCfgResp,
                                     SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmRingCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmRingCfg: Negative Arg Test Passed.\n");
        }
        else
        {
            rmRingCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmRingCfg: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmRingCfgTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmRingCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmRingCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

     return rmRingCfgTestStatus;
}

static int32_t SciclientApp_rmRingMonCfgNegTest(void)
{
    int32_t  status                 = CSL_PASS;
    int32_t  sciclientInitStatus    = CSL_PASS;
    int32_t  rmRingMonCfgTestStatus = CSL_PASS;
    const struct tisci_msg_rm_ring_mon_cfg_req SciApp_RmRingMonCfgReq = {0};
    struct tisci_msg_rm_ring_mon_cfg_resp SciApp_RmRingMonCfgResp;
    Sciclient_ConfigPrms_t SciApp_Config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
        NULL,
        0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0U)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&SciApp_Config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf ("Sciclient_init PASSED.\n");
      /* Passing a zero request parameter, sciclient_service function will return pass but response flag will be NAK */
        status = Sciclient_rmRingMonCfg(&SciApp_RmRingMonCfgReq, &SciApp_RmRingMonCfgResp,
                                        SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmRingMonCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmRingMonCfg: Negative Arg Test Passed.\n");
        }
        else
        {
            rmRingMonCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmRingMonCfg: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmRingMonCfgTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmRingMonCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmRingMonCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

     return rmRingMonCfgTestStatus;
}

static int32_t SciclientApp_rmUdmapNegTest(void)
{
    int32_t  status              = CSL_PASS;
    int32_t  sciclientInitStatus = CSL_PASS;
    int32_t  rmUdmapTestStatus   = CSL_PASS;
    const struct tisci_msg_rm_udmap_gcfg_cfg_req SciApp_RmUdmapGcfgReq       = {0};
    const struct tisci_msg_rm_udmap_tx_ch_cfg_req SciApp_RmUdmapTxChCfgReq   = {0};
    const struct tisci_msg_rm_udmap_rx_ch_cfg_req SciApp_RMUdmapRxChCfgReq   = {0};
    const struct tisci_msg_rm_udmap_flow_cfg_req SciApp_RmUdmapFlowCfgReq    = {0};
    const struct tisci_msg_rm_udmap_flow_size_thresh_cfg_req SciApp_RmUdmapFlowSizeThreshCfgReq = {0};
    struct tisci_msg_rm_udmap_gcfg_cfg_resp SciApp_RmUdmapGcfgResp;
    struct tisci_msg_rm_udmap_tx_ch_cfg_resp SciApp_RmUdmapTxChCfgResp;
    struct tisci_msg_rm_udmap_rx_ch_cfg_resp SciApp_RMUdmapRxChCfgResp;
    struct tisci_msg_rm_udmap_flow_cfg_resp SciApp_RmUdmapFlowCfgResp;
    struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp SciApp_RmUdmapFlowSizeThreshCfgResp;

    Sciclient_ConfigPrms_t SciApp_Config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
        NULL,
        0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0U)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&SciApp_Config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf ("Sciclient_init PASSED.\n");
      /* Passing a zero request parameter, sciclient_service function will return pass but response flag will be NAK */
        status = Sciclient_rmUdmapTxChCfg(&SciApp_RmUdmapTxChCfgReq, &SciApp_RmUdmapTxChCfgResp,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmUdmapTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmUdmapTxChCfg: Negative Arg Test Passed.\n");
        }
        else
        {
            rmUdmapTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmUdmapTxChCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmUdmapRxChCfg(&SciApp_RMUdmapRxChCfgReq, &SciApp_RMUdmapRxChCfgResp,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmUdmapTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmUdmapRxChCfg: Negative Arg Test Passed.\n");
        }
        else
        {
            rmUdmapTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmUdmapRxChCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmUdmapFlowCfg(&SciApp_RmUdmapFlowCfgReq, &SciApp_RmUdmapFlowCfgResp,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmUdmapTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmUdmapFlowCfg: Negative Arg Test Passed.\n");
        }
        else
        {
            rmUdmapTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmUdmapFlowCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmUdmapFlowSizeThreshCfg(&SciApp_RmUdmapFlowSizeThreshCfgReq, 
                                                    &SciApp_RmUdmapFlowSizeThreshCfgResp,
                                                    SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmUdmapTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmUdmapFlowSizeThreshCfg: Negative Arg Test Passed.\n");
        }
        else
        {
            rmUdmapTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmUdmapFlowSizeThreshCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmUdmapGcfgCfg(&SciApp_RmUdmapGcfgReq, &SciApp_RmUdmapGcfgResp,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmUdmapTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmUdmapGcfgCfg: Negative Arg Test Passed.\n");
        }
        else
        {
            rmUdmapTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmUdmapGcfgCfg: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmUdmapTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmUdmapTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmUdmapTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

     return rmUdmapTestStatus;
}

static int32_t SciclientApp_rmSetProxyNegTest(void)
{
    int32_t  status               = CSL_PASS;
    int32_t  sciclientInitStatus  = CSL_PASS;
    int32_t  rmSetProxyTestStatus = CSL_PASS;
    const struct tisci_msg_rm_proxy_cfg_req SciApp_RmSetProxyCfgReq = {0};
    Sciclient_ConfigPrms_t SciApp_Config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
        NULL,
        0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0U)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&SciApp_Config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf ("Sciclient_init PASSED.\n");
      /* Passing a zero request parameter, sciclient_service function will return pass but response flag will be NAK */
        status = Sciclient_rmSetProxyCfg(&SciApp_RmSetProxyCfgReq, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmSetProxyTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmSetProxyCfg: Negative Arg Test Passed.\n");
        }
        else
        {
            rmSetProxyTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmSetProxyCfg: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmSetProxyTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmSetProxyTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmSetProxyTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

     return rmSetProxyTestStatus;
}

#if defined(BUILD_MCU1_0)
static int32_t SciclientApp_directNegTest(void)
{
    int32_t status                = CSL_PASS;
    int32_t sciclientInitStatus   = CSL_PASS;
    int32_t directTestStatus      = CSL_PASS;
    Sciclient_ConfigPrms_t config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };
    const uint32_t reqFlags       = 0U;
    struct tisci_header *negHdr;

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
          SciApp_printf ("Sciclient_init PASSED.\n");
          status = Sciclient_boardCfgPrepHeader(NULL, NULL, NULL, NULL);
          if (status == CSL_EBADARGS)
          {
              directTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_boardCfgPrepHeader: Negative Arg Test Passed.\n");
          }
          else
          {
             directTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_boardCfgPrepHeader: Negative Arg Test Failed.\n");
          }

          status = Sciclient_boardCfgParseHeader(NULL, NULL, NULL);
          if (status == CSL_EBADARGS)
          {
              directTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_boardCfgParseHeader: Negative Arg Test Passed.\n");
          }
          else
          {
             directTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_boardCfgParseHeader: Negative Arg Test Failed.\n");
          }

          status = Sciclient_ProcessPmMessage(reqFlags, &negHdr);
          if (status == CSL_EFAIL)
          {
              directTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_ProcessPmMessage: Negative Arg Test Passed.\n");
          }
          else
          {
             directTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_ProcessPmMessage: Negative Arg Test Failed.\n");
          }
    }
    else
    {
        directTestStatus += CSL_EFAIL;
        SciApp_printf ("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            directTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_deinit PASSED.\n");
        }
        else
        {
            directTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_deinit FAILED.\n");
        }
    }

    return directTestStatus;
}

static int32_t SciclientApp_pmMessageNegTest(void)
{
    int32_t  status                 = CSL_PASS;
    int32_t  sciclientInitStatus    = CSL_PASS;
    int32_t  pmMessageNegTestStatus = CSL_PASS;
    uint64_t reqFreq                = 164UL;
    uint64_t respFreq               = 0UL;
    uint32_t clockStatus            = 1U;
#if defined(SOC_J721S2) || defined(SOC_J784S4)
    uint32_t parentStatus           = 0U;
    uint32_t numParents             = 0U;
#endif
    uint64_t freq                   = 0UL;
    uint32_t moduleState            = 0U;
    uint32_t resetState             = 0U;
    uint32_t contextLossState       = 0U;
    uint32_t invalidModuleId        = 440U;
    Sciclient_ConfigPrms_t config   =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
        NULL,
        1U,
        0U,
        UTRUE
    };
  
    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if (status == CSL_PASS)
    {
        SciApp_printf ("Sciclient_Init Passed.\n");
        status = Sciclient_pmSetModuleState(SCICLIENT_DEV_MCU_R5FSS0_CORE0,
                                            TISCI_MSG_VALUE_DEVICE_SW_STATE_ON,
                                            1U,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmSetModuleState Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmSetModuleState Negative Test Failed.\n");
        }

        status = Sciclient_pmGetModuleState(invalidModuleId,
                                            &moduleState,
                                            &resetState,
                                            &contextLossState,
                                            SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmGetModuleState Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmGetModuleState Negative Test Failed.\n");
        }

        status = Sciclient_pmSetModuleRst(invalidModuleId,
                                          1U,
                                          SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmSetModuleRst Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmSetModuleRst Negative Test Failed.\n");
        }

        status = Sciclient_pmSetModuleRst_flags(invalidModuleId, 0U, 0U, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmSetModuleRst_flags Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmSetModuleRst_flags Negative Test Failed.\n");
        }

        status = Sciclient_pmModuleClkRequest(invalidModuleId,
                                              256U,
                                              TISCI_MSG_VALUE_CLOCK_HW_STATE_READY,
                                              0U,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmModuleClkRequest Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmModuleClkRequest Negative Test Failed.\n");
        }

        status = Sciclient_pmModuleGetClkStatus(invalidModuleId,
                                                256U,
                                                &clockStatus,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmModuleGetClkStatus Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmModuleGetClkStatus Negative Test Failed.\n");
        }

    #if defined(SOC_J721S2) || defined(SOC_J784S4)
       status = Sciclient_pmSetModuleClkParent(invalidModuleId,
                                                256U,
                                                256U,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmSetModuleClkParent Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmSetModuleClkParent Negative Test Failed.\n");
        }

        status = Sciclient_pmGetModuleClkParent(invalidModuleId,
                                                256U,
                                                &parentStatus,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmGetModuleClkParent Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmGetModuleClkParent Negative Test Failed.\n");
        }

        status = Sciclient_pmGetModuleClkNumParent(invalidModuleId,
                                                  256U,
                                                  &numParents,
                                                  SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmGetModuleClkNumParent Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmGetModuleClkNumParent Negative Test Failed.\n");
        }
    #endif

        status = Sciclient_pmQueryModuleClkFreq(invalidModuleId,
                                                256U,
                                                reqFreq,
                                                &respFreq,
                                                SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmQueryModuleClkFreq Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmQueryModuleClkFreq Negative Test Failed.\n");
        }

        status = Sciclient_pmSetModuleClkFreq(invalidModuleId,
                                              256U,
                                              reqFreq,
                                              TISCI_MSG_FLAG_CLOCK_ALLOW_FREQ_CHANGE,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmSetModuleClkFreq Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmSetModuleClkFreq Negative Test Failed.\n");
        }

        status = Sciclient_pmGetModuleClkFreq(invalidModuleId,
                                              256U,
                                              &freq,
                                              SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmGetModuleClkFreq Negative Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmGetModuleClkFreq Negative Test Failed.\n");
        }

#if defined(SOC_J784S4)
        status = Sciclient_pmEnableWdt(SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmEnableWdt Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmEnableWdt Test Failed.\n");
        }

        status = Sciclient_pmDisableWakeup(SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmDisableWakeup Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmDisableWakeup Test Failed.\n");
        }

        status = Sciclient_pmPrepareSleep(SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmPrepareSleep Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmPrepareSleep Test Failed.\n");
        }

        status = Sciclient_pmEnterSleep(SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_pmEnterSleep Test Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_pmEnterSleep Test Failed.\n");
        }
#endif
    }
    else
    {
        pmMessageNegTestStatus += CSL_EFAIL;
        SciApp_printf ("Sciclient_Init Failed.\n");
    }

    if (sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            pmMessageNegTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_deinit Passed.\n");
        }
        else
        {
            pmMessageNegTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_deinit Failed.\n");
        }
    }

    return pmMessageNegTestStatus;
}
#endif

static int32_t SciclientApp_procbootNegTest(void)
{
    int32_t  status               = CSL_PASS;
    int32_t  sciclientInitStatus  = CSL_PASS;
    int32_t  procbootTestStatus   = CSL_PASS;
    uint8_t  invalidProcID        = 0x81U;
    uint32_t ctrlFlagSet          = 1U;
    uint32_t ctrlFlagClr          = 2U;
    uint8_t  numMatchIterations   = 1U;
    uint8_t  delayPerIterations   = 10U;
    uint32_t statusFlagSetAllWait = 1U;
    uint32_t statusFlagSetAnyWait = 2U;
    uint32_t statusFlagClrAllWait = 1U;
    uint32_t statusFlagClrAnyWait = 2U;
    const struct tisci_msg_proc_set_config_req procSetConfigReq  = {0};
    const struct tisci_msg_proc_auth_boot_req procAuthBootReq    = {0};
    struct tisci_msg_proc_get_status_resp procGetStatusResp;
    Sciclient_ConfigPrms_t config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
        SciApp_printf ("Sciclient_init PASSED.\n");
        status = Sciclient_procBootRequestProcessor(invalidProcID, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootRequestProcessor: Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootRequestProcessor: Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootReleaseProcessor(invalidProcID, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootReleaseProcessor: TISCI_MSG_FLAG_AOP Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootReleaseProcessor: TISCI_MSG_FLAG_AOP Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootReleaseProcessor(invalidProcID, TISCI_MSG_FLAG_RESERVED0, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootReleaseProcessor: TISCI_MSG_FLAG_RESERVED0 Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootReleaseProcessor: TISCI_MSG_FLAG_RESERVED0 Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootHandoverProcessor(invalidProcID, TISCI_HOST_ID_MCU_0_R5_1, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootHandoverProcessor: Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootHandoverProcessor: Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootSetSequenceCtrl(invalidProcID, ctrlFlagSet, ctrlFlagClr, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootSetSequenceCtrl: TISCI_MSG_FLAG_AOP Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootSetSequenceCtrl: TISCI_MSG_FLAG_AOP Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootSetSequenceCtrl(invalidProcID, ctrlFlagSet, ctrlFlagClr, TISCI_MSG_FLAG_RESERVED0, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootSetSequenceCtrl: TISCI_MSG_FLAG_RESERVED0 Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootSetSequenceCtrl: TISCI_MSG_FLAG_RESERVED0 Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootSetProcessorCfg(NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootSetProcessorCfg: Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootSetProcessorCfg: Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootAuthAndStart(NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootAuthAndStart: Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootAuthAndStart: Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootGetProcessorState(invalidProcID, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootGetProcessorState: Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootGetProcessorState: Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootWaitProcessorState(invalidProcID, numMatchIterations, 
                                                      delayPerIterations,statusFlagSetAllWait, 
                                                      statusFlagSetAnyWait, statusFlagClrAllWait,
                                                      statusFlagClrAnyWait, TISCI_MSG_FLAG_AOP, 
                                                      SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootWaitProcessorState: TISCI_MSG_FLAG_AOP Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootWaitProcessorState: TISCI_MSG_FLAG_AOP Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootWaitProcessorState(invalidProcID, numMatchIterations, 
                                                      delayPerIterations, statusFlagSetAllWait, 
                                                      statusFlagSetAnyWait, statusFlagClrAllWait,
                                                      statusFlagClrAnyWait, TISCI_MSG_FLAG_RESERVED0, 
                                                      SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootWaitProcessorState: TISCI_MSG_FLAG_RESERVED0 Negative Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootWaitProcessorState: TISCI_MSG_FLAG_RESERVED0 Negative Arg Test FAILED \n");
        }

        status = Sciclient_procBootGetProcessorState(invalidProcID, &procGetStatusResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootGetProcessorState: Negative Arg Test Passed.\n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootGetProcessorState: Negative Arg Test Failed.\n");
        }

        status = Sciclient_procBootSetProcessorCfg(&procSetConfigReq, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootSetProcessorCfg: Negative Arg Test Passed.\n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootSetProcessorCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_procBootAuthAndStart(&procAuthBootReq, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootAuthAndStart: Negative Arg Test Passed.\n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootAuthAndStart: Negative Arg Test Failed.\n");
        }
     }
     else
     {
         procbootTestStatus += CSL_EFAIL;
         SciApp_printf ("Sciclient_init FAILED.\n");
     }

     if(sciclientInitStatus == CSL_PASS)
     {
         status = Sciclient_deinit();
         if(status == CSL_PASS)
         {
             procbootTestStatus += CSL_PASS;
             SciApp_printf ("Sciclient_deinit PASSED.\n");
         }
         else
         {
             procbootTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_deinit FAILED.\n");
         }
     }

   return procbootTestStatus;
}

static int32_t SciclientApp_rmNegTest(void)
{
      int32_t  status               = CSL_PASS;
      int32_t  sciclientInitStatus  = CSL_PASS;
      int32_t  rmTestStatus         = CSL_PASS;
      uint16_t intNum               = 0U;
      uint16_t invalidDevId         = 450U;
      uint16_t iaOutput             = 0U;
      uint16_t dstInput             = 0U;
      Sciclient_ConfigPrms_t config =
      {
         SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
         NULL,
         0 /* isSecure = 0 un secured for all cores */
      };
      struct tisci_msg_rm_get_resource_range_req  negReq;
      struct tisci_msg_rm_get_resource_range_resp resp;

      while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
        SciApp_printf ("Sciclient_init PASSED.\n");
        negReq.type = 2000U;
        negReq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status = Sciclient_rmGetResourceRange(&negReq, &resp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmGetResourceRange: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmGetResourceRange: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmIrqSetRaw(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmIrqSetRaw: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmIrqSetRaw: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmIrqReleaseRaw(NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmIrqReleaseRaw: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmIrqReleaseRaw: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmIrqTranslateIaOutput(invalidDevId, iaOutput, 
                                                  TISCI_DEV_R5FSS0_CORE0, &intNum);
        if (status == CSL_EBADARGS)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmIrqTranslateIaOutput: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmIrqTranslateIaOutput: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmIrqTranslateIrqInput(invalidDevId, dstInput, 
                                                  TISCI_DEV_R5FSS0_CORE0, &intNum);
        if (status == CSL_EBADARGS)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmIrqTranslateIrqInput: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmIrqTranslateIrqInput: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmPsilPair(NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmPsilPair: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmPsilPair: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmPsilUnpair(NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmPsilUnpair: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmPsilUnpair: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmPsilRead(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmPsilRead: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmPsilRead: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmPsilWrite(NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmPsilWrite: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmPsilWrite: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmRingCfg(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmRingCfg: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmRingCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmRingMonCfg(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmRingMonCfg: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmRingMonCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmUdmapTxChCfg(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmUdmapTxChCfg: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmUdmapTxChCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmUdmapRxChCfg(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmUdmapRxChCfg: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmUdmapRxChCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmUdmapFlowCfg(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmUdmapFlowCfg: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmUdmapFlowCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmUdmapFlowSizeThreshCfg(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmUdmapFlowSizeThreshCfg: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmUdmapFlowSizeThreshCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmUdmapGcfgCfg(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmUdmapGcfgCfg: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmUdmapGcfgCfg: Negative Arg Test Failed.\n");
        }

        status = Sciclient_rmSetProxyCfg(NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmSetProxyCfg: Negative Arg Test Passed.\n");
        }
        else
        {
           rmTestStatus += CSL_EFAIL;
           SciApp_printf ("Sciclient_rmSetProxyCfg: Negative Arg Test Failed.\n");
        }
     }
    else
    {
          rmTestStatus += CSL_EFAIL;
          SciApp_printf ("Sciclient_init FAILED.\n");
    }
    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_deinit FAILED.\n");
        }
    }

    return rmTestStatus;
}

static int32_t SciclientApp_procbootPositiveTest(void)
{
    int32_t  status                      = CSL_PASS;
    int32_t  sciclientInitStatus         = CSL_PASS;
    int32_t  procbootTestStatus          = CSL_PASS;
    struct tisci_msg_proc_get_status_resp procGetStatusResp;
    Sciclient_ConfigPrms_t SciApp_Config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&SciApp_Config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
        SciApp_printf ("Sciclient_init PASSED.\n");
        status = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootRequestProcessor: Positive Arg Test Passed.\n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootRequestProcessor: Positive Arg Test Failed.\n");
        }

        status = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, &procGetStatusResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootGetProcessorState: Positive Arg Test Passed.\n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootGetProcessorState: Positive Arg Test Failed.\n");
        }

        status = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootReleaseProcessor: Positive Arg Test Passed.\n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootReleaseProcessor: Positive Arg Test Failed.\n");
        }

        status = Sciclient_procBootRequestProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            status = Sciclient_procBootGetProcessorState(SCICLIENT_PROC_ID_R5FSS0_CORE0, &procGetStatusResp, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                SciApp_printf ("Sciclient_procBootGetProcessorState: PASSED \n");
                const struct tisci_msg_proc_set_config_req procSetConfigReq = 
                {
                    .processor_id         = procGetStatusResp.processor_id,
                    .bootvector_lo        = procGetStatusResp.bootvector_lo,
                    .bootvector_hi        = procGetStatusResp.bootvector_hi,
                    .config_flags_1_clear = 0,
                    .config_flags_1_set   = 0
                };
                status = Sciclient_procBootSetProcessorCfg(&procSetConfigReq, SCICLIENT_SERVICE_WAIT_FOREVER);
                if(status == CSL_PASS)
                {
                    procbootTestStatus += CSL_PASS;
                    SciApp_printf ("Sciclient_procBootSetProcessorCfg: Positive Arg Test PASSED \n");
                }
                else
                {
                    procbootTestStatus += CSL_EFAIL;
                    SciApp_printf ("Sciclient_procBootSetProcessorCfg: Positive Arg Test FAILED \n");
                }
            }
            else
            {
                procbootTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_procBootGetProcessorState: FAILED \n");
            }

            status = Sciclient_procBootSetSequenceCtrl(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_MSG_VAL_PROC_BOOT_CTRL_FLAG_R5_CORE_HALT, 0, TISCI_MSG_FLAG_AOP, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                procbootTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_procBootSetSequenceCtrl: Positive Arg Test PASSED \n");
            }
            else
            {
                procbootTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_procBootSetSequenceCtrl: Positive Arg Test FAILED \n");
            }

            status = Sciclient_procBootWaitProcessorState(SCICLIENT_PROC_ID_R5FSS0_CORE0, 1, 1, 0, 3, 0, 0, 0, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                procbootTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_procBootWaitProcessorState: Positive Arg Test PASSED \n");
            }
            else
            {
                procbootTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_procBootWaitProcessorState: Positive Arg Test FAILED \n");
            }

            status = Sciclient_procBootHandoverProcessor(SCICLIENT_PROC_ID_R5FSS0_CORE0, TISCI_HOST_ID_MAIN_0_R5_1, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                procbootTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_procBootHandoverProcessor: Positive Arg Test PASSED \n");
            }
            else
            {
                procbootTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_procBootHandoverProcessor: Positive Arg Test FAILED \n");
            }
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootHandoverProcessor: Positive Arg Test FAILED \n");
        }

        status = Sciclient_procBootReleaseProcessor(SCICLIENT_PROC_ID_MCU_R5FSS0_CORE0, 0U, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_procBootReleaseProcessor: Positive Arg Test PASSED \n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_procBootReleaseProcessor: Positive Arg Test FAILED \n");
        }
    }
    else
    {
        procbootTestStatus += CSL_EFAIL;
        SciApp_printf ("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            procbootTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_deinit PASSED.\n");
        }
        else
        {
            procbootTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_deinit FAILED.\n");
        }
    }

     return procbootTestStatus;
}

#if defined (BUILD_MCU1_0)
static int32_t SciclientApp_boardCfgTest(void)
{
    int32_t status                = CSL_PASS;
    int32_t sciclientInitStatus   = CSL_PASS;
    int32_t boardCfgTestStatus    = CSL_PASS;
    Sciclient_ConfigPrms_t config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
        NULL,
        1U,
        0U,
        UTRUE
    };
    Sciclient_BoardCfgPrms_t pmBoardCfgParams = {0};
    pmBoardCfgParams.devGrp = DEVGRP_04;

    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if (CSL_PASS == status)
    {
        SciApp_printf ("Sciclient_init Passed.\n");
        status = Sciclient_boardCfgPm(&pmBoardCfgParams);
        if(status != CSL_PASS)
        {
            boardCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_boardCfgPm NULL Arg Test PASSED \n");
        }
        else
        {
            boardCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_boardCfgPm NULL Arg Test FAILED \n");
        }

        status = Sciclient_getDefaultBoardCfgInfo(NULL);
        if(status != CSL_PASS)
        {
            boardCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_getDefaultBoardCfgInfo NULL Arg Test PASSED \n");
        }
        else
        {
            boardCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_getDefaultBoardCfgInfo NULL Arg Test FAILED \n");
        }

        /* Passing NULL parameter to cover branch in Sciclient_boardCfg */
        status = Sciclient_boardCfg(NULL);
        if (status == CSL_PASS)
        {
            boardCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_boardCfg NULL Arg Test PASSED \n");
        }
        else
        {
            boardCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_boardCfg NULL Arg Test FAILED \n");
        }

        /* Passing NULL parameter to cover branch in Sciclient_boardCfgRm */
        status = Sciclient_boardCfgRm(NULL);
        if (status == CSL_PASS)
        {
            boardCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_boardCfgRm NULL Arg Test PASSED \n");
        }
        else
        {
            boardCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_boardCfgRm NULL Arg Test FAILED \n");
        }

        /* Passing NULL parameter to cover branch in  Sciclient_boardCfgSec */
        status = Sciclient_boardCfgSec(NULL);
        if (status == CSL_PASS)
        {
            boardCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_boardCfgSec NULL Arg Test PASSED \n");
        }
        else
        {
            boardCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_boardCfgSec NULL Arg Test FAILED \n");
        }
        
        /* Passing NULL parameter to cover branch in Sciclient_boardCfgPm */
        status = Sciclient_boardCfgPm(NULL);
        if (status == CSL_PASS)
        {
            boardCfgTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_boardCfgPm NULL Arg Test PASSED \n");
        }
        else
        {
            boardCfgTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_boardCfgPm NULL Arg Test FAILED \n");
        }
    }
    else
    {
        boardCfgTestStatus += CSL_EFAIL;
        SciApp_printf ("Sciclient_init Failed.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            boardCfgTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_deinit Passed.\n");
        }
        else
        {
            boardCfgTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_deinit Failed.\n");
        }
    }

    return boardCfgTestStatus;
}
#endif

static int32_t SciclientApp_rmIrqValidParamsNegTest(void)
{
    int32_t  status               = CSL_PASS;
    int32_t  sciclientInitStatus  = CSL_PASS;
    int32_t  rmIrqTestStatus      = CSL_PASS;                                                               
    Sciclient_ConfigPrms_t config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };
    
    while (gSciclientHandle.initCount != 0)
    {
       status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;
    
   /* For example, if a branch statement exists in the following way:
      if(A && B && C && D) ==> Inorder to cover 16(2^4) combinations for MC/DC, we have to just cover 5 combinations given below:
      (FFFF) ==> covers 8 combinations {The "&&" operation will stop it's search once it reaches a false condition, it doesn't 
                                        care about what the other conditions evaluates to. So, on covering (FFFF) LDRA will
                                        assume that (FTFF),(FTTF),(FTTT) etc... are also covered.}
      (TFFF) ==> covers 4 combinations
      (TTFF) ==> covers 2 combinations
      (TTTF) ==> covers 1 combination
      (TTTT) ==> covers 1 combination 
      
      The above logic is followed for all the below five sub-tests. These sub-tests have 6 conditions in their if statement,
      so only 7 combinations are needed to covered inorder to cover all 64(2^6) MC/DC combinations. */

    if(status == CSL_PASS)
    {
        SciApp_printf("Sciclient_init PASSED.\n");
        SciApp_printf("This test has five sub-tests:\n");
        rmIrqTestStatus += SciclientApp_rmIrqCfgIsUnmappedVintDirectEventNegTest();
        rmIrqTestStatus += SciclientApp_rmIrqCfgIsEventToVintMappingOnlyNegTest();
        rmIrqTestStatus += SciclientApp_rmIrqCfgIsOesOnlyNegTest();
        rmIrqTestStatus += SciclientApp_rmIrqCfgIsDirectEventTest();
        rmIrqTestStatus += SciclientApp_rmIrqCfgIsDirectNonEventTest();
    }
    else
    {
        rmIrqTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
       status = Sciclient_deinit();
       if(status == CSL_PASS)
       {
           rmIrqTestStatus += CSL_PASS;
           SciApp_printf("Sciclient_deinit PASSED.\n");
       }
       else
       {
           rmIrqTestStatus += CSL_EFAIL;
           SciApp_printf("Sciclient_deinit FAILED.\n");
       }
    }

    return rmIrqTestStatus;
}

static int32_t SciclientApp_rmIrqCfgIsUnmappedVintDirectEventNegTest(void)
{
    int32_t  status                     = CSL_PASS;
    int32_t  vintDirectEventTestStatus  = CSL_PASS;
    uint8_t  loopCounter                = 0U;
    uint32_t numConditions              = 6U;
    uint32_t validParams[7]             = { 
                                            (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                             TISCI_MSG_VALUE_RM_IA_ID_VALID  | TISCI_MSG_VALUE_RM_VINT_VALID |
                                             TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID),                                        
                                            (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                             TISCI_MSG_VALUE_RM_IA_ID_VALID  | TISCI_MSG_VALUE_RM_VINT_VALID |
                                             TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID),                                       
                                            (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                             TISCI_MSG_VALUE_RM_IA_ID_VALID),                                       
                                            (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                             TISCI_MSG_VALUE_RM_VINT_VALID),  
                                            (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_IA_ID_VALID |
                                             TISCI_MSG_VALUE_RM_VINT_VALID),
                                            (TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID | TISCI_MSG_VALUE_RM_IA_ID_VALID |
                                             TISCI_MSG_VALUE_RM_VINT_VALID),                
                                            (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                             TISCI_MSG_VALUE_RM_IA_ID_VALID  | TISCI_MSG_VALUE_RM_VINT_VALID)
                                           };
    struct tisci_msg_rm_irq_set_req   rmIrqReq  = {0};
    struct tisci_msg_rm_irq_set_resp  rmIrqResp = {0};
            
    /* To cover MC/DC for Sciclient_rmIrqCfgIsUnmappedVintDirectEvent() */
    for(loopCounter = 0U; loopCounter <= numConditions; loopCounter++)
    {
          rmIrqReq.valid_params = validParams[loopCounter];
          status += Sciclient_rmProgramInterruptRoute(&rmIrqReq, &rmIrqResp, 
                                                     SCICLIENT_SERVICE_WAIT_FOREVER);
          if(status != CSL_PASS)
          {
              vintDirectEventTestStatus += CSL_PASS;
          }
          else
          {
              vintDirectEventTestStatus += CSL_EFAIL;
          }
    }
    
    if(vintDirectEventTestStatus == CSL_PASS)
    {
        SciApp_printf("Sciclient_rmIrqCfgIsUnmappedVintDirectEvent() Test Passed.\n");                                                  
    }
    else
    {
        SciApp_printf("Sciclient_rmIrqCfgIsUnmappedVintDirectEvent() Test Failed.\n");                                                  
    }
    
    return vintDirectEventTestStatus;
}

static int32_t SciclientApp_rmIrqCfgIsEventToVintMappingOnlyNegTest(void)
{
    int32_t  status                     = CSL_PASS;
    int32_t  vintMappingOnlyTestStatus  = CSL_PASS;
    uint8_t  loopCounter                = 0U;
    uint32_t numConditions              = 6U;
    uint32_t validParams[7]             = { 
                                            (TISCI_MSG_VALUE_RM_IA_ID_VALID  | TISCI_MSG_VALUE_RM_VINT_VALID |
                                             TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID),
                                            (TISCI_MSG_VALUE_RM_IA_ID_VALID  | TISCI_MSG_VALUE_RM_VINT_VALID |
                                             TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID),
                                            (TISCI_MSG_VALUE_RM_IA_ID_VALID  | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID |
                                             TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID),
                                            (TISCI_MSG_VALUE_RM_VINT_VALID  | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID |
                                             TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID),
                                            (TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID | TISCI_MSG_VALUE_RM_IA_ID_VALID | 
                                             TISCI_MSG_VALUE_RM_VINT_VALID  | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | 
                                             TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID),
                                            (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_IA_ID_VALID | 
                                             TISCI_MSG_VALUE_RM_VINT_VALID  | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | 
                                              TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID),
                                            (TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID  | 
                                             TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID)
                                          };
    struct tisci_msg_rm_irq_set_req   rmIrqReq  = {0};
    struct tisci_msg_rm_irq_set_resp  rmIrqResp = {0};
    
    /* To cover statement and MC/DC coverage for Sciclient_rmIrqCfgIsEventToVintMappingOnly() */
    for(loopCounter = 0U; loopCounter <= numConditions; loopCounter++)
    {
          rmIrqReq.valid_params = validParams[loopCounter];
          status = Sciclient_rmProgramInterruptRoute(&rmIrqReq, &rmIrqResp, 
                                                     SCICLIENT_SERVICE_WAIT_FOREVER);
          if(status != CSL_PASS)
          {
              vintMappingOnlyTestStatus += CSL_PASS;                                                
          }
          else
          {
              vintMappingOnlyTestStatus += CSL_EFAIL;
          }
    }
    
    if(vintMappingOnlyTestStatus == CSL_PASS)
    {
        SciApp_printf("Sciclient_rmIrqCfgIsEventToVintMappingOnly() Test Passed.\n");                                                  
    }
    else
    {
        SciApp_printf("Sciclient_rmIrqCfgIsEventToVintMappingOnly() Test Failed.\n");                                                  
    }
    
    return vintMappingOnlyTestStatus;
}

static int32_t SciclientApp_rmIrqCfgIsOesOnlyNegTest(void)
{
    int32_t  status                       = CSL_PASS;
    int32_t  rmIrqCfgIsOesOnlyTestStatus  = CSL_PASS;
    uint8_t  loopCounter                  = 0U;
    uint32_t numConditions                = 6U;
    uint32_t validParams[7]               = {
                                                (TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID  | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID),
                                                (0U),
                                                (TISCI_MSG_VALUE_RM_VINT_VALID  | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID),
                                                (TISCI_MSG_VALUE_RM_IA_ID_VALID  | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID),
                                                (TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID  | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID),
                                                (TISCI_MSG_VALUE_RM_DST_ID_VALID  | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID),
                                                (TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID)
                                            };
    struct tisci_msg_rm_irq_set_req   rmIrqReq  = {0};
    struct tisci_msg_rm_irq_set_resp  rmIrqResp = {0};
    
    /* To cover MC/DC conditions for Sciclient_rmIrqCfgIsOesOnly() */
    for(loopCounter = 0U; loopCounter <= numConditions; loopCounter++)
    {
      rmIrqReq.valid_params = validParams[loopCounter];
      status = Sciclient_rmProgramInterruptRoute(&rmIrqReq, &rmIrqResp, 
                                                 SCICLIENT_SERVICE_WAIT_FOREVER);
      if(status != CSL_PASS)
      {
          rmIrqCfgIsOesOnlyTestStatus += CSL_PASS;
      }
      else
      {
          rmIrqCfgIsOesOnlyTestStatus += CSL_EFAIL;
      }
    }
    
    if(rmIrqCfgIsOesOnlyTestStatus == CSL_PASS)
    {
        SciApp_printf("Sciclient_rmIrqCfgIsOesOnly() Test Passed.\n");                                                  
    }
    else
    {
        SciApp_printf("Sciclient_rmIrqCfgIsOesOnly() Test Failed.\n");                                                  
    }
    
    return rmIrqCfgIsOesOnlyTestStatus;
}

static int32_t SciclientApp_rmIrqCfgIsDirectEventTest(void)
{
    int32_t  status                          = CSL_PASS;
    int32_t  rmIrqCfgIsDirectEventTestStatus = CSL_PASS;
    uint32_t rmVintStatusBitIndexInvalid     = (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                               TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID);
    uint32_t rmGlobalEventInvalid            = (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID | TISCI_MSG_VALUE_RM_IA_ID_VALID |
                                                TISCI_MSG_VALUE_RM_VINT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID);
    uint32_t rmVintInvalid                   = (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID | TISCI_MSG_VALUE_RM_IA_ID_VALID |
                                                TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID);
    uint32_t rmIaIdInvalid                   = (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID | TISCI_MSG_VALUE_RM_VINT_VALID | 
                                                TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID);
    uint32_t rmDstHostIrqInvalid             = (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID |
                                                TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID);
    uint32_t rmDstIdInvalid                  = (TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID | TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID |
                                                TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID);
    uint32_t directEventPass                 = (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                                TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID |
                                                TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID);
    uint32_t inValidParams[7]                = {directEventPass,
                                                rmVintStatusBitIndexInvalid,
                                                rmGlobalEventInvalid,
                                                rmVintInvalid,
                                                rmIaIdInvalid,
                                                rmDstHostIrqInvalid,
                                                rmDstIdInvalid};
    uint8_t  num;
    uint32_t numConditions                   = 6U;
    struct tisci_msg_rm_irq_set_resp sciclient_DirectEventResp;

    /* To cover MC/DC for Sciclient_rmIrqCfgIsDirectEvent() */
    for(num = 0; num <= numConditions; num++)
    {
        const struct tisci_msg_rm_irq_set_req sciclient_DirectEventReq = 
        {
            .valid_params = inValidParams[num]
        };
        status = Sciclient_rmProgramInterruptRoute(&sciclient_DirectEventReq,
                                                    &sciclient_DirectEventResp,
                                                    SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != CSL_PASS)
        {
            rmIrqCfgIsDirectEventTestStatus += CSL_PASS;
        }
        else
        {
            rmIrqCfgIsDirectEventTestStatus += CSL_EFAIL;
        }
    }

    if(rmIrqCfgIsDirectEventTestStatus == CSL_PASS)
    {
        SciApp_printf("Sciclient_rmIrqCfgIsDirectEvent() Test Passed.\n");                                                  
    }
    else
    {
        SciApp_printf("Sciclient_rmIrqCfgIsDirectEvent() Test Failed.\n");                                                  
    }

    return rmIrqCfgIsDirectEventTestStatus;
}

static int32_t SciclientApp_rmIrqCfgIsDirectNonEventTest(void)
{
    int32_t status                                = CSL_PASS;
    int32_t rmIrqCfgIsDirectNonEventTestStatus    = CSL_PASS;
    int32_t rmIrqCfgIsDirectNonEventParms[7]      = {(TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID  | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID),
													 (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID),
													 (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID | TISCI_MSG_VALUE_RM_VINT_VALID),
													 (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID | TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID),
                                                      TISCI_MSG_VALUE_RM_DST_ID_VALID,
                                                      TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID,
                                                     (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID)
													};
    int8_t number;                 
    uint32_t numConditions                        = 6U;                               
    struct tisci_msg_rm_irq_release_req rmIrqReleaseReq;
    struct tisci_msg_rm_irq_release_resp rmIrqReleaseResp;

    /* To cover MC/DC for Sciclient_rmIrqCfgIsDirectNonEvent() */
    for(number = 0; number <= numConditions; number++)
    {
        rmIrqReleaseReq.valid_params = rmIrqCfgIsDirectNonEventParms[number];
        status = Sciclient_rmClearInterruptRoute(&rmIrqReleaseReq, &rmIrqReleaseResp, SCICLIENT_SERVICE_WAIT_FOREVER);        
        if (status != CSL_PASS)
        {
            rmIrqCfgIsDirectNonEventTestStatus += CSL_PASS;
        }
        else
        {
            rmIrqCfgIsDirectNonEventTestStatus += CSL_EFAIL;
        }
    }

    if(rmIrqCfgIsDirectNonEventTestStatus == CSL_PASS)
    {
        SciApp_printf("Sciclient_rmIrqCfgIsDirectNonEvent() Test Passed.\n");                                                  
    }
    else
    {
        SciApp_printf("Sciclient_rmIrqCfgIsDirectNonEvent() Test Failed.\n");                                                  
    }

    return rmIrqCfgIsDirectNonEventTestStatus;
}

static void SciclientApp_getResoureRange(uint16_t src_id, uint16_t dst_dev_id, uint16_t dst_host_id, struct SciApp_RangeOfLines *range)
{
    /* Get the range of lines between the given src_id and dst_id */
    struct tisci_msg_rm_get_resource_range_req resourceRangeReq={0};
    struct tisci_msg_rm_get_resource_range_resp resourceRangeRes={0};
    uint16_t dst_start;
    uint16_t dst_end;

    resourceRangeReq.type = src_id;
    resourceRangeReq.secondary_host = dst_host_id;
    Sciclient_rmGetResourceRange(&resourceRangeReq, &resourceRangeRes, SCICLIENT_SERVICE_WAIT_FOREVER);
    (*range).src_start = resourceRangeRes.range_start;
    (*range).src_end   = resourceRangeRes.range_start + resourceRangeRes.range_num - 1;

    Sciclient_rmTranslateIntOutput(src_id, (*range).src_start, dst_dev_id, &dst_start);
    Sciclient_rmTranslateIntOutput(src_id, (*range).src_end, dst_dev_id, &dst_end);
    (*range).dst_start = dst_start;
    (*range).dst_end = dst_end;
}

static int32_t SciclientApp_rmTranslateIntOutputTest(void)
{
    int32_t  status                         = CSL_PASS;
    int32_t  sciclientInitStatus            = CSL_PASS;
    int32_t  rmTranslateIntOutputTestStatus = CSL_PASS;
    uint16_t dstInput;
    Sciclient_ConfigPrms_t config           =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };
    struct SciApp_RangeOfLines range;
    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf("Sciclient_init PASSED.\n");

        SciclientApp_getResoureRange(TISCI_DEV_NAVSS0_INTR, TISCI_DEV_R5FSS0_CORE0, TISCI_HOST_ID_MAIN_0_R5_0, &range);

        /* Passing valid dst_dev_id to translate the specified IA output to the destination processor IRQ input */
        status = Sciclient_rmTranslateIntOutput(TISCI_DEV_NAVSS0_INTR, (range).src_start, TISCI_DEV_R5FSS0_CORE0, &dstInput);
        if (status == CSL_PASS)
        {
            rmTranslateIntOutputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Valid Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIntOutputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Valid Arg Test Failed.\n");
        }

        /* Passing invalid dst_dev_id */
        status = Sciclient_rmTranslateIntOutput(TISCI_DEV_NAVSS0_INTR, (range).src_start, TISCI_DEV_GPIO0, &dstInput);
        if (status != CSL_PASS)
        {
            rmTranslateIntOutputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Negative Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIntOutputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Negative Arg Test Failed.\n");
        }

        /* Passing valid src_id, dst_dev_id and invalid src_output */
        status = Sciclient_rmTranslateIntOutput(TISCI_DEV_NAVSS0_INTR, (range).src_end + 1, TISCI_DEV_R5FSS0_CORE0, &dstInput);
        if (status != CSL_PASS)
        {
            rmTranslateIntOutputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Negative Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIntOutputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Negative Arg Test Failed.\n");
        }

        /* Passing invalid src_id and invalid dst_dev_id */
        status = Sciclient_rmTranslateIntOutput(TISCI_DEV_R5FSS0_CORE0, (range).src_start, TISCI_DEV_R5FSS0_CORE1, &dstInput);
        if (status != CSL_PASS)
        {
            rmTranslateIntOutputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Negative Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIntOutputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Negative Arg Test Failed.\n");
        }
        
        /* Passing valid IA src_id and invalid dst_dev_id */
        status = Sciclient_rmTranslateIntOutput(TISCI_DEV_NAVSS0_MODSS_INTAGG, (range).src_start, TISCI_DEV_R5FSS0_CORE1, &dstInput);
        if (status != CSL_PASS)
        {
            rmTranslateIntOutputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Negative Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIntOutputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIntOutput: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmTranslateIntOutputTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmTranslateIntOutputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmTranslateIntOutputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

    return rmTranslateIntOutputTestStatus;
}

static int32_t SciclientApp_rmTranslateIrqInputTest(void)
{
    int32_t  status                         = CSL_PASS;
    int32_t  sciclientInitStatus            = CSL_PASS;
    int32_t  rmTranslateIrqInputTestStatus  = CSL_PASS;
    Sciclient_ConfigPrms_t config           =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };
    struct SciApp_RangeOfLines range;
    uint16_t srcOutput;

    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf("Sciclient_init PASSED.\n");

        SciclientApp_getResoureRange(TISCI_DEV_NAVSS0_INTR, TISCI_DEV_R5FSS0_CORE0, TISCI_HOST_ID_MAIN_0_R5_0, &range);

        /* Passing valid dst_dev_id to translate the specified destination processor IRQ input to the IA output */
        status = Sciclient_rmTranslateIrqInput(TISCI_DEV_R5FSS0_CORE0, (range).dst_start, TISCI_DEV_NAVSS0_INTR, &srcOutput);
        if (status == CSL_PASS)
        {
            rmTranslateIrqInputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Valid Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIrqInputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Valid Arg Test Failed.\n");
        }

        /* Passing invalid dst_dev_id */
        status = Sciclient_rmTranslateIrqInput(TISCI_DEV_GPIO0, (range).dst_start, TISCI_DEV_NAVSS0_INTR, &srcOutput);
        if (status != CSL_PASS)
        {
            rmTranslateIrqInputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Negative Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIrqInputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Negative Arg Test Failed.\n");
        }

        /* Passing invalid src_id and invalid dst_dev_id */
        status = Sciclient_rmTranslateIrqInput(TISCI_DEV_R5FSS0_CORE0, (range).dst_start, TISCI_DEV_R5FSS0_CORE1, &srcOutput);
        if (status != CSL_PASS)
        {
            rmTranslateIrqInputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Negative Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIrqInputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Negative Arg Test Failed.\n");
        }

        /* Passing valid src_id, dst_dev_id and invalid dst_input */
        status = Sciclient_rmTranslateIrqInput(TISCI_DEV_R5FSS0_CORE0, (range).dst_end + 1, TISCI_DEV_NAVSS0_INTR, &srcOutput);
        if (status != CSL_PASS)
        {
            rmTranslateIrqInputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Negative Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIrqInputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Negative Arg Test Failed.\n");
        }
        
        /* Passing valid IA src_id, dst_dev_id and invalid dst_input */
        status = Sciclient_rmTranslateIrqInput(TISCI_DEV_NAVSS0_INTR, (range).dst_end + 1, TISCI_DEV_NAVSS0_MODSS_INTAGG, &srcOutput);
        if (status != CSL_PASS)
        {
            rmTranslateIrqInputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Negative Arg Test Passed.\n");
        }
        else
        {
            rmTranslateIrqInputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmTranslateIrqInput: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmTranslateIrqInputTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmTranslateIrqInputTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmTranslateIrqInputTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

    return rmTranslateIrqInputTestStatus;
}

static int32_t SciclientApp_rmClearInterruptRouteTest(void)
{
    int32_t status                            = CSL_PASS;
    int32_t sciclientInitStatus               = CSL_PASS;
    int32_t rmClearInterruptRouteTestStatus   = CSL_PASS;
    int32_t rmClearInterruptRouteTestCases[4] = {0xffffff07,0x000000fc,0x0000000f,0x0000003f};
    int8_t number;
    struct tisci_msg_rm_irq_release_req rmIrqReleaseReq;
    struct tisci_msg_rm_irq_release_req rmIrqReleaseFailReq;
    struct tisci_msg_rm_irq_release_resp rmIrqReleaseFailResp;
    struct tisci_msg_rm_irq_release_req rmIrqReleaseValidParamsReq;
    rmIrqReleaseValidParamsReq.valid_params = TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID;

    Sciclient_ConfigPrms_t config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf("Sciclient_init PASSED.\n");
        /* Passing a NULL request and NULL response */
        status = Sciclient_rmClearInterruptRoute(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EBADARGS)
        {
            rmClearInterruptRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmClearInterruptRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Failed.\n");
        }

        /* Passing a NULL response */
        status = Sciclient_rmClearInterruptRoute(&rmIrqReleaseReq, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);    
        if (status == CSL_EBADARGS)
        {
            rmClearInterruptRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmClearInterruptRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Failed.\n");
        }  

        /* Covers negative test for Sciclient_rmIrqCfgIsOesOnly */
        status = Sciclient_rmClearInterruptRoute(&rmIrqReleaseValidParamsReq, &rmIrqReleaseFailResp, SCICLIENT_SERVICE_WAIT_FOREVER);    
        if (status == CSL_EFAIL)
        {
            rmClearInterruptRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmClearInterruptRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Failed.\n");
        }

        /* Covers the various event types */
        for(number = 0; number < 4; number++)
        {
            rmIrqReleaseFailReq.valid_params = rmClearInterruptRouteTestCases[number];
            status = Sciclient_rmClearInterruptRoute(&rmIrqReleaseFailReq, &rmIrqReleaseFailResp, SCICLIENT_SERVICE_WAIT_FOREVER);
            if (status == CSL_EBADARGS)
            {
                rmClearInterruptRouteTestStatus += CSL_PASS;
                SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Passed.\n");
            }
            else
            {
                rmClearInterruptRouteTestStatus += CSL_EFAIL;
                SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Failed.\n");
            }  
        }
    }
    else
    {
        rmClearInterruptRouteTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }
    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmClearInterruptRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmClearInterruptRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

    return rmClearInterruptRouteTestStatus;
}

static int32_t SciclientApp_rmProgramInterruptRouteTest(void)
{
    int32_t status                                           = CSL_PASS;
    int32_t sciclientInitStatus                              = CSL_PASS;
    int32_t rmProgramInterruptRouteTestStatus                = CSL_PASS;
    int32_t rmProgramInterruptRouteTestparams[5]             = {0xffffff07,0x000000fc,0x0000000f,0x00000010,0x0000003f};
    int8_t  number;
    struct tisci_msg_rm_irq_set_req rmIrqSetReq;
    struct tisci_msg_rm_irq_set_resp rmIrqSetResp;

    Sciclient_ConfigPrms_t config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf("Sciclient_init PASSED.\n");
        /* Passing a NULL request and a NULL response parameter */
        status = Sciclient_rmProgramInterruptRoute(NULL, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EBADARGS)
        {
            rmProgramInterruptRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmProgramInterruptRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Failed.\n");
        }

        /* Passing a NULL response parameter */
        status = Sciclient_rmProgramInterruptRoute(&rmIrqSetReq, NULL, SCICLIENT_SERVICE_WAIT_FOREVER);   
        if (status == CSL_EBADARGS)
        {
            rmProgramInterruptRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmProgramInterruptRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Failed.\n");
        }

        /* Covers the various event types */
        for(number = 0; number < 5; number++)
        {
            rmIrqSetReq.valid_params = rmProgramInterruptRouteTestparams[number];
            status = Sciclient_rmProgramInterruptRoute(&rmIrqSetReq, &rmIrqSetResp, SCICLIENT_SERVICE_WAIT_FOREVER);  
            if (status != CSL_PASS)
            {
                rmProgramInterruptRouteTestStatus += CSL_PASS;
                SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Passed.\n");
            }
            else
            {
                rmProgramInterruptRouteTestStatus += CSL_EFAIL;
                SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Failed.\n");
            } 
        }
        
        /* Passing src_id as interrupt aggregator and remaining parameters as invalid covers Sciclient_rmIaIsIa() in sciclient_rmProgramInterruptRoute() */
        rmIrqSetReq.valid_params = (TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID);
        rmIrqSetReq.src_id       = TISCI_DEV_NAVSS0_MODSS_INTAGG1 ;
        status = Sciclient_rmProgramInterruptRoute(&rmIrqSetReq, &rmIrqSetResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status != CSL_PASS )
        {
            rmProgramInterruptRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
           rmProgramInterruptRouteTestStatus += CSL_EFAIL;
           SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Failed.\n");
        } 
    }
    else
    {
        rmProgramInterruptRouteTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }
    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmProgramInterruptRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmProgramInterruptRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

    return rmProgramInterruptRouteTestStatus;
}

static int32_t SciclientApp_rmIrqUnmappedVintRouteDeleteNegTest(void)
{
    int32_t  status                                 = CSL_PASS;
    int32_t  sciclientInitStatus                    = CSL_PASS;
    int32_t  rmIrqUnmappedVintRouteDeleteTestStatus = CSL_PASS;
    struct tisci_msg_rm_irq_release_resp sciclient_UnmappedVintRouteDeleteResp;
    const struct tisci_msg_rm_irq_release_req sciclient_UnmappedVintRouteDeleteReqIa = 
    {
        .valid_params = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID,
        .src_id       = TISCI_DEV_NAVSS0_MODSS_INTAGG
    };
    const struct tisci_msg_rm_irq_release_req sciclient_UnmappedVintRouteDeleteReq   = 
    {
        .valid_params = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                        TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID,
        .src_id       = TISCI_DEV_NAVSS0_MAILBOX_0
    };
    Sciclient_ConfigPrms_t config                   =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
        SciApp_printf("Sciclient_init PASSED.\n");
        /* By passing src_id as TISCI_DEV_NAVSS0_MODSS_INTAGG, Sciclient_rmIaVintGetInfo function will return pass */
        status = Sciclient_rmClearInterruptRoute(&sciclient_UnmappedVintRouteDeleteReqIa,
                                                 &sciclient_UnmappedVintRouteDeleteResp,
                                                 SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmIrqUnmappedVintRouteDeleteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmIrqUnmappedVintRouteDeleteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Failed.\n");
        }

        /* By passing src_id as TISCI_DEV_NAVSS0_MAILBOX_0, Sciclient_rmIaVintGetInfo function will return fail */
        status = Sciclient_rmClearInterruptRoute(&sciclient_UnmappedVintRouteDeleteReq,
                                                 &sciclient_UnmappedVintRouteDeleteResp,
                                                 SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EBADARGS)
        {
            rmIrqUnmappedVintRouteDeleteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmIrqUnmappedVintRouteDeleteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmClearInterruptRoute: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmIrqUnmappedVintRouteDeleteTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmIrqUnmappedVintRouteDeleteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmIrqUnmappedVintRouteDeleteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return rmIrqUnmappedVintRouteDeleteTestStatus;
}

static int32_t SciclientApp_rmIrqFindRouteNegTest(void)
{
    int32_t  status                                 = CSL_PASS;
    int32_t  sciclientInitStatus                    = CSL_PASS;
    int32_t  rmIrqFindRouteTestStatus               = CSL_PASS;
    struct tisci_msg_rm_irq_set_req Sciclient_ReqSrcIr =
    {
        .valid_params = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID,
        .src_id       = TISCI_DEV_NAVSS0_INTR
    };
    struct tisci_msg_rm_irq_set_req Sciclient_ReqIa =
    {
        .valid_params = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                        TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID |
                        TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID,
        .ia_id        = TISCI_DEV_NAVSS0_MODSS_INTAGG
    };
    struct tisci_msg_rm_irq_set_req Sciclient_ReqDstIr =
    {
        .valid_params = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID,
        .src_id       = TISCI_DEV_NAVSS0_MAILBOX_0,
        .dst_id       = TISCI_DEV_NAVSS0_INTR
    };
    struct tisci_msg_rm_irq_set_resp Sciclient_Resp;
    Sciclient_ConfigPrms_t config                   =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
        SciApp_printf("Sciclient_init PASSED.\n");
        /* Passing source_id as IR fails the source and destination node checks for Sciclient_rmIrqFindRoute function */
        status = Sciclient_rmProgramInterruptRoute(&Sciclient_ReqSrcIr,
                                                   &Sciclient_Resp,
                                                   SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EBADARGS)
        {
            rmIrqFindRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmIrqFindRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Failed.\n");
        }
        
        /* Passing device ID of interrupt aggregator will retrieve source device's node for Sciclient_rmIrqFindRoute function */
        status = Sciclient_rmProgramInterruptRoute(&Sciclient_ReqIa,
                                                   &Sciclient_Resp,
                                                   SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmIrqFindRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmIrqFindRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Failed.\n");
        }

        /* Passing dest_id as IR fails the source and destination node checks for Sciclient_rmIrqFindRoute function */
        status = Sciclient_rmProgramInterruptRoute(&Sciclient_ReqDstIr,
                                                   &Sciclient_Resp,
                                                   SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EBADARGS)
        {
            rmIrqFindRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmIrqFindRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmIrqFindRouteTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmIrqFindRouteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmIrqFindRouteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return rmIrqFindRouteTestStatus;
}

#if defined (BUILD_MCU1_0)
/* This function covers the MC/DC coverage of sciclient_direct.c file */
static int32_t SciclientApp_directFuncTest(void)
{
    int32_t  status                    = CSL_PASS;
    int32_t  sciclientInitStatus       = CSL_PASS;
    int32_t  sciclientDirectTestStatus = CSL_PASS;
    uint32_t msg                       = TISCI_MSG_BOARD_CONFIG_PM;
    void     *messageType              = (uint32_t *)&msg;
    uint8_t  boardCfgHeader;
    uint8_t  commonHeader;
    Sciclient_BoardCfgPrms_t SciclientApp_PmRmPrms;
    Sciclient_ReqPrm_t SciclientApp_ReqPrm;
    Sciclient_ConfigPrms_t config      =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
          SciApp_printf ("Sciclient_init PASSED.\n");
          /* Passing response parameter as NULL to cover BADARGS condition for MCDC */
          status = Sciclient_service(&SciclientApp_ReqPrm, NULL);
          if (status == CSL_EBADARGS)
          {
              sciclientDirectTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_service: Negative Arg Test Passed.\n");
          }
          else
          {
             sciclientDirectTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_service: Negative Arg Test Failed.\n");
          }

          /* Passing boardcfgheader parameter as NULL to cover BADARGS condition for MCDC */
          status = Sciclient_boardCfgPrepHeader(&commonHeader, NULL, &SciclientApp_PmRmPrms, &SciclientApp_PmRmPrms);
          if (status == CSL_EBADARGS)
          {
              sciclientDirectTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_boardCfgPrepHeader: Negative Arg Test Passed.\n");
          }
          else
          {
             sciclientDirectTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_boardCfgPrepHeader: Negative Arg Test Failed.\n");
          }

          /* Passing pm parameter as NULL to cover BADARGS condition for MCDC */
          status = Sciclient_boardCfgPrepHeader(&commonHeader, &boardCfgHeader, NULL, &SciclientApp_PmRmPrms);
          if (status == CSL_EBADARGS)
          {
              sciclientDirectTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_boardCfgPrepHeader: Negative Arg Test Passed.\n");
          }
          else
          {
             sciclientDirectTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_boardCfgPrepHeader: Negative Arg Test Failed.\n");
          }

          /* Passing rm parameter as NULL to cover BADARGS condition for MCDC */
          status = Sciclient_boardCfgPrepHeader(&commonHeader, &boardCfgHeader, &SciclientApp_PmRmPrms, NULL);
          if (status == CSL_EBADARGS)
          {
              sciclientDirectTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_boardCfgPrepHeader: Negative Arg Test Passed.\n");
          }
          else
          {
             sciclientDirectTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_boardCfgPrepHeader: Negative Arg Test Failed.\n");
          }

          /* Passing valid parameters to Sciclient_boardCfgPrepHeader function */
          status = Sciclient_boardCfgPrepHeader(&commonHeader, &boardCfgHeader, &SciclientApp_PmRmPrms, &SciclientApp_PmRmPrms);
          if (status == CSL_PASS)
          {
              sciclientDirectTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_boardCfgPrepHeader: Valid Arg Test Passed.\n");
          }
          else
          {
             sciclientDirectTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_boardCfgPrepHeader: Valid Arg Test Failed.\n");
          }

          /* Passing pm parameter as NULL to cover BADARGS condition for MCDC */
          status = Sciclient_boardCfgParseHeader(&commonHeader, NULL, &SciclientApp_PmRmPrms);
          if (status == CSL_EBADARGS)
          {
              sciclientDirectTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_boardCfgParseHeader: Negative Arg Test Passed.\n");
          }
          else
          {
             sciclientDirectTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_boardCfgParseHeader: Negative Arg Test Failed.\n");
          }

          /* Passing rm parameter as NULL to cover BADARGS condition for MCDC */
          status = Sciclient_boardCfgParseHeader(&commonHeader, &SciclientApp_PmRmPrms, NULL);
          if (status == CSL_EBADARGS)
          {
              sciclientDirectTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_boardCfgParseHeader: Negative Arg Test Passed.\n");
          }
          else
          {
             sciclientDirectTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_boardCfgParseHeader: Negative Arg Test Failed.\n");
          }

          /* Passing TISCI_MSG_BOARD_CONFIG_PM as message type will cover default switch condition in Sciclient_ProcessRmMessage */
          status = Sciclient_ProcessRmMessage(messageType);
          if (status == CSL_EFAIL)
          {
              sciclientDirectTestStatus += CSL_PASS;
              SciApp_printf ("Sciclient_ProcessRmMessage: Negative Arg Test Passed.\n");
          }
          else
          {
             sciclientDirectTestStatus += CSL_EFAIL;
             SciApp_printf ("Sciclient_ProcessRmMessage: Negative Arg Test Failed.\n");
          }
    }
    else
    {
        sciclientDirectTestStatus += CSL_EFAIL;
        SciApp_printf ("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            sciclientDirectTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_deinit PASSED.\n");
        }
        else
        {
            sciclientDirectTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_deinit FAILED.\n");
        }
    }

  return sciclientDirectTestStatus;
}

/* This function covers the positive testcases for sciclient_rm.c file */
static int32_t SciclientApp_rmUdmapRingPsilProxyPositiveTest(void)
{
    int32_t  rmUdmapRingPsilProxyPositiveTestStatus                                = 0;
    int32_t  status                                                                = 0;
    int32_t  sciclientInitStatus                                                   = CSL_PASS;
    struct tisci_msg_rm_get_resource_range_req rmGetResourceRangeReq               = {0};
    struct tisci_msg_rm_udmap_gcfg_cfg_req rmUdmapGcfgReq                          = {0};
    struct tisci_msg_rm_psil_pair_req rmPsilPairReq                                = {0};
    struct tisci_msg_rm_psil_read_req rmPsilReadReq                                = {0};
    struct tisci_msg_rm_psil_write_req rmPsilWriteReq                              = {0};
    struct tisci_msg_rm_ring_cfg_req rmRingCfgReq                                  = {0};
    struct tisci_msg_rm_ring_mon_cfg_req rmRingMonCfgReq                           = {0};
    struct tisci_msg_rm_udmap_tx_ch_cfg_req rmUdmapTxChCfgReq                      = {0};
    struct tisci_msg_rm_udmap_rx_ch_cfg_req rmUdmapRxChCfgReq                      = {0};
    struct tisci_msg_rm_udmap_flow_cfg_req rmUdmapFlowCfgReq                       = {0};
    struct tisci_msg_rm_udmap_flow_size_thresh_cfg_req rmUdmapFlowSizeThreshCfgReq = {0};
    struct tisci_msg_rm_proxy_cfg_req rmProxyCfgReq                                = {0};
    struct tisci_msg_rm_get_resource_range_resp rmGetResourceRangeResp;
    struct tisci_msg_rm_udmap_gcfg_cfg_resp rmUdmapGcfgResp;
    struct tisci_msg_rm_psil_unpair_req rmPsilUnpairReq;
    struct tisci_msg_rm_psil_read_resp rmPsilReadResp;
    struct tisci_msg_rm_ring_cfg_resp rmRingCfgResp;
    struct tisci_msg_rm_ring_mon_cfg_resp rmRingMonCfgResp;
    struct tisci_msg_rm_udmap_tx_ch_cfg_resp rmUdmapTxChCfgResp;
    struct tisci_msg_rm_udmap_rx_ch_cfg_resp rmUdmapRxChCfgResp;
    struct tisci_msg_rm_udmap_flow_cfg_resp rmUdmapFlowCfgResp;
    struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp rmUdmapFlowSizeThreshCfgResp;
    Sciclient_ConfigPrms_t SciApp_Config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&SciApp_Config);
    sciclientInitStatus = status;

    if(sciclientInitStatus == CSL_PASS)
    {
        rmGetResourceRangeReq.type           = TISCI_DEV_NAVSS0_INTR;
        rmGetResourceRangeReq.secondary_host = TISCI_HOST_ID_MAIN_0_R5_0;
        status = Sciclient_rmGetResourceRange(&rmGetResourceRangeReq, &rmGetResourceRangeResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmGetResourceRange Test Passed.\n");
        }
        else
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_rmGetResourceRange Test Failed.\n");
        }
        
        rmGetResourceRangeReq.type           = TISCI_DEV_MCU_NAVSS0_RINGACC0;
        rmGetResourceRangeReq.subtype        = TISCI_RESASG_SUBTYPE_RA_UDMAP_TX;
        rmGetResourceRangeReq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status = Sciclient_rmGetResourceRange(&rmGetResourceRangeReq, &rmGetResourceRangeResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmRingCfgReq.nav_id = TISCI_DEV_MCU_NAVSS0_RINGACC0;
            rmRingCfgReq.index  = rmGetResourceRangeResp.range_start;
            status              = Sciclient_rmRingCfg(&rmRingCfgReq, &rmRingCfgResp, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_rmRingCfg Test Passed.\n");
            }
            else
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_rmRingCfg Test Failed.\n");
            }
        }
        else
        {
            SciApp_printf ("Sciclient_rmGetResourceRange() Failed.\n");
        }

        rmGetResourceRangeReq.type           = TISCI_DEV_MCU_NAVSS0_RINGACC0;
        rmGetResourceRangeReq.subtype        = TISCI_RESASG_SUBTYPE_RA_MONITORS;
        rmGetResourceRangeReq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status = Sciclient_rmGetResourceRange(&rmGetResourceRangeReq, &rmGetResourceRangeResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmRingMonCfgReq.nav_id  = TISCI_DEV_MCU_NAVSS0_RINGACC0;
            rmRingMonCfgReq.index   = rmGetResourceRangeResp.range_start;
            status                  = Sciclient_rmRingMonCfg(&rmRingMonCfgReq, &rmRingMonCfgResp, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_rmRingMonCfg Test Passed.\n");
            }
            else
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_rmRingMonCfg Test Failed.\n");
            }
        }
        else
        {
            SciApp_printf ("Sciclient_rmGetResourceRange() Failed.\n");
        }

        rmGetResourceRangeReq.type           = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
        rmGetResourceRangeReq.subtype        = TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN;
        rmGetResourceRangeReq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status = Sciclient_rmGetResourceRange(&rmGetResourceRangeReq, &rmGetResourceRangeResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUdmapTxChCfgReq.nav_id = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
            rmUdmapTxChCfgReq.index  = rmGetResourceRangeResp.range_start;
            status                   = Sciclient_rmUdmapTxChCfg(&rmUdmapTxChCfgReq, &rmUdmapTxChCfgResp, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_rmUdmapTxChCfg Test Passed.\n");
            }
            else
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_rmUdmapTxChCfg Test Failed.\n");
            }
        }
        else
        {
            SciApp_printf ("Sciclient_rmGetResourceRange() Failed.\n");
        }

        rmGetResourceRangeReq.type           = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
        rmGetResourceRangeReq.subtype        = TISCI_RESASG_SUBTYPE_UDMAP_RX_CHAN;
        rmGetResourceRangeReq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status = Sciclient_rmGetResourceRange(&rmGetResourceRangeReq, &rmGetResourceRangeResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUdmapRxChCfgReq.nav_id = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
            rmUdmapRxChCfgReq.index  = rmGetResourceRangeResp.range_start;
            status                   = Sciclient_rmUdmapRxChCfg(&rmUdmapRxChCfgReq, &rmUdmapRxChCfgResp, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_rmUdmapRxChCfg Test Passed.\n");
            }
            else
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_rmUdmapRxChCfg Test Failed.\n");
            }
        }
        else
        {
            SciApp_printf ("Sciclient_rmGetResourceRange() Failed.\n");  
        }

        rmGetResourceRangeReq.type           = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
        rmGetResourceRangeReq.subtype        = TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON;
        rmGetResourceRangeReq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status = Sciclient_rmGetResourceRange(&rmGetResourceRangeReq, &rmGetResourceRangeResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUdmapFlowCfgReq.nav_id      = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
            rmUdmapFlowCfgReq.flow_index  = rmGetResourceRangeResp.range_start;
            status                        = Sciclient_rmUdmapFlowCfg(&rmUdmapFlowCfgReq, &rmUdmapFlowCfgResp, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_rmUdmapFlowCfg Test Passed.\n");
            }
            else
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_rmUdmapFlowCfg Test Failed.\n");
            }
        }
        else
        {
            SciApp_printf ("Sciclient_rmGetResourceRange() Failed.\n");
        }

        rmGetResourceRangeReq.type              = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
        rmGetResourceRangeReq.subtype           = TISCI_RESASG_SUBTYPE_UDMAP_RX_FLOW_COMMON;
        rmGetResourceRangeReq.secondary_host    = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status = Sciclient_rmGetResourceRange(&rmGetResourceRangeReq, &rmGetResourceRangeResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUdmapFlowSizeThreshCfgReq.nav_id      = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
            rmUdmapFlowSizeThreshCfgReq.flow_index  = rmGetResourceRangeResp.range_start;
            status                                  = Sciclient_rmUdmapFlowSizeThreshCfg(&rmUdmapFlowSizeThreshCfgReq, &rmUdmapFlowSizeThreshCfgResp, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_rmUdmapFlowSizeThreshCfg Test Passed.\n");
            }
            else
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_rmUdmapFlowSizeThreshCfg Test Failed.\n");
            }
        }
        else
        {
            SciApp_printf ("Sciclient_rmGetResourceRange() Failed.\n");
        }

        rmGetResourceRangeReq.type           = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
        rmGetResourceRangeReq.subtype        = TISCI_RESASG_SUBTYPE_UDMAP_TX_CHAN;
        rmGetResourceRangeReq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status = Sciclient_rmGetResourceRange(&rmGetResourceRangeReq, &rmGetResourceRangeResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmPsilPairReq.nav_id     = TISCI_DEV_MCU_NAVSS0;
            rmPsilPairReq.src_thread = CSL_PSILCFG_NAVSS_MCU_UDMAP0_STRM_PSILS_THREAD_OFFSET + rmGetResourceRangeResp.range_start;
            rmPsilPairReq.dst_thread = CSL_PSILCFG_NAVSS_MCU_UDMAP0_STRM_PSILD_THREAD_OFFSET + rmGetResourceRangeResp.range_start;
            status                   = Sciclient_rmPsilPair(&rmPsilPairReq, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
                SciApp_printf("Sciclient_rmPsilPair Test Passed.\n");
            }
            else
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
                SciApp_printf("Sciclient_rmPsilPair Test Failed.\n");
            }
        }
        else
        {
            SciApp_printf ("Sciclient_rmGetResourceRange() Failed.\n");
        }

        rmPsilUnpairReq.nav_id     = TISCI_DEV_MCU_NAVSS0;
        rmPsilUnpairReq.src_thread = CSL_PSILCFG_NAVSS_MCU_UDMAP0_STRM_PSILS_THREAD_OFFSET + rmGetResourceRangeResp.range_start;
        rmPsilUnpairReq.dst_thread = CSL_PSILCFG_NAVSS_MCU_UDMAP0_STRM_PSILD_THREAD_OFFSET + rmGetResourceRangeResp.range_start;
        status                     = Sciclient_rmPsilUnpair(&rmPsilUnpairReq, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmPsilUnpair Test Passed.\n");
        }
        else
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmPsilUnpair Test Failed.\n");
        }

        rmPsilReadReq.nav_id = TISCI_DEV_MCU_NAVSS0;
        rmPsilReadReq.thread = CSL_PSILCFG_NAVSS_MCU_UDMAP0_STRM_PSILS_THREAD_OFFSET + rmGetResourceRangeResp.range_start;
        rmPsilReadReq.taddr  = CSL_PSILCFG_REG_ENABLE;
        status               = Sciclient_rmPsilRead(&rmPsilReadReq, &rmPsilReadResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmPsilRead Test Passed.\n");
        }
        else
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmPsilRead Test Failed.\n");
        }

        rmPsilWriteReq.nav_id = TISCI_DEV_MCU_NAVSS0;
        rmPsilWriteReq.thread = CSL_PSILCFG_NAVSS_MCU_UDMAP0_STRM_PSILS_THREAD_OFFSET + rmGetResourceRangeResp.range_start;
        rmPsilWriteReq.taddr  = CSL_PSILCFG_REG_ENABLE;
        rmPsilWriteReq.data   = 1;
        status                = Sciclient_rmPsilWrite(&rmPsilWriteReq, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmPsilWrite Test Passed.\n");
        }
        else
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmPsilWrite Test Failed.\n");
        }

        rmUdmapGcfgReq.nav_id = TISCI_DEV_MCU_NAVSS0_UDMAP_0;
        status                = Sciclient_rmUdmapGcfgCfg(&rmUdmapGcfgReq, &rmUdmapGcfgResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_rmUdmapGcfgCfg Test Passed.\n");
        }
        else
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_rmUdmapGcfgCfg Test Failed.\n");
        }

        rmGetResourceRangeReq.type           = TISCI_DEV_MCU_NAVSS0_PROXY0;
        rmGetResourceRangeReq.subtype        = TISCI_RESASG_SUBTYPE_PROXY_PROXIES;
        rmGetResourceRangeReq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status = Sciclient_rmGetResourceRange(&rmGetResourceRangeReq, &rmGetResourceRangeResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmProxyCfgReq.nav_id = TISCI_DEV_MCU_NAVSS0_PROXY0;
            rmProxyCfgReq.index  = rmGetResourceRangeResp.range_start;
            status               = Sciclient_rmSetProxyCfg(&rmProxyCfgReq, SCICLIENT_SERVICE_WAIT_FOREVER);
            if(status == CSL_PASS)
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
                SciApp_printf ("Sciclient_rmSetProxyCfg Test Passed.\n");
            }
            else
            {
                rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
                SciApp_printf ("Sciclient_rmSetProxyCfg Test Failed.\n");
            }
        }
        else
        {
            SciApp_printf ("Sciclient_rmGetResourceRange() Failed.\n");
        }
    }
    else
    {
        rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
        SciApp_printf ("Sciclient_init Failed.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_deinit Passed.\n");
        }
        else
        {
            rmUdmapRingPsilProxyPositiveTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_deinit Failed.\n");
        }
    }

    return rmUdmapRingPsilProxyPositiveTestStatus;
}

/* This function covers the positive testcase for UnmappedVintRouteCreate() */
static int32_t SciclientApp_rmUnmappedVintRouteCreatePositiveTest(void)
{
    int32_t  status                                                        = CSL_PASS;
    int32_t  sciclientInitStatus                                           = CSL_PASS;
    uint16_t intNum                                                        = 0U;
    int32_t  rmUnmappedVintRouteCreatePositiveTestStatus                   = CSL_PASS;
    const struct tisci_msg_rm_irq_set_resp Sciclient_Resp                  = {0};
    struct tisci_msg_rm_get_resource_range_req rmGetResourceRangeReqVint   = {0};
    struct tisci_msg_rm_get_resource_range_req rmGetResourceRangeReqGlobal = {0};
    struct tisci_msg_rm_get_resource_range_req rmGetResourceRangeReqIrq    = {0};
    struct tisci_msg_rm_get_resource_range_resp rmGetResourceRangeRespVint;
    struct tisci_msg_rm_get_resource_range_resp rmGetResourceRangeRespGlobal;
    struct tisci_msg_rm_get_resource_range_resp rmGetResourceRangeRespIrq;
    Sciclient_ConfigPrms_t config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf("Sciclient_init PASSED.\n");
        rmGetResourceRangeReqVint.type           = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0;
        rmGetResourceRangeReqVint.subtype        = TISCI_RESASG_SUBTYPE_IA_VINT;
        rmGetResourceRangeReqVint.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status  = Sciclient_rmGetResourceRange(&rmGetResourceRangeReqVint,
                                               &rmGetResourceRangeRespVint,
                                               SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            rmUnmappedVintRouteCreatePositiveTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmGetResourceRange() execution is successful for vint\n");
        }
        else
        {
            rmUnmappedVintRouteCreatePositiveTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmGetResourceRange() execution is failed for vint\n");
        }
        
        rmGetResourceRangeReqGlobal.type           = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0;
        rmGetResourceRangeReqGlobal.subtype        = TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT;
        rmGetResourceRangeReqGlobal.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status  = Sciclient_rmGetResourceRange(&rmGetResourceRangeReqGlobal,
                                               &rmGetResourceRangeRespGlobal,
                                               SCICLIENT_SERVICE_WAIT_FOREVER);    
        if(status == CSL_PASS)
        {
            rmUnmappedVintRouteCreatePositiveTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmGetResourceRange() execution is successful for globalevent\n");
        }
        else
        {
            rmUnmappedVintRouteCreatePositiveTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmGetResourceRange() execution is failed for globalevent\n");
        } 

        rmGetResourceRangeReqIrq.type           = TISCI_DEV_MCU_NAVSS0_INTR;
        rmGetResourceRangeReqIrq.subtype        = TISCI_RESASG_SUBTYPE_IR_OUTPUT;
        rmGetResourceRangeReqIrq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status  = Sciclient_rmGetResourceRange(&rmGetResourceRangeReqIrq,
                                               &rmGetResourceRangeRespIrq,
                                               SCICLIENT_SERVICE_WAIT_FOREVER);  

        if(status == CSL_PASS)
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is successful\n");
            status = Sciclient_rmIrqTranslateIrOutput(rmGetResourceRangeReqIrq.type,
                                                      rmGetResourceRangeRespIrq.range_start,
                                                      TISCI_DEV_MCU_R5FSS0_CORE0,
                                                      &intNum);
            if(status == CSL_PASS)
            {
                SciApp_printf("Sciclient_rmIrqTranslateIrOutput() execution is successful and host interrupt number is %d\n", intNum);
                const struct tisci_msg_rm_irq_set_req Sciclient_Req =
                {
                    .valid_params          = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                             TISCI_MSG_VALUE_RM_IA_ID_VALID  | TISCI_MSG_VALUE_RM_VINT_VALID,
                    .src_id                = TISCI_DEV_MCU_NAVSS0_MCRC_0,
                    .src_index             = 0U,
                    .dst_id                = TISCI_DEV_MCU_R5FSS0_CORE0,
                    .dst_host_irq          = intNum,
                    .global_event          = rmGetResourceRangeRespGlobal.range_start,
                    .ia_id                 = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0,
                    .vint                  = rmGetResourceRangeRespVint.range_start,
                    .vint_status_bit_index = 0U
                };
                status = Sciclient_rmProgramInterruptRoute(&Sciclient_Req, &Sciclient_Resp, SCICLIENT_SERVICE_WAIT_FOREVER);
                if (status == CSL_PASS)
                {
                    rmUnmappedVintRouteCreatePositiveTestStatus += CSL_PASS;
                    SciApp_printf("Sciclient_rmProgramInterruptRoute: Valid Arg Test Passed.\n");
                }
                else
                {
                    rmUnmappedVintRouteCreatePositiveTestStatus += CSL_EFAIL;
                    SciApp_printf("Sciclient_rmProgramInterruptRoute: Valid Arg Test Failed.\n");
                }
            }
            else
            {
                SciApp_printf("Sciclient_rmIrqTranslateIrOutput() has failed\n");
            }
        }
        else
        {
            SciApp_printf("Sciclient_rmGetResourceRange() has failed\n");
        }
    }
    else
    {
        rmUnmappedVintRouteCreatePositiveTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmUnmappedVintRouteCreatePositiveTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmUnmappedVintRouteCreatePositiveTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return rmUnmappedVintRouteCreatePositiveTestStatus;
}

static int32_t SciclientApp_secureProxyNegTest(void)
{
  int32_t status                      = CSL_PASS;
  int32_t sciclientInitStatus         = CSL_PASS;
  int32_t secureProxyTestStatus       = CSL_PASS;
  uint32_t thread                     = TISCI_SEC_PROXY_MCU_0_R5_0_READ_NOTIFY_THREAD_ID;
  uint32_t threadAddr                 = 0U;
  uint32_t regVal                     = 0U;
  uint32_t gSciclient_maxMsgSizeBytes = 0U;
  uint32_t timeout                    = 2U;
  Sciclient_ConfigPrms_t config       =
  {
     SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
     NULL,
     0 /* isSecure = 0 un secured for all cores */
  };

  while (gSciclientHandle.initCount != 0)
  {
      status = Sciclient_deinit();
  }
  status = Sciclient_init(&config);
  sciclientInitStatus = status;

  if(status == CSL_PASS)
  {
      SciApp_printf("Sciclient_init PASSED.\n");
      
      /* Setting up MSB in thread value to fail Sciclient_verifyThread() */
      gSciclient_maxMsgSizeBytes = CSL_secProxyGetMaxMsgSize(pSciclient_secProxyCfg) - CSL_SEC_PROXY_RSVD_MSG_BYTES;
      threadAddr = CSL_secProxyGetDataAddr(pSciclient_secProxyCfg, thread, 0U) + ((uintptr_t) gSciclient_maxMsgSizeBytes  - (uintptr_t) 4U);
      regVal = HW_RD_REG32(threadAddr);
      regVal = regVal | 0x8000000;
      HW_WR_REG32(threadAddr, regVal);
      status = Sciclient_verifyThread(thread);
      if (status == CSL_EFAIL)
      {
          secureProxyTestStatus += CSL_PASS;
          SciApp_printf("Sciclient_verifyThread: Negative Arg Test Passed.\n");
      }
      else
      {
          secureProxyTestStatus += CSL_EFAIL;
          SciApp_printf("Sciclient_verifyThread: Negative Arg Test Failed.\n");
      }
      
      /* Less timeout is given */
      status = Sciclient_waitThread(thread, timeout);
      if (status == CSL_ETIMEOUT)
      {
          secureProxyTestStatus += CSL_PASS;
          SciApp_printf("Sciclient_waitThread: Negative Arg Test Passed.\n");
      }
      else
      {
          secureProxyTestStatus += CSL_EFAIL;
          SciApp_printf("Sciclient_waitThread: Negative Arg Test Failed.\n");
      }
      
      /* 0 timeout is given */
      status = Sciclient_waitThread(thread, SCICLIENT_SERVICE_NO_WAIT);
      if (status == CSL_ETIMEOUT)
      {
          secureProxyTestStatus += CSL_PASS;
          SciApp_printf("Sciclient_waitThread: Negative Arg Test Passed.\n");
      }
      else
      {
          secureProxyTestStatus += CSL_EFAIL;
          SciApp_printf("Sciclient_waitThread: Negative Arg Test Failed.\n");
      }
      
      /* Few NULL, 0U Arguments and appropriate gSciclient_maxMsgSizeBytes argument is passed
         to Sciclient_sendMessage */
      gSciclient_maxMsgSizeBytes = 8U;
      Sciclient_sendMessage(thread, NULL, 0U, NULL, NULL, 0U, gSciclient_maxMsgSizeBytes);
  }
  else
  {
      secureProxyTestStatus += CSL_EFAIL;
      SciApp_printf("Sciclient_init FAILED.\n");
  }
  
  if(sciclientInitStatus == CSL_PASS)
  {
      status = Sciclient_deinit();
      if(status == CSL_PASS)
      {
          secureProxyTestStatus += CSL_PASS;
          SciApp_printf("Sciclient_deinit PASSED.\n");
      }
      else
      {
          secureProxyTestStatus += CSL_EFAIL;
          SciApp_printf("Sciclient_deinit FAILED.\n");
      }
  }

  return secureProxyTestStatus;
}

static int32_t SciclientApp_rmIrqVintDeleteNegTest(void)
{
    int32_t  status                         = CSL_PASS;
    int32_t  sciclientInitStatus            = CSL_PASS;
    int32_t  rmIrqVintDeleteTestStatus      = CSL_PASS;
    uint16_t intNum                         = 0U;
    struct tisci_msg_rm_get_resource_range_req Sciclient_ReqVint;
    struct tisci_msg_rm_get_resource_range_resp Sciclient_ResVint;
    struct tisci_msg_rm_get_resource_range_req Sciclient_ReqGlobal;
    struct tisci_msg_rm_get_resource_range_resp Sciclient_ResGlobal;
    struct tisci_msg_rm_get_resource_range_req Sciclient_ReqIrq;
    struct tisci_msg_rm_get_resource_range_resp Sciclient_ResIrq;
    struct tisci_msg_rm_irq_release_resp Sciclient_Resp;
    Sciclient_ConfigPrms_t config           =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf("Sciclient_init PASSED.\n");
        Sciclient_ReqVint.type       = TISCI_DEV_NAVSS0_UDMASS_INTAGG;
        Sciclient_ReqVint.subtype    = TISCI_RESASG_SUBTYPE_IA_VINT;
        status  = Sciclient_rmGetResourceRange(&Sciclient_ReqVint, &Sciclient_ResVint, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is successful for vint\n");
        }
        else
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is failed for vint\n");
        }

        Sciclient_ReqGlobal.type       = TISCI_DEV_NAVSS0_UDMASS_INTAGG;
        Sciclient_ReqGlobal.subtype    = TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT;
        status  = Sciclient_rmGetResourceRange(&Sciclient_ReqGlobal, &Sciclient_ResGlobal, SCICLIENT_SERVICE_WAIT_FOREVER);    
        if(status == CSL_PASS)
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is successful for globalevent\n");
        }
        else
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is failed for globalevent\n");
        } 

        Sciclient_ReqIrq.type           = TISCI_DEV_NAVSS0_INTR;
        Sciclient_ReqIrq.subtype        = TISCI_RESASG_SUBTYPE_IR_OUTPUT;
        Sciclient_ReqIrq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status  = Sciclient_rmGetResourceRange(&Sciclient_ReqIrq, &Sciclient_ResIrq, SCICLIENT_SERVICE_WAIT_FOREVER);

        if(status == CSL_PASS)
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is successful\n");
            status = Sciclient_rmIrqTranslateIrOutput(Sciclient_ReqIrq.type,
                                                      Sciclient_ResIrq.range_start,
                                                      TISCI_DEV_MCU_R5FSS0_CORE0,
                                                      &intNum);
            if(status == CSL_PASS)
            {
                SciApp_printf("Sciclient_rmIrqTranslateIrOutput() execution is successful and host interrupt number is %d\n", intNum);
                const struct tisci_msg_rm_irq_release_req Sciclient_Req =
                {
                    .valid_params          = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                             TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID |
                                             TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID,
                    .src_id                = TISCI_DEV_NAVSS0_MAILBOX,
                    .src_index             = 0U,
                    .dst_id                = TISCI_DEV_MCU_R5FSS0_CORE0,
                    .dst_host_irq          = intNum,
                    .global_event          = Sciclient_ResGlobal.range_start,
                    .ia_id                 = TISCI_DEV_NAVSS0_UDMASS_INTAGG,
                    .vint                  = Sciclient_ResVint.range_start,
                    .vint_status_bit_index = 0U
                };
                /* No events are present for TISCI_DEV_NAVSS0_UDMASS_INTAGG, so Sciclient_rmIrqVintDelete
                   returns CSL_EBADARGS since no events are there to unmap */
                status = Sciclient_rmClearInterruptRoute(&Sciclient_Req, &Sciclient_Resp, SCICLIENT_SERVICE_WAIT_FOREVER);
                if (status == CSL_EBADARGS)
                {
                    rmIrqVintDeleteTestStatus += CSL_PASS;
                    SciApp_printf("Sciclient_rmClearInterruptRoute: rmIrqVintDelete Test Passed.\n");
                }
                else
                {
                    rmIrqVintDeleteTestStatus += CSL_EFAIL;
                    SciApp_printf("Sciclient_rmClearInterruptRoute: rmIrqVintDelete Test Failed.\n");
                }
            }
            else
            {
                rmIrqVintDeleteTestStatus += CSL_EFAIL;
                SciApp_printf("Sciclient_rmIrqTranslateIrOutput() has failed\n");
            }
        }
        else
        {
            rmIrqVintDeleteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmGetResourceRange() has failed\n");
        }
    }
    else
    {
        rmIrqVintDeleteTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmIrqVintDeleteTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmIrqVintDeleteTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return rmIrqVintDeleteTestStatus;
}

static int32_t SciclientApp_rmIaValidateEvtTest(void)
{
    int32_t  status                         = CSL_PASS;
    int32_t  sciclientInitStatus            = CSL_PASS;
    int32_t  rmIaValidateEvtTestStatus      = CSL_PASS;
    uint16_t intNum                         = 0U;
    struct tisci_msg_rm_get_resource_range_req Sciclient_ReqVint;
    struct tisci_msg_rm_get_resource_range_resp Sciclient_ResVint;
    struct tisci_msg_rm_get_resource_range_req Sciclient_ReqGlobal;
    struct tisci_msg_rm_get_resource_range_resp Sciclient_ResGlobal;
    struct tisci_msg_rm_get_resource_range_req Sciclient_ReqIrq;
    struct tisci_msg_rm_get_resource_range_resp Sciclient_ResIrq;
    struct tisci_msg_rm_irq_set_resp Sciclient_Resp;
    Sciclient_ConfigPrms_t config           =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf("Sciclient_init PASSED.\n");
        Sciclient_ReqVint.type       = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0;
        Sciclient_ReqVint.subtype    = TISCI_RESASG_SUBTYPE_IA_VINT;
        status  = Sciclient_rmGetResourceRange(&Sciclient_ReqVint, &Sciclient_ResVint, SCICLIENT_SERVICE_WAIT_FOREVER);
        if(status == CSL_PASS)
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is successful for vint\n");
        }
        else
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is failed for vint\n");
        }

        Sciclient_ReqGlobal.type       = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0;
        Sciclient_ReqGlobal.subtype    = TISCI_RESASG_SUBTYPE_GLOBAL_EVENT_SEVT;
        status  = Sciclient_rmGetResourceRange(&Sciclient_ReqGlobal, &Sciclient_ResGlobal, SCICLIENT_SERVICE_WAIT_FOREVER);    
        if(status == CSL_PASS)
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is successful for globalevent\n");
        }
        else
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is failed for globalevent\n");
        } 

        Sciclient_ReqIrq.type           = TISCI_DEV_MCU_NAVSS0_INTR;
        Sciclient_ReqIrq.subtype        = TISCI_RESASG_SUBTYPE_IR_OUTPUT;
        Sciclient_ReqIrq.secondary_host = TISCI_MSG_VALUE_RM_UNUSED_SECONDARY_HOST;
        status  = Sciclient_rmGetResourceRange(&Sciclient_ReqIrq, &Sciclient_ResIrq, SCICLIENT_SERVICE_WAIT_FOREVER);  
        if(status == CSL_PASS)
        {
            SciApp_printf("Sciclient_rmGetResourceRange() execution is successful\n");
            status = Sciclient_rmIrqTranslateIrOutput(Sciclient_ReqIrq.type, Sciclient_ResIrq.range_start, TISCI_DEV_MCU_R5FSS0_CORE0, &intNum);
            if(status == CSL_PASS)
            {
                const struct tisci_msg_rm_irq_set_req Sciclient_Req =
                {
                    .valid_params          = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                             TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID |
                                             TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID,
                    .src_id                = TISCI_DEV_MCU_NAVSS0_MCRC_0,
                    .src_index             = 0U,
                    .dst_id                = TISCI_DEV_MCU_R5FSS0_CORE0,
                    .dst_host_irq          = intNum,
                    .global_event          = Sciclient_ResGlobal.range_start + Sciclient_ResGlobal.range_num + 16400U, /* Invalid global event value for TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 */
                    .ia_id                 = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0,
                    .vint                  = Sciclient_ResVint.range_start,
                    .vint_status_bit_index = 0U
                };
                /* Passing invalid global event value to cover Sciclient_rmIaEvtRomMapped function from Sciclient_rmIaValidateEvt */
                status = Sciclient_rmProgramInterruptRoute(&Sciclient_Req, &Sciclient_Resp, SCICLIENT_SERVICE_WAIT_FOREVER);
                if (status == CSL_EFAIL)
                {
                    rmIaValidateEvtTestStatus += CSL_PASS;
                    SciApp_printf("Sciclient_rmProgramInterruptRoute: Valid Arg Test Passed.\n");
                }
                else
                {
                    rmIaValidateEvtTestStatus += CSL_EFAIL;
                    SciApp_printf("Sciclient_rmProgramInterruptRoute: Valid Arg Test Failed.\n");
                }
                const struct tisci_msg_rm_irq_set_req Sciclient_Req1 =
                {
                    .valid_params          = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                                             TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID |
                                             TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID,
                    .src_id                = TISCI_DEV_MCU_NAVSS0_MCRC_0,
                    .src_index             = 0U,
                    .dst_id                = TISCI_DEV_MCU_R5FSS0_CORE0,
                    .dst_host_irq          = intNum,
                    .global_event          = Sciclient_ResGlobal.range_start,
                    .ia_id                 = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0,
                    .vint                  = Sciclient_ResVint.range_start,
                    .vint_status_bit_index = 0U
                };
                /* Passing these parameters can cover Sciclient_rmIaValidateEvt badargs condition */
                status = Sciclient_rmProgramInterruptRoute(&Sciclient_Req1, &Sciclient_Resp, SCICLIENT_SERVICE_WAIT_FOREVER);
                if (status == CSL_EFAIL)
                {
                    rmIaValidateEvtTestStatus += CSL_PASS;
                    SciApp_printf("Sciclient_rmProgramInterruptRoute: Arg Test Passed.\n");
                }
                else
                {
                    rmIaValidateEvtTestStatus += CSL_EFAIL;
                    SciApp_printf("Sciclient_rmProgramInterruptRoute: Arg Test Failed.\n");
                }
            }
            else
            {
                rmIaValidateEvtTestStatus += CSL_EFAIL;
                SciApp_printf("Sciclient_rmIrqTranslateIrOutput() has failed\n");
            }
        }
        else
        {
            rmIaValidateEvtTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmGetResourceRange() has failed\n");
        }
    }
    else
    {
        rmIaValidateEvtTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmIaValidateEvtTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmIaValidateEvtTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return rmIaValidateEvtTestStatus;
}
#endif

static int32_t SciclientApp_rmIaVintGetInfoNegTest(void)
{
    int32_t  status                                     = CSL_PASS;
    int32_t  sciclientInitStatus                        = CSL_PASS;
    int32_t  rmIaVintGetInfoTestStatus                  = CSL_PASS;
    const struct tisci_msg_rm_irq_set_req Sciclient_Req =
    {
        .valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                          TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID,
        .ia_id          = TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0,
        .vint           = 300U /* Invalid vint value for TISCI_DEV_MCU_NAVSS0_UDMASS_INTA_0 */
    };
    struct tisci_msg_rm_irq_set_resp Sciclient_Resp;
    Sciclient_ConfigPrms_t config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
        SciApp_printf("Sciclient_init PASSED.\n");
        /* Passing invalid vint value(greater than the vint value of ia_id) to cover the badargs condition for Sciclient_rmIaVintGetInfo */
        status = Sciclient_rmProgramInterruptRoute(&Sciclient_Req, &Sciclient_Resp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EBADARGS)
        {
            rmIaVintGetInfoTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmIaVintGetInfoTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmIaVintGetInfoTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmIaVintGetInfoTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmIaVintGetInfoTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return rmIaVintGetInfoTestStatus;
}

static int32_t SciclientApp_rmIrqIsVintRouteSetNegTest(void)
{
    int32_t  status                                     = CSL_PASS;
    int32_t  sciclientInitStatus                        = CSL_PASS;
    int32_t  rmIrqIsVintRouteSetTestStatus              = CSL_PASS;
    const struct tisci_msg_rm_irq_set_req Sciclient_Req =
    {
        .valid_params   = TISCI_MSG_VALUE_RM_DST_ID_VALID | TISCI_MSG_VALUE_RM_DST_HOST_IRQ_VALID |
                          TISCI_MSG_VALUE_RM_IA_ID_VALID | TISCI_MSG_VALUE_RM_VINT_VALID |
                          TISCI_MSG_VALUE_RM_GLOBAL_EVENT_VALID | TISCI_MSG_VALUE_RM_VINT_STATUS_BIT_INDEX_VALID,
        .ia_id          = TISCI_DEV_NAVSS0_MODSS_INTAGG,
        .vint           = 200U /* Invalid vint value for TISCI_DEV_NAVSS0_MODSS_INTAGG */
    };
    struct tisci_msg_rm_irq_set_resp Sciclient_Resp;
    Sciclient_ConfigPrms_t config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

     while (gSciclientHandle.initCount != 0)
     {
         status = Sciclient_deinit();
     }
     status = Sciclient_init(&config);
     sciclientInitStatus = status;

     if(status == CSL_PASS)
     {
        SciApp_printf("Sciclient_init PASSED.\n");
        /* "IR input tied to the IA VINT is in use" check will fail by passing invalid vint value to Sciclient_rmIrqIsVintRouteSet */
        status = Sciclient_rmProgramInterruptRoute(&Sciclient_Req, &Sciclient_Resp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_EFAIL)
        {
            rmIrqIsVintRouteSetTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Passed.\n");
        }
        else
        {
            rmIrqIsVintRouteSetTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_rmProgramInterruptRoute: Negative Arg Test Failed.\n");
        }
    }
    else
    {
        rmIrqIsVintRouteSetTestStatus += CSL_EFAIL;
        SciApp_printf("Sciclient_init FAILED.\n");
    }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            rmIrqIsVintRouteSetTestStatus += CSL_PASS;
            SciApp_printf("Sciclient_deinit PASSED.\n");
        }
        else
        {
            rmIrqIsVintRouteSetTestStatus += CSL_EFAIL;
            SciApp_printf("Sciclient_deinit FAILED.\n");
        }
    }

  return rmIrqIsVintRouteSetTestStatus;
}

static int32_t SciclientApp_firewallPositiveTest(void)
{
    int32_t status                       = CSL_PASS;
    int32_t sciclientInitStatus          = CSL_PASS;
    int32_t firewallPositiveTestStatus   = CSL_PASS;
    struct tisci_msg_fwl_get_firewall_region_resp getFirewallRegionResp;
    struct tisci_msg_fwl_get_firewall_region_req getFirewallRegionReq =
    {
        .fwl_id            = SCICLIENT_APP_DRAM_FWL_ID,
        .region            = 0,
        .n_permission_regs = 3
    };
    Sciclient_ConfigPrms_t SciApp_Config =
    {
       SCICLIENT_SERVICE_OPERATION_MODE_INTERRUPT,
       NULL,
       0 /* isSecure = 0 un secured for all cores */
    };

    while (gSciclientHandle.initCount != 0U)
    {
        status = Sciclient_deinit();
    }
    status = Sciclient_init(&SciApp_Config);
    sciclientInitStatus = status;

    if(status == CSL_PASS)
    {
        SciApp_printf ("Sciclient_init PASSED.\n");
        status = Sciclient_firewallGetRegion(&getFirewallRegionReq, &getFirewallRegionResp, SCICLIENT_SERVICE_WAIT_FOREVER);
        if (status == CSL_PASS)
        {
            firewallPositiveTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_firewallGetRegion: Positive Arg Test Passed.\n");
        }
        else
        {
            firewallPositiveTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_firewallGetRegion: Positive Arg Test Failed.\n");
        }

     }
     else
     {
         firewallPositiveTestStatus += CSL_EFAIL;
         SciApp_printf ("Sciclient_init FAILED.\n");
     }

    if(sciclientInitStatus == CSL_PASS)
    {
        status = Sciclient_deinit();
        if(status == CSL_PASS)
        {
            firewallPositiveTestStatus += CSL_PASS;
            SciApp_printf ("Sciclient_deinit PASSED.\n");
        }
        else
        {
            firewallPositiveTestStatus += CSL_EFAIL;
            SciApp_printf ("Sciclient_deinit FAILED.\n");
        }
    }

   return firewallPositiveTestStatus;
}

static int32_t SciclientApp_sciclientMcdcTest(void)
{
  int32_t  status               = CSL_PASS;
  int32_t  sciclientInitStatus  = CSL_PASS;
  int32_t  sciclientTestStatus  = CSL_PASS;
  Sciclient_ConfigPrms_t config =
  {
     SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
     NULL,
     0 /* isSecure = 0 un secured for all cores */
  };
  Sciclient_ReqPrm_t reqPrms;
  Sciclient_RespPrm_t respPrms;
  while (gSciclientHandle.initCount != 0)
  {
      status = Sciclient_deinit();
  }
  status = Sciclient_init(&config);
  sciclientInitStatus = status;

  if(status == CSL_PASS)
  {
      SciApp_printf("Sciclient_init PASSED.\n");
      
      //setting up PM and RM boardcfg parameters
#if defined(BUILD_MCU1_0)
  Sciclient_BoardCfgPrms_t  pmBoardCfgParams = {
        .boardConfigLow  = SCICLIENT_ALLOWED_BOARDCFG_BASE_START - 1U,
        .boardConfigHigh = 0U,
        .boardConfigSize = SCICLIENT_BOARDCFG_PM_SIZE_IN_BYTES,
        .devGrp          = DEVGRP_ALL
  };
  Sciclient_BoardCfgPrms_t rmBoardCfgParams =  {
        .boardConfigLow  = SCICLIENT_ALLOWED_BOARDCFG_BASE_START,
        .boardConfigHigh = 0,
        .boardConfigSize = SCICLIENT_BOARDCFG_RM_SIZE_IN_BYTES,
        .devGrp          = DEVGRP_ALL  
  };
      status = Sciclient_boardCfgPm(&pmBoardCfgParams);
      if(status == CSL_PASS)
      {
          sciclientTestStatus += CSL_PASS;
          SciApp_printf("Sciclient_boardCfgPm(): Execution successful\n");
      }
      else
      {
          sciclientTestStatus += CSL_EFAIL;
          SciApp_printf("Sciclient_boardCfgPm(): Execution failed\n");
      }
      
      status = Sciclient_boardCfgRm(&rmBoardCfgParams);
      if(status == CSL_PASS)
      {
          sciclientTestStatus += CSL_PASS;
          SciApp_printf("Sciclient_boardCfgRm(): Execution successful\n");
      }
      else
      {
          sciclientTestStatus += CSL_EFAIL;
          SciApp_printf("Sciclient_boardCfgRm(): Execution failed\n");
      }
      
      status = Sciclient_configPrmsInit(&config);
      if(status == CSL_PASS)
      {
          sciclientTestStatus += CSL_PASS;
          SciApp_printf("Sciclient_configPrmsInit test Passed\n");
      }
      else
      {
          sciclientTestStatus += CSL_EFAIL;
          SciApp_printf("Sciclient_configPrmsInit test Failed\n");
      }          
#endif
          
          //passing invalid arguments
          while (gSciclientHandle.initCount != 0)
          {
              status = Sciclient_deinit();
          }
          config.opModeFlag = 2U;
          status = Sciclient_init(&config);
          if(status == CSL_EBADARGS)
          {
              sciclientTestStatus += CSL_PASS;
              SciApp_printf("Sciclient_init Negative test Passed\n");
          }
          else
          {
              sciclientTestStatus += CSL_EFAIL;
              SciApp_printf("Sciclient_init Negative test Failed\n");
          }
          
          while (gSciclientHandle.initCount != 0)
          {
              status = Sciclient_deinit();
          }
          config.opModeFlag = SCICLIENT_SERVICE_OPERATION_MODE_POLLED;
          config.isSecureMode = 2U;
          status = Sciclient_init(&config);
          if(status == CSL_EBADARGS)
          {
              sciclientTestStatus += CSL_PASS;
              SciApp_printf("Sciclient_init Negative test Passed\n");
          }
          else
          {
              sciclientTestStatus += CSL_EFAIL;
              SciApp_printf("Sciclient_init Negative test Failed\n");
          }
          
          //passing NULL argument
          while (gSciclientHandle.initCount != 0)
          {
              status = Sciclient_deinit();
          }
          status = Sciclient_serviceSecureProxy(&reqPrms, NULL);
          if(status == CSL_EBADARGS)
          {
              sciclientTestStatus += CSL_PASS;
              SciApp_printf("Sciclient_serviceGetPayloadSize Negative test Passed\n");
          }
          else
          {
              sciclientTestStatus += CSL_EFAIL;
              SciApp_printf("Sciclient_serviceGetPayloadSize Negative test Failed\n");
          }
          
          reqPrms.pReqPayload = NULL;
          reqPrms.reqPayloadSize = sizeof(reqPrms.pReqPayload);
          status = Sciclient_serviceSecureProxy(&reqPrms, &respPrms);
          if(status == CSL_EBADARGS)
          {
              sciclientTestStatus += CSL_PASS;
              SciApp_printf("Sciclient_serviceGetPayloadSize Negative test Passed\n");
          }
          else
          {
              sciclientTestStatus += CSL_EFAIL;
              SciApp_printf("Sciclient_serviceGetPayloadSize Negative test Failed\n");
          }
                    
          //passing TISCI_MSG_ALLOW_FWL_CTRL_READ message type
          status = Sciclient_getCurrentContext(TISCI_MSG_ALLOW_FWL_CTRL_READ);
          if(status == SCICLIENT_CONTEXT_SEC)
          {
              sciclientTestStatus += CSL_PASS;
              SciApp_printf("Sciclient_getCurrentContext test Passed\n");
          }
          else
          {
              sciclientTestStatus += CSL_EFAIL;
              SciApp_printf("Sciclient_serviceGetPayloadSize test Failed\n");
          }
          
          //passing TISCI_MSG_FORBID_FWL_CTRL_READ message type
          status = Sciclient_getCurrentContext(TISCI_MSG_FORBID_FWL_CTRL_READ);
          if(status == SCICLIENT_CONTEXT_SEC)
          {
              sciclientTestStatus += CSL_PASS;
              SciApp_printf("Sciclient_getCurrentContext test Passed\n");
          }
          else
          {
              sciclientTestStatus += CSL_EFAIL;
              SciApp_printf("Sciclient_serviceGetPayloadSize test Failed\n");
          }
  }
  else
  {
      sciclientTestStatus += CSL_EFAIL;
      SciApp_printf("Sciclient_init FAILED.\n");
  }

  if(sciclientInitStatus == CSL_PASS)
  {
      status = Sciclient_deinit();
      if(status == CSL_PASS)
      {
          sciclientTestStatus += CSL_PASS;
          SciApp_printf("Sciclient_deinit PASSED.\n");
      }
      else
      {
          sciclientTestStatus += CSL_EFAIL;
          SciApp_printf("Sciclient_deinit FAILED.\n");
      }
  }

  return sciclientTestStatus;
}

#if defined(BUILD_MPU) || defined (BUILD_C7X)
extern void Osal_initMmuDefault(void);
void InitMmu(void)
{
    Osal_initMmuDefault();
}
#endif
