
#include "board_internal.h"

/**
 *  \file   board_init.c
 *
 *  \brief  Board library main file
 */

Board_STATUS Board_init(Board_initCfg cfg)
{
    Board_STATUS ret = BOARD_SOK;

    if (cfg & BOARD_INIT_UNLOCK_MMR)
        ret = Board_unlockMMR();
    if (ret != BOARD_SOK)
        return ret;
    if (cfg & BOARD_INIT_PINMUX_CONFIG)
        ret = Board_uartTxPinmuxConfig();
    if (ret != BOARD_SOK)
        return ret;
    if (cfg & BOARD_INIT_UART_STDIO)
        ret = Board_uartStdioInit();
    if (ret != BOARD_SOK)
        return ret;
    return ret;
}
