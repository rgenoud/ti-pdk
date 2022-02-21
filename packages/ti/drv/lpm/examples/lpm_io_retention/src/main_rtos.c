/*
*
* Copyright (c) 2021 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

/* FreeRTOS Header files */
#include <ti/osal/osal.h>
#include <ti/osal/src/nonos/Nonos_config.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/HwiP.h>

#include <ti/csl/soc.h>
#include <ti/csl/cslr_pmmc.h>
#include <dmsc_cm.h>
#include <dev_info.h>
#include <lpm_mmr_functions.h>
#include <ti/drv/lpm/include/lpm_pmic.h>
#include <ti/drv/lpm/lpm.h>
#include <ti/drv/gpio/soc/GPIO_soc.h>

#include <ti/drv/sciclient/sciserver_tirtos.h>
#include <ti/drv/uart/UART_stdio.h>

#include <ti/drv/lpm/include/io_retention/dev_info.h>

#if (defined(SOC_J721E) || defined(SOC_J7200))
Board_I2cInitCfg_t boardI2cInitCfg = {0, BOARD_SOC_DOMAIN_WKUP, false};
#endif

/* Test application stack size */
#define APP_TASK_STACK                  (20U * 1024U)
/**< Stack required for the stack */
#define MAIN_APP_TASK_PRIORITY          (2)


/*********************************  *************************************
 ************************** Internal functions ************************
 **********************************************************************/
int main_io_pm_seq (void);
void main_configure_can_uart_lock_dmsc();
void wkup_configure_can_uart_lock_dmsc();

int32_t SetupSciServer(void);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

TaskP_Handle mainAppTask;
TaskP_Params mainAppTaskParams;
static uint8_t MainApp_TaskStack[APP_TASK_STACK] __attribute__((aligned(32)));
extern GPIO_v0_Config GPIO_v0_config;

/* Board specific definitions */
#define io_timeout  150

/* Boot defines */
#define COLD_BOOT (0x0)
#define IO_RETENTION_BOOT (0x1)
uint32_t global_boot_mode_status = COLD_BOOT;


int io_retention_main()
{
    int ret = 0;
    Board_IDInfo_v2 info = {0};
    int32_t stat = BOARD_SOK;
    int c;
    int done = 0;

    Board_setI2cInitConfig(&boardI2cInitCfg);
    stat = Board_getIDInfo_v2(&info, BOARD_I2C_EEPROM_ADDR);

    if(stat == BOARD_INVALID_PARAM)
    {
        stat = BOARD_SOK;
    }

    /* WKUP GPIO 77 (TP for benchmarking) */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C120) = 0x0C018007;


    if(stat == BOARD_SOK)
    {

        Lpm_pmicInit();
        AppUtils_Printf(MSG_NORMAL, "Press 1 to enter low power mode with MAIN IO Retention configured\n");
        AppUtils_Printf(MSG_NORMAL, "Press 2 to enter low power mode with MCU IO Retention configured\n");
        AppUtils_Printf(MSG_NORMAL, "Press 3 to enter low power mode with both MCU & MAIN IO Retention configured\n");
        AppUtils_Printf(MSG_NORMAL, "Input: ");

        while(!done)
        {
            UART_scanFmt("%d", &c);

            switch (c)
            {
                case 1:
                    main_configure_can_uart_lock_dmsc();
                    Lpm_activeToIoRetSwitch();
                    done = 0xFF;
                    break;
                case 2:
                    wkup_configure_can_uart_lock_dmsc();
                    Lpm_activeToIoRetSwitch();
                    done = 0xFF;
                    break;
                case 3:
                    main_configure_can_uart_lock_dmsc();
                    wkup_configure_can_uart_lock_dmsc();
                    Lpm_activeToIoRetSwitch();
                    done = 0xFF;
                    break;
                default:
                    AppUtils_Printf(MSG_NORMAL, "Invalid option - please enter 1 to enter MAIN IO retention mode, 2 to enter MCU IO retention mode, or 3 to enter both.\n");
                    AppUtils_Printf(MSG_NORMAL, "Input: ");
                    break;
            }
        }
    }
    return ret;
}


