/*
 * mcasp_cfg.h
 *
 * This file contains Application programming interface for the Audio application
 * related EVM (platform) specifc initialization routines
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
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
 * \file   mcasp_cfg.h
 *
 * \brief  This file contains the board level functions of Audio driver.
 *
 *  (C) Copyright 2009, Texas Instruments, Inc
 *
 */

#ifndef _MCASP_CFG_H_
#define _MCASP_CFG_H_

#include <string.h>

#include <mcasp_drv.h>

#include <Aic31.h>

#include <ti/csl/soc.h>
#ifdef __cplusplus
extern "C"
{
#endif

#define MCASP_NUM 4
#define SOC_I2C_1_REGS CSL_DSP_I2C1_REGS
#define I2C_MCASP_INSTANCE 0
#define I2C_CODEC_INSTANCE 3
#define I2C_CODEC_SLAVE_ADDRESS 0X44


extern void GblErr(int arg);
extern Mcasp_HwSetupData mcaspRcvSetup;
extern Mcasp_HwSetupData mcaspXmtSetup;
extern Mcasp_ChanParams  mcasp_chanparam[];
extern ICodec_ChannelConfig AIC31_config;

/** Number of serializers configured for record */


#define RX_NUM_SERIALIZER       (1u)
#define TX_NUM_SERIALIZER       (2u)

#ifdef __cplusplus
}
#endif

#endif /* _AUDIO_EVMINIT_H_ */
/* ========================================================================== */
/*                              END OF FILE                                   */
/* ========================================================================== */
