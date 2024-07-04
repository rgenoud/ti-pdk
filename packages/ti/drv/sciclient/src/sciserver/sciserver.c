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
 *  \file sciserver.c
 *
 *  \brief File containing the Sciserver driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_sec_proxy.h>
#include <ti/drv/sciclient/sciserver.h>
#include <sciserver_secproxyConfigData.h>
#include <sciserver_secproxyTransfer.h>
#include <ti/drv/sciclient/src/sciclient/sciclient_priv.h>
#include <ti/drv/sciclient/src/version/sciserver_version.h>
#include <ti/drv/sciclient/src/version/rmpmhal_version.h>
#include <ti/drv/uart/UART_stdio.h>

#include "ti/debug_qnr.c"
/* Set VERBOSE to 1 for trace information on message routing */
#define VERBOSE 0

#if VERBOSE
#define Sciserver_printf UART_printf
#else
#define Sciserver_printf(...)
#endif

/**
 * sciserver_stringify - Turn expression into a string literal
 * @expr: any C expression
 *
 * Example:
 *      #define PRINT_COND_IF_FALSE(cond) \
 *              ((cond) || printf("%s is SFALSE!", sciserver_stringify(cond)))
 */
#define sciserver_stringify(expr)   sciserver_stringify_1(expr)
/* Double-indirection required to stringify expansions */
#define sciserver_stringify_1(expr) #expr

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/** \brief Sciserver Internal Structure */
typedef struct {
    uint8_t ctrlState;
    /**< Ctrl State of the Sciserver */
    uint8_t processState;
    /**< Processing State of the Sciserver */
    uint8_t initDone;
    /**< Initialization Done State */
} Sciserver_InternalState_t ;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static int32_t Sciserver_MsgVerifyHost(uint32_t *msg, uint8_t known_host);

static int32_t Sciserver_UserProcessMsg(uint32_t *msg_recv,
                                        uint32_t *pRespMsgSize,
                                        uint8_t hw_host);

static int32_t Sciserver_TisciMsgResponse(uint8_t   response_host,
                                   uint32_t  *response,
                                   uint32_t  size);
                                   
static void Sciserver_SetMsgHostId(uint32_t *msg, uint8_t hostId);

static int32_t Sciserver_ProcessFullMessage(uint32_t *msg_recv,
                                            uint32_t reqMsgSize,
                                            uint32_t respMsgSize);
                                            
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

const char sciserver_version_str[] = SCISERVER_MAJOR_VERSION_NAME "." sciserver_stringify(SCISERVER_SUBVERSION) \
                                   "." sciserver_stringify(SCISERVER_PATCHVERSION) \
                                   SCISERVER_SCMVERSION;

const char rmpmhal_version_str[] = RMPMHAL_SCMVERSION;

/** Global state of the Sciserver */
static Sciserver_InternalState_t gSciserverState = {
    SCISERVER_CTRL_CMD_HALT,
    SCISERVER_PROCESS_STATE_WAIT,
    SCISERVER_INIT_NOT_DONE
};


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

char * Sciserver_getVersionStr(void)
{
    return (char *) sciserver_version_str;
}

char * Sciserver_getRmPmHalVersionStr(void)
{
    return (char *) rmpmhal_version_str;
}

int32_t Sciserver_initPrms_Init(Sciserver_CfgPrms_t *pPrms)
{
    int32_t ret = CSL_PASS;

    return ret;
}

int32_t Sciserver_init(Sciserver_CfgPrms_t *pPrms)
{
    int32_t ret = CSL_PASS;

    if (gSciserverState.initDone == (uint8_t)SCISERVER_INIT_NOT_DONE)
    {
        if (pPrms == NULL)
        {
            ret = CSL_EBADARGS;
        }
        if (CSL_PASS == ret)
        {
            /* Implement SoC specific configuration */
            Sciserver_socInit();

            gSciserverState.ctrlState = SCISERVER_CTRL_CMD_HALT;
            gSciserverState.processState = SCISERVER_PROCESS_STATE_WAIT;
            gSciserverState.initDone = SCISERVER_INIT_DONE;
        }
    }
    else
    {
        ret = CSL_EFAIL;
    }
    return ret;
}

int32_t Sciserver_deinit(void)
{
    int32_t ret = CSL_PASS;

    if (gSciserverState.initDone == (uint8_t)SCISERVER_INIT_DONE)
    {
        if (CSL_PASS == ret)
        {
            gSciserverState.ctrlState = SCISERVER_CTRL_CMD_HALT;
            gSciserverState.processState = SCISERVER_PROCESS_STATE_WAIT;
            gSciserverState.initDone = SCISERVER_INIT_NOT_DONE;
        }
    }
    else
    {
        ret = CSL_EFAIL;
    }
    return ret;
}

