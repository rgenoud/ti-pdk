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
/*
 *  ======== Queue_qnx.c ========
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ti/osal/Queue.h>
#include <ti/osal/HwiP.h>

void Osal_Queue_Params_init(const Osal_Queue_Params * queueParams)
{
    return;
}

Osal_Queue_Handle Osal_Queue_create(const  Osal_Queue_Params * queueParams, void * eb)
{
    Osal_Queue_Elem *obj = NULL;

    obj = calloc(1, sizeof(Osal_Queue_Elem));
    if (obj != NULL)
    {
        obj->next = (struct Osal_QueueElem *)obj;
        obj->prev = (struct Osal_QueueElem *)obj;
    }
    return obj;
}

uint32_t Osal_Queue_empty(Osal_Queue_Handle queueHandle)
{
    uint32_t status = 1U;
    Osal_Queue_Elem *obj = (Osal_Queue_Elem *) queueHandle;

    if (obj != NULL)
    {
        if(obj->next != (struct Osal_QueueElem*)obj)
        {
            status = 0U;
        }
    }

    return status;
}

void * Osal_Queue_get(Osal_Queue_Handle queueHandle)
{
    Osal_Queue_Elem *elem = NULL;
    Osal_Queue_Elem *obj = (Osal_Queue_Elem *) queueHandle;
    uintptr_t key;

    if (obj != NULL)
    {
        key = HwiP_disable();

        elem = (Osal_Queue_Elem*)obj->next;
        obj->next = elem->next;
        ((Osal_Queue_Elem*)(elem->next))->prev = (struct Osal_QueueElem*)obj;

        HwiP_restore(key);
    }

    return (elem);
}

void Osal_Queue_put(Osal_Queue_Handle queueHandle,Osal_Queue_Elem *elem)
{
    uintptr_t key;
    Osal_Queue_Elem *obj = (Osal_Queue_Elem *) queueHandle;

    if ((obj != NULL) && (elem != NULL))
    {
        key = HwiP_disable();

        elem->next = (struct Osal_QueueElem*)obj;
        elem->prev = obj->prev;
        ((Osal_Queue_Elem*)(obj->prev))->next = (struct Osal_QueueElem*)elem;
        obj->prev = (struct Osal_QueueElem*)elem;

        HwiP_restore(key);
    }

    return;
}

void Osal_Queue_delete(Osal_Queue_Handle queueHandle)
{
    if (queueHandle != NULL)
    {
        free(queueHandle);
    }

    return;
}
