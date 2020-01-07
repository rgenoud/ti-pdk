/*
 * Copyright (c) 2016, Texas Instruments Incorporated
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
/*
 *  ======== HwiP_linux.c ========
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/neutrino.h>
#include <ti/osal/HwiP.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define QNX_DEBUG_PRINT(f_, ...) printf((f_), ##__VA_ARGS__);
#define QNX_TRACE_PRINT printf("-> %s: entered\n", __func__);
#define QNX_TRACE_PRINT_DONE printf("<- %s: exit\n", __func__);

static int hwip_chid = -1; // Channel ID per process

static int threadSpawned = 0;

intrspin_t spinlock;

#define ISR_PULSE		_PULSE_CODE_MINAVAIL

/* Assume a maximum of 1024 interrupt events supported by 1 process */
#define OSAL_QNX_INTERRUPT_MAX 1024

/* Parameters stored per IRQ */
struct    sigevent isr_event[OSAL_QNX_INTERRUPT_MAX];
HwiP_Fxn  hwiFxns[OSAL_QNX_INTERRUPT_MAX];
uintptr_t hwiFxns_arg[OSAL_QNX_INTERRUPT_MAX];
uint32_t  irq_autoEnable[OSAL_QNX_INTERRUPT_MAX];

/* Thread level ISR handler */
void *isr_thread (HwiP_Fxn hwiFxn)
{

	int			    rcvid;
    struct _pulse	pulse;
    uintptr_t       interruptNum;

    while (1) {
        rcvid = MsgReceivePulse(hwip_chid, &pulse, sizeof(struct _pulse), NULL);
	    if (rcvid != -1) {
	        switch (pulse.code) {
				case ISR_PULSE:
					interruptNum = pulse.value.sival_int;
                    /* Call the callback function */
                    hwiFxns[interruptNum](hwiFxns_arg[interruptNum]);

                    /* Check if application wants interrupt re-enabled */
                    if(irq_autoEnable[interruptNum] == 1) {
                        HwiP_enableInterrupt(interruptNum);
                    }
					break;
				default:
					printf("%s: Rx Unknown pulse %d received\n",__func__, pulse.code);
					break;
	        }
	    }
	    else {
            /* TODO */
	        delay(20);
	    }
    }

    return NULL;
}

/*
 *  ======== HwiP_clearInterrupt ========
 */
void HwiP_clearInterrupt(int32_t interruptNum)
{
  /* Empty */
}

/*
 *  ======== HwiP_create ========
 */
HwiP_Handle HwiP_create(int32_t interruptNum, HwiP_Fxn hwiFxn,
                        const HwiP_Params *params)
{
    pthread_attr_t thread_attr;
    uint32_t evtId;

    if(threadSpawned == 0)
    {
		    // Spawn an interrupt handler thread
		    pthread_attr_init(&thread_attr);
		    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

		    if (pthread_create(NULL, &thread_attr, (void *) isr_thread, hwiFxn) != EOK) {
			    printf("%s: Unable to create isr thread\n", __FUNCTION__);
		    }
		    else {
			    threadSpawned = 1;
		}
    }

	/* Init the pulse for interrupt event */
	isr_event[interruptNum].sigev_notify = SIGEV_PULSE;
	isr_event[interruptNum].sigev_code = ISR_PULSE;
	isr_event[interruptNum].sigev_coid = ConnectAttach(0, 0, hwip_chid, _NTO_SIDE_CHANNEL, 0);
	isr_event[interruptNum].sigev_priority = 21;		/* service interrupts at a higher priority then client requests */
	isr_event[interruptNum].sigev_value.sival_int = interruptNum;


    /* Store pointer to the argument that should be passed back to the ISR routine */
    hwiFxns_arg[interruptNum] = params->arg;

    /* Store pointer to the ISR routine */
    hwiFxns[interruptNum] = hwiFxn;

    /* Store whether interrupt should automatically be re-neabled
     * after calling ISR Routine */
    irq_autoEnable[interruptNum] = params->autoEnable;

    /*
     * Attach interrupt handler (thread level)
     *
     * _NTO_INTR_FLAGS_TRK_MSK - Track mask/unmask
     * _NTO_INTR_FLAGS_NO_UNMASK - Start with interrupt masked
     */

    evtId = InterruptAttachEvent (interruptNum, &isr_event[interruptNum],  0 /*_NTO_INTR_FLAGS_NO_UNMASK*/);
    if(evtId == -1)
    {
        printf("%s: InterruptAttachEvent failed\n",__FUNCTION__);
    }
    else
    {
	//printf("%s: InterruptAttachEvent succeed irq/%d coid/%d event/%p\n",__FUNCTION__, interruptNum, isr_event[interruptNum].sigev_coid, &isr_event[interruptNum]);
    }

    return ((HwiP_Handle) (long)evtId);
}

/*
 *  ======== HwiP_delete ========
 */
HwiP_Status HwiP_delete(HwiP_Handle handle)
{

    /* Need params->evtId returned by InterruptAttach */
    //InterruptDetach();

    return (HwiP_OK);
}

static uint32_t g_lockCount = 0;
/*
 *  ======== HwiP_disable ========
 */
uintptr_t HwiP_disable(void)
{
    //QNX_DEBUG_PRINT("%s: InterruptLock \n",__FUNCTION__);

    if (g_lockCount == 0) {
        InterruptLock(&spinlock);
    }
    g_lockCount++;

    return (0);
}

/*
 *  ======== HwiP_disableInterrupt ========
 */
void HwiP_disableInterrupt(int32_t interruptNum)
{
	InterruptMask(interruptNum, -1); // -1, don't track mask/unmask count
}

/*
 *  ======== HwiP_enableInterrupt ========
 */
void HwiP_enableInterrupt(int32_t interruptNum)
{
    /* Unmask interrupt */
    InterruptUnmask (interruptNum, -1);
}

/*
 *  ======== HwiP_Params_init ========
 */
void HwiP_Params_init(HwiP_Params *params)
{
	/* Get I/O privelege */
    ThreadCtl (_NTO_TCTL_IO_PRIV, 0);

    /* Create a channel Id for this process if not already specified */
    if(hwip_chid == -1)
    {
	hwip_chid = ChannelCreate( _NTO_CHF_DISCONNECT | _NTO_CHF_UNBLOCK);
    }
    if(hwip_chid == -1)
    {
	printf("%s: failed to create chid/%d\n",__FUNCTION__,hwip_chid);
    }
    else
    {
	//printf("%s: Using ChId/%d\n",__FUNCTION__, hwip_chid);
    }
}

/*
 *  ======== HwiP_restore ========
 */
void HwiP_restore(uintptr_t key)
{
    /* Enable interrupts */
    //QNX_DEBUG_PRINT("%s: InterruptUnlock \n",__FUNCTION__);

    g_lockCount--;
    if (g_lockCount == 0) {
        InterruptUnlock(&spinlock);
    }
}

/* Nothing past this point */
