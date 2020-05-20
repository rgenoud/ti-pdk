/*
 * SDL EXCEPTION
 *
 * Software Diagnostics Library module for handling exceptions
 *
 *  Copyright (c) Texas Instruments Incorporated 2018-2020
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

#include <stddef.h>
#include <stdbool.h>

#include <sdl_esm.h>
#include <sdl_mpu.h>
#include <sdl_utils.h>

#include "sdl_exception.h"
#include "sdl_exception_priv.h"

/* Local defines */

#define SDL_EXCEPTION_SYNC_PARITY_OR_ECC_ERROR_MASK 0x409u
#define SDL_EXCEPTION_ASYNC_PARITY_OR_ECC_ERROR_MASK 0x408u
#define SDL_EXCEPTION_MPU_WRITE_PERMISSION_FAULT_MASK      (0x080DU)
#define SDL_EXCEPTION_MPU_READ_PERMISSION_FAULT_MASK       (0x000DU)

#ifdef mcu1_0
#define SDL_LOCAL_EXCEPTION_DED_ERROR SDL_ESM_ECC_PARAM_MCU_CPU0_DED_ERROR
#else
#define SDL_LOCAL_EXCEPTION_DED_ERROR SDL_ESM_ECC_PARAM_MCU_CPU1_DED_ERROR
#endif

void SDL_EXCEPTION_undefInstructionExptnHandler(void *param);
void SDL_EXCEPTION_swIntrExptnHandler(void *param);
void SDL_EXCEPTION_prefetchAbortExptnHandler(void *param);
void SDL_EXCEPTION_dataAbortExptnHandler(void *param);
void SDL_EXCEPTION_irqExptnHandler(void *param);
void SDL_EXCEPTION_fiqExptnHandler(void *param);
extern bool SDL_MPU_exceptionChkSelfTest(SDL_MPU_memAccessType faultType,
                                        uint32_t              faultAddr);

static SDL_EXCEPTION_Instance_t SDL_EXCEPTION_instance;

/*********************************************************************
 * @fn      SDL_exceptionInit
 *
 * @brief   Initialise Exception module
 *
 * @param1  callbackFunctions: Pointer to callback Functions
 *
 * @return  None
 */
void SDL_EXCEPTION_init(const SDL_EXCEPTION_CallbackFunctions_t *callbackFunctions)
{
    /* Store exception callback functions */
    SDL_EXCEPTION_instance.callbackFunctions = *callbackFunctions;
    /* Initialize ECC Callback Function */
    SDL_EXCEPTION_instance.ECCCallBackFunction = NULL;
    return;
}

/*********************************************************************
 * @fn      SDL_exceptionRegisterECCHandler
 *
 * @brief   Function to register ECC exception handler
 *
 * @param1  ECCCallBackFunctionPtr: callback function to register
 *
 * @return  None
 */
void SDL_EXCEPTION_registerECCHandler(SDL_EXCEPTION_ECCCallback_t ECCCallBackFunctionPtr)
{
    /* Store call back function */
    SDL_EXCEPTION_instance.ECCCallBackFunction = ECCCallBackFunctionPtr;

    return;
}


/*********************************************************************
 * @fn      SDL_undefInstructionExptnHandler
 *
 * @brief   SDL exception handler for undefined instructions
 *
 * @param1  param: parameter pointer
 *
 * @return  None
 */
void SDL_EXCEPTION_undefInstructionExptnHandler(void *param)
{

    /* Store param pointer */
    SDL_EXCEPTION_instance.paramPtr = param;

    /* Execute callback function */
    if (SDL_EXCEPTION_instance.callbackFunctions.udefExptnCallback != ((void *)0u)) {
        SDL_EXCEPTION_instance.callbackFunctions.udefExptnCallback();
    }

}

/*********************************************************************
 * @fn      SDL_swIntrExptnHandler
 *
 * @brief   SDL exception handler for Software interrupts
 *
 * @param1  param: parameter pointer
 *
 * @return  None
 */
void SDL_EXCEPTION_swIntrExptnHandler(void *param)
{
    /* Store param pointer */
    SDL_EXCEPTION_instance.paramPtr = param;


    /* Execute callback function */
    if (SDL_EXCEPTION_instance.callbackFunctions.swiExptnCallback != ((void *)0u)) {
        SDL_EXCEPTION_instance.callbackFunctions.swiExptnCallback();
    }
}

/*********************************************************************
 * @fn      SDL_prefetchAbortExptnHandler
 *
 * @brief   SDL exception handler for Prefetch abort
 *
 * @param1  param: parameter pointer
 *
 * @return  None
 */
