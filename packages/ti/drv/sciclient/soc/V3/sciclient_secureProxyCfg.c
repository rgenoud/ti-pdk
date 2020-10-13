/*
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 *  \file V3/sciclient_secureProxyCfg.c
 *
 *  \brief File containing the secure proxy configuration
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/soc.h>
#include <ti/csl/csl_sec_proxy.h>

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief This structure contains configuration parameters for
*       the sec_proxy IP */
CSL_SecProxyCfg gSciclient_secProxyCfg =
{
    (CSL_sec_proxyRegs *)       CSL_DMASS0_SEC_PROXY_MMRS_BASE,
    /*< pSecProxyRegs */
    (CSL_sec_proxy_scfgRegs *)  CSL_DMASS0_SEC_PROXY_SCFG_BASE,
    /*< pSecProxyScfgRegs */
    (CSL_sec_proxy_rtRegs *)    CSL_DMASS0_SEC_PROXY_RT_BASE,
    /*< pSecProxyRtRegs */
    (uint64_t)                  CSL_DMASS0_SEC_PROXY_SRC_TARGET_DATA_BASE,
    /*< proxyTargetAddr */
    0
    /*< maxMsgSize */
};
