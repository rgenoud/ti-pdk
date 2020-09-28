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
#include <sciserver_hwiData.h>
#include <ti/drv/uart/UART_stdio.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

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
                                        int32_t *pRespMsgSize);

static void Sciserver_TisciMsgClearFlags(struct tisci_header *hdr);
static int32_t Sciserver_TisciMsgResponse(uint8_t   response_host,
                                   uint32_t  *response,
                                   uint32_t  size);
static void Sciserver_SetMsgHostId(uint32_t *msg, uint8_t hostId);
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** Global state of the Sciserver */
static Sciserver_InternalState_t gSciserverState = {
    SCISERVER_CTRL_CMD_HALT,
    SCISERVER_PROCESS_STATE_WAIT,
    SCISERVER_INIT_NOT_DONE
};


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Sciserver_init(Sciserver_CfgPrms_t *pPrms)
{
    int32_t ret = CSL_PASS;
    Sciclient_ConfigPrms_t        config =
    {
        SCICLIENT_SERVICE_OPERATION_MODE_POLLED,
        NULL,
        1
    };
    if (gSciserverState.initDone == SCISERVER_INIT_NOT_DONE)
    {
        if (pPrms == NULL)
        {
            ret = CSL_EBADARGS;
        }
        if (CSL_PASS == ret)
        {
            ret = Sciclient_init(&config);
        }
        /* Run pm_init */
        if (CSL_PASS == ret)
        {
            ret = Sciclient_boardCfgPm(&pPrms->inPmPrms);
        }
        /* Run rm_init */
        if (CSL_PASS == ret)
        {
            ret = Sciclient_boardCfgRm(&pPrms->inRmPrms);
        }
        if (CSL_PASS == ret)
        {
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

int32_t Sciserver_deinit()
{
    int32_t ret = CSL_PASS;
    
    if (gSciserverState.initDone == SCISERVER_INIT_DONE)
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

uint8_t Sciserver_getCtrlState ()
{
   return gSciserverState.ctrlState;
}

void Sciserver_setProcessState (uint8_t state)
{
    gSciserverState.processState = state;
}

uint8_t Sciserver_getProcessState ()
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
        uhd->user_msg_data->host = hw_host;
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
    int32_t respMsgSize;
    /* the response message pointer */
    uint32_t *respMsg;
    /* the response message header pointer. Same as respMsg */
    struct tisci_header *respMsgHeader;

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
        UART_printf("processtask: UserProcessMsg\n");
        ret = Sciserver_UserProcessMsg(
                utd->hw_msg_buffer_list[utd->state->current_buffer_idx],
                &respMsgSize);
        respMsg = utd->hw_msg_buffer_list[utd->state->current_buffer_idx];
        respMsgHeader = (struct tisci_header *) respMsg;
    }
    else
    {
        ret = CSL_EFAIL;
    }

    if (ret == CSL_PASS)
    {
        Sciclient_TisciMsgSetAckResp(respMsgHeader);
    }
    else if ((respMsgHeader->flags & TISCI_MSG_FLAG_AOP) != 0)
    {
        Sciserver_TisciMsgClearFlags(respMsgHeader);
        Sciclient_TisciMsgSetNakResp(respMsgHeader);
    }

    respHost = utd->user_msg_data[utd->state->current_buffer_idx]->host;
    if (respHost == TISCI_HOST_ID_DMSC2DM)
    {
        /* DMSC2DM is processed by DM. Need to update response message value
         * so the host verification on TIFS can succeed */
        Sciserver_SetMsgHostId(respMsg, TISCI_HOST_ID_DM);
    }

    ret = Sciserver_TisciMsgResponse(respHost, respMsg, respMsgSize);

    if (ret == CSL_PASS)
    {
        utd->user_msg_data[utd->state->current_buffer_idx]->is_pending = false;
    }

    utd->state->state = SCISERVER_TASK_PENDING;

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

    if (ret == CSL_PASS) {
        if (hdr->host != known_host) {
            ret = CSL_EFAIL;
        }
    }

    return ret;
}


static void Sciserver_TisciMsgClearFlags(struct tisci_header *hdr)
{
    hdr->flags = 0;
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

int32_t Sciserver_ProcessForwardedMessage(uint32_t *msg_recv,
    int32_t reqMsgSize,
    int32_t respMsgSize)
{
    int32_t ret = CSL_EFAIL;
    Sciclient_ReqPrm_t reqPrm;
    Sciclient_RespPrm_t respPrm;
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

    respPrm.flags = 0;
    respPrm.pRespPayload = (uint8_t *) respMsgBuffer;
    respPrm.respPayloadSize = respMsgSize;

    ret = Sciclient_service(&reqPrm, &respPrm);

    if ((CSL_PASS == ret) && (respPrm.flags == TISCI_MSG_FLAG_ACK))
    {
        UART_printf("Sciserver_ProcessForwardedMessage: success type=%d\n", hdr->type);
        memcpy(msg_recv, respMsgBuffer, respMsgSize);

        /* Must restore the seq field. When forwarded message is processed by
         * TIFS, the returned message would have incorrect sequence value */
        hdr->seq = reqSeq;
    }
    else
    {
        UART_printf("Sciserver_ProcessForwardedMessage: failed type=%d\n", hdr->type);
        ret = CSL_EFAIL;
    }

    return ret;
}

static int32_t Sciserver_UserProcessMsg(uint32_t *msg_recv,
                                        int32_t *pRespMsgSize)
{
    int32_t ret = CSL_PASS;
    struct  tisci_header *hdr = (struct tisci_header *) msg_recv;
    int32_t isRmMsg = 0, isPmMsg = 0, isFwdMsg = 0;
    int32_t reqMsgSize;
    int32_t respMsgSize;

    UART_printf("hdr->type = %d\n", hdr->type);
    UART_printf("hdr->host = %d\n", hdr->host);

    switch (hdr->type)
    {
        case TISCI_MSG_VERSION:
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_version_req);
            respMsgSize = sizeof(struct tisci_msg_version_resp);
            break;
        /* Start of RM messages */
        case TISCI_MSG_BOARD_CONFIG_RM:
            isRmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_board_config_rm_resp);
            break;
        case TISCI_MSG_RM_GET_RESOURCE_RANGE:
            isRmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_rm_get_resource_range_resp);
            break;
        case TISCI_MSG_RM_IRQ_SET:
            isRmMsg = 1;
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_irq_set_req);
            respMsgSize = sizeof(struct tisci_msg_rm_irq_set_resp);
            break;
        case TISCI_MSG_RM_IRQ_RELEASE:
            isRmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_rm_irq_release_resp);
            break;
        case TISCI_MSG_RM_RING_CFG:
            isRmMsg = 1;
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_ring_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_ring_cfg_resp);
            break;
        case TISCI_MSG_RM_RING_MON_CFG:
            isRmMsg = 1;
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_ring_mon_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_ring_mon_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_TX_CH_CFG:
            isRmMsg = 1;
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_udmap_tx_ch_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_tx_ch_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_RX_CH_CFG:
            isRmMsg = 1;
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_udmap_rx_ch_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_rx_ch_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_CFG:
            isRmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_flow_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG:
            isRmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_flow_size_thresh_cfg_resp);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_DELEGATE:
            isRmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_flow_delegate_resp);
            break;
        case TISCI_MSG_RM_UDMAP_GCFG_CFG:
            isRmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_rm_udmap_gcfg_cfg_resp);
            break;
        case TISCI_MSG_RM_PSIL_PAIR:
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_psil_pair_req);
            respMsgSize = sizeof(struct tisci_msg_rm_psil_pair_resp);
            break;
        case TISCI_MSG_RM_PSIL_UNPAIR:
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_psil_unpair_req);
            respMsgSize = sizeof(struct tisci_msg_rm_psil_unpair_resp);
            break;
        case TISCI_MSG_RM_PSIL_READ:
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_psil_read_req);
            respMsgSize = sizeof(struct tisci_msg_rm_psil_read_resp);
            break;
        case TISCI_MSG_RM_PSIL_WRITE:
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_psil_write_req);
            respMsgSize = sizeof(struct tisci_msg_rm_psil_write_resp);
            break;
        case TISCI_MSG_RM_PROXY_CFG:
            isFwdMsg = 1;
            reqMsgSize = sizeof(struct tisci_msg_rm_proxy_cfg_req);
            respMsgSize = sizeof(struct tisci_msg_rm_proxy_cfg_resp);
            break;
        /* Start of PM messages */
        case TISCI_MSG_BOARD_CONFIG_PM:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_board_config_pm_resp);
            break;
        case TISCI_MSG_SET_CLOCK:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_set_clock_resp);
            break;
        case TISCI_MSG_GET_CLOCK:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_get_clock_resp);
            break;
        case TISCI_MSG_SET_CLOCK_PARENT:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_set_clock_parent_resp);
            break;
        case TISCI_MSG_GET_CLOCK_PARENT:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_get_clock_parent_resp);
            break;
        case TISCI_MSG_GET_NUM_CLOCK_PARENTS:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_get_num_clock_parents_resp);
            break;
        case TISCI_MSG_SET_FREQ:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_set_freq_resp);
            break;
        case TISCI_MSG_QUERY_FREQ:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_query_freq_resp);
            break;
        case TISCI_MSG_GET_FREQ:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_get_freq_resp);
            break;
        case TISCI_MSG_SET_DEVICE:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_set_device_resp);
            break;
        case TISCI_MSG_GET_DEVICE:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_get_device_resp);
            break;
        case TISCI_MSG_SET_DEVICE_RESETS:
            isPmMsg = 1;
            respMsgSize = sizeof(struct tisci_msg_set_device_resets_resp);
            break;

        default:
            isRmMsg = 0;
            isPmMsg = 0;
            isPmMsg = 0;
            respMsgSize = sizeof(struct tisci_header);
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
            if (hdr->host == TISCI_HOST_ID_DMSC2DM)
            {
                UART_printf("Skip forward: type = %d\n", hdr->type);
                isFwdMsg = 0;
                isRmMsg = 1;
            }
            break;
    }

    if (isRmMsg)
    {
        extern int32_t Sciclient_ProcessRmMessage(void *tx_msg);
        ret = Sciclient_ProcessRmMessage(msg_recv);
    }

    if (isPmMsg)
    {
        extern int32_t Sciclient_ProcessPmMessage(void *tx_msg);
        ret = Sciclient_ProcessPmMessage(msg_recv);
    }

    if (isFwdMsg)
    {
        ret = Sciserver_ProcessForwardedMessage(msg_recv,
                                                reqMsgSize, respMsgSize);
    }

    if (hdr->type == TISCI_MSG_GET_FREQ)
    {
        struct tisci_msg_get_freq_resp *respGetFreq = (struct tisci_msg_get_freq_resp *) msg_recv;
        uint32_t freq = respGetFreq->freq_hz & 0xFFFFFFFF;
        UART_printf("GET_FREQ = %d MHz\n", freq/1000000);
    }

    *pRespMsgSize = respMsgSize;

    return ret;
}

