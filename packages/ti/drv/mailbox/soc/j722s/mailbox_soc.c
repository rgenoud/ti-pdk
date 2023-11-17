/*
 *  Copyright (c) Texas Instruments Incorporated 2023
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
 *   \file mailbox_soc.c
 *
 *   \brief The file implements the Platform specific Mailbox Driver Interface
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/mailbox/mailbox.h>
#include <ti/drv/mailbox/src/mailbox_internal.h>
#include <ti/csl/src/ip/mailbox/V0/priv/mailbox.c>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/*!
 * @brief
 *  Mailbox Entry Information
 *
 *  This structure is used to store the cluser/user/fifo information used for communication between a core pair
 *
 *  \ingroup MAILBOX_DRIVER_INTERNAL_DATA_STRUCTURE
 */
typedef struct Mailbox_Entry_s
{
    /**
     * @brief  Cluster id.
     */
    uint32_t    cluster;

    /**
     * @brief  User id.
     */
    uint32_t    user;

    /**
     * @brief  Fifo id.
     */
    uint32_t    fifo;

} Mailbox_Entry;

/**
 * @brief
 *  Mailbox Driver HW configuration
 *
 * @details
 *  The structure is used to store the hardware specific configuration which is
 *  passed to each driver instance
 *
 */
typedef struct Mailbox_HwCfg_t
{
    /**
     * @brief  Entry for the mailbox info for receiving messages
     */
    Mailbox_Entry    rx;
    /**
     * @brief  Entry for the mailbox info for sending messages
     */
    Mailbox_Entry    tx;
    /**
     * @brief  Flag to indicate if there is exclusive access to the mailbox
     *         for receiving messages from a single remote core. For example, if
     *         the interrupt line for mailbox cluster 0 is only used for
     *         receiving messages from a single remote core. Some optimiation
     *         can be done when handling the incoming message in this case.
     */
    bool             exclusive;
    /**
     * @brief  The associated eventId for the interrupt.
     */
    uint32_t         eventId;
} Mailbox_HwCfg;


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define  MAILBOX_MAXFIFO_CNT    (16U)
#define  MAILBOX_CLUSTER_CNT     (8U)
#define  MAILBOX_USER_CNT        (4U)

/**
 * @brief
 *  Global Variable for tracking information required by the mailbox driver.
 */
extern Mailbox_MCB gMailboxMCB;

/**
 * \brief Maps mBoxData allocated to a given Remote Processor
 */
uintptr_t           gInstToMBoxDataMap[MAILBOX_MAX_INST];

typedef struct Mailbox_Fifo_s
{
    int32_t                 cfgNdx;
    Mailbox_Callback        func;
    uint32_t                arg;
    uint32_t                queueId;
    void                   *handle;
} Mailbox_Fifo;

/* mboxData */
typedef struct Mailbox_Data_s
{
    uintptr_t         baseAddr;
    uint32_t          fifoCnt;
    Mailbox_Fifo      fifoTable[MAILBOX_MAXFIFO_CNT];
    uint32_t          noMsgCnt;
    uint32_t          intCnt;
    uint32_t          userId;

} Mailbox_Data;

/* ========================================================================== */
/*                             Globals                                        */
/* ========================================================================== */
uint32_t               g_mBoxCnt = 0U;
Mailbox_Data           g_mBoxData[MAILBOX_MAX_INST];
Mailbox_Callback       g_VimCallback[MAILBOX_MAX_INST];
Mbox_Handle            g_VimCallbackArg[MAILBOX_MAX_INST];
Mailbox_Callback       g_FastCallback[MAILBOX_MAX_INST];
Mbox_Handle            g_FastCallbackArg[MAILBOX_MAX_INST];
Mailbox_Driver         g_mBoxDrivers[MAILBOX_MAX_INST];

/* Mailbox Cluster Base Address */
static uintptr_t g_Mailbox_BaseAddr[MAILBOX_CLUSTER_CNT] =
{
    CSL_MAILBOX0_REGS0_BASE,
    CSL_MAILBOX0_REGS1_BASE,
    CSL_MAILBOX0_REGS2_BASE,
    CSL_MAILBOX0_REGS3_BASE,
    CSL_MAILBOX0_REGS4_BASE,
    CSL_MAILBOX0_REGS5_BASE,
    CSL_MAILBOX0_REGS6_BASE,
    CSL_MAILBOX0_REGS7_BASE,
};

