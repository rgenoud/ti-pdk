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
 *  \file sciclient_direct.c
 *
 *  \brief File containing the SCICLIENT driver APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/drv/sciclient/soc/sysfw/include/tisci/tisci_protocol.h>
#include <boardcfg/boardcfg.h>
#include <startup.h>
#include <pm.h>
#include <rm.h>
/* Sciclient APIs are kept in the end of the include list to make sure the 
 * RM and PM HAL typedefs are used.
 */
#include <ti/drv/sciclient/sciclient.h>
#include <ti/drv/sciclient/src/sciclient/sciclient_priv.h>

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

int32_t Sciclient_ProcessRmMessage(void *tx_msg);
int32_t Sciclient_ProcessPmMessage (void *tx_msg);
static int32_t board_config_pm_handler(uint32_t *msg_recv);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t Sciclient_service (const Sciclient_ReqPrm_t *pReqPrm,
                           Sciclient_RespPrm_t      *pRespPrm)
{
    int32_t ret = CSL_PASS;
    uint32_t msgType = pReqPrm->messageType;
    uint32_t message[20] = {0};
    struct tisci_header *hdr;
    uint8_t localSeqId;
    uint32_t contextId;
    uint32_t txThread __attribute__((unused));
    uint32_t rxThread __attribute__((unused));

    if ((pReqPrm == NULL) || (pRespPrm == NULL))
    {
        ret = CSL_EBADARGS;
    }
    if (CSL_PASS == ret)
    {
        ret = Sciclient_serviceGetThreadIds (pReqPrm, &contextId, &txThread,
                                         &rxThread);
    }
    if (CSL_PASS == ret)
    {
        ret = Sciclient_servicePrepareHeader(pReqPrm, &localSeqId,
                 contextId, &hdr);
    }
    if (CSL_PASS == ret)
    {
        switch (msgType) {
            case TISCI_MSG_BOARD_CONFIG_PM:
            case TISCI_MSG_SET_CLOCK:
            case TISCI_MSG_GET_CLOCK:
            case TISCI_MSG_SET_CLOCK_PARENT:
            case TISCI_MSG_GET_CLOCK_PARENT:
            case TISCI_MSG_GET_NUM_CLOCK_PARENTS:
            case TISCI_MSG_SET_FREQ:
            case TISCI_MSG_QUERY_FREQ:
            case TISCI_MSG_GET_FREQ:
            case TISCI_MSG_SET_DEVICE:
            case TISCI_MSG_GET_DEVICE:
            case TISCI_MSG_SET_DEVICE_RESETS:
                memcpy(message, pReqPrm->pReqPayload, pReqPrm->reqPayloadSize);
                ret = Sciclient_ProcessPmMessage(message);
                if (pRespPrm->pRespPayload != NULL)
                {
                    memcpy(pRespPrm->pRespPayload, message, pRespPrm->respPayloadSize);
                }
                hdr = (struct tisci_header *) &message;
                pRespPrm->flags = hdr->flags;
                break;
            case TISCI_MSG_BOARD_CONFIG_RM:
            case TISCI_MSG_RM_GET_RESOURCE_RANGE:
            case TISCI_MSG_RM_IRQ_SET:
            case TISCI_MSG_RM_IRQ_RELEASE:
            case TISCI_MSG_RM_RING_CFG:
            case TISCI_MSG_RM_RING_MON_CFG:
            case TISCI_MSG_RM_UDMAP_TX_CH_CFG:
            case TISCI_MSG_RM_UDMAP_RX_CH_CFG:
            case TISCI_MSG_RM_UDMAP_FLOW_CFG:
            case TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG:
            case TISCI_MSG_RM_UDMAP_FLOW_DELEGATE:
            case TISCI_MSG_RM_UDMAP_GCFG_CFG:
            case TISCI_MSG_RM_PROXY_CFG:
                memcpy(message, pReqPrm->pReqPayload, pReqPrm->reqPayloadSize);
                ret = Sciclient_ProcessRmMessage(message);
                if (pRespPrm->pRespPayload != NULL)
                {
                    memcpy(pRespPrm->pRespPayload, message, pRespPrm->respPayloadSize);
                }
                hdr = (struct tisci_header *) &message;
                pRespPrm->flags = hdr->flags;
                break;
            case TISCI_MSG_RM_PSIL_PAIR:
            case TISCI_MSG_RM_PSIL_UNPAIR:
            case TISCI_MSG_RM_PSIL_READ:
            case TISCI_MSG_RM_PSIL_WRITE:
            default:
                ret = Sciclient_serviceSecureProxy(pReqPrm, pRespPrm);
        }
    }

    return ret;
}

void Sciclient_TisciMsgSetAckResp(struct tisci_header *hdr)
{
    hdr->flags |= TISCI_MSG_FLAG_ACK;
}

