/**
 * @file   am65xx/USB_soc.c
 *
 * @brief  This file defines the USB interface structure specific to AM57x
 */
/*
 * Copyright (c) 2015-2021, Texas Instruments Incorporated
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
/** ============================================================================*/

#include "types.h"

/* pdk includes */
#include <ti/drv/usb/usb_drv.h>


/* USB_dwc functions */
USB_Handle   USB_open_dwc(USB_Handle handle, USB_Params *params);
void         USB_close_dwc(USB_Handle handle);
void         USB_irqConfig_dwc(USB_Handle handle, USB_Params* params);
void         USB_irqCore_dwc(USB_Handle handle, USB_Params* params);
void         USB_irqMisc_dwc(USB_Handle handle, USB_Params* params);

/* USB interface function table for USB_dwc (Synopsys) implementation */
const USB_FxnTable USB_FxnTable_dwc = {
    &USB_open_dwc,
    &USB_close_dwc,
    &USB_irqConfig_dwc,
    &USB_irqCore_dwc,
    &USB_irqMisc_dwc
};


/* USB configuration structure - for each of 
 * the USB instances + the null terminate entry */
USB_Config USB_config[3] = {
    {
        &USB_FxnTable_dwc,  /*fxnTablePtr */
        0,                  /* isOpenned */
        0,                  /* handleCppiDmaInApp */
        0,                  /* dmaEnabled */
        0,                  /* usb30Enabled  - disabled by default */
        0                   /* usbParams */
    },

    {
        &USB_FxnTable_dwc,  /*fxnTablePtr */
        0,                  /* isOpenned */
        0,                  /* handleCppiDmaInApp */
        0,                  /* dmaEnabled */
        0,                  /* usb30Enabled */
        0                   /* usbParams */
    },

    {NULL, 0}
};



/* 
 * return the configurable USB config 
 *
 * Used to modify default configuration
 *
 */
void USB_getConfig(uint32_t usbInstanceNo, USB_Config** usbConfig)
{
    if ((usbInstanceNo == 0) || (usbInstanceNo == 1))
    {
        *usbConfig = &USB_config[usbInstanceNo];
    }
    else
    {
       /* invalid usbInstance number. return null */
       *usbConfig = 0; 
    }
}


