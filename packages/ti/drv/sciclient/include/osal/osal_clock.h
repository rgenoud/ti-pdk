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

/*
 * \file osal_clock.h
 *
 * OSAL Core Public APIs used for subsystem control
 *
 */

#ifndef _OSAL_CLOCK_H_
#define _OSAL_CLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/osal/src/nonos/Nonos_config.h>
#include <stdio.h>

static inline void osal_delay(uint64_t usecs)
{
    TimeStamp_Struct tStamp;
    uint64_t delay = usecs * 1000U; /* Convert to ns */
    uint64_t timestamp;
    uint64_t timestampNow;
    osalArch_TimestampGet64(&tStamp);
    timestamp = (uint64_t) tStamp.lo | ((uint64_t) tStamp.hi << 32);
    timestampNow = timestamp;
    while ((timestampNow - timestamp) < delay) {
        osalArch_TimestampGet64(&tStamp);
        timestampNow = (uint64_t) tStamp.lo | ((uint64_t) tStamp.hi << 32);
    }
}

#ifdef __cplusplus
}
#endif

#endif

