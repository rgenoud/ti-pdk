/**
 *  \file   board_i2cLed.c
 *
 *  \brief  AM572x IDK i2cLed APIs
 *
 */

/*
 * Copyright (c) 2018, Texas Instruments Incorporated
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
 **/

#include <ti/drv/i2c/i2c.h>
#include <ti/board/board_cfg.h>

I2C_Handle i2cLedhandle = NULL;
static I2C_Transaction i2cLedTransaction;
static char i2cLedtxBuf[2] = {0x44 , 0x00};

void Board_i2cLedInit()
{
    /*I2C Init */
    I2C_Params i2cParams;



    if(i2cLedhandle ==NULL)
    {
        I2C_init();
        I2C_Params_init(&i2cParams);
        i2cParams.bitRate = I2C_400kHz;
        i2cLedhandle = I2C_open(BOARD_I2C_LED_INSTANCE, &i2cParams);
    }

    i2cLedTransaction.slaveAddress = 0x60U;
    i2cLedTransaction.writeBuf = (uint8_t *)&i2cLedtxBuf[0];
    i2cLedTransaction.writeCount = 2;
}

void Board_setDigOutput(uint8_t ledData)
{
    i2cLedtxBuf[1] = ledData;
    I2C_transfer(i2cLedhandle, &i2cLedTransaction);
}