/* Pre-defined mailbox config to allow any CPU to send and receive messages from any CPU on this SOC (J722S)
 *
 * Each element consists of [maibox base addr, hw fifo, user id]
 * These assignments need to be in sync with gIpcNotifyInterruptConfig* done later below,
 *
 * This is a 2D array
 * - 1st indexed by source core ID
 * - then indexed by destination core ID
 *
 * --------------------------------
 *  Cluster | FIFO |     IPC
 * --------------------------------
 *   0      |  0   | WKUP R5F -> A53SS0_0
 *   0      |  1   | A53SS0_0 -> WKUP R5F
 *   0      |  2   | MCU R5F  -> A53SS0_0
 *   0      |  3   | A53SS0_0 -> MCU R5F
 *   0      |  4   | A53SS1_0 -> WKUP R5F
 *   0      |  5   | WKUP R5F -> A53SS1_0
 *   0      |  6   | A53SS1_0 -> MCU R5F
 *   0      |  7   | MCU R5F  -> A53SS1_0
 *   0      |  8   | A53SS1_0 -> A53SS0_0
 *   0      |  9   | A53SS0_0 -> A53SS1_0
 *
 *   1      |  0   | WKUP R5F -> MCU R5F
 *   1      |  1   | MAIN R5F -> MCU R5F
 *   1      |  2   | C75SS0_0 -> MCU R5F
 *   1      |  3   | C75SS1_0 -> MCU R5F
 *
 *   2      |  0   | MAIN R5F -> A53SS0_0
 *   2      |  1   | A53SS0_0 -> MAIN R5F
 *   2      |  2   | C75SS0_0 -> A53SS0_0
 *   2      |  3   | A53SS0_0 -> C75SS0_0
 *   2      |  4   | A53SS1_0 -> MAIN R5F
 *   2      |  5   | MAIN R5F -> A53SS1_0
 *   2      |  6   | A53SS1_0 -> C75SS0_0
 *   2      |  7   | C75SS0_0 -> A53SS1_0
 *
 *   3      |  0   | C75SS1_0 -> A53SS0_0
 *   3      |  1   | A53SS0_0 -> C75SS1_0
 *   3      |  2   | A53SS1_0 -> C75SS1_0
 *   3      |  3   | C75SS1_0 -> A53SS1_0
 *
 *   4      |  0   | MCU R5F  -> WKUP R5F
 *   4      |  1   | MAIN R5F -> WKUP R5F
 *   4      |  2   | C75SS0_0 -> WKUP R5F
 *   4      |  3   | C75SS1_0 -> WKUP R5F
 *
 *   5      |  0   | WKUP R5F -> MAIN R5F
 *   5      |  1   | MCU R5F  -> MAIN R5F
 *   5      |  2   | C75SS0_0 -> MAIN R5F
 *   5      |  3   | C75SS1_0 -> MAIN R5F
 *
 *   6      |  0   | WKUP R5F -> C75SS0_0
 *   6      |  1   | MCU R5F  -> C75SS0_0
 *   6      |  2   | MAIN R5F -> C75SS0_0
 *   6      |  3   | C75SS1_0 -> C75SS0_0
 *
 *   7      |  0   | WKUP R5F -> C75SS1_0
 *   7      |  1   | MCU R5F  -> C75SS1_0
 *   7      |  2   | MAIN R5F -> C75SS1_0
 *   7      |  3   | C75SS0_0 -> C75SS1_0
 *
 * User ID (different IDs are used on different MB clusters):
 *     MCU R5F Rx : 2, 0
 *     WKUP R5F Rx: 1, 0
 *     MAIN R5F Rx: 1, 0
 *     C75SS0 Rx  : 2, 0
 *     C75SS1 Rx  : 1, 0
 *     A53SS0_0 Rx: 0
 *     A53SS0_1 Rx: n/a
 *     A53SS1_0 Rx: 3
 *     A53SS1_1 Rx: n/a
 */

/**
 * \brief This structure describes the mailbox information to send a message from core A to core B
 */ 
typedef struct IpcNotify_MailboxConfig_s
{
    uint8_t mailboxId;   /**< Mailbox to use, mailbox index is specified and base address is derived using \ref gIpcNotifyMailboxBaseAddr */
    uint8_t hwFifoId;    /**< HW fifo within this mailbox to use to exchange the message, 
                            *  used by sender to write to the FIFO, recevier to read from the FIFO */
    uint8_t userId;      /**< user ID to use to receive interrupt for this message exchange, used by receiver only */

} IpcNotify_MailboxConfig;

/* values to use when a mailbox config is not used in gIpcNotifyMailboxConfig */
#define  MAILBOX_UNUSED      MAILBOX_INST_INVALID, MAILBOX_INST_INVALID, MAILBOX_INST_INVALID

