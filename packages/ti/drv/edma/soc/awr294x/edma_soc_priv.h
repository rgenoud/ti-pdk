/*
 *  Copyright (c) Texas Instruments Incorporated 2020
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
 */

/**
 *   @file  edma_soc.h
 *
 *   @brief
 *      This is the internal Header for EDMA hardware attributes definition.
 *      This header file should *NOT* be directly included by applications.
 *
 */

#ifndef EDMA_SOC_PRIV_H_
#define EDMA_SOC_PRIV_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/soc.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#if defined (__TI_ARM_V7R4__)
#define EDMA_NUM_CC        EDMA_MSS_NUM_CC
#define EDMA_MAX_NUM_TC    EDMA_MSS_MAX_NUM_TC
#elif defined (_TMS320C6X)
#define EDMA_NUM_CC        EDMA_DSS_NUM_CC
#define EDMA_MAX_NUM_TC    EDMA_DSS_MAX_NUM_TC
#else
#error Core Not supported
#endif


/*! brief In some devices, EDMA interrupts are not mapped to interrupt space of the
 *        processor, use max 16-bit value as a identifier to designate such cases.
 */
#define EDMA_INTERRUPT_NOT_CONNECTED_ID ((uint16_t)(0xFFFF))

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/*! brief EDMA Hardware attributes. */
typedef struct EDMA_hwAttrs_t_
{
    /*! brief Number of event queues. Same as number of transfer controllers. */
    uint8_t  numEventQueues;

    /*! brief Number of PaRAM sets */
    uint16_t numParamSets;

    /*! brief Transfer completion interrupt number. If not mapped, set to
     *  @ref EDMA_INTERRUPT_NOT_CONNECTED_ID */
    uint16_t transferCompletionInterruptNum;

    /*! Channel Controller (CC) Error interrupt number. If not mapped, set to
     *  @ref EDMA_INTERRUPT_NOT_CONNECTED_ID */
    uint16_t errorInterruptNum;

    /*! Transfer controller error interrupt numbers. If not mapped, set to
     *  @ref EDMA_INTERRUPT_NOT_CONNECTED_ID */
    uint16_t transferControllerErrorInterruptNum[EDMA_MAX_NUM_TC];

    /*! Channel Controller (CC) base address */
    uint32_t CCbaseAddress;

    /*! CC Completion Interrupts aggregator Mask register address */
    uint32_t CCcompletionInterruptsAggregatorMaskRegAddress;

    /*! CC Completion Interrupts aggregator Status and status clear register address */
    uint32_t CCcompletionInterruptsAggregatorStatusRegAddress;

    /*! CC Error Interrupts aggregator Mask register address */
    uint32_t CCerrorInterruptsAggregatorMaskRegAddress;

    /*! CC Error Interrupts aggregator Status and status clear register address */
    uint32_t CCerrorInterruptsAggregatorStatusRegAddress;

    /*! Transfer Controllers (TC) base addresses. */
    uint32_t TCbaseAddress[EDMA_MAX_NUM_TC];

    /*! Channel Mapping feature existence - true if exists, false if does not exist.
        See DCHMAP in EDMA UG. Note this existence can also be derived by reading
        the chip configuration register CCCFG. */
    bool isChannelMapExist;
} EDMA_hwAttrs_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

const EDMA_hwAttrs_t* EDMA_getHwAttrs(uint32_t instanceId);

#ifdef __cplusplus
}
#endif

#endif /* EDMA_XWR1XXX_H */
