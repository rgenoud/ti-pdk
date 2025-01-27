/*
 * Copyright (C) 2019-2022 Texas Instruments Incorporated - http://www.ti.com/
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

/**
 *  \file   lin_test.h
 *
 *  \brief  LIN diagnostic test header file.
 *
 */
 
#ifndef _LIN_TEST_H_
#define _LIN_TEST_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <tistdtypes.h>
#include <ti/drv/uart/UART.h>
#include <ti/drv/uart/UART_stdio.h>
#include <ti/drv/gpio/GPIO.h>
#include "board.h"
#include "diag_common_cfg.h"
#include "board_control.h"

#ifdef __cplusplus
extern "C" {
#endif

/* LIN packet structure */
typedef struct
{
    uint8_t breakfield1;
    uint8_t breakfield2;
    uint8_t sync;
    uint8_t pid;
    uint8_t slaveResponse;
    uint8_t data[8];
}linData_t;

typedef struct BoardDiagLinUartInfo_s
{
    uint32_t instance;
    uint32_t baseAddress;
    uint16_t nodeID;
} BoardDiagLinUartInfo_t;

#if defined(DIAG_STRESS_TEST)
#define PKT_SEND_COUNT                  (10240U)
#else
#define PKT_SEND_COUNT                  (1U)
#endif

#define BOARD_DIAG_LIN_BAUDRATE                    (9600U)
#define BOARD_DIAG_LIN_DATA_BYTES                  (8U)
#define BOARD_DIAG_LIN_MASTER_MODE                 (0U)
#define BOARD_DIAG_LIN_SLAVE_MODE                  (1U)
#define BOARD_DIAG_LIN_TEST_TIMEOUT                (100U)

#define BOARD_DIAG_LIN_BREAKFIELD1                (0U)
#define BOARD_DIAG_LIN_BREAKFIELD2                (0x20U)
#define BOARD_DIAG_LIN_SYNCFIELD                  (0x55U)
#define BOARD_DIAG_LIN_SLAVE_RSP                  (0x01U)


#if defined(j721e_evm)
#define BOARD_DIAG_LIN_MAX_PORTS                  (0x01U)
#define BOARD_DIAG_LIN_NODE_ID                    (0x81U)
#elif defined(j721s2_evm)
#define BOARD_DIAG_LIN_MAX_PORTS                  (0x02U)
#define BOARD_DIAG_LIN1_NODE_ID                   (0x81U)
#define BOARD_DIAG_LIN2_NODE_ID                   (0x82U)
#define BOARD_DIAG_LIN3_NODE_ID                   (0x83U)
#elif defined(j784s4_evm)
#define BOARD_DIAG_LIN_MAX_PORTS                  (0x02U)
#define BOARD_DIAG_LIN1_NODE_ID                   (0x81U)
#define BOARD_DIAG_LIN2_NODE_ID                   (0x82U)
#else
#define BOARD_DIAG_LIN_MAX_PORTS                  (0x06U)
#define BOARD_DIAG_LIN1_NODE_ID                   (0x81U)
#define BOARD_DIAG_LIN2_NODE_ID                   (0x82U)
#define BOARD_DIAG_LIN3_NODE_ID                   (0x83U)
#define BOARD_DIAG_LIN4_NODE_ID                   (0x84U)
#define BOARD_DIAG_LIN5_NODE_ID                   (0x85U)
#define BOARD_DIAG_LIN6_NODE_ID                   (0x86U)
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _LIN_TEST_H_ */