void Sciclient_TisciMsgSetNakResp(struct tisci_header *hdr)
{
    hdr->flags &= (~TISCI_MSG_FLAG_ACK);
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static int32_t board_config_pm_handler(uint32_t *msg_recv)
{
    int32_t ret;
    struct tisci_msg_board_config_pm_req *req =
        (struct tisci_msg_board_config_pm_req *) msg_recv;

    ret = boardcfg_pm_receive_and_validate(req->hdr.host,
                           req->tisci_boardcfg_pmp_low,
                           req->tisci_boardcfg_pmp_high,
                           req->tisci_boardcfg_pm_size,
                           req->tisci_boardcfg_pm_devgrp);

    if (ret == CSL_PASS) {
        ret = pm_init();
    }

    return ret;
}

int32_t Sciclient_ProcessPmMessage (void *tx_msg)
{
    int32_t ret = CSL_PASS;
    uint32_t msg_inval = 0U;
    uint32_t msgType = ((struct tisci_header *) tx_msg)->type;
    uint32_t flags = ((struct tisci_header *) tx_msg)->flags;
    switch (msgType)
    {
        case TISCI_MSG_BOARD_CONFIG_PM         :
            ret = board_config_pm_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_CLOCK               :
            ret = set_clock_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_GET_CLOCK               :
            ret = get_clock_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_CLOCK_PARENT        :
            ret = set_clock_parent_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_GET_CLOCK_PARENT        :
            ret = get_clock_parent_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_GET_NUM_CLOCK_PARENTS   :
            ret = get_num_clock_parents_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_FREQ                :
            ret = set_freq_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_QUERY_FREQ              :
            ret = query_freq_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_GET_FREQ                :
            ret = get_freq_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_DEVICE              :
            ret = set_device_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_GET_DEVICE              :
            ret = get_device_handler((uint32_t*)tx_msg); break;
        case TISCI_MSG_SET_DEVICE_RESETS       :
            ret = set_device_resets_handler((uint32_t*)tx_msg); break;
        default:
            ret = CSL_EFAIL; msg_inval = 1U;
    }
    if ((flags & TISCI_MSG_FLAG_AOP) != 0UL) {
        if (ret == CSL_PASS) {
            Sciclient_TisciMsgSetAckResp((struct tisci_header *) tx_msg);
        } else {
            Sciclient_TisciMsgSetNakResp((struct tisci_header *) tx_msg);
        }
    }
    /*
     * Avoid overwriting status of calling message handler if the message
     * handler has a failure status.
     */
    if ((ret != CSL_PASS) && !msg_inval) {
        /*
         * NACK will be sent in message if error so send CSL_PASS back
         * in return status
         */
        ret = CSL_PASS;
    }
    return ret;
}

static int32_t tisci_msg_board_config_rm_handler(uint32_t *msg_recv)
{
    int32_t r = CSL_PASS;
    struct tisci_msg_board_config_rm_req *req =
        (struct tisci_msg_board_config_rm_req *) msg_recv;

    r = boardcfg_rm_receive_and_validate(req->hdr.host,
                         req->tisci_boardcfg_rmp_low,
                         req->tisci_boardcfg_rmp_high,
                         req->tisci_boardcfg_rm_size,
                         req->tisci_boardcfg_rm_devgrp);

    if (r == CSL_PASS) {
        r = rm_init();
    }

    return r;
}

int32_t Sciclient_ProcessRmMessage(void *tx_msg)
{
    int32_t r = CSL_PASS;
    uint32_t msg_inval = 0U;
    uint32_t msgType = ((struct tisci_header *) tx_msg)->type;

    switch (msgType) {
        case TISCI_MSG_BOARD_CONFIG_RM:
            r = tisci_msg_board_config_rm_handler((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_GET_RESOURCE_RANGE:
            r = rm_core_get_resource_range((uint32_t *)tx_msg, (uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_IRQ_SET:
            r = rm_irq_set((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_IRQ_RELEASE:
            r = rm_irq_release((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_RING_CFG:
            r = rm_ra_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_RING_MON_CFG:
            r = rm_ra_mon_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_TX_CH_CFG:
            r = rm_udmap_tx_ch_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_RX_CH_CFG:
            r = rm_udmap_rx_ch_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_CFG:
            r = rm_udmap_flow_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_SIZE_THRESH_CFG:
            r = rm_udmap_flow_size_thresh_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_FLOW_DELEGATE:
            r = rm_udmap_flow_delegate((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_UDMAP_GCFG_CFG:
            r = rm_udmap_gcfg_cfg((uint32_t *)tx_msg);
            break;
        case TISCI_MSG_RM_PROXY_CFG:
            r = rm_proxy_cfg((uint32_t *)tx_msg);
            break;
        default:
            r = CSL_EFAIL;
            msg_inval = 1U;
            break;
    }

    if ((((struct tisci_header *) tx_msg)->flags & TISCI_MSG_FLAG_AOP) != 0) {
        if (r != CSL_PASS) {
            Sciclient_TisciMsgSetNakResp((struct tisci_header *)tx_msg);
        } else {
            Sciclient_TisciMsgSetAckResp((struct tisci_header *)tx_msg);
        }
    }

    /*
     * Avoid overwriting status of calling message handler if the message
     * handler has a failure status.
     */
    if ((r != CSL_PASS) && !msg_inval) {
        /*
         * NACK will be sent in message if error so send CSL_PASS back
         * in return status
         */
        r = CSL_PASS;
    }

    return r;
}
