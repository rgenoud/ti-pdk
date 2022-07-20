/*
 *  Copyright (c) Texas Instruments Incorporated 2020
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

/*!
 * \file     cpsw_test_rxflow_maxlength.c
 *
 * \brief    This file contains the cpsw_test_rxflow_maxlength test implementation.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <ti/drv/uart/UART_stdio.h>
#include <ti/csl/csl_cpswitch.h>

#include <ti/drv/enet/enet.h>
#include <ti/drv/enet/examples/utils/include/enet_appmemutils_cfg.h>
#include <ti/drv/enet/examples/utils/include/enet_appmemutils.h>
#include <ti/drv/enet/examples/utils/include/enet_apputils.h>
#include <ti/drv/enet/examples/utils/include/enet_appboardutils.h>
#include <ti/drv/enet/examples/utils/include/enet_ethutils.h>

#include <ti/osal/osal.h>

#include <ti/board/board.h>
#if defined (SOC_J721E)
#include <ti/board/src/j721e_evm/include/board_ethernet_config.h>
#elif defined(SOC_J7200)
#include <ti/board/src/j7200_evm/include/board_ethernet_config.h>
#endif
#include "enet_test_entry.h"
#include "enet_test_base.h"
#include "cpsw_test_phystrapping.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void EnetTestPhyStrap_openPrmsUpdate(EnetTestTaskObj *taskObj,
                                     Cpsw_Cfg *pCpswCfg,
                                     EnetOsal_Cfg *pOsalPrms,
                                     EnetUtils_Cfg *pUtilsPrms)
{
#if defined(BUILD_MCU2_0) && defined(SOC_J721E)
    /* RGMII ports: 1, 2, 3, 4
     *  RMII ports: 8 */
    Board_pinmuxUpdate(gJ721E_MainPinmuxDataGesiCpsw9g,
                       BOARD_SOC_DOMAIN_MAIN);
#endif
}

void EnetTestPhyStrap_updatePortLinkCfg(EnetPer_PortLinkCfg *pLinkArgs,
                                        Enet_MacPort portNum)
{
    CpswMacPort_Cfg *macCfg     = (CpswMacPort_Cfg*)pLinkArgs->macCfg;
    EnetPhy_Cfg *phyCfg         = (EnetPhy_Cfg*)&pLinkArgs->phyCfg;

   EnetAppUtils_assert(portNum == ENET_MAC_PORT_8);

    /* We use RMII port for this testing */
    EnetBoard_setPhyConfigRmii(portNum,
                                       macCfg,
                                       &pLinkArgs->mii,
                                       phyCfg);
    phyCfg->isStrapped = true;
    pLinkArgs->linkCfg.speed     = ENET_SPEED_1GBIT;
    pLinkArgs->linkCfg.duplexity = ENET_DUPLEX_FULL;

}
