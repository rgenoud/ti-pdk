/**
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/**
 *  Copyright (c) Texas Instruments Incorporated 2021
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
 * This file is dervied from the ``ethernetif.c'' skeleton Ethernet network
 * interface driver for lwIP.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* Standard language headers */
#include <stdio.h>

#include <ti/osal/osal.h>
#include <ti/osal/TaskP.h>
#include <ti/osal/SemaphoreP.h>
#include <ti/osal/ClockP.h>
#include <ti/osal/DebugP.h>

/* lwIP specific header files */
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include <lwip/netifapi.h>
#include "netif/etharp.h"
#include "netif/ppp/pppoe.h"

/* This module's header */
#include "lwip2enet.h"
#include "lwip2lwipif.h"
#include "lwipopts.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Define those to better describe your network interface. */
#define IFNAME0 't'
#define IFNAME1 'i'

#define ENETLWIPAPP_POLL_PERIOD      500

#define OS_TASKPRIHIGH               7

#define LWIP_RX_PACKET_TASK_STACK    (4096)

#define LWIP_POLL_TASK_PRI           (OS_TASKPRIHIGH)

/* Ethernet MTU */
#define ETH_FRAME_MTU                (1500U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Called by the stack to send a packet on the Enet interface.
 */
static err_t LWIPIF_LWIP_send(struct netif *netif,
                              struct pbuf *pbuf)
{
    Lwip2Enet_Handle hLwip2Enet;

    /* Get the pointer to the private data */
    hLwip2Enet = (Lwip2Enet_Handle)netif->state;

    /*
     * When transmitting a packet, the buffer may be deleted before transmission by the
     * stack. The stack implements a 'ref' feature within the buffers. The following happens
     * internally:
     *  If p->ref > 1, ref--;
     *  If p->ref == 1, free(p);
     * pbuf_ref(p) increments the ref.
     */
    pbuf_ref(pbuf);

    /* Enqueue the packet */
    Lwip2EnetQ_enq(&hLwip2Enet->tx.readyPbufQ, pbuf);
    Lwip2EnetStats_addOne(&hLwip2Enet->tx.stats.readyPbufPktEnq);

    /* Pass the packet to the translation layer */
    Lwip2Enet_sendTxPackets(&hLwip2Enet->tx);

    /* Packet has been successfully transmitted or enqueued to be sent when link comes up */
    return ERR_OK;
}

/*
 * Called by RX packet task to pass the received packets up to the TCP/IP stack.
 */
void LWIPIF_LWIP_input(struct netif *netif,
                       Lwip2Enet_RxObj *rx,
                       struct pbuf *pbuf)
{
    uint32_t bufSize;

    /* Pass the packet to the LwIP stack */
    if (netif->input(pbuf, netif) != ERR_OK)
    {
        LWIP_DEBUGF(NETIF_DEBUG, ("lwipif_input: IP input error\n"));
        pbuf_free(pbuf);
        pbuf = NULL;
    }
    else
    {
        Lwip2EnetStats_addOne(&rx->stats.stackNotifyCnt);

        /* Allocate a new Pbuf packet to be used */
        bufSize = ENET_UTILS_ALIGN(PBUF_POOL_BUFSIZE, ENETDMA_CACHELINE_ALIGNMENT);

        pbuf = pbuf_alloc(PBUF_RAW, bufSize, PBUF_POOL);
        if (pbuf != NULL)
        {
            Lwip2Enet_assert(pbuf->payload != NULL);

            /* Ensures that the ethernet frame is always on a fresh cacheline */
            Lwip2Enet_assert(ENET_UTILS_IS_ALIGNED(pbuf->payload, ENETDMA_CACHELINE_ALIGNMENT));

            /* Put the new packet on the free queue */
            Lwip2EnetQ_enq(&rx->freePbufQ, pbuf);
            Lwip2EnetStats_addOne(&rx->stats.freePbufPktEnq);
        }
    }
}

/*
 * Periodically polls for changes in the link status and updates both the abstraction layer
 * as well as the stack.
 */
static void LWIPIF_LWIP_poll(void *arg0, void *arg1)
{
    struct netif* netif = (struct netif*)arg0;
    SemaphoreP_Handle hLinkPollSem = (SemaphoreP_Handle)arg1;
    Lwip2Enet_Handle hLwip2Enet = (Lwip2Enet_Handle)netif->state;

    while (!hLwip2Enet->shutDownFlag)
    {
        SemaphoreP_pend(hLinkPollSem, SemaphoreP_WAIT_FOREVER);

        /* Query link status */
        Lwip2Enet_periodicFxn(hLwip2Enet);

        if (!(hLwip2Enet->linkIsUp == (netif->flags & 0x04U)>>2))
        {
            if (hLwip2Enet->linkIsUp)
            {
                sys_lock_tcpip_core();
                netif_set_link_up(netif);
                sys_unlock_tcpip_core();
            }
            else
            {
                sys_lock_tcpip_core();
                netif_set_link_down(netif);
                sys_unlock_tcpip_core();
            }
        }
    }
}

/*
 * Link poll timer callback function.
 */
