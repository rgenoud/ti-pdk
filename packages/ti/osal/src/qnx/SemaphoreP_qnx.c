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
 *  ======== SemaphoreP_linux.c ========
 */
#include <ti/osal/SemaphoreP.h>
#include <ti/osal/osal.h>
#include <pthread.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <string.h>

typedef struct SemaphoreP_Struct_s {
    SemaphoreP_Mode mode;
    union {
        sem_t *sem_handle;
        pthread_mutex_t *mutex_handle;
    }type;
} SemaphoreP_Struct;

/*
 *  ======== SemaphoreP_create ========
 */
SemaphoreP_Handle SemaphoreP_create(uint32_t count,
                                    const SemaphoreP_Params *params)
{
    char sem_name[128];
    SemaphoreP_Struct *handle = NULL;

    handle = (SemaphoreP_Struct *)calloc(1, sizeof(SemaphoreP_Struct));
    if (handle == NULL) return NULL;
    if (params->mode == SemaphoreP_Mode_COUNTING)
    {
        handle->mode = SemaphoreP_Mode_COUNTING;
        /* Assign a name if one is not specified */
        if(params->name == NULL)
        {
           static int counter = 0;
           sprintf(sem_name,"qnx_sem_%ld_%ld_%d", (long int)getpid(), (long int)gettid(), counter++);
        }
        else
        {
            strcpy(sem_name, params->name);
        }

        /* Creates a COUNTING semaphore */
        handle->type.sem_handle = sem_open(sem_name, O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH, count);
        if (handle->type.sem_handle == SEM_FAILED)
        {
            printf("%s: for QNX Failed\n",__FUNCTION__);
            free(handle);
            return NULL;
        }
    }
    else if (params->mode == SemaphoreP_Mode_BINARY)
    {
        handle->mode = SemaphoreP_Mode_BINARY;

        handle->type.mutex_handle = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
        if (EOK != pthread_mutex_init((pthread_mutex_t *) handle->type.mutex_handle, NULL))
        {
            free(handle->type.mutex_handle);
            free(handle);
            return (NULL);
        }
    }
    return ((SemaphoreP_Handle)handle);
}


/*
 *  ======== SemaphoreP_delete ========
 */
SemaphoreP_Status SemaphoreP_delete(SemaphoreP_Handle handle)
{
    OSAL_Assert((handle == NULL));

    SemaphoreP_Struct *int_handle = (SemaphoreP_Struct *)handle;

    if (int_handle->mode == SemaphoreP_Mode_COUNTING)
    {
        sem_close((sem_t *)int_handle->type.sem_handle);
    }
    else if (int_handle->mode == SemaphoreP_Mode_BINARY)
    {
        pthread_mutex_destroy((pthread_mutex_t*) int_handle->type.mutex_handle);
        free (int_handle->type.mutex_handle);
    }
    free(int_handle);
    return (SemaphoreP_OK);
}

/*
 *  ======== SemaphoreP_Params_init ========
 */
void SemaphoreP_Params_init(SemaphoreP_Params *params)
{
    OSAL_Assert((params == NULL));

    params->mode = SemaphoreP_Mode_COUNTING;
    params->name = NULL;
}

/*
 *  ======== SemaphoreP_pend ========
 */
SemaphoreP_Status SemaphoreP_pend(SemaphoreP_Handle handle, uint32_t timeout)
{
    OSAL_Assert((handle == NULL));

    int ret = 0;
    struct timespec ts;
    int timeout_ns = timeout*1000;
    SemaphoreP_Struct *int_handle = (SemaphoreP_Struct *)handle;

    if (timeout == SemaphoreP_WAIT_FOREVER)
    {
        if (int_handle->mode == SemaphoreP_Mode_COUNTING)
        {
            ret = sem_wait((sem_t *)int_handle->type.sem_handle);
        }
        else if (int_handle->mode == SemaphoreP_Mode_BINARY)
        {
            ret = pthread_mutex_lock((pthread_mutex_t *)int_handle->type.mutex_handle);
        }
    }
    else
    {
        clock_gettime(CLOCK_REALTIME, &ts);
        ts.tv_sec += (timeout_ns)/1000000000;
        ts.tv_nsec += timeout_ns%1000000000;

        if (int_handle->mode == SemaphoreP_Mode_COUNTING)
        {
            ret = sem_timedwait((sem_t *)int_handle->type.sem_handle, &ts);
        }
        else if (int_handle->mode == SemaphoreP_Mode_BINARY)
        {
            ret = pthread_mutex_timedlock((pthread_mutex_t *)int_handle->type.mutex_handle, &ts);
        }
    }
    if (ret < 0)
    {
        if (errno == ETIMEDOUT)
        {
            return (SemaphoreP_TIMEOUT);
        }
        else
        {
            return (SemaphoreP_FAILURE);
        }
    }

    return (SemaphoreP_OK);
}

/*
 *  ======== SemaphoreP_post ========
 */
SemaphoreP_Status SemaphoreP_post(SemaphoreP_Handle handle)
{
    OSAL_Assert((handle == NULL));

    int ret = 0;
    SemaphoreP_Struct *int_handle = (SemaphoreP_Struct *)handle;

    if (int_handle->mode == SemaphoreP_Mode_COUNTING)
    {
        ret = sem_post((sem_t *)int_handle->type.sem_handle);
    }
    else if (int_handle->mode == SemaphoreP_Mode_BINARY)
    {
        ret = pthread_mutex_unlock((pthread_mutex_t *)int_handle->type.mutex_handle);
    }

    if (ret < 0)
    {
        return (SemaphoreP_FAILURE);
    }

    return (SemaphoreP_OK);
}

/*
 *  ======== SemaphoreP_postFromClock ========
 */
SemaphoreP_Status SemaphoreP_postFromClock(SemaphoreP_Handle handle)
{
    return (SemaphoreP_post(handle));
}

/*
 *  ======== SemaphoreP_postFromISR ========
 */
SemaphoreP_Status SemaphoreP_postFromISR(SemaphoreP_Handle handle)
{
    return (SemaphoreP_post(handle));
}

/* Nothing past this point */
