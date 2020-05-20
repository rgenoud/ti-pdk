/*
 *  Copyright (C) 2020 Texas Instruments Incorporated
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
 * \ingroup DRV_SCICLIENT_MODULE
 * \defgroup SCICLIENT_FMW_SA2UL_IF Sciclient SA2UL API Interface
 *
 * The DMSC firmware maintains ownership of SA2UL on HS devices for
 * authentication and decryption services. These resources may be acquired for
 * use by software application crypto requests and released back to the firmware
 * to re-enable the services once again.
 *
 * @{
 */
/**
 *  \file   sciclient_sec_sa2ul.h
 *
 *  \brief  This file contains the definition of all the message IDs, message
 *          formats to be able to interact with the System Controller firmware
 *          for hand over of SA2UL authentication resources.
 */

#ifndef SCICLIENT_SA2UL_H_
#define SCICLIENT_SA2UL_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Acquire the authentication resources from System Fimrware
 *
 *  \n<b>Message</b>:    #TISCI_MSG_SA2UL_AUTH_RES_ACQUIRE
 *  \n<b>Request</b>:    #tisci_msg_sa2ul_auth_res_acquire_req
 *  \n<b>Response</b>:   #tisci_msg_sa2ul_auth_res_acquire_resp
 *
 *  \param  req             Pointer to authentication resource acquire request
 *                          payload
 *
 *  \param  resp            Pointer to authentication resource acquire request
 *                          payload
 *
 *  \param  timeout         Gives a sense of how long to wait for the operation.
 *                          Refer \ref Sciclient_ServiceOperationTimeout.
 *
 *  \return CSL_PASS on success, else failure
 */
int32_t Sciclient_sa2ulAuthResourceAcquire(
    const struct tisci_msg_sa2ul_auth_res_acquire_req *req,
    struct tisci_msg_sa2ul_auth_res_acquire_resp *resp,
    uint32_t timeout);

/**
 *  \brief Release the authentication resources back to System Fimrware
 *
 *  \n<b>Message</b>:    #TISCI_MSG_SA2UL_AUTH_RES_RELEASE
 *  \n<b>Request</b>:    #tisci_msg_sa2ul_auth_res_release_req
 *  \n<b>Response</b>:   #tisci_msg_sa2ul_auth_res_release_resp
 *
 *  \param  req             Pointer to authentication resource release request
 *                          payload
 *
 *  \param  resp            Pointer to authentication resource release request
 *                          payload
 *
 *  \param  timeout         Gives a sense of how long to wait for the operation.
 *                          Refer \ref Sciclient_ServiceOperationTimeout.
 *
 *  \return CSL_PASS on success, else failure
 */
int32_t Sciclient_sa2ulAuthResourceRelease(
    const struct tisci_msg_sa2ul_auth_res_release_req *req,
    struct tisci_msg_sa2ul_auth_res_release_resp *resp,
    uint32_t timeout);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SCICLIENT_SA2UL_H_ */

/* @} */