void Sciserver_setCtrlState (uint8_t state)
{
    gSciserverState.ctrlState = state;
}

uint8_t Sciserver_getCtrlState (void)
{
   return gSciserverState.ctrlState;
}

void Sciserver_setProcessState (uint8_t state)
{
    gSciserverState.processState = state;
}

uint8_t Sciserver_getProcessState (void)
{
   return gSciserverState.processState;
}

int32_t Sciserver_interruptHandler(Sciserver_hwiData *uhd, bool* soft_error)
{
    int32_t ret = CSL_PASS;
    uint32_t msg_words;
    uint32_t hw_host = 0U;

    *soft_error = false;
    if (ret == CSL_PASS)
    {
        (void) memset(uhd->hw_msg_buffer, 0, SCISERVER_HW_QUEUE_SIZE);
        msg_words = ((uint32_t) SCISERVER_HW_QUEUE_SIZE + 3U) / 4U;
        ret = Sciserver_SproxyMsgRead(uhd->hw_msg_queue_id, 
                                      uhd->hw_msg_buffer,
                                      msg_words);
    }

    if (ret == CSL_PASS)
    {
        ret = Sciserver_SproxyMsgGetSenderHostId(uhd->hw_msg_queue_id,
                                                &hw_host);
    }

    if (ret == CSL_PASS) {
        /*
         * We must ensure that the incoming message hdr host field
         * matches the host ID returned to us from the messaging
         * hardware, otherwise this may be a spoofed message. If
         * message appears to be spoofed, send a nak and then
         * move on to the next one.
         */
        ret = Sciserver_MsgVerifyHost(uhd->hw_msg_buffer, (uint8_t) hw_host);
        if (ret != CSL_PASS) {
            /*
             * It is ok to continue after this but flag
             * the invalid message so that the queue is cleared
             * and we can ignore this message and move on.
             */
            *soft_error = true;
        }
    }

    if (ret == CSL_PASS)
    {
        uhd->user_msg_data->host = (uint8_t)hw_host;
        uhd->user_msg_data->is_pending = true;
        ret = Sciserver_SproxyMsgAck(uhd->hw_msg_queue_id);
    }
    else
    {
        Sciserver_SproxyMsgAck(uhd->hw_msg_queue_id);
    }
    return ret;
}

