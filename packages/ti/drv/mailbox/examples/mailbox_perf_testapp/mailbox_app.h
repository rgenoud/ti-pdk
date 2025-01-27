/*
 *  Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   mailbox_app.h
 *
 *  \brief   This file has mailbox app messages defined as macro's
 *
 *  \details
 *
 **/
#ifndef MAILBOX_APP_H_
#define MAILBOX_APP_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */

#define MAILBOX_APP_M4_MSG  'D'
#define MAILBOX_APP_DSP_MSG 'E'
#define MAILBOX_APP_MCU1_0_MSG 'F'
#define MAILBOX_APP_MCU1_1_MSG 'G'
#define MAILBOX_APP_MPU1_0_MSG 'H'
#define MAILBOX_APP_MCU2_0_MSG 'I'
#define MAILBOX_APP_MCU2_1_MSG 'J'
#define MAILBOX_APP_M4F_0_MSG  'K'

#define MAILBOX_APP_SYNC_MESSAGE       0xBABEFACE
#define MAILBOX_APP_ACK_MESSAGE        0xC00DC00D
#define MAILBOX_APP_STOP_MESSAGE       0xE00DE00D
#define MAILBOX_APP_SEND_TOKEN_MESSAGE 0x500D500D

#if defined (__TI_ARM_V7M4__)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_M4_MSG
#elif defined (_TMS320C6X)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_DSP_MSG
#elif defined (BUILD_MCU1_0)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_MCU1_0_MSG
#elif defined (BUILD_MCU1_1)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_MCU1_1_MSG
#elif defined (BUILD_MCU2_0)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_MCU2_0_MSG
#elif defined (BUILD_MCU2_1)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_MCU2_1_MSG
#elif defined (BUILD_MPU1_0)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_MPU1_0_MSG
#elif defined (BUILD_M4F_0)
#define MAILBOX_APP_MSG_TO_SEND MAILBOX_APP_M4F_MSG
#endif

#define MAILBOX_SEND_NUM_MESSAGES 1000

extern volatile uint32_t gOpMode;

void MailboxAppPrint(const char * str);
void MailboxAppPrintf(const char *pFormat, ...);

int32_t perfTestInit(void);
int32_t perfTestInterruptModeInit(void);

int32_t perfTestRun(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* MAILBOX_APP_H_ */
/********************************* End of file ******************************/