void disable_isolation_bit_and_unlock()
{
    unsigned int read_data = 0;
    int i = 0;
    int cnt = 0;

    /* Check to see if wakeup events occurred on various pins */
    if (*mkptr(MAIN_CTRL_BASE, 0x1c020) & (0b1 << 30))
    {  
        UART_printf("Wakeup occured on MAIN_MCAN0_TX pin\n");
    }
    if (*mkptr(MAIN_CTRL_BASE, 0x1c02c) & (0b1 << 30))
    {  
        UART_printf("Wakeup occured on MAIN_MCAN1_TX pin\n");
    }
    if (*mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0B8) & (0b1 << 30))
    {
        UART_printf("Wakeup occured on MCU_MCAN0_TX pin\n");
    }
    if (*mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0D0) & (0b1 << 30))
    {
        UART_printf("Wakeup occured on MCU_MCAN1_TX pin\n");
    }

    /* Unlock MMRs */
    Lpm_mmr_unlock(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 6);
    Lpm_mmr_unlock(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 7);
    Lpm_mmr_unlock(MAIN_CTRL_BASE, 7);

    /* exit MCU canuart io retention with magic word - won't have any affect if already out of io retention */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_MCU_GEN_WAKE_CTRL) = 0x55555554;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_MCU_GEN_WAKE_CTRL) = 0x55555555;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_MCU_GEN_WAKE_CTRL) = 0x55555554;

    /* exit MAIN canuart io retention with magic word - won't have any affect if already out of io retention */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL) = 0x55555554;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL) = 0x55555555;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL) = 0x55555554;

    /* Disable MCU isolation bit if it is active */
    read_data =  *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO);
    while(read_data & 0x2000000)
    {
        read_data =  *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO);
        *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO) = read_data & ~(0b1 << 24);
        for(i=0; i<io_timeout; i++);
        if (cnt == 1000)
        {
            UART_printf(".");
        }
    }

    /* Disable MAIN isolation bit if it is active */
    read_data =  *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR);
    while(read_data & 0x2000000)
    {
        read_data =  *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR);
        *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR) = read_data & ~(0b1 << 24);
        for(i=0; i<io_timeout; i++);
        if (cnt == 1000)
        {
            UART_printf(".");
        }
    }

    UART_printf("Exited IO Retention for MAIN and MCU domains\n");
}


/*----------------------------------------------------------------------------------------------------------*
 * MAIN IO PM daisy chain deepsleep + isolation entry sequence                                              *
 *----------------------------------------------------------------------------------------------------------*/
int main_io_pm_seq (void)
{

    unsigned int read_data = 0;
    volatile unsigned int i = 0; /* Make sure below for loop is not optimized */

    /* Configure MCAN0 PADCONF */
    *mkptr(MAIN_CTRL_BASE, 0x1c020) = 0x20050000;

    /* Configure MCAN1 PADCONF */
    *mkptr(MAIN_CTRL_BASE, 0x1c02c) = 0x20050000;

    /* Configure PMIC_WAKE */
    *mkptr(MAIN_CTRL_BASE, 0x1c124) = 0x38038000;

    /* Unlock DMSC reg */
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK0) = 0x8a6b7cda;
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK1) = 0x823caef9;

    /* Enable fw_ctrl_out[0] */
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_FW_CTRL_OUT0_SET) |= 0x2;
    read_data = *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL);
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL) = read_data | 0x100;

    /* Enable Wakeup_enable */
    read_data =  *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR);
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR) = read_data | 0x10000;

    /* Enable ISOIN */
    read_data =  *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR);
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR) = read_data | 0x1000000;
    for(i=0; i<io_timeout; i++);    /* Wait for 10us */

    /* Check ISOIN status */
    read_data = *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR);

    return 1;

}

int wkup_io_pm_seq (void)
{
    unsigned int read_data = 0;
    volatile unsigned int i = 0; /* Make sure below for loop is not optimized */

    /* CONFIGURE MCU_MCAN0_TX with internal pull up resistor */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0B8) = 0x20060000;

    /* CONFIGURE MCU_MCAN1_TX with internal pull up resistor */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0D0) = 0x20060000;

    /* Configure PMIC_WAKE1 */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1c190) = 0x38038000;

    UART_printf("MCAN1_TX (0x4301C0D0) immediately after pad value is set : 0x%x\n", *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0D0));
    UART_printf("MCAN0_TX (0x4301C0B8) immediately after pad value is set : 0x%x\n", *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0B8));

/* Enable to check that wakeup events are being received */
#if 0
    AppUtils_Printf(MSG_NORMAL, "Trigger the interrupt and then press enter : ");
    int c;
    UART_scanFmt("%d", &c);
    UART_printf("PADCONFIG52 (0x4301c0d0) immediately after manual trigger : 0x%x\n", *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1c0d0));
    UART_printf("MCAN1_TX (0x4301c0d0) immediately after manual trigger : 0x%x\n", *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0D0));
    UART_printf("MCAN0_TX (0x4301C0B8) immediately after manual trigger  : 0x%x\n", *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0B8));