void SDL_EXCEPTION_prefetchAbortExptnHandler(void *param)
{
    uint32_t ifsrValue;
    uint32_t ifarValue;

    /* Store param pointer */
    SDL_EXCEPTION_instance.paramPtr = param;

    /* Handle any instruction abort due to ECC errors */
    /* read IFSR value */
    ifsrValue = SDL_UTILS_getIFSR();
    if ((ifsrValue & SDL_EXCEPTION_SYNC_PARITY_OR_ECC_ERROR_MASK)
        == SDL_EXCEPTION_SYNC_PARITY_OR_ECC_ERROR_MASK) {
        ifarValue = SDL_UTILS_getIFAR();
        /* Execute callback function */
        if (SDL_EXCEPTION_instance.ECCCallBackFunction != ((void *)0u)) {
            SDL_EXCEPTION_instance.ECCCallBackFunction(
                SDL_LOCAL_EXCEPTION_DED_ERROR,
                ifarValue);
        }
    } else if ((ifsrValue & SDL_EXCEPTION_ASYNC_PARITY_OR_ECC_ERROR_MASK)
            == SDL_EXCEPTION_ASYNC_PARITY_OR_ECC_ERROR_MASK) {
             /* Execute callback function */
            if (SDL_EXCEPTION_instance.ECCCallBackFunction != ((void *)0u)) {
                SDL_EXCEPTION_instance.ECCCallBackFunction(
                    SDL_LOCAL_EXCEPTION_DED_ERROR,
                    SDL_ESM_ERRORADDR_INVALID);
            }
    } else {
        /* Execute callback function */
        if (SDL_EXCEPTION_instance.callbackFunctions.pabtExptnCallback != ((void *)0u)) {
            SDL_EXCEPTION_instance.callbackFunctions.pabtExptnCallback();
        }
    }
}

/*********************************************************************
 * @fn      SDL_dataAbortExptnHandler
 *
 * @brief   SDL exception handler for Data abort
 *
 * @param1  param: parameter pointer
 *
 * @return  None
 */
void SDL_EXCEPTION_dataAbortExptnHandler(void *param)
{
   uint32_t dfsrValue;
   uint32_t dfarValue;
   bool     isMPUSelfTest;

   /* Store last param pointer */
   SDL_EXCEPTION_instance.paramPtr = param;

   /* Handle any data abort due to ECC errors */
   /* read DFSR value */
   dfsrValue = SDL_UTILS_getDFSR();
   if ((dfsrValue & SDL_EXCEPTION_SYNC_PARITY_OR_ECC_ERROR_MASK)
       == SDL_EXCEPTION_SYNC_PARITY_OR_ECC_ERROR_MASK) {
       dfarValue = SDL_UTILS_getDFAR();
       /* Execute callback function */
       if (SDL_EXCEPTION_instance.ECCCallBackFunction != ((void *)0u)) {
           SDL_EXCEPTION_instance.ECCCallBackFunction(
               SDL_ESM_ECC_PARAM_MCU_CPU0_DED_ERROR,
               dfarValue);
       }
   } else if ((dfsrValue & SDL_EXCEPTION_ASYNC_PARITY_OR_ECC_ERROR_MASK)
           == SDL_EXCEPTION_ASYNC_PARITY_OR_ECC_ERROR_MASK) {
            /* Execute callback function */
           if (SDL_EXCEPTION_instance.ECCCallBackFunction != ((void *)0u)) {
               SDL_EXCEPTION_instance.ECCCallBackFunction(
                   SDL_ESM_ECC_PARAM_MCU_CPU0_DED_ERROR,
                   SDL_ESM_ERRORADDR_INVALID);
           }
   } else {
       /* Get the fault address */
       dfarValue = SDL_UTILS_getDFAR();
       if ((dfsrValue & SDL_EXCEPTION_MPU_WRITE_PERMISSION_FAULT_MASK) 
                  == SDL_EXCEPTION_MPU_WRITE_PERMISSION_FAULT_MASK) {
              /* Call the MPU exception check function to check if it is
               * due to write permission fault from self test, 
               * if yes, correct the fault to proceed the self test */
               isMPUSelfTest = SDL_MPU_exceptionChkSelfTest(SDL_MPU_DATA_WRITE_ACCESS,
                                                             dfarValue);
       }
       else {
              /* Call the MPU exception check function to check if it is
               * due to read permission fault from self test, 
               * if yes, correct the fault to proceed the self test */
               isMPUSelfTest = SDL_MPU_exceptionChkSelfTest(SDL_MPU_DATA_READ_ACCESS,
                                                             dfarValue);
       }

       /* Execute callback function */
       if ((!isMPUSelfTest) &&
           (SDL_EXCEPTION_instance.callbackFunctions.dabtExptnCallback != ((void *)0u))) {
           SDL_EXCEPTION_instance.callbackFunctions.dabtExptnCallback();
       }
   }
}

/*********************************************************************
 * @fn      SDL_irqExptnHandler
 *
 * @brief   SDL exception handler for IRQ
 *
 * @param1  param: parameter pointer
 *
 * @return  None
 */
void SDL_EXCEPTION_irqExptnHandler(void *param)
{
    /* Store param pointer */
    SDL_EXCEPTION_instance.paramPtr = param;

    /* Execute callback function */
    if (SDL_EXCEPTION_instance.callbackFunctions.irqExptnCallback != ((void *)0u)) {
        SDL_EXCEPTION_instance.callbackFunctions.irqExptnCallback();
    }
}

/*********************************************************************
 * @fn      SDL_fiqExptnHandler
 *
 * @brief   SDL exception handler for FIQ
 *
 * @param1  param: parameter pointer
 *
 * @return  None
 */
void SDL_EXCEPTION_fiqExptnHandler(void *param)
{
    /* Store param pointer */
    SDL_EXCEPTION_instance.paramPtr = param;

    /* Execute callback function */
    if (SDL_EXCEPTION_instance.callbackFunctions.fiqExptnCallback != ((void *)0u)) {
        SDL_EXCEPTION_instance.callbackFunctions.fiqExptnCallback();
    }
}
