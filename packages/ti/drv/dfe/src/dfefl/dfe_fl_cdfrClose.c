/********************************************************************
* Copyright (C) 2012-2013 Texas Instruments Incorporated.
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
/** @file dfe_fl_cdfrClose.c
 *
 *  @path  $(CSLPATH)\src\ip\dfe
 *
 *  @brief File for functional layer of CSL API dfeFl_CdfrClose()
 *
 *
 */
/* =============================================================================
 * Revision History
 * ===============
 *
 *
 * =============================================================================
 */
#include <ti/drv/dfe/dfe_fl_cdfr.h>

/** ============================================================================
 *   @n@b dfeFl_CdfrClose
 *
 *   @b Description
 *   @n Close the Dfe Cdfr handle.
 *
 *   @b Arguments
 *   @verbatim
         hDfeCdfr    Valid dfeFl_CdfrHandle
     @endverbatim
 *
 *   <b> Return Value </b>  DfeFl_Status
 *   @li                    DFE_FL_SOK             - Close successful
 *   @li                    DFE_FL_BADHANDLE  - Close failure
 *
 *   <b> Pre Condition </b>
 *   @n  Valid dfeFl_CdfrHandle handle
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Reads
 *   @n  None
 *
 *   @b Writes
 *   @n  None
 *
 *   @b Example
 *   @verbatim

         DfeFl_Context dfeCtx;
         DfeFl_Param dfeParam;
         DfeFl_Obj objDfe;
         DfeFl_CdfrObj objDfeCdfr[DFE_FL_CDFR_PER_CNT];
         DfeFl_Handle hDfe;
         DfeFl_CdfrHandle hDfeCdfr[DFE_FL_CDFR_PER_CNT];
         DfeFl_Status status = DFE_FL_SOK;

         // open DFE
         dfeFl_Init(&dfeCtx);
         dfeParam.flags = 0;
         hDfe = dfeFl_Open(&objDfe, 0, &dfeParam, &status);
         if(status != DFE_FL_SOK)
         {
         	 return FAIL;
         }

         for(i = 0; i < DFE_FL_CDFR_PER_CNT; i++)
         {
		 	 hDfeCdfr[i] = dfeFl_CdfrOpen(hDfe, &objDfeCdfr[i], i, &status);
		 	 if(status != DFE_FL_SOK)
			 {
				 return FAIL;
			 }
         }

         // close handle
         for(i = 0; i < DFE_FL_CDFR_PER_CNT; i++)
         {
         	 status = dfeFl_CdfrClose(hDfeCdfr[i]);
         	 if(status != DFE_FL_SOK)
         	 {
         	 	 return FAIL;
         	 }
         }
         return PASS;

     @endverbatim
 * ===========================================================================
 */
DfeFl_Status dfeFl_CdfrClose(DfeFl_CdfrHandle hDfeCdfr)
{
    DfeFl_Status st;

    if (hDfeCdfr != NULL)
    {
        hDfeCdfr->hDfe = NULL;
        hDfeCdfr->regs = (DfeFl_CdfrRegsOvly)NULL;
        hDfeCdfr->perNum = (DfeFl_InstNum)-1;

        st = DFE_FL_SOK;
    }
    else 
    {
        st = DFE_FL_BADHANDLE;
    }

    return st;
}