IpcNotify_MailboxConfig gIpcNotifyMailboxConfig[CSL_CORE_ID_MAX][CSL_CORE_ID_MAX] =
{                            /* to MCU R5FSS0-0 */  /* to WKUP R5FSS0-0 */ /* to MAIN R5FSS0-0 */ /* to C75SS0_0 */     /* to C75SS1_0 */     /* to A53SS0_0 */     /* to A53SS0_1 */     /* to A53SS1_0 */     /* to A53SS1_1 */     /* to HSM_R5FSS0_0 */
    /* from MCU R5FSS0-0 */  { { MAILBOX_UNUSED },  { 4U, 0U, 0U },        { 5U, 1U, 0U },        { 6U, 1U, 0U },       { 7U, 1U, 0U },       { 0U, 2U, 0U },       { MAILBOX_UNUSED },   { 0U, 7U, 3U },       { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
    /* from WKUP R5FSS0-0 */ { { 1U, 0U, 0U },      { MAILBOX_UNUSED },    { 5U, 0U, 0U },        { 6U, 0U, 0U },       { 7U, 0U, 0U },       { 0U, 0U, 0U },       { MAILBOX_UNUSED },   { 0U, 5U, 3U },       { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
    /* from MAIN R5FSS0-0 */ { { 1U, 1U, 0U },      { 4U, 1U, 0U },        { MAILBOX_UNUSED },    { 6U, 2U, 0U },       { 7U, 2U, 0U },       { 2U, 0U, 0U },       { MAILBOX_UNUSED },   { 2U, 5U, 3U },       { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
    /* from C75SS0_0 */      { { 1U, 2U, 0U },      { 4U, 2U, 0U },        { 5U, 2U, 0U },        { MAILBOX_UNUSED },   { 7U, 3U, 0U },       { 2U, 2U, 0U },       { MAILBOX_UNUSED },   { 2U, 7U, 3U },       { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
    /* from C75SS1_0 */      { { 1U, 3U, 0U },      { 4U, 3U, 0U },        { 5U, 3U, 0U },        { 6U, 3U, 0U },       { MAILBOX_UNUSED },   { 3U, 0U, 0U },       { MAILBOX_UNUSED },   { 3U, 3U, 3U },       { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
    /* from A53SS0_0 */      { { 0U, 3U, 2U },      { 0U, 1U, 1U },        { 2U, 1U, 1U },        { 2U, 3U, 2U },       { 3U, 1U, 1U },       { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { 0U, 9U, 3U },       { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
    /* from A53SS0_1 */      { { MAILBOX_UNUSED },  { MAILBOX_UNUSED },    { MAILBOX_UNUSED },    { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
    /* from A53SS1_0 */      { { 0U, 6U, 2U },      { 0U, 4U, 1U },        { 2U, 4U, 1U },        { 2U, 6U, 2U },       { 3U, 2U, 1U },       { 0U, 8U, 0U },       { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
    /* from A53SS1_1 */      { { MAILBOX_UNUSED },  { MAILBOX_UNUSED },    { MAILBOX_UNUSED },    { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
    /* from HSM_R5FSS0_0 */  { { MAILBOX_UNUSED },  { MAILBOX_UNUSED },    { MAILBOX_UNUSED },    { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED },   { MAILBOX_UNUSED }, },
};

#define MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(HOST_PROC_ID, DST_PROC_ID) {gIpcNotifyMailboxConfig[HOST_PROC_ID][DST_PROC_ID].mailboxId, gIpcNotifyMailboxConfig[HOST_PROC_ID][DST_PROC_ID].userId, gIpcNotifyMailboxConfig[HOST_PROC_ID][DST_PROC_ID].hwFifoId}, {gIpcNotifyMailboxConfig[DST_PROC_ID][HOST_PROC_ID].mailboxId, gIpcNotifyMailboxConfig[DST_PROC_ID][HOST_PROC_ID].userId, gIpcNotifyMailboxConfig[DST_PROC_ID][HOST_PROC_ID].hwFifoId}

Mailbox_HwCfg g_Mailbox_HwCfg[MAILBOX_MAX_INST][MAILBOX_MAX_INST] =
{
    /* Host Processor - MCU R5FSS0-0 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 0), true, 0 },  /* Self - MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 1), true, 0 },  /* WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 2), true, 0 },  /* MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 3), true, 0 },  /* C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 4), true, 0 },  /* C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 5), true, 0 },  /* A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 6), true, 0 },  /* A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 7), true, 0 },  /* A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 8), true, 0 },  /* A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(0, 9), true, 0 },  /* HSM_R5FSS0_0 */
    },
    /* Host Processor - WKUP R5FSS0-0 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 0), true, 0 },  /* MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 1), true, 0 },  /* Self - WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 2), true, 0 },  /* MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 3), true, 0 },  /* C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 4), true, 0 },  /* C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 5), true, 0 },  /* A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 6), true, 0 },  /* A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 7), true, 0 },  /* A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 8), true, 0 },  /* A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(1, 9), true, 0 },  /* HSM_R5FSS0_0 */
    },
    /* Host Processor - MAIN R5FSS0-0 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 0), true, 0 },  /* MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 1), true, 0 },  /* WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 2), true, 0 },  /* Self - MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 3), true, 0 },  /* C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 4), true, 0 },  /* C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 5), true, 0 },  /* A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 6), true, 0 },  /* A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 7), true, 0 },  /* A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 8), true, 0 },  /* A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(2, 9), true, 0 },  /* HSM_R5FSS0_0 */
    },
    /* Host Processor - C75SS0_0 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 0), true, 0 },  /* MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 1), true, 0 },  /* WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 2), true, 0 },  /* MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 3), true, 0 },  /* Self - C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 4), true, 0 },  /* C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 5), true, 0 },  /* A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 6), true, 0 },  /* A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 7), true, 0 },  /* A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 8), true, 0 },  /* A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(3, 9), true, 0 },  /* HSM_R5FSS0_0 */
    },
    /* Host Processor - C75SS1_0 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 0), true, 0 },  /* MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 1), true, 0 },  /* WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 2), true, 0 },  /* MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 3), true, 0 },  /* C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 4), true, 0 },  /* Self - C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 5), true, 0 },  /* A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 6), true, 0 },  /* A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 7), true, 0 },  /* A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 8), true, 0 },  /* A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(4, 9), true, 0 },  /* HSM_R5FSS0_0 */
    },
    /* Host Processor - A53SS0_0 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 0), true, 0 },  /* MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 1), true, 0 },  /* WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 2), true, 0 },  /* MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 3), true, 0 },  /* C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 4), true, 0 },  /* C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 5), true, 0 },  /* Self - A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 6), true, 0 },  /* A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 7), true, 0 },  /* A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 8), true, 0 },  /* A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(5, 9), true, 0 },  /* HSM_R5FSS0_0 */
    },
    /* Host Processor - A53SS0_1 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 0), true, 0 },  /* MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 1), true, 0 },  /* WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 2), true, 0 },  /* MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 3), true, 0 },  /* C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 4), true, 0 },  /* C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 5), true, 0 },  /* A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 6), true, 0 },  /* Self - A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 7), true, 0 },  /* A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 8), true, 0 },  /* A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(6, 9), true, 0 },  /* HSM_R5FSS0_0 */
    },
    /* Host Processor - A53SS1_0 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 0), true, 0 },  /* MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 1), true, 0 },  /* WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 2), true, 0 },  /* MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 3), true, 0 },  /* C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 4), true, 0 },  /* C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 5), true, 0 },  /* A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 6), true, 0 },  /* A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 7), true, 0 },  /* Self - A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 8), true, 0 },  /* A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(7, 9), true, 0 },  /* HSM_R5FSS0_0 */
    },
    /* Host Processor - A53SS1_1 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 0), true, 0 },  /* MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 1), true, 0 },  /* WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 2), true, 0 },  /* MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 3), true, 0 },  /* C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 4), true, 0 },  /* C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 5), true, 0 },  /* A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 6), true, 0 },  /* A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 7), true, 0 },  /* A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 8), true, 0 },  /* Self - A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(8, 9), true, 0 },  /* HSM_R5FSS0_0 */
    },
    /* Host Processor - HSM_R5FSS0_0 */
    {
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 0), true, 0 },  /* MCU R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 1), true, 0 },  /* WKUP R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 2), true, 0 },  /* MAIN R5FSS0-0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 3), true, 0 },  /* C75SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 4), true, 0 },  /* C75SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 5), true, 0 },  /* A53SS0_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 6), true, 0 },  /* A53SS0_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 7), true, 0 },  /* A53SS1_0 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 8), true, 0 },  /* A53SS1_1 */
        { MCU_PLUS_MAILBOX_CFG_TO_PDK_MAILBOX_CFG(9, 9), true, 0 },  /* Self - HSM_R5FSS0_0 */
    },
};

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Mailbox_Instance Mailbox_getLocalEndPoint(void)
{
    Mailbox_Instance localEndpoint = MAILBOX_INST_INVALID;

#if defined (BUILD_MPU1_0)
    localEndpoint = MAILBOX_INST_MPU1_0;
#elif defined (BUILD_MCU_R5F)
    localEndpoint = MAILBOX_INST_MCU_R5F;
#elif defined (BUILD_WKUP_R5F)
    localEndpoint = MAILBOX_INST_WKUP_R5F;
#endif

    return localEndpoint;
}

int32_t Mailbox_validateLocalEndPoint(Mailbox_Instance localEndpoint)
{
    int32_t retVal = MAILBOX_SOK;
    /* Validate local End point based on the Core. */
#if defined (BUILD_MPU1_0)
    if (localEndpoint != MAILBOX_INST_MPU1_0)
    {
        retVal = MAILBOX_EINVAL;
    }
#elif defined (BUILD_WKUP_R5F)
    if (localEndpoint != MAILBOX_INST_WKUP_R5F)
    {
        retVal = MAILBOX_EINVAL;
    }
#elif defined (BUILD_MCU_R5F)
    if (localEndpoint != MAILBOX_INST_MCU_R5F)
    {
        retVal = MAILBOX_EINVAL;
    }
#else
    /* Currently not supported for other cores. */
    retVal = MAILBOX_EINVAL;
#endif
    return retVal;
}

int32_t Mailbox_validateRemoteEndPoint(Mailbox_Instance localEndpoint, Mailbox_Instance remoteEndpoint)
{
    int32_t retVal = MAILBOX_SOK;
    if(g_Mailbox_HwCfg[localEndpoint][remoteEndpoint].mailboxId == MAILBOX_INST_INVALID)
    {
        retVal = MAILBOX_EINVAL;
    }
    return retVal;
}

int32_t Mailbox_validateDataTransferMode(Mailbox_DataTransferMode dataTransferMode)
{
    /* We ignore data transfer mode for this Mailbox IP. Only way to get data is with register read */
    return MAILBOX_SOK;
}

int32_t Mailbox_validateReadWriteMode(Mailbox_Mode readMode, Mailbox_Mode writeMode)
{
    int32_t retVal = MAILBOX_SOK;
    if ((writeMode == MAILBOX_MODE_CALLBACK) || (writeMode == MAILBOX_MODE_BLOCKING) ||
        (readMode == MAILBOX_MODE_BLOCKING))
    {
        retVal = MAILBOX_EINVAL;
    }
    return retVal;
}

int32_t Mailbox_isMultiChannelSupported(Mailbox_Instance localEndpoint, Mailbox_Instance remoteEndpoint)
{
    /* We do not support Multi-channel for this Mailbox IP */
    return MAILBOX_EINVAL;
}

Mbox_Handle Mailbox_allocDriver(Mailbox_Instance remoteEndpoint)
{
    Mailbox_Driver *driver = NULL;

    driver = &g_mBoxDrivers[remoteEndpoint];

    return (Mbox_Handle)driver;
}

int32_t Mailbox_freeDriver(Mbox_Handle handle)
{
    return MAILBOX_SOK;
}

/**
 *  @b Description
 *  @n
 *      The function configures the hardware base addresses and interrupt numbers
 *      It populates the driver with hard coded information derived from the platform
 *      files.
 *
 *  @param[in]  driver handle
 *
 *
 *  @retval
 *      Not applicable
 *
 *  \ingroup MAILBOX_DRIVER_INTERNAL_FUNCTION
 *
 */
void* Mailbox_getHwCfg(Mailbox_Instance remoteEndpoint)
{
    Mailbox_HwCfg *hwCfg = NULL;
    Mailbox_Instance localEndpoint = Mailbox_getLocalEndPoint();

    if ((remoteEndpoint < MAILBOX_MAX_INST) && (localEndpoint < MAILBOX_MAX_INST))
    {
        hwCfg = &g_Mailbox_HwCfg[localEndpoint][remoteEndpoint];
    }

    return (void *)hwCfg;
}

int32_t Mailbox_initHw(Mbox_Handle handle)
{
    int32_t             retVal = MAILBOX_SOK;

    if (handle == NULL)
    {
        retVal = MAILBOX_EINVAL;
    }

    if (retVal == MAILBOX_SOK)
    {
        // TODO
    }
    return retVal;
}

uint32_t Mailbox_GetMessageCount(Mbox_Handle handle)
{
    int32_t count = 0;

    if (handle != NULL)
    {
        count = MailboxGetMessageCount(((Mailbox_Driver *)handle)->baseAddrRx,
                                       ((Mailbox_HwCfg *)(((Mailbox_Driver *)handle)->hwCfg))->rx.fifo);
    }
    return count;
}

/*
 *  ======== Mailbox_write ========
 */
int32_t Mailbox_write(Mbox_Handle handle, const uint8_t *buffer, uint32_t size)
{
    int32_t retVal = MAILBOX_SOK;

    if ((handle != NULL) &&
        (((Mailbox_Driver *)handle)->hwCfg != NULL) &&
        (buffer != NULL) &&
        (((Mailbox_Driver *)handle)->cfg.writeMode == MAILBOX_MODE_FAST))
    {
        MailboxWriteMessage(((Mailbox_Driver *)handle)->baseAddrTx,
                            ((Mailbox_HwCfg *)(((Mailbox_Driver *)handle)->hwCfg))->tx.fifo,
                            *((uint32_t *)buffer));
    }
    else
    {
        Mailbox_Driver* driver = (Mailbox_Driver*)handle;
        Mailbox_HwCfg *hwCfg = NULL;
        int32_t key = 0U;
        uint32_t cnt;

        if (handle == NULL)
        {
            retVal = MAILBOX_EINVAL;
        }
        else if (driver->hwCfg == NULL)
        {
            retVal = MAILBOX_EINVAL;
        }
        else if (buffer == NULL)
        {
            retVal = MAILBOX_EINVAL;
        }
        else
        {
            hwCfg = (Mailbox_HwCfg *)driver->hwCfg;
            cnt = driver->cfg.writeTimeout;

            key = gMailboxMCB.initParam.osalPrms.disableAllIntr();

            do
            {
                retVal = MailboxSendMessage(driver->baseAddrTx, hwCfg->tx.fifo, *((uint32_t *)buffer));
                cnt--;
            } while( (cnt != 0U) && (retVal == MESSAGE_INVALID));

            if (MESSAGE_INVALID == retVal)
            {
                retVal = MAILBOX_EINVAL;
            }

            gMailboxMCB.initParam.osalPrms.restoreAllIntr(key);
        }
    }

    return retVal;
}

int32_t Mailbox_read(Mbox_Handle handle, uint8_t *buffer, uint32_t size)
{
   int32_t retVal = MAILBOX_SOK;

    if ((handle != NULL) &&
        (((Mailbox_Driver *)handle)->hwCfg != NULL) &&
        (buffer != NULL) &&
        (((Mailbox_Driver *)handle)->cfg.readMode == MAILBOX_MODE_FAST))
    {
        MailboxReadMessage(((Mailbox_Driver *)handle)->baseAddrRx,
                           ((Mailbox_HwCfg *)(((Mailbox_Driver *)handle)->hwCfg))->rx.fifo,
                           (uint32_t *)buffer);
    }
    else
    {
        Mailbox_Driver* driver = (Mailbox_Driver*)handle;
        Mailbox_HwCfg* hwCfg = NULL;

        if (handle == NULL)
        {
            retVal = MAILBOX_EINVAL;
        }
        else if (driver->hwCfg == NULL)
        {
            retVal = MAILBOX_EINVAL;
        }
        else if (buffer == NULL)
        {
            retVal = MAILBOX_EINVAL;
        }
        else
        {
            hwCfg = (Mailbox_HwCfg *)driver->hwCfg;

            /* Get the message from Mailbox fifo */
            retVal = MailboxGetMessage(driver->baseAddrRx, hwCfg->rx.fifo, (uint32_t *)buffer);
            if (retVal == MESSAGE_INVALID)
            {
                retVal = MAILBOX_EINVAL;
            }
        }
    }

    return retVal;
}

#if defined(BUILD_MPU1_0) && defined(QNX_OS)
/* Mailbox Cluster Base Address  - virtual address for HLOS */
static uintptr_t g_Mailbox_BaseVirtAddr[MAILBOX_CLUSTER_CNT] = {0};

uintptr_t Mailbox_getQnxVirMemAddress(uint32_t daAddr, uint32_t size)
{
#include <sys/mman.h>
    void* p = mmap_device_memory(NULL, size, PROT_READ|PROT_WRITE|PROT_NOCACHE,
            0, daAddr);
    if( p == MAP_FAILED)
    {
        //SystemP_printf("Mailbox_getQnxVirMemAddress : failed to map..\n");
    }
    return (uintptr_t)p;
}
#endif

uintptr_t Mailbox_getBaseAddr(uint32_t clusterId)
{
    uintptr_t baseAddrPhy = 0x00000000U;
    uintptr_t baseAddrVirt = 0x00000000U;

    if( clusterId < MAILBOX_CLUSTER_CNT)
    {
        baseAddrPhy = g_Mailbox_BaseAddr[clusterId];
        if (gMailboxMCB.initParam.phyToVirtFxn)
        {
            baseAddrVirt = (uintptr_t)gMailboxMCB.initParam.phyToVirtFxn(baseAddrPhy);
        }
        else
        {
            baseAddrVirt = baseAddrPhy;
        }

#if defined(BUILD_MPU1_0) && defined(QNX_OS)
        if (g_Mailbox_BaseVirtAddr[clusterId] == 0)
        {
            g_Mailbox_BaseVirtAddr[clusterId] =
                Mailbox_getQnxVirMemAddress(baseAddrVirt, CSL_MAILBOX0_REGS0_SIZE);
        }
        baseAddrVirt = g_Mailbox_BaseVirtAddr[clusterId];
#endif
    }

    return baseAddrVirt;
}

int32_t Mailbox_getMailboxIntrRouterCfg(uint32_t selfId, uint32_t clusterId, uint32_t userId,
            Mailbox_MbConfig* cfg, uint32_t cnt)
{
    int32_t    retVal         = MAILBOX_SOK;


    switch(selfId)
    {
        case MAILBOX_INST_MPU1_0:
            if (clusterId == 0 && userId == 0)
            { //A53 VM0
                cfg->eventId = CSLR_GICSS0_SPI_MAILBOX0_MAILBOX_CLUSTER_0_MAILBOX_CLUSTER_PEND_0; //108U
            }
            else if (clusterId == 2 && userId == 0)
            {
                cfg->eventId = CSLR_GICSS0_SPI_MAILBOX0_MAILBOX_CLUSTER_2_MAILBOX_CLUSTER_PEND_0; //140U;
            }
            else if (clusterId == 3 && userId == 0)
            {
                cfg->eventId = CSLR_GICSS0_SPI_MAILBOX0_MAILBOX_CLUSTER_3_MAILBOX_CLUSTER_PEND_0; //141U;
            }
            else {
                retVal = MAILBOX_EINVAL;
            }
            break;
        case MAILBOX_INST_MCU_R5F:
            if (clusterId == 0 && userId == 2)
            {
                cfg->eventId = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MAILBOX0_MAILBOX_CLUSTER_0_MAILBOX_CLUSTER_PEND_2; //240U;
            }
            else if (clusterId == 1 && userId == 2)
            {
                cfg->eventId = CSLR_MCU_R5FSS0_CORE0_CPU0_INTR_MAILBOX0_MAILBOX_CLUSTER_1_MAILBOX_CLUSTER_PEND_2; //241U;
            }
            else
            {
                retVal = MAILBOX_EINVAL;
            }
	        break;

        case MAILBOX_INST_WKUP_R5F:
            if (clusterId == 0 && userId == 1)
            {
                cfg->eventId = CSLR_WKUP_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_0_MAILBOX_CLUSTER_PEND_3; //240U;
            }
            else if (clusterId == 4 && userId == 0)
            {
                cfg->eventId = CSLR_WKUP_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_4_MAILBOX_CLUSTER_PEND_0; //115U;
            }
            else
            {
                retVal = MAILBOX_EINVAL;
            }
            break;
        case MAILBOX_INST_MAIN_R5F:
            if (clusterId == 2 && userId == 1)
            {
                cfg->eventId = CSLR_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_2_MAILBOX_CLUSTER_PEND_3;
            }
            else if (clusterId == 5 && userId == 0)
            {
                cfg->eventId = CSLR_R5FSS0_CORE0_INTR_MAILBOX0_MAILBOX_CLUSTER_5_MAILBOX_CLUSTER_PEND_3;
            }
            else
            {
                retVal = MAILBOX_EINVAL;
            }
            break;
        case MAILBOX_INST_C7X_0:
            if (clusterId == 2 && userId == 2)
            {
                cfg->eventId = 59U + CSLR_C7X256V0_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_2_MAILBOX_CLUSTER_PEND_1;
            }
            else if (clusterId == 6 && userId == 0)
            {
                cfg->eventId = 59U + CSLR_C7X256V0_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_6_MAILBOX_CLUSTER_PEND_1;
            }
            else
            {
                retVal = MAILBOX_EINVAL;
            }
            break;
        case MAILBOX_INST_C7X_1:
            if (clusterId == 3 && userId == 1)
            {
                cfg->eventId = 59U + CSLR_C7X256V1_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_3_MAILBOX_CLUSTER_PEND_2;
            }
            else if (clusterId == 7 && userId == 0)
            {
                cfg->eventId = 59U + CSLR_C7X256V1_CLEC_SOC_EVENTS_IN_MAILBOX0_MAILBOX_CLUSTER_7_MAILBOX_CLUSTER_PEND_2;
            }
            else
            {
                retVal = MAILBOX_EINVAL;
            }
            break;


        default:

	    retVal = MAILBOX_EINVAL;
            break;
    }

    cfg->priority      = 1U;

    return retVal;
}

#if defined(BUILD_MCU) && defined(VIM_DIRECT_REGISTRATION)
static inline void Mailbox_directClrNewMsgStatus(Mbox_Handle handle)
{
    MailboxClrNewMsgStatus(((Mailbox_Driver *)handle)->baseAddrRx,
                           ((Mailbox_HwCfg *)((Mailbox_Driver *)handle)->hwCfg)->rx.user,
                           ((Mailbox_HwCfg *)((Mailbox_Driver *)handle)->hwCfg)->rx.fifo);

    CSL_vimClrIntrPending((CSL_vimRegs *)(uintptr_t)TEST_VIM_BASE_ADDR,
                          ((Mailbox_HwCfg *)((Mailbox_Driver *)handle)->hwCfg)->eventId);
    /* Acknowledge interrupt servicing */
    CSL_vimAckIntr((CSL_vimRegs *)(uintptr_t)TEST_VIM_BASE_ADDR, \
                    (CSL_VimIntrMap)0u );
}

__attribute__((interrupt("IRQ")))     void mailboxIsr_0(void);
__attribute__((interrupt("IRQ")))     void mailboxIsr_1(void);
__attribute__((interrupt("IRQ")))     void mailboxIsr_5(void);



#ifdef __cplusplus
__attribute__((target("code_state")))
#else
 __attribute__((target("code_state"))) void mailboxIsr_0(void);
#endif  /* #ifdef __cplusplus */
void mailboxIsr_0(void)
{
    (g_VimCallback[MAILBOX_INST_MPU1_0])(g_VimCallbackArg[MAILBOX_INST_MPU1_0], MAILBOX_INST_MPU1_0);
    Mailbox_directClrNewMsgStatus(g_VimCallbackArg[MAILBOX_INST_MPU1_0]);
}

#ifdef __cplusplus
__attribute__((target("code_state")))
#else
__attribute__((target("code_state"))) void mailboxIsr_1(void);
#endif  /* #ifdef __cplusplus */
void mailboxIsr_1(void)
{
    (g_VimCallback[MAILBOX_INST_MCU1_0])(g_VimCallbackArg[MAILBOX_INST_MCU1_0], MAILBOX_INST_MCU1_0);
    Mailbox_directClrNewMsgStatus(g_VimCallbackArg[MAILBOX_INST_MCU1_0]);
}

uintptr_t mailboxIsrArray[6] =
{
    (uintptr_t)&mailboxIsr_0,
    (uintptr_t)&mailboxIsr_1,
};
#endif

void Mailbox_InternalCallbackFast(uintptr_t arg)
{
    uint32_t idx = (uint32_t)arg;
    Mbox_Handle handle = g_FastCallbackArg[idx];

    (g_FastCallback[idx])(g_FastCallbackArg[idx], idx);

    MailboxClrNewMsgStatus(((Mailbox_Driver *)handle)->baseAddrRx,
                           ((Mailbox_HwCfg *)((Mailbox_Driver *)handle)->hwCfg)->rx.user,
                           ((Mailbox_HwCfg *)((Mailbox_Driver *)handle)->hwCfg)->rx.fifo);
}

void Mailbox_InternalCallback(uintptr_t arg)
{
    uint32_t              n;
    Mailbox_Data         *mbox;
    Mailbox_Fifo         *fifo;

    mbox = (Mailbox_Data *)arg;
    if(mbox != NULL)
    {
        mbox->intCnt++;
        /* Optimization to save time checking the fifo if only one is being used */
        if (mbox->fifoCnt == 1U)
        {
            fifo = &mbox->fifoTable[0];
            if (mbox->fifoTable[0].func)
            {
                /* Call the function with handle and arg */
                (mbox->fifoTable[0].func)(fifo->handle, fifo->arg);
            }
            /* Clear new message status of Mailbox */
            MailboxClrNewMsgStatus(mbox->baseAddr, mbox->userId, fifo->queueId);
        }
        else
        {
            for(n = 0; n < mbox->fifoCnt; n++)
            {
                fifo = &mbox->fifoTable[n];

                if(0U != MailboxGetRawNewMsgStatus(mbox->baseAddr, mbox->userId, fifo->queueId))
                {
                    if (mbox->fifoTable[n].func)
                    {
                        /* Call the function with handle and arg */
                        (mbox->fifoTable[n].func)(fifo->handle, fifo->arg);
                    }
                    /* Clear new message status of Mailbox */
                    MailboxClrNewMsgStatus(mbox->baseAddr, mbox->userId, fifo->queueId);
                }
            }
        }
        mbox->noMsgCnt++;
    }
}

int32_t Mailbox_registerInterrupts(Mbox_Handle handle)
{
    Mailbox_Driver        *driver;
    int32_t               retVal = MAILBOX_SOK;
    Mailbox_HwCfg         *hwCfg = NULL;
    uint32_t              n;
    Mailbox_Data          *mbox = NULL;
    Mailbox_MbConfig      cfg;
    Mailbox_Instance      localEndpoint;
    void                  *hwiHandle = NULL;
    uint32_t              i = 0;
    Mailbox_Instance remoteEndpoint;
    uint32_t              q = 0;

    driver = (Mailbox_Driver *)handle;
    localEndpoint = driver->localEndpoint;
    remoteEndpoint = driver->remoteEndpoint;

    hwCfg = (Mailbox_HwCfg *)driver->hwCfg;

    /* Get the mailbox base addr for RX cluster */
    driver->baseAddrRx = Mailbox_getBaseAddr(hwCfg->rx.cluster);
    driver->baseAddrTx = Mailbox_getBaseAddr(hwCfg->tx.cluster);

    if ((driver->cfg.readMode != MAILBOX_MODE_POLLING) && (driver->cfg.readCallback != NULL))
    {
        if (gMailboxMCB.initParam.osalPrms.registerIntr == NULL)
        {
            retVal = MAILBOX_EINVAL;
        }

        if (retVal == MAILBOX_SOK)
        {
            /*
             * check if this cluster and user ID is already registered, and if so,
             * skip interrupt registration and just store callback/arg data for this
             * fifo to be handled in the callback
             */
            for (n = 0; n < g_mBoxCnt; n++)
            {
                if ((driver->baseAddrRx == g_mBoxData[n].baseAddr) &&
                    (hwCfg->rx.user == g_mBoxData[n].userId))
                        break;
            }

            /* Get the MailBox Data */
            mbox = &g_mBoxData[n];

            if (n == g_mBoxCnt)
            {
                /* Could not find one, this is new entry */
                mbox->baseAddr = driver->baseAddrRx;
                mbox->fifoCnt  = 0;
                mbox->userId   = hwCfg->rx.user;

                /*
                 * Before we register for the interrupt, make sure that all the fifo
                 * new msg interrupts are disabled. This helps in case there is
                 * some stale state from previous run.
                 */
                for (q = 0; q < MAILBOX_MAXFIFO_CNT; q++)
                {
                    MailboxDisableNewMsgInt(driver->baseAddrRx, hwCfg->rx.user, q);
                    MailboxClrNewMsgStatus(driver->baseAddrRx, hwCfg->rx.user, q);
                }

                /* clear new msg status */
                MailboxClrNewMsgStatus(driver->baseAddrRx, hwCfg->rx.user, hwCfg->rx.fifo);

                /* Get the interrupt configuration */
                retVal = Mailbox_getMailboxIntrRouterCfg(localEndpoint, hwCfg->rx.cluster, hwCfg->rx.user, &cfg, g_mBoxCnt);
                if (retVal == MAILBOX_SOK)
                {
                    hwCfg->eventId = cfg.eventId;

                    /* Register interrupts */
                    if ((hwCfg->exclusive == TRUE) && ((driver->cfg.readMode == MAILBOX_MODE_FAST)))
                    {
#if defined(BUILD_MCU) && defined(VIM_DIRECT_REGISTRATION)
                        if (driver->cfg.enableVIMDirectInterrupt == true)
                        {
                            g_VimCallback[remoteEndpoint] = driver->cfg.readCallback;
                            g_VimCallbackArg[remoteEndpoint] = driver;

                            hwiHandle = gMailboxMCB.initParam.osalPrms.registerDirectIntr((Mbox_OsalDirectIsrFxn)mailboxIsrArray[remoteEndpoint],
                                                                                      cfg.eventId,
                                                                                      cfg.priority);
                        }
#endif
                        if (hwiHandle == NULL)
                        {
                            /* Direct interrupt registration failed or isn't enabled, try regular registration */
                            g_FastCallback[remoteEndpoint] = driver->cfg.readCallback;
                            g_FastCallbackArg[remoteEndpoint] = driver;
                            hwiHandle = gMailboxMCB.initParam.osalPrms.registerIntr(Mailbox_InternalCallbackFast,
                                                                                    cfg.eventId,
                                                                                    cfg.priority,
                                                                                    (void *)((uintptr_t)remoteEndpoint),
                                                                                    (char *)"MAILBOX_NEW_MSG");
                            gMailboxMCB.hwiHandles.mailboxFull = hwiHandle;
                            if(hwiHandle == NULL)
                            {
                                //SystemP_printf("Mailbox_plugInterrupt : Failed to register ISR...\n");
                            }
                        }
                    }
                    else
                    {
                        hwiHandle = gMailboxMCB.initParam.osalPrms.registerIntr(Mailbox_InternalCallback,
                                                                                cfg.eventId,
                                                                                cfg.priority,
                                                                                (void *)mbox,
                                                                                (char *)"MAILBOX_NEW_MSG");
                        gMailboxMCB.hwiHandles.mailboxFull = hwiHandle;
                        if(hwiHandle == NULL)
                        {
                            //SystemP_printf("Mailbox_plugInterrupt : Failed to register ISR...\n");
                        }
                    }
                    g_mBoxCnt++;
                }
            }
        }

        if (retVal == MAILBOX_SOK)
        {
            /* Check if there is empty space in our fifoTable (for example if handle is closed and re-opened) */
            for (i = 0; i < mbox->fifoCnt; i++)
            {
                if (mbox->fifoTable[i].func == NULL)
                {
                    break;
                }
            }

            /* Add the fifo data for the remoteProcId. */
            mbox->fifoTable[i].cfgNdx  = n;
            mbox->fifoTable[i].func    = driver->cfg.readCallback;
            mbox->fifoTable[i].arg     = driver->remoteEndpoint;
            mbox->fifoTable[i].queueId = hwCfg->rx.fifo;
            mbox->fifoTable[i].handle  = driver;
            gInstToMBoxDataMap[driver->remoteEndpoint] = (uintptr_t)mbox;

            if (i == mbox->fifoCnt)
            {
                mbox->fifoCnt++;
            }

            if (driver->cfg.enableInterrupts == true)
            {
                /* enable the mailbox interrupt */
                MailboxEnableNewMsgInt(driver->baseAddrRx, hwCfg->rx.user, hwCfg->rx.fifo);
            }
        }
    }

    return retVal;
}

int32_t Mailbox_unregisterInterrupts(Mbox_Handle handle)
{
    Mailbox_Driver*    driver;
    int32_t            retVal = MAILBOX_SOK;
    Mailbox_HwCfg      *hwCfg = NULL;
    Mailbox_Data       *mbox = NULL;
    uint8_t            i = 0;

    driver = (Mailbox_Driver *)handle;
    hwCfg = (Mailbox_HwCfg *)driver->hwCfg;

    if ((driver->cfg.readMode != MAILBOX_MODE_POLLING) && (driver->cfg.readCallback != NULL))
    {
        mbox = (Mailbox_Data *)gInstToMBoxDataMap[driver->remoteEndpoint];

        /* Disable the mailbox interrupt */
        MailboxDisableNewMsgInt(driver->baseAddrRx, hwCfg->rx.user, hwCfg->rx.fifo);

        /* Remove the callback info from the fifo table */
        gInstToMBoxDataMap[driver->remoteEndpoint] = (uintptr_t)NULL;

        for (i = 0; i < mbox->fifoCnt; i++)
        {
            if (mbox->fifoTable[i].queueId == hwCfg->rx.fifo)
            {
                /* clear the fifo info */
                mbox->fifoTable[i].cfgNdx  = 0;
                mbox->fifoTable[i].func    = NULL;
                mbox->fifoTable[i].arg     = 0;
                mbox->fifoTable[i].queueId = 0;
                mbox->fifoTable[i].handle  = NULL;
            }
        }
    }

    return retVal;
}

int32_t Mailbox_enableInterrupts(Mbox_Handle handle)
{
    Mailbox_Driver*    driver;
    int32_t            retVal = MAILBOX_SOK;
    Mailbox_HwCfg      *hwCfg = NULL;

    if (handle != NULL)
    {
        driver = (Mailbox_Driver *)handle;
        hwCfg = (Mailbox_HwCfg *)driver->hwCfg;

        if (hwCfg != NULL)
        {
            MailboxEnableNewMsgInt(driver->baseAddrRx, hwCfg->rx.user, hwCfg->rx.fifo);
	}
        else
        {
            retVal = MAILBOX_EINVAL;
        }
    }
    else
    {
        retVal = MAILBOX_EINVAL;
    }

    return retVal;
}

int32_t Mailbox_disableInterrupts(Mbox_Handle handle)
{
    Mailbox_Driver*    driver;
    int32_t            retVal = MAILBOX_SOK;
    Mailbox_HwCfg      *hwCfg = NULL;

    if (handle != NULL)
    {
        driver = (Mailbox_Driver *)handle;
        hwCfg = (Mailbox_HwCfg *)driver->hwCfg;

        if (hwCfg != NULL)
        {
            MailboxDisableNewMsgInt(driver->baseAddrRx, hwCfg->rx.user, hwCfg->rx.fifo);
        }
        else
        {
            retVal = MAILBOX_EINVAL;
        }
    }
    else
    {
        retVal = MAILBOX_EINVAL;
    }

    return retVal;
}

uint64_t Mailbox_defaultVirtToPhyFxn(const void *virtAddr)
{
    return ((uint64_t) virtAddr);
}

void *Mailbox_defaultPhyToVirtFxn(uint64_t phyAddr)
{
#if defined (__aarch64__)
    uint64_t temp = phyAddr;
#else
    /* R5 is 32-bit machine, need to truncate to avoid void * typecast error */
    uint32_t temp = (uint32_t) phyAddr;
#endif

    return ((void *) temp);
}