#endif

    /* Bypass IO Isolation for I2C Pins */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C100) = 0x00840000;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C104) = 0x00840000;

    /* Bypass IO Isolation for UART Pins so that we can print after entering IO Isolation */
    /* REMOVE THIS IF YOU WOULD LIKE TO WAKEUP FROM THE UART PINS */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0E8) = 0x00840000;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0EC) = 0x00840000;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0F0) = 0x00840000;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0F4) = 0x00840000;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0F8) = 0x00840000;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0FC) = 0x00840000;


    /* Unlock DMSC reg */
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK0) = 0x8a6b7cda;
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK1) = 0x823caef9;

    /* Enable fw_ctrl_out[0] */
    read_data = *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_FW_CTRL_OUT0_SET);
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_FW_CTRL_OUT0_SET) = read_data | 0x1;

    read_data = *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL);
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL) = read_data | 0x1;

    /* Enable Wakeup_enable */
    read_data = *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO);
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO) = read_data | 0x10000;

    /* Enable ISOIN */
    read_data = *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO);
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO) = read_data | 0x1000000 | (0x1 << 6);

    for(i=0; i<io_timeout; i++);    /* Wait for 10us */
    
    return 1;
}

void wkup_configure_can_uart_lock_dmsc()
{

    uint32_t daisy_chain = wkup_io_pm_seq();

    /* Load the Magic Word */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_MCU_GEN_WAKE_CTRL) = 0x55555554;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_MCU_GEN_WAKE_CTRL) = 0x55555555;

    /* re-lock DMSC reg */
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK0) = 0x0;
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK1) = 0x0;

/* Pause before entering the low power mode and check the PADCONF values*/
#if 0
    UART_printf("PADCONFIG52 (0x4301c0d0) immediately after entering IO retention : 0x%x\n", *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1c0d0);
    AppUtils_Printf(MSG_NORMAL, "Press enter key to send I2C commands to PMIC to enter low power mode... ");
    int c;
    UART_scanFmt("%d", &c);
#endif
}


void main_configure_can_uart_lock_dmsc()
{
    uint32_t daisy_chain = main_io_pm_seq();

    /* Load the Magic word */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL) = 0x55555554;
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL) = 0x55555555;

    /* re-lock DMSC reg */
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK0) = 0x0;
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK1) = 0x0;
}


static void MainApp_TaskFxn(void* a0, void* a1)
{
    /* make sure that DMSC isolation bit is turned off
       and that mmrs are unlocked. If this is not the
       case, code will not execute correctly on other
       cores */
    disable_isolation_bit_and_unlock();
	/* execute overall application*/
    io_retention_main();
}


/*
 *  ======== main ========
 */
int main(void)
{
    int32_t ret = CSL_PASS;
    Board_initCfg boardCfg;
    int i;
    boardCfg = BOARD_INIT_UART_STDIO | BOARD_INIT_PINMUX_CONFIG | BOARD_INIT_MODULE_CLOCK;
    Board_init(boardCfg);

    if ((*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO) & 0x2000000) ||
        (*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR) & 0x2000000))
    {
        global_boot_mode_status = IO_RETENTION_BOOT;
        UART_printf("\n\nBOOT STATUS : Booting back up from IO Retention\n");
    }
    else
    {
        global_boot_mode_status = COLD_BOOT;
        UART_printf("\n\nBOOT STATUS : Cold Boot\n");
    }

    /* GPIO early response for timing reasons */
    if (global_boot_mode_status == IO_RETENTION_BOOT)
    {
        GPIO_init();
        {
            GPIO_write(PIN_WKUP_GPIO0_77, 1);
            for(i=0; i<10000; i++);
            GPIO_write(PIN_WKUP_GPIO0_77, 0);
            for(i=0; i<10000; i++);
        }
    }

    OS_init();

    /* Initialize SCI Client Server */
    Sciclient_init(NULL_PTR);
    ret = SetupSciServer();
    if(ret != CSL_PASS)
    {
        OS_stop();
    }

    /* Initialize the task params */
    TaskP_Params_init(&mainAppTaskParams);
    mainAppTaskParams.priority       = MAIN_APP_TASK_PRIORITY;
    mainAppTaskParams.stack          = MainApp_TaskStack;
    mainAppTaskParams.stacksize      = sizeof (MainApp_TaskStack);

    mainAppTask = TaskP_create(MainApp_TaskFxn, &mainAppTaskParams);

    OS_start();

    return 0;
}


int32_t SetupSciServer(void)
{

    Sciserver_TirtosCfgPrms_t appPrms;
    Sciclient_ConfigPrms_t clientPrms;
    int32_t ret = CSL_PASS;

    appPrms.taskPriority[SCISERVER_TASK_USER_LO] = 6;
    appPrms.taskPriority[SCISERVER_TASK_USER_HI] = 7;

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
        AppUtils_Printf(MSG_NORMAL, "Starting Sciserver..... PASSED\n");
    }
    else
    {
        AppUtils_Printf(MSG_NORMAL, "Starting Sciserver..... FAILED\n");
    }

    return ret;
}