int32_t Sciserver_processtask(Sciserver_taskData *utd)
{
    int32_t ret = CSL_PASS;
    uint8_t i;
    /* the host ID that the response message is sent to */
    uint8_t respHost;
    /* the response message size */
    uint32_t respMsgSize;
    /* the response message pointer */
    uint32_t *respMsg = NULL;
    /* TISCI flags of the received message  */
    uint32_t  tisci_flags;

    for (i = 0; i < SCISERVER_SECPROXY_INSTANCE_COUNT; i++)
    {
        utd->state->current_buffer_idx++;
        if (utd->state->current_buffer_idx >= SCISERVER_SECPROXY_INSTANCE_COUNT)
        {
            utd->state->current_buffer_idx = 0;
        }

        if (utd->user_msg_data[utd->state->current_buffer_idx]->is_pending == true)
        {
            utd->state->state = SCISERVER_TASK_PROCESSING_USER_MSG;
            break;
        }
    }

    if (utd->state->state == SCISERVER_TASK_PROCESSING_USER_MSG)
    {
        struct tisci_header * hdr = (struct tisci_header *)  utd->hw_msg_buffer_list[utd->state->current_buffer_idx];
        tisci_flags = hdr->flags;
        ret = Sciserver_UserProcessMsg(
                utd->hw_msg_buffer_list[utd->state->current_buffer_idx],
                &respMsgSize,
                utd->user_msg_data[utd->state->current_buffer_idx]->host);
        respMsg = utd->hw_msg_buffer_list[utd->state->current_buffer_idx];
    }
    else
    {
        ret = CSL_EFAIL;
    }

    if (ret == CSL_PASS)
    {
        respHost = utd->user_msg_data[utd->state->current_buffer_idx]->host;
        if (respHost == TISCI_HOST_ID_DMSC2DM)
        {
            /* DMSC2DM is processed by DM. Need to update response message value
             * so the host verification on TIFS can succeed */
            Sciserver_SetMsgHostId(respMsg, TISCI_HOST_ID_DM);
        }
        /* Check AOP flag before sending a respone back */
        if((tisci_flags & TISCI_MSG_FLAG_AOP)!= 0U){
            ret = Sciserver_TisciMsgResponse(respHost, respMsg, respMsgSize);
        }

        if (ret == CSL_PASS)
        {
            utd->user_msg_data[utd->state->current_buffer_idx]->is_pending = false;
        }

        utd->state->state = SCISERVER_TASK_PENDING;
    }

    return ret;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t Sciserver_MsgVerifyHost(uint32_t *msg, uint8_t known_host)
{
    int32_t ret = CSL_PASS;
    struct tisci_header *hdr = (struct tisci_header *) msg;

    if (hdr == NULL) {
        ret = CSL_EFAIL;
    }

    if (ret == CSL_PASS) { if (hdr->host != known_host) {
            /*
             * We check the header against the queue id to verify that the host
             * has not spoofed the request. The special case is when a message
             * is sent via the forwarded DMSC2DM queue, then by design the
             * header host does not match the host assigned to the queue. We
             * rely on the host id from the message header to allow us to
             * process the message on behalf of the host who made the original
             * request.
             */
            if (known_host != TISCI_HOST_ID_DMSC2DM) {
                ret = CSL_EFAIL;
            }
        }
    }

    return ret;
}


static int32_t Sciserver_TisciMsgResponse(uint8_t   response_host,
                           uint32_t *response,
                           uint32_t  size)
{
    uint16_t sproxy_conf_id;
    uint32_t msg_words;
    int32_t ret = CSL_PASS;

    /*
     * We calculate words here without a check because we rely on the
     * underlying HW implementation to validate sanity of size value that
     * is passed.
     */
    msg_words = (size + 3U) / 4U;

    ret = Sciserver_SproxyGetResponseConfId(response_host,
                          &sproxy_conf_id);

    if (ret == CSL_PASS) {
        ret = Sciserver_SproxyMsgSend(sproxy_conf_id, response,
                          msg_words);
    }

    if (ret == 0) {
        ret = Sciserver_SproxyMsgFinish(sproxy_conf_id);
    }

    return ret;
}

static void Sciserver_SetMsgHostId(uint32_t *msg, uint8_t hostId)
{
    struct tisci_header *hdr = (struct tisci_header *) msg;
    hdr->host = hostId;
}

static int32_t Sciserver_ProcessFullMessage(uint32_t *msg_recv,
    uint32_t reqMsgSize,
    uint32_t respMsgSize)
{
    int32_t ret = CSL_EFAIL;
    Sciclient_ReqPrm_t reqPrm = {0};
    Sciclient_RespPrm_t respPrm = {0};
    struct tisci_header *hdr = (struct tisci_header *) msg_recv;
    uint8_t reqSeq;
    uint32_t reqMsgBuffer[14] = {0};
    uint32_t respMsgBuffer[14] = {0};

    /* Store the request sequence value */
    reqSeq = hdr->seq;

    memcpy(reqMsgBuffer, msg_recv, reqMsgSize);

    reqPrm.messageType = hdr->type;
    reqPrm.flags = TISCI_MSG_FLAG_AOP;
    reqPrm.pReqPayload = (const uint8_t *)reqMsgBuffer;
    reqPrm.reqPayloadSize = reqMsgSize;
    reqPrm.timeout = SCICLIENT_SERVICE_WAIT_FOREVER;

    /*
     * If here, the message is intended to be forwarded to another service
     * provider.
     */
    reqPrm.forwardStatus = SCISERVER_FORWARD_MSG;

    respPrm.flags = 0;
    respPrm.pRespPayload = (uint8_t *) respMsgBuffer;
    respPrm.respPayloadSize = respMsgSize;

    ret = Sciclient_service(&reqPrm, &respPrm);

    memcpy(msg_recv, respMsgBuffer, respMsgSize);

    /* Must restore the seq field. When forwarded message is processed by
     * TIFS, the returned message would have incorrect sequence value */
    hdr->seq = reqSeq;

    return ret;
}

static char *get_msg_type(int t)
{
	static char *type = "";
	switch(t) {
	case TISCI_MSG_VERSION: type = "TISCI_MSG_VERSION"; break;
	case TISCI_MSG_BOOT_NOTIFICATION: type = "TISCI_MSG_BOOT_NOTIFICATION"; break;
	case TISCI_MSG_BOARD_CONFIG: type = "TISCI_MSG_BOARD_CONFIG"; break;
	case TISCI_MSG_BOARD_CONFIG_RM: type = "TISCI_MSG_BOARD_CONFIG_RM"; break;
	case TISCI_MSG_BOARD_CONFIG_SECURITY: type = "TISCI_MSG_BOARD_CONFIG_SECURITY"; break;
	case TISCI_MSG_BOARD_CONFIG_PM: type = "TISCI_MSG_BOARD_CONFIG_PM"; break;
	case TISCI_MSG_ENABLE_WDT: type = "TISCI_MSG_ENABLE_WDT"; break;
	case TISCI_MSG_WAKE_RESET: type = "TISCI_MSG_WAKE_RESET"; break;
	case TISCI_MSG_WAKE_REASON: type = "TISCI_MSG_WAKE_REASON"; break;
	case TISCI_MSG_GOODBYE: type = "TISCI_MSG_GOODBYE"; break;
	case TISCI_MSG_SYS_RESET: type = "TISCI_MSG_SYS_RESET"; break;
	case TISCI_MSG_QUERY_MSMC: type = "TISCI_MSG_QUERY_MSMC"; break;
	case TISCI_MSG_GET_TRACE_CONFIG: type = "TISCI_MSG_GET_TRACE_CONFIG"; break;
	case TISCI_MSG_QUERY_FW_CAPS: type = "TISCI_MSG_QUERY_FW_CAPS"; break;
	case TISCI_MSG_SET_CLOCK: type = "TISCI_MSG_SET_CLOCK"; break;
	case TISCI_MSG_GET_CLOCK: type = "TISCI_MSG_GET_CLOCK"; break;
	case TISCI_MSG_SET_CLOCK_PARENT: type = "TISCI_MSG_SET_CLOCK_PARENT"; break;
	case TISCI_MSG_GET_CLOCK_PARENT: type = "TISCI_MSG_GET_CLOCK_PARENT"; break;
	case TISCI_MSG_GET_NUM_CLOCK_PARENTS: type = "TISCI_MSG_GET_NUM_CLOCK_PARENTS"; break;
	case TISCI_MSG_SET_FREQ: type = "TISCI_MSG_SET_FREQ"; break;
	case TISCI_MSG_QUERY_FREQ: type = "TISCI_MSG_QUERY_FREQ"; break;
	case TISCI_MSG_GET_FREQ: type = "TISCI_MSG_GET_FREQ"; break;
	case TISCI_MSG_SET_DEVICE: type = "TISCI_MSG_SET_DEVICE"; break;
	case TISCI_MSG_GET_DEVICE: type = "TISCI_MSG_GET_DEVICE"; break;
	case TISCI_MSG_SET_DEVICE_RESETS: type = "TISCI_MSG_SET_DEVICE_RESETS"; break;
	case TISCI_MSG_DEVICE_DROP_POWERUP_REF: type = "TISCI_MSG_DEVICE_DROP_POWERUP_REF"; break;
	case TISCI_MSG_PREPARE_SLEEP: type = "TISCI_MSG_PREPARE_SLEEP"; break;
	case TISCI_MSG_ENTER_SLEEP: type = "TISCI_MSG_ENTER_SLEEP"; break;
	case TISCI_MSG_SYNC_RESUME: type = "TISCI_MSG_SYNC_RESUME"; break;
	case TISCI_MSG_CONTINUE_RESUME: type = "TISCI_MSG_CONTINUE_RESUME"; break;
	case TISCI_MSG_CORE_RESUME: type = "TISCI_MSG_CORE_RESUME"; break;
	case TISCI_MSG_ABORT_ENTER_SLEEP: type = "TISCI_MSG_ABORT_ENTER_SLEEP"; break;
	case TISCI_MSG_LPM_WAKE_REASON: type = "TISCI_MSG_LPM_WAKE_REASON"; break;
	case TISCI_MSG_SET_IO_ISOLATION: type = "TISCI_MSG_SET_IO_ISOLATION"; break;
	case TISCI_MSG_FIRMWARE_LOAD: type = "TISCI_MSG_FIRMWARE_LOAD"; break;
	case MSG_FIRMWARE_LOAD_RESULT: type = "MSG_FIRMWARE_LOAD_RESULT"; break;
	case TISCI_MSG_SET_FWL_REGION: type = "TISCI_MSG_SET_FWL_REGION"; break;
	case TISCI_MSG_GET_FWL_REGION: type = "TISCI_MSG_GET_FWL_REGION"; break;
	case TISCI_MSG_CHANGE_FWL_OWNER: type = "TISCI_MSG_CHANGE_FWL_OWNER"; break;
	case TISCI_MSG_SA2UL_SET_DKEK: type = "TISCI_MSG_SA2UL_SET_DKEK"; break;
	case TISCI_MSG_SA2UL_RELEASE_DKEK: type = "TISCI_MSG_SA2UL_RELEASE_DKEK"; break;
	case TISCI_MSG_KEYSTORE_IMPORT_SKEY: type = "TISCI_MSG_KEYSTORE_IMPORT_SKEY"; break;
	case TISCI_MSG_KEYSTORE_ERASE_SKEY: type = "TISCI_MSG_KEYSTORE_ERASE_SKEY"; break;
	case TISCI_MSG_SEC_RESERVED_9007: type = "TISCI_MSG_SEC_RESERVED_9007"; break;
	case TISCI_MSG_SEC_RESERVED_9008: type = "TISCI_MSG_SEC_RESERVED_9008"; break;
	case TISCI_MSG_SET_ISC_REGION: type = "TISCI_MSG_SET_ISC_REGION"; break;
	case TISCI_MSG_GET_ISC_REGION: type = "TISCI_MSG_GET_ISC_REGION"; break;
	case TISCI_MSG_FWL_EXCP_NOTIFICATION: type = "TISCI_MSG_FWL_EXCP_NOTIFICATION"; break;
	case TISCI_MSG_OPEN_DEBUG_FWLS: type = "TISCI_MSG_OPEN_DEBUG_FWLS"; break;
	case TISCI_MSG_KEYSTORE_WRITE: type = "TISCI_MSG_KEYSTORE_WRITE"; break;
	case TISCI_MSG_KEYSTORE_EXPORT_ALL: type = "TISCI_MSG_KEYSTORE_EXPORT_ALL"; break;
	case TISCI_MSG_KEYSTORE_IMPORT_ALL: type = "TISCI_MSG_KEYSTORE_IMPORT_ALL"; break;
	case TISCI_MSG_SEC_RESERVED_9010: type = "TISCI_MSG_SEC_RESERVED_9010"; break;
	case TISCI_MSG_SEC_RESERVED_9011: type = "TISCI_MSG_SEC_RESERVED_9011"; break;
	case TISCI_MSG_SEC_RESERVED_9012: type = "TISCI_MSG_SEC_RESERVED_9012"; break;
	case TISCI_MSG_SEC_RESERVED_9013: type = "TISCI_MSG_SEC_RESERVED_9013"; break;
	case TISCI_MSG_SEC_RESERVED_9014: type = "TISCI_MSG_SEC_RESERVED_9014"; break;
	case TISCI_MSG_SEC_RESERVED_9015: type = "TISCI_MSG_SEC_RESERVED_9015"; break;
	case TISCI_MSG_SEC_RESERVED_9016: type = "TISCI_MSG_SEC_RESERVED_9016"; break;
	case TISCI_MSG_SA2UL_AUTH_RES_ACQUIRE: type = "TISCI_MSG_SA2UL_AUTH_RES_ACQUIRE"; break;
	case TISCI_MSG_SA2UL_AUTH_RES_RELEASE: type = "TISCI_MSG_SA2UL_AUTH_RES_RELEASE"; break;
	case TISCI_MSG_SEC_RESERVED_9020: type = "TISCI_MSG_SEC_RESERVED_9020"; break;
	case TISCI_MSG_GET_SOC_UID: type = "TISCI_MSG_GET_SOC_UID"; break;
	case TISCI_MSG_READ_OTP_MMR: type = "TISCI_MSG_READ_OTP_MMR"; break;
	case TISCI_MSG_WRITE_OTP_ROW: type = "TISCI_MSG_WRITE_OTP_ROW"; break;
	case TISCI_MSG_LOCK_OTP_ROW: type = "TISCI_MSG_LOCK_OTP_ROW"; break;
	case TISCI_MSG_SOFT_LOCK_OTP_WRITE_GLOBAL: type = "TISCI_MSG_SOFT_LOCK_OTP_WRITE_GLOBAL"; break;
	case TISCI_MSG_GET_OTP_ROW_LOCK_STATUS: type = "TISCI_MSG_GET_OTP_ROW_LOCK_STATUS"; break;
	case TISCI_MSG_RSVD_OTP_1: type = "TISCI_MSG_RSVD_OTP_1"; break;
	case TISCI_MSG_RSVD_OTP_2: type = "TISCI_MSG_RSVD_OTP_2"; break;
	case TISCI_MSG_SA2UL_GET_DKEK: type = "TISCI_MSG_SA2UL_GET_DKEK"; break;
	case TISCI_MSG_ALLOW_FWL_CTRL_READ: type = "TISCI_MSG_ALLOW_FWL_CTRL_READ"; break;
	case TISCI_MSG_FORBID_FWL_CTRL_READ: type = "TISCI_MSG_FORBID_FWL_CTRL_READ"; break;
	case TISCI_MSG_SEC_HANDOVER: type = "TISCI_MSG_SEC_HANDOVER"; break;
	case TISCI_MSG_KEY_WRITER: type = "TISCI_MSG_KEY_WRITER"; break;
	case TISCI_MSG_WRITE_SWREV: type = "TISCI_MSG_WRITE_SWREV"; break;
	case TISCI_MSG_READ_SWREV: type = "TISCI_MSG_READ_SWREV"; break;
	case TISCI_MSG_READ_KEYCNT_KEYREV: type = "TISCI_MSG_READ_KEYCNT_KEYREV"; break;
	case TISCI_MSG_WRITE_KEYREV: type = "TISCI_MSG_WRITE_KEYREV"; break;
	case TISCI_MSG_SA2UL_GET_DSMEK: type = "TISCI_MSG_SA2UL_GET_DSMEK"; break;
	case TISCI_MSG_SA2UL_SET_DSMEK: type = "TISCI_MSG_SA2UL_SET_DSMEK"; break;
	case TISCI_MSG_SA2UL_RELEASE_DSMEK: type = "TISCI_MSG_SA2UL_RELEASE_DSMEK"; break;
	case TISCI_MSG_KEYRING_IMPORT: type = "TISCI_MSG_KEYRING_IMPORT"; break;
	case TISCI_MSG_SA2UL_SET_DKEK_CONST: type = "TISCI_MSG_SA2UL_SET_DKEK_CONST"; break;
	case TISCI_MSG_SA2UL_GET_DKEK_CONST: type = "TISCI_MSG_SA2UL_GET_DKEK_CONST"; break;
	case TISCI_MSG_PROC_REQUEST: type = "TISCI_MSG_PROC_REQUEST"; break;
	case TISCI_MSG_PROC_RELEASE: type = "TISCI_MSG_PROC_RELEASE"; break;
	case TISCI_MSG_PROC_HANDOVER: type = "TISCI_MSG_PROC_HANDOVER"; break;
	case TISCI_MSG_PROC_SET_CONFIG: type = "TISCI_MSG_PROC_SET_CONFIG"; break;
	case TISCI_MSG_PROC_SET_CONTROL: type = "TISCI_MSG_PROC_SET_CONTROL"; break;
	case TISCI_MSG_PROC_GET_STATUS: type = "TISCI_MSG_PROC_GET_STATUS"; break;
	case TISCI_MSG_PROC_WAIT_STATUS: type = "TISCI_MSG_PROC_WAIT_STATUS"; break;
	case TISCI_MSG_PROC_AUTH_BOOT: type = "TISCI_MSG_PROC_AUTH_BOOT"; break;
	case TISCI_MSG_RM_GET_RESOURCE_RANGE: type = "TISCI_MSG_RM_GET_RESOURCE_RANGE"; break;
	case TISCI_MSG_RM_IRQ_SET: type = "TISCI_MSG_RM_IRQ_SET"; break;
	case TISCI_MSG_RM_IRQ_RELEASE: type = "TISCI_MSG_RM_IRQ_RELEASE"; break;
	case TISCI_MSG_RM_RESERVED_1100: type = "TISCI_MSG_RM_RESERVED_1100"; break;
	case TISCI_MSG_RM_RESERVED_1101: type = "TISCI_MSG_RM_RESERVED_1101"; break;
	case TISCI_MSG_RM_RESERVED_1102: type = "TISCI_MSG_RM_RESERVED_1102"; break;
	case TISCI_MSG_RM_RESERVED_1103: type = "TISCI_MSG_RM_RESERVED_1103"; break;
	case TISCI_MSG_RM_RING_CFG: type = "TISCI_MSG_RM_RING_CFG"; break;
	case TISCI_MSG_RM_RESERVED_1111: type = "TISCI_MSG_RM_RESERVED_1111"; break;
	case TISCI_MSG_RM_RING_MON_CFG: type = "TISCI_MSG_RM_RING_MON_CFG"; break;
	case TISCI_MSG_RM_RESERVED_1200: type = "TISCI_MSG_RM_RESERVED_1200"; break;
	case TISCI_MSG_RM_RESERVED_1201: type = "TISCI_MSG_RM_RESERVED_1201"; break;
	case TISCI_MSG_RM_UDMAP_TX_CH_CFG: type = "TISCI_MSG_RM_UDMAP_TX_CH_CFG"; break;
	case TISCI_MSG_RM_RESERVED_1206: type = "TISCI_MSG_RM_RESERVED_1206"; break;
	case TISCI_MSG_RM_RESERVED_1210: type = "TISCI_MSG_RM_RESERVED_1210"; break;
	case TISCI_MSG_RM_RESERVED_1211: type = "TISCI_MSG_RM_RESERVED_1211"; break;
	case TISCI_MSG_RM_UDMAP_RX_CH_CFG: type = "TISCI_MSG_RM_UDMAP_RX_CH_CFG"; break;
	case TISCI_MSG_RM_RESERVED_1216: type = "TISCI_MSG_RM_RESERVED_1216"; break;
	case TISCI_MSG_RM_RESERVED_1220: type = "TISCI_MSG_RM_RESERVED_1220"; break;
	case TISCI_MSG_RM_RESERVED_1221: type = "TISCI_MSG_RM_RESERVED_1221"; break;
	case TISCI_MSG_RM_UDMAP_FLOW_CFG: type = "TISCI_MSG_RM_UDMAP_FLOW_CFG"; break;
	case TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG: type = "TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG"; break;
	case TISCI_MSG_RM_RESERVED_1232: type = "TISCI_MSG_RM_RESERVED_1232"; break;
	case TISCI_MSG_RM_RESERVED_1233: type = "TISCI_MSG_RM_RESERVED_1233"; break;
	case TISCI_MSG_RM_UDMAP_FLOW_DELEGATE: type = "TISCI_MSG_RM_UDMAP_FLOW_DELEGATE"; break;
	case TISCI_MSG_RM_UDMAP_GCFG_CFG: type = "TISCI_MSG_RM_UDMAP_GCFG_CFG"; break;
	case TISCI_MSG_RM_RESERVED_1241: type = "TISCI_MSG_RM_RESERVED_1241"; break;
	case TISCI_MSG_RM_PSIL_PAIR: type = "TISCI_MSG_RM_PSIL_PAIR"; break;
	case TISCI_MSG_RM_PSIL_UNPAIR: type = "TISCI_MSG_RM_PSIL_UNPAIR"; break;
	case TISCI_MSG_RM_PSIL_READ: type = "TISCI_MSG_RM_PSIL_READ"; break;
	case TISCI_MSG_RM_PSIL_WRITE: type = "TISCI_MSG_RM_PSIL_WRITE"; break;
	case TISCI_MSG_RM_PROXY_CFG: type = "TISCI_MSG_RM_PROXY_CFG"; break;
	}
	return type;
}
static int32_t Sciserver_UserProcessMsg(uint32_t *msg_recv,
                                        uint32_t *pRespMsgSize,
                                        uint8_t hw_host_id)
{
    int32_t ret = CSL_PASS;
    struct  tisci_header *hdr = (struct tisci_header *) msg_recv;
    int32_t runLocalRmOnly = 0;
    uint32_t reqMsgSize;
    uint32_t respMsgSize;

    Sciserver_printf("type = 0x%x, host = %d\n", hdr->type, hw_host_id);
//    Lpm_debugFullPrintf("Msg type = %s(0x%x), host = 0x%x\n", get_msg_type(hdr->type),hdr->type, hw_host_id);
//    Lpm_debugFullPrintf("Msg type = (0x%x), host = 0x%x\n", hdr->type, hw_host_id);

    switch (hdr->type)
    {
        case TISCI_MSG_VERSION:
            reqMsgSize = sizeof(struct tisci_msg_version_req);
            respMsgSize = sizeof(struct tisci_msg_version_resp);
            break;
        /* Start of RM messages */
        case TISCI_MSG_BOARD_CONFIG_RM:
            reqMsgSize = sizeof(struct tisci_msg_board_config_rm_req);
            respMsgSize = sizeof(struct tisci_msg_board_config_rm_resp);
            break;
        case TISCI_MSG_RM_GET_RESOURCE_RANGE:
            reqMsgSize = sizeof(struct tisci_msg_rm_get_resource_range_req);
            respMsgSize = sizeof(struct tisci_msg_rm_get_resource_range_resp);
            break;
        case TISCI_MSG_RM_IRQ_SET:
            reqMsgSize = sizeof(struct tisci_msg_rm_irq_set_req);
            respMsgSize = sizeof(struct tisci_msg_rm_irq_set_resp);
            break;
        case TISCI_MSG_RM_IRQ_RELEASE:
            reqMsgSize = sizeof(struct tisci_msg_rm_irq_release_req);
            respMsgSize = sizeof(struct tisci_msg_rm_irq_release_resp);
            break;
        case TISCI_MSG_RM_RING_CFG:
            reqMsgSize = sizeof(struct tisci_msg_rm_ring_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_ring_cfg_resp);
            break;
        case TISCI_MSG_RM_RING_MON_CFG:
            reqMsgSize = sizeof(struct tisci_msg_rm_ring_mon_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_ring_mon_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_TX_CH_CFG:
            reqMsgSize = sizeof(struct tisci_msg_rm_udmap_tx_ch_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_tx_ch_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_RX_CH_CFG:
            reqMsgSize = sizeof(struct tisci_msg_rm_udmap_rx_ch_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_rx_ch_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_CFG:
            reqMsgSize = sizeof(struct tisci_msg_rm_udmap_flow_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_flow_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG:
            reqMsgSize = sizeof(struct tisci_msg_rm_udmap_flow_size_thresh_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_DELEGATE:
            reqMsgSize = sizeof(struct tisci_msg_rm_udmap_flow_delegate_req);
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_flow_delegate_resp);
            break;
        case TISCI_MSG_RM_UDMAP_GCFG_CFG:
            reqMsgSize = sizeof(struct tisci_msg_rm_udmap_gcfg_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_gcfg_cfg_resp);
            break;
        case TISCI_MSG_RM_PSIL_PAIR:
            reqMsgSize = sizeof(struct tisci_msg_rm_psil_pair_req);
            respMsgSize = sizeof(struct tisci_msg_rm_psil_pair_resp);
            break;
        case TISCI_MSG_RM_PSIL_UNPAIR:
            reqMsgSize = sizeof(struct tisci_msg_rm_psil_unpair_req);
            respMsgSize = sizeof(struct tisci_msg_rm_psil_unpair_resp);
            break;
        case TISCI_MSG_RM_PSIL_READ:
            reqMsgSize = sizeof(struct tisci_msg_rm_psil_read_req);
            respMsgSize = sizeof(struct tisci_msg_rm_psil_read_resp);
            break;
        case TISCI_MSG_RM_PSIL_WRITE:
            reqMsgSize = sizeof(struct tisci_msg_rm_psil_write_req);
            respMsgSize = sizeof(struct tisci_msg_rm_psil_write_resp);
            break;
        case TISCI_MSG_RM_PROXY_CFG:
            reqMsgSize = sizeof(struct tisci_msg_rm_proxy_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_proxy_cfg_resp);
            break;
        /* Start of PM messages */
        case TISCI_MSG_BOARD_CONFIG_PM:
            reqMsgSize = sizeof(struct tisci_msg_board_config_pm_req);
            respMsgSize = sizeof(struct tisci_msg_board_config_pm_resp);
            break;
        case TISCI_MSG_SET_CLOCK:
            reqMsgSize = sizeof(struct tisci_msg_set_clock_req);
            respMsgSize = sizeof(struct tisci_msg_set_clock_resp);
            break;
        case TISCI_MSG_GET_CLOCK:
            reqMsgSize = sizeof(struct tisci_msg_get_clock_req);
            respMsgSize = sizeof(struct tisci_msg_get_clock_resp);
            break;
        case TISCI_MSG_SET_CLOCK_PARENT:
            reqMsgSize = sizeof(struct tisci_msg_set_clock_parent_req);
            respMsgSize = sizeof(struct tisci_msg_set_clock_parent_resp);
            break;
        case TISCI_MSG_GET_CLOCK_PARENT:
            reqMsgSize = sizeof(struct tisci_msg_get_clock_parent_req);
            respMsgSize = sizeof(struct tisci_msg_get_clock_parent_resp);
            break;
        case TISCI_MSG_GET_NUM_CLOCK_PARENTS:
            reqMsgSize = sizeof(struct tisci_msg_get_num_clock_parents_req);
            respMsgSize = sizeof(struct tisci_msg_get_num_clock_parents_resp);
            break;
        case TISCI_MSG_SET_FREQ:
            reqMsgSize = sizeof(struct tisci_msg_set_freq_req);
            respMsgSize = sizeof(struct tisci_msg_set_freq_resp);
            break;
        case TISCI_MSG_QUERY_FREQ:
            reqMsgSize = sizeof(struct tisci_msg_query_freq_req);
            respMsgSize = sizeof(struct tisci_msg_query_freq_resp);
            break;
        case TISCI_MSG_GET_FREQ:
            reqMsgSize = sizeof(struct tisci_msg_get_freq_req);
            respMsgSize = sizeof(struct tisci_msg_get_freq_resp);
            break;
        case TISCI_MSG_SET_DEVICE:
            reqMsgSize = sizeof(struct tisci_msg_set_device_req);
            respMsgSize = sizeof(struct tisci_msg_set_device_resp);
            break;
        case TISCI_MSG_GET_DEVICE:
            reqMsgSize = sizeof(struct tisci_msg_get_device_req);
            respMsgSize = sizeof(struct tisci_msg_get_device_resp);
            break;
        case TISCI_MSG_SET_DEVICE_RESETS:
            reqMsgSize = sizeof(struct tisci_msg_set_device_resets_req);
            respMsgSize = sizeof(struct tisci_msg_set_device_resets_resp);
            break;
        case TISCI_MSG_SYS_RESET:
            reqMsgSize = sizeof(struct tisci_msg_sys_reset_req);
            respMsgSize = sizeof(struct tisci_msg_sys_reset_resp);
            break;
        default:
            /* Forward the full message size */
            reqMsgSize = SCISERVER_HW_QUEUE_SIZE;
            respMsgSize = SCISERVER_HW_QUEUE_SIZE;
            break;
    }

    switch (hdr->type)
    {
        case TISCI_MSG_RM_IRQ_SET:
        case TISCI_MSG_RM_RING_CFG:
        case TISCI_MSG_RM_RING_MON_CFG:
        case TISCI_MSG_RM_UDMAP_TX_CH_CFG:
        case TISCI_MSG_RM_UDMAP_RX_CH_CFG:
        case TISCI_MSG_RM_PROXY_CFG:
            if (hw_host_id == TISCI_HOST_ID_DMSC2DM)
            {
                runLocalRmOnly = 1;
            }
            break;
        default:
         /* Do-Nothing */
            break;
    }

    if (runLocalRmOnly == 1)
    {
        ret = Sciclient_ProcessRmMessage(msg_recv);
    }
    else
    {
        ret = Sciserver_ProcessFullMessage(msg_recv,
                                           reqMsgSize, respMsgSize);
    }

    *pRespMsgSize = respMsgSize;

    return ret;
}