static void LWIPIF_LWIP_pollTimerCb(void *arg)
{
    SemaphoreP_Handle hLinkPollSem = (SemaphoreP_Handle)arg;

    SemaphoreP_post(hLinkPollSem);
}

/*
 * Start the Enet LLD interface and start the polling timer.
 */
static err_t LWIPIF_LWIP_start(struct netif *netif)
{
    Lwip2Enet_Handle hLwip2Enet;
    TaskP_Params taskParams;
    SemaphoreP_Params semParams;
    ClockP_Params clkParams;
    err_t status = ERR_IF;

    /* Open the translation layer, which itself opens the hardware driver */
    hLwip2Enet = Lwip2Enet_open(netif);

    if (NULL != hLwip2Enet)
    {
        /* Save off a pointer to the translation layer */
        netif->state = (void *)hLwip2Enet;

        /* Initialize link poll semaphore, which is posted by timer */
        SemaphoreP_Params_init(&semParams);
        semParams.mode = SemaphoreP_Mode_BINARY;
        hLwip2Enet->hLinkPollSem = SemaphoreP_create(0U, &semParams);
        Lwip2Enet_assert(NULL != hLwip2Enet->hLinkPollSem);

        /* Initialize the poll function as a thread */
        TaskP_Params_init(&taskParams);
        taskParams.name      = (uint8_t *)"lwip_link_poll";
        taskParams.priority  = LWIP_POLL_TASK_PRI;
        taskParams.stack     = &hLwip2Enet->pollTaskStack[0U];
        taskParams.stacksize = sizeof(hLwip2Enet->pollTaskStack);
        taskParams.arg0      = netif;
        taskParams.arg1      = hLwip2Enet->hLinkPollSem;

        hLwip2Enet->hLinkPollTask = TaskP_create((void *)&LWIPIF_LWIP_poll, &taskParams);
        Lwip2Enet_assert(NULL != hLwip2Enet->hLinkPollTask);

        ClockP_Params_init(&clkParams);
        clkParams.startMode = ClockP_StartMode_AUTO;
        clkParams.runMode   = ClockP_RunMode_CONTINUOUS;
        clkParams.period    = ENETLWIPAPP_POLL_PERIOD;
        clkParams.arg       = (hLwip2Enet->hLinkPollSem);

        /* Creating timer and setting timer callback function */
        hLwip2Enet->hPollTimer = ClockP_create((void *)&LWIPIF_LWIP_pollTimerCb, &clkParams);
        Lwip2Enet_assert(NULL != hLwip2Enet->hPollTimer);

        /* First RX channel/flow must be enabled, as it's the 'default' RX object
         * whose MAC address is used in this adaptation layer */
        Lwip2Enet_assert(hLwip2Enet->rx[0U].enabled);

        /* Copy the MAC Address into the network interface object here. */
        memcpy(netif->hwaddr, &hLwip2Enet->rx[0U].macAddr, (uint32_t)6U);
        netif->hwaddr_len = 6U;

        status = ERR_OK;
    }

    return status;
}

/*
 * Stop polling timer and close Enet LLD TX/RX channels.
 */
static void LWIPIF_LWIP_stop(struct netif *netif)
{
    Lwip2Enet_Handle hLwip2Enet = (Lwip2Enet_Handle)netif->state;

    /* Stop and delete poll timer */
    if (hLwip2Enet->hPollTimer != NULL)
    {
        ClockP_stop(hLwip2Enet->hPollTimer);
        ClockP_delete(hLwip2Enet->hPollTimer);
        hLwip2Enet->hPollTimer = NULL;
    }

    /* Delete link poll semaphore */
    if (hLwip2Enet->hLinkPollSem != NULL)
    {
        SemaphoreP_delete(hLwip2Enet->hLinkPollSem);
        hLwip2Enet->hLinkPollSem = NULL;
    }

    /* Call low-level close function */
    Lwip2Enet_close(hLwip2Enet);
}

/*
 * Populate parameters/ops for the Enet LLD based netif and start it.
 * This function is expected to be called when adding the netif via netif_add().
 */
err_t LWIPIF_LWIP_init(struct netif *netif)
{
    err_t status;

#ifdef LWIPIF_CHECKSUM_SUPPORT
    /* TODO: Add checksum support */
#endif

    /* Populate the Network Interface Object */
    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;

    /*
     * MTU is the total size of the (IP) packet that can fit into an Ethernet.
     * For Ethernet it is 1500bytes
     */
    netif->mtu = ETH_FRAME_MTU;

    /* Populate the netif's operation functions */
    netif->remove_callback      = LWIPIF_LWIP_stop;
    netif->output               = etharp_output;
    netif->linkoutput           = LWIPIF_LWIP_send;
    netif->flags               |= NETIF_FLAG_ETHARP;
    netif->flags               |= NETIF_FLAG_ETHERNET;

    status = LWIPIF_LWIP_start(netif);
    if (status == ERR_OK)
    {
        EnetUtils_printf("[LWIPIF_LWIP] Enet LLD netif initialized successfully\n");
    }
    else
    {
        EnetUtils_printf("[LWIPIF_LWIP] Failed to initialize Enet LLD netif: %d\n", status);
    }

    return status;
}
