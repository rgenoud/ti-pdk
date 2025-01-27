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
/** @file dfe_flOpen.c
 *
 *  @path  $(CSLPATH)\src\ip\dfe
 *
 *  @brief File for functional layer of CSL API dfeFl_Open()
 *
 *
 */

#include <ti/drv/dfe/dfe_fl.h>

/** ============================================================================
 *   @n@b dfeFl_Open
 *
 *   @b Description
 *   @n The API would open the Dfe module. It returns a valid handle
 *      which is  used for subsequent Dfe APIs.
 *
 *   @b Arguments
 *   @verbatim
         pDfeObj    Pointer to the Dfe object
         dfeNum     Dfe Instance number
         pDfeParam  Pointer to the parameter
         status     Pointer for the returning status
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li	Valid DfeFl_Handle if oper properly
 *   @li	NULL if any error
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1.    Dfe object structure is populated
 *   @n   2.    The status is returned in the status variable. If status
 *              returned is
 *   @li            DFE_FL_SOK             	Valid Dfe handle is returned
 *   @li            DFE_FL_INVPARAMS		The open command fails
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
         DfeFl_InstNum dfeInstNum;
         DfeFl_Handle hDfe;
         DfeFl_Status status = DFE_FL_SOK;

         // open DFE
         dfeFl_Init(&dfeCtx);
         dfeParam.flags = 0;
		 dfeInstNum = CSL_DFE;
         hDfe = dfeFl_Open(&objDfe, dfeInstNum, &dfeParam, &status);

     @endverbatim
 * ===========================================================================
 */
DfeFl_Handle dfeFl_Open (
    DfeFl_Obj   *pDfeObj,
    DfeFl_InstNum  dfeNum,
    DfeFl_Param *pDfeParam,
    uint32_t       dfeBaseAddr,
    DfeFl_Status   *status
)
{
    // check parameter
	if (status == NULL)
		return NULL;

    if(pDfeObj == NULL || dfeNum != 0)
    {
        *status = DFE_FL_INVPARAMS;
        return NULL;
    }
    
    pDfeObj->regs = (DfeFl_RegsOvly)dfeBaseAddr;
    pDfeObj->dfeNum = dfeNum;
    return (DfeFl_Handle)pDfeObj;
}
