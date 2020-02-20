/*
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdint.h>

#define ICSSG_MAX       3

#define HWQ_MAX         64
#define HWQ_PEEK_MAX    16

typedef struct hwq_ip_tag{
    volatile uint32_t hq[HWQ_MAX];
    volatile uint32_t hq_peek[HWQ_PEEK_MAX];
    volatile uint32_t hq_len[HWQ_MAX];
    volatile uint32_t reset;
} hwq_ip_t;

static uint32_t smem_start[3] = { 0x0b010000, 0x0b110000, 0xb210000 };

static hwq_ip_t *hwq_a[3] = {
    (hwq_ip_t*) 0x0b033d00, //TODO: replace with macro from CSL 
    (hwq_ip_t*) 0x0b133d00,
    (hwq_ip_t*) 0x0b233d00,
};

void *hwq_pop(int icssg, int qn)
{
    if (qn >= HWQ_MAX || icssg >= ICSSG_MAX )
        return (void *)0;

    return (void *)(hwq_a[icssg]->hq[qn] | smem_start[icssg]);
}

void hwq_push(int icssg, int qn, void *p)
{
    if (qn >= HWQ_MAX || icssg >= ICSSG_MAX )
        return;

    hwq_a[icssg]->hq[qn] = (uint32_t)p;
}

void *hwq_peek(int icssg, int qn)
{
    if (qn >= HWQ_PEEK_MAX || icssg >= ICSSG_MAX )
        return (void *)0;

    return (void *)(hwq_a[icssg]->hq_peek[qn] | smem_start[icssg]);
}

int hwq_level(int icssg, int qn)
{
    if (qn >= HWQ_MAX || icssg >= ICSSG_MAX )
        return 0;

    return hwq_a[icssg]->hq_len[qn];
}

