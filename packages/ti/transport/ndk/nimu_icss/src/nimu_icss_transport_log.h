/**
 *  \file   NIMU_ICSS_transport_log.h
 *
 *  \brief  This file contains the prototypes for the log print functions. By
            default the prints will be directed to serial console using UART.
 *
 */

/* Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/ 
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

#ifndef NIMU_ICSS_TRANSPORT_LOG__H
#define NIMU_ICSS_TRANSPORT_LOG__H

#ifdef __cplusplus
extern "C" {
#endif


/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/

/**********************************************************************
 ************************** Macros ************************************
 **********************************************************************/
/* Enable the below macro to have prints on the IO Console */
/* #define CIO_DRV_CONSOLE */

#ifdef CIO_DRV_CONSOLE
#define NIMU_ICSS_transport_log            printf
#define NIMU_ICSS_transport_log1           printf
#define NIMU_ICSS_transport_log2           printf
#define NIMU_ICSS_transport_log3           printf
#else
#define NIMU_ICSS_transport_log(x)
#define NIMU_ICSS_transport_log1(x,y)
#define NIMU_ICSS_transport_log2(x,y,z)
#define NIMU_ICSS_transport_log3(x,y,z,l)
#endif

#ifdef __cplusplus
}
#endif

#endif /* _NIMU_ICSS_TRANSPORT_LOG_H */
