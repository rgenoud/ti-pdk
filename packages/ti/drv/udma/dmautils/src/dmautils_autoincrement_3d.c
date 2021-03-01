/*
 *  Copyright (c) Texas Instruments Incorporated 2018
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


/*
 *******************************************************************************
 *
 *  DMA utility functions
 *
 *******************************************************************************
*/

/**
 *****************************************************************************
 * \file  dmautils_autoincrement_3d.c
 *
 * \brief*  This file contains function implementation for dma util functions for
 *  configuring DMA on J7 device for autoincrement 3D usecase.
 *
 *
 *****************************************************************************
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "ti/drv/udma/udma.h"
#include "ti/drv/udma/dmautils/src/dmautils_autoincrement_3d_priv.h"
#include "ti/drv/udma/dmautils/include/dmautils_autoincrement_3d.h"

#if defined (__C7120__)
#include <c7x.h>
#endif

#define CRASH_DEBUG_PRINTS 0
#define XFER_DATA_WITH_TRIGGER  0
#define USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR 0
typedef enum{
  DMAUTILSAUTOINC3D_DRUSPEC_106 = 0,
  DMAUTILSAUTOINC3D_DRUSPEC_106MOD = 1
}DmaUtilsAutoInc3d_DRUSpecVersion;
#define SB_DIM1_SPEC DMAUTILSAUTOINC3D_DRUSPEC_106

/* If its a Loki Build then force the mode to be in hostemulation as Loki doesnt support DRU */
#if defined (LOKI_BUILD)
#define HOST_EMULATION (1U)
#endif
#define DMAUTILS_ALIGN_CEIL(VAL, ALIGN) ((((VAL) + (ALIGN) - 1)/(ALIGN)) * (ALIGN) )


#ifdef HOST_EMULATION
#include "stdlib.h"
#include <stdio.h>


//////////////////////////////////
// Compression helper functions //
//////////////////////////////////

/*
   secondaryTR : compression secondary TR
   symbolIn    : 8/16/32 bit symbol to compress
   symbolOut   : compressed symbol
   return      : length of compressed symbol in bits
*/
static uint8_t DmaUtilsAutoInc3d_compressElem
( CSL_UdmapSecTR * secondaryTR
, uint32_t         symbolIn
, uint64_t*        symbolOut
)
{
  uint32_t elem       = symbolIn;
  uint64_t compressed = 0;
  uint8_t  length     = 8; /* elements are 8-bit unless variable-k*/
  uint32_t temp       = elem;
  uint8_t  kVal       = ( (secondaryTR->data[0]) >> 8 ) & 0x07;  /*TODO add dynamic k-updating...*/
  uint8_t  bias       = ( (secondaryTR->data[0]) >> 8 ) & 0xFF; /*TODO CSL doesn't exist for compression fields...*/
  uint8_t  algorithm  = ( (secondaryTR->data[0])      ) & 0x0F;

  if ( algorithm != DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K )
  {
    temp = elem - bias;

    /*prevent underflowing*/
    temp &= (1 << (length)) - 1;
  }

  

  switch( algorithm ) /*TODO CSL doesn't exist for compression fields...*/
  {
    case DMAUTILSAUTOINC3D_CMPRS_ZERO : /*zero algorithm*/
    {
      /*python code (no bias)
        compressed = 0 ;
        if ( num != 0 ) :
          compressed = 1 ;
          #invert the 8 bit number
          for i in range (0,8) :
            if ( num & ( 1 << i ) ) :
              compressed |= ( 1 << (8 - i) ) ;
      */
      
      if ( temp != 0 )
      {
        compressed = 1;
        /*invert the 8 bit number*/
        for ( uint16_t i = 0; i < length; ++i )
        {
          if ( temp & ( 1 << i ) )
          {
            compressed |= ( 1 << (length - i) );
          }
        }
        length = length + 1;
      }
      else
      {
        compressed = 0;
        length     = 1;
      }
      break;
    }
    case DMAUTILSAUTOINC3D_CMPRS_UEG : /*unsigned exponential golomb*/
    {
      /*python code (no bias)
        compressed = 0 ;
        j = num + 1 ;
        z = -1 ;
        #invert j
        inverted = 0 ;
        for k in range(0,9) :
          if ( (j & (1<<k) ) ) : 
            z = k;
        for k in range(0,z+1) :
          if ( j & (1<<k) ) :
            inverted |= 1<<(z-k) ;
        compressed = inverted << z;
      */
      temp++;

      uint8_t lengthDiv2 = -1;
      /*Find how many zeroes to append*/
      for ( uint16_t i = 0; i < length+1; ++i )
      {
        if ( (temp & (1<<i) ) )
        {
          lengthDiv2 = i;
        }
      }
      /*invert temp*/
      uint32_t inverted = 0;
      for ( uint16_t i = 0; i < lengthDiv2+2; ++i )
      {
        if ( temp & (1<<i) )
          inverted |= 1<<(lengthDiv2-i);
      }
      compressed = inverted << lengthDiv2;
      length = ( lengthDiv2 << 1 ) + 1;
      break;
    }
    case DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K : /*signed exponential golomb*/
      return 0; /*TODO: variable K not yet supported...*/
         case DMAUTILSAUTOINC3D_CMPRS_SEG :
    {
      /*python code (no bias)
        compressed = 0 ;
        #need to sign extend 1 bit
        if ( num & ( 1 << (elsize-1) ) ) :
          temp = num | ( 1 << elsize ) ;
        else :
          temp = num ;
        
        #add in variable-k
        temp += (1 << my_k) - 1
        
        #mask out top bit in case of rollover
        temp &= ( (1 << elsize+1) - 1 )
        
        #alternate positive negative
        if ( temp < ( 1 << elsize ) ) :
          j = ( temp << 1 ) + 1 ;
        else :
          j = ( ( 1<<(elsize+1) ) - temp ) << 1 ;
        
        #invert j
        inverted =  0 ;
        z        = -1 ;
        for k in range(0,elsize+1) :
          if ( (j & (1<<k) ) ) : 
            z = k;
        for k in range(0,z+1) :
          if ( j & (1<<k) ) :
            inverted |= 1<<(z-k) ;
        compressed = inverted << z;
      */

      /* sign extend by 1 bit*/
      if ( temp & ( 1 << (length-1) ) )
      {
        temp |= ( 1 << length );
      }

      if ( algorithm == DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K )
      {
        temp   = elem + (1 << kVal) - 1;
        temp  &= ((1 << (length+1)) - 1); /*mask out top bit in case of rollover*/
      }

      /*alternate output mapping between positive and negative inputs*/
      if ( temp & ( 1 << length ) )
        temp = ( ( 1<<(length+1) ) - temp ) << 1;
      else
        temp = ( temp << 1 ) + 1;

      /*Find how many zeroes to append*/
      uint8_t lengthDiv2 = -1 ;
      for ( uint16_t i = 0; i < length+1; ++i )
      {
        if ( (temp & (1<<i) ) )
        {
          lengthDiv2 = i;
        }
      }

      /*invert temp*/
      uint64_t inverted = 0;
      for ( uint16_t i = 0; i < lengthDiv2+1; ++i )
      {
        if ( temp & (1<<i) )
          inverted |= 1<<(lengthDiv2-i);
      }
      compressed = inverted << lengthDiv2;
      length = ( lengthDiv2 << 1 ) + 1;
      break;
    }
    default:
    {
      break;
    }
  }
  *symbolOut = compressed;
  return length;
}
/*secondaryTR : compression secondary TR
 symbolIn    : next 64-bits of compressed data
 symbolOut   : uncompressed symbol
 return      : length of compressed symbol
*/
static uint8_t DmaUtilsAutoInc3d_decompressElem ( CSL_UdmapSecTR * secondaryTR, 
                                                       uint64_t           symbolIn, 
                                                       uint32_t*          symbolOut)
{
  uint64_t elem         = symbolIn;
  uint32_t uncompressed = 0;
  uint8_t  length       = 8; /*elements are 8-bit unless variable-k*/
  uint8_t  elsize       = length;
  uint64_t temp         = elem;
  uint8_t  kVal       = ( (secondaryTR->data[0]) >> 8 ) & 0x07;  /*TODO add dynamic k-updating...*/
  uint8_t  bias       = ( (secondaryTR->data[0]) >> 8 ) & 0xFF; /*TODO CSL doesn't exist for compression fields...*/
  uint8_t  algorithm  = ( (secondaryTR->data[0])      ) & 0x0F;

  switch( algorithm ) /*TODO CSL doesn't exist for compression fields...*/
  {
    case DMAUTILSAUTOINC3D_CMPRS_ZERO : /*zero algorithm*/
    {
      /*python code
        uncompressed = 0 ;
        if ( compressed & 1 ) :
          #invert the remaining 8 bit number
          for i in range (1,9) :
            if ( compressed & ( 1 << i ) ) :
              uncompressed |= ( 1 << (8 - i) ) ;
      */
      if ( temp & 1 )
      {
        length = elsize + 1;
        for ( uint8_t i = 1; i < length; i++ )
        {
          if ( temp & (1<<i) )
            uncompressed |= ( 1 << (8-i) );
        }
      }
      else
        length = 1;

      break;
    }
    case DMAUTILSAUTOINC3D_CMPRS_UEG : /*unsigned exponential golomb*/
    {
      /*python code
        uncompressed = 0 ;
        z = -1 ;
        for k in range(0,9) :
          if ( compressed & (1<<k) ) :
            z = k ;
            break ;
        length = 2*z + 1 ;
        for k in range(0,z+1) :
          if ( compressed & (1<<(length-k-1)) ) :
            uncompressed |= (1<<k) ;
        uncompressed -= 1 ;
      */
      int zeros = -1;
      for ( uint8_t i = 0; i <= elsize; i++ )
      {
        if ( temp & (1<<i) )
        {
          zeros = i;
          break;
        }
      }

      if ( zeros == -1 )
        return 0; /*TODO add status*/

      length = (zeros<<1) + 1;

      for ( uint8_t i = 0; i < zeros+1; i++ )
      {
        if ( temp & (1<<(length-i-1)) )
          uncompressed |= (1<<i);
      }
      uncompressed--;

      break;
    }
    case DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K : /*signed exponential golomb*/
    case DMAUTILSAUTOINC3D_CMPRS_SEG :
    {
      /*uncompressed = 0 ;
        z = -1 ;
        for k in range(0,elsize+1) :
          if ( compressed & (1<<k) ) :
            z = k ;
            break ;
        length = 2*z + 1 ;
        for k in range(0,z+1) :
          if ( compressed & (1<<(length-k-1)) ) :
            uncompressed |= (1<<k) ;
        if ( uncompressed & 1 ) :
          uncompressed = ( uncompressed - 1 ) >> 1 ;
        else :
          uncompressed = ( 1 << (elsize+1) ) - ( uncompressed >> 1 ) ;
        
        #remove variable-k
        if ( uncompressed >= (1 << my_k) - 1 ) :
          uncompressed -= (1 << my_k) - 1
        else :
          uncompressed += (1 << elsize) - (1 << my_k) + 1
        
        #mask out top bit if set
        uncompressed &= (1<<elsize)-1
      */
      int zeros = -1;
      for ( uint8_t i = 0; i <= elsize; i++ )
      {
        if ( temp & (1<<i) )
        {
          zeros = i;
          break;
        }
      }

      if ( zeros == -1 )
        return 0; /*TODO add status*/

      length = (zeros<<1) + 1;

      for (uint8_t i = 0; i < zeros+1; i++ )
      {
        if ( temp & (1<<(length-i-1)) )
          uncompressed |= (1<<i);
      }

      if ( uncompressed & 1 )
        uncompressed = uncompressed >> 1;
      else
        uncompressed = ( 1 << (elsize+1) ) - ( uncompressed >> 1 );

      /*remove variable-k*/
      if ( algorithm == DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K )
      {
        if ( uncompressed >= (1 << kVal) - 1 )
          uncompressed -= (1 << kVal) - 1;
        else
          uncompressed += (1 << elsize) - (1 << kVal) + 1;
      }

      break;
    }
    default:
    {
      return 0; /*TODO add status*/
      break;
    }
  }

  if ( algorithm != DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K )
  {
    /*add bias back in*/
    uncompressed += bias;

    /*prevent overflow*/
    uncompressed &= (1<<elsize)-1;
  }

  *symbolOut = uncompressed;
  return length;
}

//////////////////////////////////////
// END Compression helper functions //
//////////////////////////////////////


void hostEmulation_updateTriggerCount(struct Udma_DrvObj * udmaDrvHandle,
                                                                              volatile uint64_t *pSwTrigReg)
{
  uint32_t i;
  CSL_DRU_t *druRegs = udmaDrvHandle->utcInfo[0].druRegs;
  uintptr_t origPtr = (uintptr_t)pSwTrigReg;
  uintptr_t currPtr;

  for ( i = 0; i < udmaDrvHandle->utcInfo[0].numCh; i++)
  {
    currPtr = (uintptr_t)&druRegs->CHRT[i].CHRT_SWTRIG;
    if ( currPtr == origPtr)
    {
      /* Use reserved space for tracking number of triggers submitted for a given channel */
      druRegs->CHRT[i].Resv_256[0]++;
      break;
    }
  }
}   
void hostEmulation_druChSubmitAtomicTr(CSL_DRU_t *pRegs,
                                           uint32_t chId,
                                           void *  vdata)
{
  //memset(pRegs, 0, sizeof(CSL_DRU_t));
  
  CSL_UdmapTR * tr = (CSL_UdmapTR *)vdata;
  CSL_UdmapTR * origTransferRecord  = (CSL_UdmapTR *)&pRegs->CHATOMIC[chId];
  CSL_UdmapTR * nextTransferRecord  = (CSL_UdmapTR *)&pRegs->CHATOMIC[chId].DEBUG[0];
  CSL_UdmapTR * nextTransferRecord1 = (CSL_UdmapTR *)&pRegs->CHATOMIC[chId].DEBUG[1];
  CSL_UdmapTR * nextTransferRecord2 = (CSL_UdmapTR *)&pRegs->CHATOMIC[chId].DEBUG[2];


  /* Use reserved space for tracking number of triggers submitted for a given channel */
  pRegs->CHRT[chId].Resv_256[0] = 0;

  *origTransferRecord  = *tr;
  *nextTransferRecord  = *tr;
  *nextTransferRecord1 = *tr;
  *nextTransferRecord2 = *tr;

  /*nextTransferRecord 0,1,2 need to track the CDB table address if in compression*/
  uint32_t DFMT  = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_DFMT);
  if ( DFMT == DMAUTILSAUTOINC3D_DFMT_COMP ) /*TODO CSL definitions for compression don't exist yet*/
  {
    uint64_t cdbPtr            = origTransferRecord->daddr + DMAUTILS_COMP_SECTR_PROG_SIZE;
    nextTransferRecord ->daddr = cdbPtr; /*compression doesn't need destination addr tracking*/
    nextTransferRecord1->daddr = cdbPtr;
    nextTransferRecord2->daddr = cdbPtr;
  }
  else if ( DFMT == DMAUTILSAUTOINC3D_DFMT_DECOMP ) /*TODO CSL definitions for decompression don't exist yet*/
  {
    CSL_UdmapSecTR* sectrPtr  = (CSL_UdmapSecTR *)  origTransferRecord->addr;
    int32_t cdbOffset         = (int32_t)(sectrPtr->data[4]);
    uint64_t cdbPtr           = origTransferRecord->addr + cdbOffset;
    nextTransferRecord ->addr = cdbPtr; /*decompression doesn't need source addr tracking*/
    nextTransferRecord1->addr = cdbPtr;
    nextTransferRecord2->addr = cdbPtr;
  }

    FILE *fp= fopen("/user/a0393878/Documents/TIDL/druMMRSpace.bin", "wb");
    fwrite(pRegs, sizeof(CSL_DRU_t), 1, fp);
    fclose(fp);
}


uint64_t hostEmulation_addressUpdate( uint64_t base, int32_t offset, uint64_t addrMask )
{
  uint64_t newAddr;

  newAddr = base + offset;

  if ( addrMask != 0 )
  {
    newAddr = ( base & addrMask ) | ( newAddr & ~addrMask );
  }

  return newAddr;
}

void hostEmulation_circMask( uint32_t cbk0, uint32_t cbk1, uint64_t * circMask0, uint64_t * circMask1  )
{
  uint32_t blockSize0 = cbk0 + 9U; /* power-of-2 of block size in bytes */
  uint32_t blockSize1 = cbk0 + cbk1 + 10U; /* power-of-2 of block size in bytes */

  if ( blockSize1 > 31U )
  {
    blockSize1 = 32U; /* clamp to 4GB maximum size */
  }
  *circMask0 = (~0ULL) << blockSize0;
  *circMask1 = (~0ULL) << blockSize1;
}

static void hostEmulation_triggerDMA(struct Udma_DrvObj * udmaDrvHandle)
{
  uint32_t chId;
  CSL_DRU_t * druRegs;
  CSL_UdmapCfg  * udmapRegs;
  CSL_ringacc_cfgRegs * ringAccCfgRegs;
  int32_t locSB_DIM1_SPEC = SB_DIM1_SPEC;

  druRegs         = udmaDrvHandle->utcInfo[0].druRegs;
  ringAccCfgRegs  = udmaDrvHandle->raRegs.pCfgRegs;
  udmapRegs       = &udmaDrvHandle->udmapRegs;
  #if CRASH_DEBUG_PRINTS
    FILE * fp;
    //fp= fopen("C:\\D\\tidlMismatchDebugDatFile.txt", "a+");
    fp= fopen("/user/a0393878/Documents/TIDL/c7x-mma-tidl/ti_dl/test/testvecs/config/tidl_models/caffe/mobilenet_v1_1mp_CompAEP/tidlMismatchDebugDatFile.txt", "a+");
  #endif
  for ( chId = 0; chId < 32; chId++)/*:TODO: Remove hard coded value of 32*/
  {
    if ( (druRegs->CHRT[chId].CHRT_SWTRIG & CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER0_MASK) == 1U)
    {
      uint8_t *srcPtr;
      uint8_t *dstPtr;
      uint8_t *cdbPtr;
      CSL_UdmapSecTR * sectrPtr;
      uint8_t  eobSize;
      uint16_t *srcPtr1;
      uint16_t *dstPtr1;
      uint32_t triggerType;
      uint8_t  cmprsType;
      uint32_t circDir;
      uint32_t icnt0, sbIcnt0, sbIcnt1;
      int32_t  sbDim1, sDim0, dDim0;
      uint32_t CBK0, CBK1;
      uint32_t AM0, AM1, AM2, AM3, sbAM0, sbAM1;
      uint64_t srcAM0, srcAM1, srcAM2, srcAM3;
      uint64_t dstAM0, dstAM1, dstAM2, dstAM3;
      
      uint64_t sbSrcAM0, sbSrcAM1;
      uint64_t sbDstAM0, sbDstAM1;

      uint64_t circMask0;
      uint64_t circMask1;
      uint32_t AMODE, DFMT, ELYPE;
      uint32_t loopCnt1Reset, loopCnt2Reset;
      uint8_t * interimBuffer = NULL;
      uint32_t srcLoopExitCondition = 0;
      uint32_t dstLoopExitCondition = 0;
      uint32_t totalSrcCnt, totalDstCnt, totalSBCnt;
      int32_t nextSBStartOffset = 0; /*Stores offset of the SB compressed bitstream form the base of the compressed bitsteram. Used in DFMT == 5*/
      /* Clear the sw trigger so that next trigger can happen */


      druRegs->CHRT[chId].Resv_256[0]--;
      /* Use reserved space for tracking number of triggers submitted for a given channel */
      if ( druRegs->CHRT[chId].Resv_256[0] == 0 )
      {
        druRegs->CHRT[chId].CHRT_SWTRIG  = druRegs->CHRT[chId].CHRT_SWTRIG & (uint64_t)(~CSL_DRU_CHRT_SWTRIG_GLOBAL_TRIGGER0_MASK);
      }

      CSL_UdmapTR * origTransferRecord  = (CSL_UdmapTR *)(void *) &druRegs->CHATOMIC[chId];
      CSL_UdmapTR * nextTransferRecord  = (CSL_UdmapTR *)(void *) &druRegs->CHATOMIC[chId].DEBUG[0];
      CSL_UdmapTR * nextTransferRecord1 = (CSL_UdmapTR *)(void *) &druRegs->CHATOMIC[chId].DEBUG[1];
      CSL_UdmapTR * nextTransferRecord2 = (CSL_UdmapTR *)(void *) &druRegs->CHATOMIC[chId].DEBUG[2];

      triggerType = CSL_FEXT(origTransferRecord->flags, UDMAP_TR_FLAGS_TRIGGER0_TYPE);
      AMODE = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_AMODE);
      DFMT  = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_DFMT );

      if ( AMODE == CSL_UDMAP_TR_FMTFLAGS_AMODE_CIRCULAR)
      {
        circDir        = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_DIR);
        CBK0         = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK0);
        CBK1         = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK1);
        AM0           = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM0);
        AM1           = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM1);
        AM2           = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM2);
        AM3           = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM3);
        hostEmulation_circMask(CBK0, CBK1, &circMask0, &circMask1);
      }
      else
      {
        /* Linear Addressing */
        circMask0 = (~0ULL);
        circMask1 = (~0ULL);
        AM0 = 0;
        AM1 = 0;
        AM2 = 0;
        AM3 = 0;
        circDir = 0;
      }
      /*Decoding secondary TR*/
      if ( DFMT == DMAUTILSAUTOINC3D_DFMT_COMP ) /*TODO compression CSL definitions don't exist yet...*/
      {
        sectrPtr   = (CSL_UdmapSecTR *)(origTransferRecord->daddr); 
        //cdbPtr     = (uint8_t        *)( nextTransferRecord->daddr);    /*Pointer to the CDB table*/
        totalSBCnt = (sectrPtr->data[1] & 0xFFFF) * ((sectrPtr->data[1] >> 16) & 0xFFFF);
        sDim0      = (int32_t)(sectrPtr->data[2]);
        dDim0      = (int32_t)(sectrPtr->data[3]);
        
        if(locSB_DIM1_SPEC == DMAUTILSAUTOINC3D_DRUSPEC_106MOD)
        {
          sbDim1     = (int32_t)((sectrPtr->flags & 0xFFFFFFF0)  >> 4);
        } 
        else
        {
          sbDim1     = (int32_t)(sectrPtr->flags & 0xFFFFFFF0);
        }
  
        cmprsType  = sectrPtr->data[0] & 0xF;
        sbAM0      = (sectrPtr->data[0] >> 4) & 0x3;
        sbAM1      = (sectrPtr->data[0] >> 6) & 0x3;
        
        switch( cmprsType )
        {
          case DMAUTILSAUTOINC3D_CMPRS_ZERO :
          {
            eobSize = 1;
            break;
          }
          case DMAUTILSAUTOINC3D_CMPRS_UEG :
          case DMAUTILSAUTOINC3D_CMPRS_SEG :
          {
            eobSize = 9;
            break;
          }
          case DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K :
          {
            eobSize = 9; /*TODO eobSize = elsize + 1 (9,13,17)*/
            break;
          }
          default:
          {
            break;
          }
        }
      }
      else if ( DFMT == DMAUTILSAUTOINC3D_DFMT_DECOMP ) /*TODO decompression CSL definition doesn't exist yet...*/
      {
        sectrPtr   = (CSL_UdmapSecTR *)origTransferRecord->addr;
        totalSBCnt = (sectrPtr->data[1] & 0xFFFF) * ((sectrPtr->data[1] >> 16) & 0xFFFF);

        if(locSB_DIM1_SPEC == DMAUTILSAUTOINC3D_DRUSPEC_106MOD)
        {
          sbDim1     = (int32_t)((sectrPtr->flags & 0xFFFFFFF0)  >> 4);
        } 
        else
        {
          sbDim1     = (int32_t)(sectrPtr->flags & 0xFFFFFFF0);
        }
        sDim0      = (int32_t)(sectrPtr->data[2]);
        dDim0      = (int32_t)(sectrPtr->data[3]);
        cmprsType  = sectrPtr->data[0] & 0xF;
        sbAM0      = (sectrPtr->data[0] >> 4) & 0x3;
        sbAM1      = (sectrPtr->data[0] >> 6) & 0x3;

        switch( cmprsType )
        {
          case DMAUTILSAUTOINC3D_CMPRS_ZERO :
          case DMAUTILSAUTOINC3D_CMPRS_UEG :
          case DMAUTILSAUTOINC3D_CMPRS_SEG :
          {
            eobSize = 9; /*EOB for zero compression is 1 bit to write and 9 to read*/
            break;
          }
          case DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K :
          {
            eobSize = 9; /*TODO eobSize = elsize + 1*/
            break;
          }
          default:
          {
            break;
          }
        }
      }

      /*Circularity masks and flags setup*/
      if ( circDir == CSL_UDMAP_TR_FMTFLAGS_DIR_DST_USES_AMODE)
      {
        dstAM0 = (AM0 == 0 ) ? 0 : ( (AM0 == 1) ? circMask0 : circMask1  );/* Circular update */
        srcAM0 = 0;/* Linear Update */

        dstAM1 = (AM1 == 0 ) ? 0 : ( (AM1 == 1) ? circMask0 : circMask1  );/* Circular update */
        srcAM1 = 0;/* Linear Update */

        dstAM2 = (AM2 == 0 ) ? 0 : ( (AM2 == 1) ? circMask0 : circMask1  );/* Circular update */
        srcAM2 = 0;/* Linear Update */

        dstAM3 = (AM3 == 0 ) ? 0 : ( (AM3 == 1) ? circMask0 : circMask1  );/* Circular update */
        srcAM3 = 0;/* Linear Update */

        if ( DFMT == DMAUTILSAUTOINC3D_DFMT_DECOMP) /* TODO decompression CSL definition doesn't exist yet...*/
        {
          sbDstAM0 = (sbAM0 == 0 ) ? 0 : ( (sbAM0 == 1) ? circMask0 : circMask1  );/* Circular update */
          sbSrcAM0 = 0; /* Linear Update */
  
          sbDstAM1 = (sbAM1 == 0 ) ? 0 : ( (sbAM1 == 1) ? circMask0 : circMask1  );/* Circular update */
          sbSrcAM1 = 0; /* Linear Update */
        }
        else 
        {
          sbDstAM0 = 0;
          sbSrcAM0 = 0;
          sbDstAM1 = 0;
          sbSrcAM1 = 0;
        }
      }
      else
      {
        dstAM0 = 0;/* Linear Update */
        srcAM0 = (AM0 == 0 ) ? 0 : ( (AM0 == 1) ? circMask0 : circMask1  );

        dstAM1 = 0;/* Linear Update */
        srcAM1 = (AM1 == 0 ) ? 0 : ( (AM1 == 1) ? circMask0 : circMask1  );

        dstAM2 = 0;/* Linear Update */
        srcAM2 = (AM2 == 0 ) ? 0 : ( (AM2 == 1) ? circMask0 : circMask1  );

        dstAM3 = 0;/* Linear Update */
        srcAM3 = (AM3 == 0 ) ? 0 : ( (AM3 == 1) ? circMask0 : circMask1  );

        
        if ( DFMT == DMAUTILSAUTOINC3D_DFMT_COMP) /* TODO decompression CSL definition doesn't exist yet...*/
        {
          sbDstAM0 = 0; /* Linear Update */ 
          sbSrcAM0 = (sbAM0 == 0 ) ? 0 : ( (sbAM0 == 1) ? circMask0 : circMask1  );/* Circular update */
  
          sbDstAM1 = 0; /* Linear Update */  
          sbSrcAM1 = (sbAM1 == 0 ) ? 0 : ( (sbAM1 == 1) ? circMask0 : circMask1  );/* Circular update */
        }
        else 
        {
          sbDstAM0 = 0;
          sbSrcAM0 = 0;
          sbDstAM1 = 0;
          sbSrcAM1 = 0;
        }
      }

      loopCnt1Reset = 0;    /*These are set as per source ICNTx*/
      loopCnt2Reset = 0;
      /*Set up interim buffers for non-compression/decompression flow. Direct copy for  compression/decompression flow.
         if we are compressing/decompressing then we don't need an interim buffer. Just write compressed data to the destination.
         Setup of dstPtr moved inside the while loop
      */
      switch ( DFMT )
      {
        case DMAUTILSAUTOINC3D_DFMT_COMP : /*compression*/
        {
          break;
        }
        case DMAUTILSAUTOINC3D_DFMT_DECOMP : /*decompression*/
        {
          break;
        }
        default:
        {
          /* allocate worst case, actual buffer used will depend on trugerType */
          ELYPE = CSL_FEXT(origTransferRecord->fmtflags, UDMAP_TR_FMTFLAGS_ELYPE);
          #if USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
            uint32_t interimBufSize = (origTransferRecord->icnt0 * origTransferRecord->icnt1 * origTransferRecord->icnt2 *
                                        origTransferRecord->icnt3);
            if ( ELYPE == CSL_UDMAP_TR_FMTFLAGS_ELYPE_2_1)
              interimBufSize *= 2; /*As icnt0 is in elements in case of 16 bit to 8 bit conversion*/

            interimBuffer = (uint8_t *)malloc(interimBufSize);
            dstPtr = interimBuffer;
            dstPtr1 = (uint16_t *)interimBuffer;
          #endif
          break;
        }
      }

      totalSrcCnt = nextTransferRecord->icnt0 * nextTransferRecord->icnt1 * nextTransferRecord->icnt2 * nextTransferRecord->icnt3;
      totalDstCnt = nextTransferRecord->dicnt0 * nextTransferRecord->dicnt1 * nextTransferRecord->dicnt2 * nextTransferRecord->dicnt3;

      srcLoopExitCondition  = ( totalSrcCnt < totalDstCnt )? totalSrcCnt : totalDstCnt;
      dstLoopExitCondition  = srcLoopExitCondition;
      /* Set the minimum value of icnt3 for both src and dst as TR completes whenever anyone of them  is exauhsted */
      /* Transfer source data to a intermediate linear buffer */

      while (1)
      {
        uint8_t* sbCdbPtr;  /*stores the pointer to cdb table entry corresponding to a SB being encoded or decoded.*/ 
        uint8_t* sbAddr;    /*stores the pointer to to a uncomressed SB data being encoded or decoded. */
        if ( DFMT == DMAUTILSAUTOINC3D_DFMT_COMP )    /*TODO decompression CSL definitions don't exist yet...*/
        {
          srcPtr = (uint8_t *)nextTransferRecord->addr;
          cdbPtr = (uint8_t *)nextTransferRecord->daddr;
          dstPtr = (uint8_t *)hostEmulation_addressUpdate(sectrPtr->addr , ((int32_t *)cdbPtr)[1], 0);
          
          sbCdbPtr    = cdbPtr;
          sbAddr      = srcPtr;    /*Stores the base pointer for a SB row*/
        }
        else if ( DFMT == DMAUTILSAUTOINC3D_DFMT_DECOMP )  /*TODO decompression CSL definitions don't exist yet...*/
        {
          cdbPtr = (uint8_t *)  nextTransferRecord->addr;
          sbCdbPtr    = cdbPtr;
          dstPtr = (uint8_t *)  nextTransferRecord->daddr;
          sbAddr = dstPtr; 
        }
        else
        {
          srcPtr = (uint8_t *)nextTransferRecord->addr;
          if ( ELYPE == CSL_UDMAP_TR_FMTFLAGS_ELYPE_2_1)
            srcPtr1 = (uint16_t *)srcPtr;
          #if !USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
            dstPtr = (uint8_t *)nextTransferRecord->daddr;
            //if ( ELYPE == CSL_UDMAP_TR_FMTFLAGS_ELYPE_2_1)
            //  dstPtr1 = (uint16_t *)dstPtr;
          #endif
        }
        
        for (icnt0 = 0; icnt0 < nextTransferRecord->icnt0; icnt0++)
        {
          if ( DFMT == DMAUTILSAUTOINC3D_DFMT_COMP )/* TODO compression CSL definition doesn't exist yet...*/
          {
            uint64_t cmprs       = 0;
            uint8_t  len         = 0;
            uint16_t cdbCnt      = 0;
            uint8_t* sb1Addr     = sbAddr;    /*Stores the base pointer for a SB row being encoded/decoded*/
            int32_t  startOffset = (int32_t)((uint64_t)dstPtr - sectrPtr->addr);
            memset(dstPtr, 0, 16);
            for (sbIcnt1 = 0; sbIcnt1 < ((sectrPtr->data[1] >> 16) & 0xFFFF); sbIcnt1++)
            {
              srcPtr = sb1Addr;
              for (sbIcnt0 = 0; sbIcnt0 < 16 * ((sectrPtr->data[1] & 0xFFFF)); sbIcnt0++)
              {
                uint8_t newLen = DmaUtilsAutoInc3d_compressElem( sectrPtr , (uint32_t)(*srcPtr) , &cmprs );
                /*merge compressed data into output*/
                if ( len + newLen + eobSize > 128 ) /*This won't fit in the current CDB*/
                {
                  /*eob only has to be written for zero compression. Otherwise it's zero*/
                  if ( cmprsType == DMAUTILSAUTOINC3D_CMPRS_ZERO )
                  {
                    *(dstPtr + (len >> 3)) |= ( 1 << (len & 0x7) );
                  }
                  dstPtr += 16;
                  /*zero out next CDB for writing    // Does this happen for CDB in HWA?*/
                  memset(dstPtr, 0, 16);
                  len = 0;
                  cdbCnt++;
                }
                /*align compressed data starting bit with the output data*/
                cmprs <<=  len & 0x7;
                
                /*deal with compressed data endianness agnostically*/
                uint8_t touchedBytes = (newLen + (len & 0x7)) >> 3;
                for ( uint8_t i = 0; i <= touchedBytes; i++ )
                {
                  uint8_t off  = (len >> 3) + i;
                  uint8_t elem = (cmprs >> (i << 3)) & 0xFF;
                  *(dstPtr + off) |= elem;
                }
                #if CRASH_DEBUG_PRINTS
                if(fp != NULL)
                {
                  fprintf(fp, "C: %d %d %d %d %d %d- %d\n", 
                                 sbIcnt0, sbIcnt1, icnt0,  
                                 origTransferRecord->icnt1 - nextTransferRecord->icnt1, 
                                 origTransferRecord->dicnt2 - nextTransferRecord->dicnt2, 
                                 origTransferRecord->dicnt3 - nextTransferRecord->dicnt3, 
                                 (uint32_t)(*srcPtr));
                }
                #endif
                len   += newLen;
                srcPtr = (uint8_t*)hostEmulation_addressUpdate((uint64_t)srcPtr , 1 , sbSrcAM0);
              }
              sb1Addr = (uint8_t*)hostEmulation_addressUpdate((uint64_t)sb1Addr , sbDim1 , sbSrcAM1);  
            }
            /*
              finish last CDB in superblock
              eob only has to be written for zero compression. Otherwise it's zero
            */
            if ( cmprsType == DMAUTILSAUTOINC3D_CMPRS_ZERO )
            {
              *(dstPtr + (len >> 3)) |= ( 1 << (len & 0x7) );
            }
            dstPtr += 16;
            /*zero out next CDB for writing*/
            memset(dstPtr, 0, 16);
            len = 0;
            cdbCnt++;

            /*Write CDB info to table*/
            ( (uint32_t*)sbCdbPtr )[0] = cdbCnt;
            ( (int32_t *)sbCdbPtr )[1] = startOffset;
            nextSBStartOffset = startOffset + (cdbCnt * 16);
            sbCdbPtr += dDim0;
            sbAddr  = (uint8_t*)hostEmulation_addressUpdate((uint64_t)sbAddr, sDim0, srcAM0);
          }
          else if ( DFMT == DMAUTILSAUTOINC3D_DFMT_DECOMP ) /*TODO decompression CSL definitions don't exist yet...*/
          {
            uint64_t cmprs         = 0;
            uint32_t decmprs       = 0;
            uint8_t  cdbLen        = 128;
            uint16_t cdbCnt        = 0;
            uint8_t  maxSymbolSize = 17; /*default for UEG/SEG*/
            uint8_t* sb1Addr       = sbAddr;
            
            switch( cmprsType )
            {
              case DMAUTILSAUTOINC3D_CMPRS_ZERO :
              {
                maxSymbolSize = 16; /*actual = 9*/
                break;
              }
              case DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K :
                maxSymbolSize = 17; /*TODO maxSymbolSize = (elemsize * 2) + 1*/
              case DMAUTILSAUTOINC3D_CMPRS_UEG :
              case DMAUTILSAUTOINC3D_CMPRS_SEG :
              {
                maxSymbolSize = (maxSymbolSize + 7) & ~0x7; /*round up to nearest multiple of 8*/
                break;
              }
              default:
              {
                break;
              }
            }
            /*The actual max size is always 1 more than a multiple of 8, so when we drop up to 7 bits during alignment we will still have enough data*/

            /*get start of superblock*/
            srcPtr = (uint8_t*)hostEmulation_addressUpdate(sectrPtr->addr, ((int32_t*)sbCdbPtr )[1], 0); /*srcAM0 ==> 0?*/
            
            for (sbIcnt1 = 0; sbIcnt1 < ((sectrPtr->data[1] >> 16) & 0xFFFF); sbIcnt1++)
            {
              dstPtr = sb1Addr;
              for (sbIcnt0 = 0; sbIcnt0 < 16*((sectrPtr->data[1] & 0xFFFF)); )
              {
                
                
                /*get at least one symbol of data in this CDB and be endianess agnostic*/
                cmprs = 0;
                uint8_t len = (cdbLen > maxSymbolSize) ? maxSymbolSize  : cdbLen;
                len         = ( len & 0x7 )            ? (len >> 3) + 1 : (len >> 3);
                uint8_t off = (128 - cdbLen) >> 3;

                /*printf("maxSymbolSize = %d : cdbLen = %d : len = %d : off = %d :\n",maxSymbolSize,cdbLen,len,off);*/
                for ( uint8_t i = 0; i < len; i++ )
                {
                  cmprs |= *(srcPtr + off + i) << (i << 3);
                }
                /*align data*/
                if (cdbLen & 0x7)
                {
                  cmprs = cmprs >> (8 - (cdbLen & 0x7));
                }

                /*check for eob symbol*/
                bool eobFound = false;
                switch( cmprsType )
                {
                  case DMAUTILSAUTOINC3D_CMPRS_ZERO :
                  {
                    eobFound = (cmprs & ((1<<eobSize)-1)) == 1;
                    break;
                  }
                  case DMAUTILSAUTOINC3D_CMPRS_UEG :
                  case DMAUTILSAUTOINC3D_CMPRS_SEG :
                  case DMAUTILSAUTOINC3D_CMPRS_SEG_VAR_K : /*TODO varK symbol is (element bits + 1) consecutive zeros*/
                  {
                    eobFound = (cmprs & ((1<<eobSize)-1)) == 0;
                    break;
                  }
                  default :
                  {
                    break;
                  }
                }

                if (eobFound)
                {
                  /*printf("EOB found!\n");*/
                  srcPtr += 16; /*move to next CDB*/
                  cdbLen  = 128;
                }
                else
                {
                  cdbLen -= DmaUtilsAutoInc3d_decompressElem( sectrPtr , cmprs , &decmprs );
                  /*TODO varK can have non-1B elements...*/
                  *dstPtr = decmprs & 0xFF;
                  #if CRASH_DEBUG_PRINTS
                    if (fp!= NULL)
                    {
                      fprintf(fp, "D: %d %d %d %d %d %d- %d\n", 
                                      sbIcnt0, sbIcnt1, icnt0,
                                      origTransferRecord->icnt1 - nextTransferRecord->icnt1, 
                                      origTransferRecord->dicnt2 - nextTransferRecord->dicnt2, 
                                      origTransferRecord->dicnt3 - nextTransferRecord->dicnt3, 
                                      (uint32_t)(*dstPtr));
                    }
                  #endif

                  dstPtr = (uint8_t *)hostEmulation_addressUpdate((uint64_t)dstPtr , 1 , sbDstAM0);
                  sbIcnt0++; /*only move on if we decompressed an actual element*/
                }
              }
              
              sb1Addr = (uint8_t *)hostEmulation_addressUpdate((uint64_t)sb1Addr , sbDim1 , sbDstAM1);
            }

            sbAddr  = (uint8_t *)hostEmulation_addressUpdate((uint64_t)sbAddr , dDim0 , dstAM0); /*Move outside?*/
            sbCdbPtr += sDim0;
          }
          else
          {
            
            if( ELYPE == CSL_UDMAP_TR_FMTFLAGS_ELYPE_2_1)
            {
              #if USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
                *dstPtr1 = *srcPtr1;
                dstPtr1++;
              #else
                *dstPtr = (uint8_t)*srcPtr1;
                dstPtr = (uint8_t *)hostEmulation_addressUpdate((uint64_t)dstPtr, 1, dstAM0);
              #endif 
              srcPtr1 = (uint16_t *)hostEmulation_addressUpdate((uint64_t)srcPtr1, 2, srcAM0);
            }
            else
            {
              *dstPtr = *srcPtr;
              srcPtr = (uint8_t *)hostEmulation_addressUpdate((uint64_t)srcPtr, 1, srcAM0);
              #if USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
                dstPtr++;
              #else
                dstPtr = (uint8_t *)hostEmulation_addressUpdate((uint64_t)dstPtr, 1, dstAM0);
              #endif
            }
          }
        }
        nextTransferRecord->icnt1--;
        if( DFMT != DMAUTILSAUTOINC3D_DFMT_COMP && DFMT != DMAUTILSAUTOINC3D_DFMT_DECOMP)
        {
          #if !USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
            nextTransferRecord->dicnt1--;
          #endif
        }
        else
        {
          nextTransferRecord->dicnt1--;
        }
        
        switch( DFMT )
        {
          case DMAUTILSAUTOINC3D_DFMT_COMP : /*compression*/
          { 
            /*update CDB table address*/
            nextTransferRecord->daddr  = hostEmulation_addressUpdate(nextTransferRecord->daddr , nextTransferRecord->ddim1, 0);
            /*move source pointer*/
            nextTransferRecord->addr   = hostEmulation_addressUpdate(nextTransferRecord->addr  , nextTransferRecord->dim1,   srcAM1);
            break;
          }
          case DMAUTILSAUTOINC3D_DFMT_DECOMP : /*decompression*/
          { 
            /*update CDB table address*/
            nextTransferRecord->addr   = hostEmulation_addressUpdate(nextTransferRecord->addr  , nextTransferRecord->dim1, 0);
            /*move destination pointer*/
            nextTransferRecord->daddr  = hostEmulation_addressUpdate(nextTransferRecord->daddr , nextTransferRecord->ddim1,   dstAM1);
            break;
          }
          default :
          {
            nextTransferRecord->addr   = hostEmulation_addressUpdate(nextTransferRecord->addr  , nextTransferRecord->dim1,   srcAM1);
            #if !USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
            	nextTransferRecord->daddr   = hostEmulation_addressUpdate(nextTransferRecord->daddr  , nextTransferRecord->ddim1,   dstAM1);
            #endif
            break;
          }
        }
        /*For compression/decompression type 9 transfer currently we assume that icnt0 = dicnt0 and icnt1 = dicnt1*/ 
        
        if ( nextTransferRecord->icnt1 == 0)
        {
          loopCnt1Reset = 1;
          nextTransferRecord->icnt2--;
          nextTransferRecord->icnt1 = origTransferRecord->icnt1;
		      if( DFMT != DMAUTILSAUTOINC3D_DFMT_COMP && DFMT != DMAUTILSAUTOINC3D_DFMT_DECOMP)
          {
         	 #if !USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
            	nextTransferRecord->dicnt2--;
				      nextTransferRecord->dicnt1 = origTransferRecord->dicnt1;
          	 #endif
          }
          else
          {
          	nextTransferRecord->dicnt2--;
			      nextTransferRecord->dicnt1 = origTransferRecord->dicnt1;
          }
		      switch( DFMT )
          {
            case DMAUTILSAUTOINC3D_DFMT_COMP : 
            { 
              /*update CDB table address*/
              nextTransferRecord->daddr  = hostEmulation_addressUpdate(nextTransferRecord1->daddr , nextTransferRecord->ddim2, 0);
              nextTransferRecord1->daddr = nextTransferRecord->daddr;
              /*move source pointer*/
              nextTransferRecord->addr   = hostEmulation_addressUpdate(nextTransferRecord1->addr  , nextTransferRecord->dim2,   srcAM2);
              nextTransferRecord1->addr  = nextTransferRecord->addr;
              break;
            }
            case DMAUTILSAUTOINC3D_DFMT_DECOMP : /*decompression*/
            { 
              /*update CDB table address*/
              nextTransferRecord->addr   = hostEmulation_addressUpdate(nextTransferRecord1->addr  , nextTransferRecord->dim2, 0);
              nextTransferRecord1->addr  = nextTransferRecord->addr;
              /*move destination pointer*/
              nextTransferRecord->daddr  = hostEmulation_addressUpdate(nextTransferRecord1->daddr , nextTransferRecord->ddim2,   dstAM2);
              nextTransferRecord1->daddr = nextTransferRecord->daddr;
              break;
            }
            default :
            {
              nextTransferRecord->addr   = hostEmulation_addressUpdate(nextTransferRecord1->addr  , nextTransferRecord->dim2,   srcAM2);
              nextTransferRecord1->addr  = nextTransferRecord->addr;
              #if !USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
                nextTransferRecord->daddr  = hostEmulation_addressUpdate(nextTransferRecord1->daddr , nextTransferRecord->ddim2,   dstAM2);
                nextTransferRecord1->daddr = nextTransferRecord->daddr;
              #endif
              break;
            }
          }
        }
          
        if ( nextTransferRecord->icnt2 == 0)
        {
          loopCnt2Reset= 1;
          nextTransferRecord->icnt3--;
          nextTransferRecord->icnt2 = origTransferRecord->icnt2;

          switch( DFMT )
          {
            case DMAUTILSAUTOINC3D_DFMT_COMP : /*compression*/
            { 
              /*update CDB table address*/
              nextTransferRecord->addr   = hostEmulation_addressUpdate(nextTransferRecord2->addr  , nextTransferRecord->dim3,   srcAM3);
              nextTransferRecord1->addr  = nextTransferRecord->addr;
              nextTransferRecord2->addr  = nextTransferRecord->addr;
              break;
            }
            case DMAUTILSAUTOINC3D_DFMT_DECOMP : /*decompression*/
            { 
              /*update CDB table address*/
              nextTransferRecord->addr   = hostEmulation_addressUpdate(nextTransferRecord2->addr  , nextTransferRecord->dim3, 0);
              nextTransferRecord1->addr  = nextTransferRecord->addr;
              nextTransferRecord2->addr  = nextTransferRecord->addr;
              break;
            }
            default :
            {
              nextTransferRecord->addr   = hostEmulation_addressUpdate(nextTransferRecord2->addr  , nextTransferRecord->dim3,   srcAM3);  
              nextTransferRecord1->addr  = nextTransferRecord->addr;
              nextTransferRecord2->addr  = nextTransferRecord->addr;
              break;
            }
          }
        }
        
        if ( nextTransferRecord->dicnt2 == 0)
        {
          
		      if( DFMT != DMAUTILSAUTOINC3D_DFMT_COMP && DFMT != DMAUTILSAUTOINC3D_DFMT_DECOMP)
          {
         	  #if !USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
			        nextTransferRecord->dicnt3--;
              nextTransferRecord->dicnt2 = origTransferRecord->dicnt2;
          	#endif
          }
          else
          {
            nextTransferRecord->dicnt3--;
            nextTransferRecord->dicnt2 = origTransferRecord->dicnt2;
          }
          switch( DFMT )
          {
            case DMAUTILSAUTOINC3D_DFMT_COMP : /*compression*/
            { 
              /*update CDB table address*/
              nextTransferRecord->daddr  = hostEmulation_addressUpdate(nextTransferRecord2->daddr , nextTransferRecord->ddim3, 0);
              nextTransferRecord1->daddr = nextTransferRecord->daddr;
              nextTransferRecord2->daddr = nextTransferRecord->daddr;
              break;
            }
            case DMAUTILSAUTOINC3D_DFMT_DECOMP : /*decompression*/
            { 
              /*move destination pointer*/
              nextTransferRecord->daddr  = hostEmulation_addressUpdate(nextTransferRecord2->daddr , nextTransferRecord->ddim3,   dstAM3);
              nextTransferRecord1->daddr = nextTransferRecord->daddr;
              nextTransferRecord2->daddr = nextTransferRecord->daddr;
              break;
            }
            default :
            {
              #if !USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
                nextTransferRecord->daddr   = hostEmulation_addressUpdate(nextTransferRecord2->daddr  , nextTransferRecord->ddim3,   dstAM3); //Validate
                nextTransferRecord1->daddr  = nextTransferRecord->daddr;
                nextTransferRecord2->daddr  = nextTransferRecord->daddr;
              #endif
              break;
            }
          }
        }
        
        /*Updating the start offset for next SB to be read in next iteration of the while loop or next trigger*/
        if ( DFMT == DMAUTILSAUTOINC3D_DFMT_COMP && nextTransferRecord->icnt3 != 0 && nextTransferRecord->dicnt3 != 0)
        {
          ((int32_t *)nextTransferRecord->daddr)[1] = nextSBStartOffset;
        }

        if ( nextTransferRecord->icnt3 == 0 || nextTransferRecord->dicnt3 == 0)
        {
          CSL_REG64_FINS(&druRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_ENABLE, 0);
          if ( DFMT == DMAUTILSAUTOINC3D_DFMT_COMP)
          {
            totalSrcCnt = origTransferRecord->icnt0 * origTransferRecord->icnt1 * origTransferRecord->icnt2 * origTransferRecord->icnt3;
      		  totalDstCnt = origTransferRecord->dicnt0 * origTransferRecord->dicnt1 * origTransferRecord->dicnt2 * origTransferRecord->dicnt3;
			      int32_t dataTobeTransferred = (( totalSrcCnt < totalDstCnt )? totalSrcCnt : totalDstCnt) * ((sectrPtr->data[1] >> 16) & 0xFFFF) * (sectrPtr->data[1] & 0xFFFF);
			      float compressedBitstreamLength = float(nextSBStartOffset);
            float compresionFactor = compressedBitstreamLength / float(dataTobeTransferred);
            //DmaUtilsAutoInc3d_printf(autoIncrementContext, 0,"Compression Factor: (%d  / %d ) %f \n", nextSBStartOffset, dataTobeTransferred, compresionFactor);
            printf("Compression Factor: (%d  / %d ) %f \n", nextSBStartOffset, dataTobeTransferred, compresionFactor);
            nextSBStartOffset = 0;
            #if CRASH_DEBUG_PRINTS
              fprintf(fp, "Layer Ends.");
            #endif
          }
          break;
        }


        if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT1_DEC )
        {
          break;
        }
        else if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT2_DEC )
        {
          if ( loopCnt1Reset == 1)
          {
            nextTransferRecord1->addr   = nextTransferRecord->addr;
            break;
          }
        }
        else if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT3_DEC )
        {
          if ( loopCnt2Reset == 1)
          {
            nextTransferRecord2->addr   = nextTransferRecord->addr;
            break;
          }
        }
        else
        {
          /*Indicates 4D sync,  Just continue */
        }
        srcLoopExitCondition--;
        if ( srcLoopExitCondition == 0)
        {
          nextTransferRecord->icnt3 = 0;
          CSL_REG64_FINS(&druRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_ENABLE, 0);
          break;
        }
      
      }
    #if USE_INTERIMBUFFER_FOR_NONCOMPRESSED_TR
      if (DFMT != DMAUTILSAUTOINC3D_DFMT_COMP && DFMT != DMAUTILSAUTOINC3D_DFMT_DECOMP)
      {
        loopCnt1Reset = 0;
        loopCnt2Reset = 0;
        srcPtr = interimBuffer;
        srcPtr1 = (uint16_t *)interimBuffer;
         /* Now copy the intermediate data to the destination buffer */
        while (1)
         {
           if( ELYPE == CSL_UDMAP_TR_FMTFLAGS_ELYPE_2_1)
           {
             dstPtr = (uint8_t *)nextTransferRecord->daddr;
             for (icnt0 = 0; icnt0 < nextTransferRecord->dicnt0; icnt0++)
             {
               *dstPtr = (uint8_t)(*srcPtr1);
                 srcPtr1++;
                 dstPtr = (uint8_t *)hostEmulation_addressUpdate((uint64_t)dstPtr, 1, dstAM0);
             }
           }
           else
          {
            dstPtr = (uint8_t *)nextTransferRecord->daddr;      
            for (icnt0 = 0; icnt0 < nextTransferRecord->dicnt0; icnt0++)
            {
              *dstPtr = *srcPtr;
              *srcPtr++;
              dstPtr = (uint8_t *)hostEmulation_addressUpdate((uint64_t)dstPtr, 1, dstAM0);
            }
          }
          nextTransferRecord->dicnt1--;

          nextTransferRecord->daddr = hostEmulation_addressUpdate(nextTransferRecord->daddr, nextTransferRecord->ddim1, dstAM1);
          
          if ( nextTransferRecord->dicnt1 == 0)
          {
            loopCnt1Reset = 1;
            nextTransferRecord->dicnt2--;
            nextTransferRecord->dicnt1 = origTransferRecord->dicnt1;

            nextTransferRecord->daddr = hostEmulation_addressUpdate(nextTransferRecord1->daddr, nextTransferRecord->ddim2, dstAM2);
            nextTransferRecord1->daddr = nextTransferRecord->daddr;
          }

          if ( nextTransferRecord->dicnt2 == 0)
          {
            loopCnt2Reset= 1;
            nextTransferRecord->dicnt3--;
            nextTransferRecord->dicnt2 = origTransferRecord->dicnt2;

            nextTransferRecord->daddr = hostEmulation_addressUpdate(nextTransferRecord2->daddr, nextTransferRecord->ddim3, dstAM3);

            nextTransferRecord1->daddr = nextTransferRecord->daddr;
            nextTransferRecord2->daddr = nextTransferRecord->daddr;
          }

          if ( nextTransferRecord->dicnt3 == 0)
          {
            CSL_REG64_FINS(&druRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_ENABLE, 0);
            break;
          }

          if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT1_DEC )
          {
            break;
          }
          else if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT2_DEC )
          {
            if ( loopCnt1Reset == 1)
            {
              break;
            }
          }
          else if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT3_DEC )
          {
            if ( loopCnt2Reset == 1)
            {
              break;
            }
          }

          dstLoopExitCondition--;
          if ( dstLoopExitCondition == 0)
          {
            nextTransferRecord->dicnt3 = 0;
            CSL_REG64_FINS(&druRegs->CHRT[chId].CHRT_CTL, DRU_CHRT_CTL_ENABLE, 0);
            break;
          }
        } /*while(1)*/
      } /*if (not compression)*/
    #endif
      if (( nextTransferRecord->icnt3 == 0 ) || ( nextTransferRecord->dicnt3 == 0 ))
      {
        /* this indicates that TR is received from PSIL */
        if ( (druRegs->CHNRT[chId].CFG & CSL_DRU_CHNRT_CFG_CHAN_TYPE_OWNER_MASK) != 0 )
        {
           CSL_UdmapCppi5TRPD * trDescriptor;
           uint64_t * ringPtr;
           uint64_t currTr;
           uint64_t numTr;
           CSL_UdmapTR           *pTr;
           /* Get Ring Memory Pointer */
          ringPtr = (uint64_t *) ((uint64_t)((uint64_t)ringAccCfgRegs->RING[udmapRegs->txChanCnt + chId].BA_HI << 32) |
                                            ringAccCfgRegs->RING[udmapRegs->txChanCnt + chId].BA_LO);

           trDescriptor = (CSL_UdmapCppi5TRPD *) (*ringPtr);

           numTr = CSL_udmapCppi5GetPktLen(trDescriptor);
           /* Use this field to track the TR, For the target build this would be handled by hardware */
           /* In real hardware this will not be like this it is done just for host emulation*/
           currTr =  druRegs->CHATOMIC[chId].DEBUG[1].NEXT_TR_WORD0_1;

            if ( currTr < numTr)
            {
               currTr++;
               pTr = (CSL_UdmapTR *)( (uint8_t *)trDescriptor + sizeof(CSL_UdmapTR) * currTr);

               /* Update both original and next transfer record by reading the TR from the TR descriptor */
              hostEmulation_druChSubmitAtomicTr(druRegs, chId, (void *) pTr);

               druRegs->CHATOMIC[chId].DEBUG[1].NEXT_TR_WORD0_1 = currTr;

            }
        }
      }
      if ( interimBuffer != NULL)
      {
        free(interimBuffer);
      }
    }
  }
  #if CRASH_DEBUG_PRINTS
  if(fp != NULL)
  {
    fclose(fp);
  }
  #endif
}
#endif


int32_t DmaUtilsAutoInc3d_getTotalBlockCount(uint8_t * trMem, uint32_t numTr)
{
    uint32_t i;
    CSL_UdmapTR * pTr;
    uint32_t isRingBasedFlowReq = 0;
    uint32_t numTotBlks = 0;
    uint32_t triggerType;
    uint32_t srcCounts;
    uint32_t dstCounts;

    pTr = ( CSL_UdmapTR * )trMem;

    if ( numTr > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
      isRingBasedFlowReq = 1U;
    }

    if (  isRingBasedFlowReq == 1U )
    {
      /* Setup TR descriptor */
      pTr = (CSL_UdmapTR *)(trMem + sizeof(CSL_UdmapTR));
    }

    for ( i = 0; i < numTr; i++)
    {
        triggerType = CSL_FEXT(pTr[i].flags, UDMAP_TR_FLAGS_TRIGGER0_TYPE );
        if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT1_DEC )
        {
            srcCounts = pTr[i].icnt1 * pTr[i].icnt2 * pTr[i].icnt3;
            dstCounts = pTr[i].dicnt1 * pTr[i].dicnt2 * pTr[i].dicnt3;
        }
        else if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT2_DEC )
        {
            srcCounts = pTr[i].icnt2 * pTr[i].icnt3;
            dstCounts = pTr[i].dicnt2 * pTr[i].dicnt3;
        }
        else if ( triggerType == CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT3_DEC )
        {
            srcCounts = pTr[i].icnt3;
            dstCounts = pTr[i].dicnt3;
        }
        else
        {
            srcCounts = 1U;
            dstCounts = 1U;
        }

        /* Always pick the minmum of the src and dst count as once any one is exhausted TR is compete */
        numTotBlks += ( srcCounts > dstCounts) ? dstCounts : srcCounts;
    }

    return numTotBlks;

}

static inline uintptr_t DmaUtilsAutoInc3d_getPhysicalAddress(DmaUtilsAutoInc3d_Context * dmautilsContext,
                                                                 const uintptr_t virtualAddr,
                                                                 int32_t chNum);

static inline uintptr_t DmaUtilsAutoInc3d_getPhysicalAddress(DmaUtilsAutoInc3d_Context * dmautilsContext,
                                                                 const uintptr_t virtualAddr,
                                                                 int32_t chNum)
{
  uintptr_t phyAddr = virtualAddr;

  /* If virtual to physical address conversion function is available then use it for
  conversion else directly program the address as it is */
  if ( dmautilsContext->initParams.udmaDrvHandle->initPrms.virtToPhyFxn != NULL )
  {
      phyAddr = (uintptr_t) dmautilsContext->initParams.udmaDrvHandle->initPrms.virtToPhyFxn(
                                                          (void *)virtualAddr,
                                                          chNum,
                                                          NULL);
  }
  return phyAddr;
}

static uint32_t DmaUtilsAutoInc3d_getTrFlags(int32_t syncType)
{
    uint32_t flags;
    uint32_t triggerBoundary;
    uint32_t waitBoundary;
    switch (syncType)
    {
        case DMAUTILSAUTOINC3D_SYNC_1D :
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT1_DEC;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_ICNT1_DEC;
          break;
        }
        case DMAUTILSAUTOINC3D_SYNC_2D :
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT2_DEC;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_ICNT2_DEC;
          break;
        }
        case DMAUTILSAUTOINC3D_SYNC_3D:
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT3_DEC;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_ICNT3_DEC;
          break;
        }
        case DMAUTILSAUTOINC3D_SYNC_4D:
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ALL;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_COMPLETION;
          break;
        }
        default :
        {
          triggerBoundary = CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT2_DEC;
          waitBoundary     = CSL_UDMAP_TR_FLAGS_EVENT_SIZE_ICNT2_DEC;
          break;
        }
    }

    flags =  CSL_FMK(UDMAP_TR_FLAGS_TYPE, CSL_UDMAP_TR_FLAGS_TYPE_4D_BLOCK_MOVE_REPACKING)             |
             CSL_FMK(UDMAP_TR_FLAGS_STATIC, 0)                                           |
             CSL_FMK(UDMAP_TR_FLAGS_EOL, 0)                                              |   /* NA */
             CSL_FMK(UDMAP_TR_FLAGS_EVENT_SIZE, waitBoundary)    |
             CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0, CSL_UDMAP_TR_FLAGS_TRIGGER_GLOBAL0)          |/*Set the trigger to local trigger*/
             CSL_FMK(UDMAP_TR_FLAGS_TRIGGER0_TYPE, triggerBoundary)      |/* This is to transfer a 2D block for each trigger*/
             CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1, CSL_UDMAP_TR_FLAGS_TRIGGER_NONE)               |
             CSL_FMK(UDMAP_TR_FLAGS_TRIGGER1_TYPE, CSL_UDMAP_TR_FLAGS_TRIGGER_TYPE_ICNT1_DEC)      |
             CSL_FMK(UDMAP_TR_FLAGS_CMD_ID, (0x25)) ;//                                         |   /* This will come back in TR response */
             //CSL_FMK(UDMAP_TR_FLAGS_SA_INDIRECT, 0U)                                         |
             //CSL_FMK(UDMAP_TR_FLAGS_DA_INDIRECT, 0U)                                         |
             //CSL_FMK(UDMAP_TR_FLAGS_EOP, 1U);

    return flags;
}

static uint32_t DmaUtilsAutoInc3d_getTrFmtFlags(DmaUtilsAutoInc3d_TransferCirc * circProp, int32_t dmaDfmt)
{
    uint32_t fmtflags = 0;
	  uint32_t  eltype    = CSL_UDMAP_TR_FMTFLAGS_ELYPE_1;
    uint32_t  sectrType = CSL_UDMAP_TR_FMTFLAGS_SECTR_NONE;
    int32_t  CBK0      = CSL_UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK_512B;
    int32_t  CBK1      = CSL_UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK_512B;
    uint32_t circDir    = CSL_UDMAP_TR_FMTFLAGS_DIR_DST_USES_AMODE;
    uint32_t  AMODE     = CSL_UDMAP_TR_FMTFLAGS_AMODE_LINEAR;

	  if ( ( circProp->circSize1 != 0 ) ||
                ( circProp->circSize2 != 0 ) )
    {
        uint32_t circSize1 = circProp->circSize1;
        uint32_t circSize2 = circProp->circSize2;
        //uint32_t circDir;

        if ( circProp->circDir == DMAUTILSAUTOINC3D_CIRCDIR_SRC )
        {
          circDir = CSL_UDMAP_TR_FMTFLAGS_DIR_SRC_USES_AMODE;
        }
        else
        {
          circDir = CSL_UDMAP_TR_FMTFLAGS_DIR_DST_USES_AMODE;
        }

        CBK0 = log2((double) circSize1) - 9;
        CBK1 = log2((double)circSize2)  - 1U -CBK0;

        if ( CBK1 < 0 )
        {
           CBK1 = 0;
        }
        AMODE = CSL_UDMAP_TR_FMTFLAGS_AMODE_CIRCULAR;
     }
    if (dmaDfmt == DMAUTILSAUTOINC3D_DFMT_COMP || dmaDfmt == DMAUTILSAUTOINC3D_DFMT_DECOMP ) /*TODO (de)compression CSLs don't exist yet*/
    {
      eltype    = CSL_UDMAP_TR_FMTFLAGS_ELYPE_16;
      sectrType = CSL_UDMAP_TR_FMTFLAGS_SECTR_64;
	  }
    fmtflags = CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE,                   AMODE                  ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_DIR,                 circDir                ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_ELYPE,               eltype                 ) |
               	   CSL_FMK(UDMAP_TR_FMTFLAGS_DFMT,                dmaDfmt                ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_SECTR,               sectrType                            ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK0, CBK0 ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_CBK1, CBK1 ) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM0, circProp->addrModeIcnt0) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM1, circProp->addrModeIcnt1) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM2, circProp->addrModeIcnt2) |
                   CSL_FMK(UDMAP_TR_FMTFLAGS_AMODE_SPECIFIC_AM3, circProp->addrModeIcnt3);

    return fmtflags;
}


static uint32_t DmaUtilsAutoInc3d_SetupCmpSecTr(DmaUtilsAutoInc3d_TransferProp * transferProp);

static uint32_t DmaUtilsAutoInc3d_SetupCmpSecTr(DmaUtilsAutoInc3d_TransferProp * transferProp)
{
    int32_t locSB_DIM1_SPEC = SB_DIM1_SPEC;
    uint32_t cmpFlags = 0;
    CSL_UdmapSecTR * secondaryTR = (CSL_UdmapSecTR *) transferProp->ioPointers.strPtr;

    if ( transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_COMP )
    {
    secondaryTR->addr    = (uint64_t)transferProp->ioPointers.dstPtr;
    secondaryTR->data[4] = 0x0UL; /*maximum offset*/
    }
    else
    {
      secondaryTR->addr = (uint64_t)transferProp->ioPointers.srcPtr;
      secondaryTR->data[4] = (uint64_t)transferProp->ioPointers.cdbPtr - (uint64_t)transferProp->ioPointers.strPtr; /*offset to CDB table*/
    }
    
    uint32_t sectrFlags  = 1U; /*TODO CSL doesn't exist yet for compression secTR type*/
    if(locSB_DIM1_SPEC == DMAUTILSAUTOINC3D_DRUSPEC_106MOD)
    {
      secondaryTR->flags   = (sectrFlags & 0xF) | ((transferProp->cmpProp.sbDim1 << 4) & 0xFFFFFFF0) ;
    } 
    else
    {
      secondaryTR->flags   = (sectrFlags & 0xF) | (transferProp->cmpProp.sbDim1 & 0xFFFFFFF0);
    }
    secondaryTR->data[1] = ( (transferProp->cmpProp.sbIcnt0 & 0xFFFF)       )
                         | ( (transferProp->cmpProp.sbIcnt1 & 0xFFFF) << 16 );
    secondaryTR->data[2] = transferProp->cmpProp.sDim0;
    secondaryTR->data[3] = transferProp->cmpProp.dDim0;
    if ( transferProp->cmpProp.cmpAlg == 3 ) /*TODO CSL doesn't exist yet for variable K SEG type */  
    { /*Image/video compression flags setup*/
      cmpFlags    = ( (transferProp->cmpProp.cmpAlg       & 0xF )       )
                  | ( (transferProp->cmpProp.varKStartK   & 0x7 ) << 8  )
                  | ( (transferProp->cmpProp.varKUpdateK  & 0x3 ) << 12 )
                  | ( (transferProp->cmpProp.varKElemSize & 0x3 ) << 16 )
                  | ( (transferProp->cmpProp.varKSubType  & 0x7 ) << 20 )
                  | ( (transferProp->cmpProp.varKSubSel0  & 0x3 ) << 24 )
                  | ( (transferProp->cmpProp.varKSubSel1  & 0x3 ) << 26 )
                  | ( (transferProp->cmpProp.varKSubSel2  & 0x3 ) << 28 )
                  | ( (transferProp->cmpProp.varKSubSel3  & 0x3 ) << 30 );
    }
    else
    { /*Analytical compression flags setup*/
      cmpFlags    = ( (transferProp->cmpProp.cmpAlg  & 0xF )      )
                  | ( (transferProp->cmpProp.sbAM0   & 0x3 ) << 4 )
                  | ( (transferProp->cmpProp.sbAM1   & 0x3 ) << 6 )
                  | ( (transferProp->cmpProp.cmpBias & 0xFF) << 8 );
    
    }
    secondaryTR->data[0] = cmpFlags;
 
  return UDMA_SOK;   
}

static void DmaUtilsAutoInc3d_setupTr(CSL_UdmapTR * tr,
                                              DmaUtilsAutoInc3d_TransferProp * transferProp);

static void DmaUtilsAutoInc3d_setupTr(CSL_UdmapTR * tr,
                                              DmaUtilsAutoInc3d_TransferProp * transferProp)
{
     /* Setup flags in TR*/
    tr->flags     = DmaUtilsAutoInc3d_getTrFlags(transferProp->syncType);
    /* Configure circularity parameters if required */
    tr->fmtflags    = DmaUtilsAutoInc3d_getTrFmtFlags(&transferProp->circProp, transferProp->dmaDfmt);
    if ( transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_DECOMP ) /*TODO decompression CSLs don't exist yet*/
      tr->addr       = (uintptr_t)transferProp->ioPointers.strPtr;
    else
   	  tr->addr       = (uintptr_t)transferProp->ioPointers.srcPtr;
	  
    tr->icnt0        = transferProp->transferDim.sicnt0;
    tr->icnt1        = transferProp->transferDim.sicnt1;
    tr->icnt2        = transferProp->transferDim.sicnt2;
    tr->icnt3        = transferProp->transferDim.sicnt3;
    tr->dim1        = transferProp->transferDim.sdim1;
    tr->dim2        = transferProp->transferDim.sdim2;
    tr->dim3        = transferProp->transferDim.sdim3;

    if ( transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_COMP ) /*TODO compression CSLs don't exist yet*/
      tr->daddr      = (uintptr_t) transferProp->ioPointers.strPtr;
    else
	  tr->daddr      = (uintptr_t) transferProp->ioPointers.dstPtr;
      

    tr->dicnt0       = transferProp->transferDim.dicnt0;
    tr->dicnt1       = transferProp->transferDim.dicnt1;
    tr->dicnt2       = transferProp->transferDim.dicnt2;
    tr->dicnt3       = transferProp->transferDim.dicnt3;
    tr->ddim1      =  transferProp->transferDim.ddim1;
    tr->ddim2      =  transferProp->transferDim.ddim2;
    tr->ddim3      =  transferProp->transferDim.ddim3;
    
	  if (transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_COMP || transferProp->dmaDfmt == DMAUTILSAUTOINC3D_DFMT_DECOMP)
    {
      int32_t success = DmaUtilsAutoInc3d_SetupCmpSecTr(transferProp);
    }
}

static void DmaUtilsAutoInc3d_printf(void * autoIncrementContext, int traceLevel, const char *format, ...);
static void DmaUtilsAutoInc3d_printf(void * autoIncrementContext, int traceLevel, const char *format, ...)
{
  DmaUtilsAutoInc3d_Context * dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;
  va_list args;

  if ( dmautilsContext->initParams.DmaUtilsVprintf != NULL )
  {
      if ( traceLevel < dmautilsContext->initParams.traceLogLevel)
      {
          va_start(args, format);
          dmautilsContext->initParams.DmaUtilsVprintf(format, args);
          va_end(args);
      }
  }
}


static void  DmaUtilsAutoInc3d_initializeContext(void * autoIncrementContext);
static void  DmaUtilsAutoInc3d_initializeContext(void * autoIncrementContext)
{
    DmaUtilsAutoInc3d_Context * autoIncHandle = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

    memset(autoIncHandle, 0, sizeof(DmaUtilsAutoInc3d_Context));

/*:TODO: This needs to be done at appropriate place*/
#ifdef HOST_EMULATION

#endif
    return ;
}


int32_t DmaUtilsAutoInc3d_getContextSize(int32_t numChannels)
{
    int32_t contextSize = 0;

    contextSize += DMAUTILS_ALIGN_CEIL(sizeof(DmaUtilsAutoInc3d_ChannelContext), 128) * numChannels;

    contextSize += DMAUTILS_ALIGN_CEIL(sizeof(DmaUtilsAutoInc3d_Context), 128);

    return contextSize;
}

static int32_t DmaUtilsAutoInc3d_setupContext(void * autoIncrementContext, DmaUtilsAutoInc3d_InitParam * initParams);
static int32_t DmaUtilsAutoInc3d_setupContext(void * autoIncrementContext, DmaUtilsAutoInc3d_InitParam * initParams)
{
    int32_t     retVal = UDMA_SOK;
    int32_t memLocation = 0;
    uint8_t * memPointer;
    int32_t i;
    DmaUtilsAutoInc3d_Context * dmaUtilsContext;

    memPointer  = (uint8_t *)autoIncrementContext;
    dmaUtilsContext = (DmaUtilsAutoInc3d_Context *)memPointer;
    memLocation += DMAUTILS_ALIGN_CEIL(sizeof(DmaUtilsAutoInc3d_Context), 128);

    dmaUtilsContext->initParams = *initParams;

    for ( i = 0; i < initParams->numChannels; i++)
    {
      dmaUtilsContext->channelContext[i] = (DmaUtilsAutoInc3d_ChannelContext *) (memPointer + memLocation);
      memLocation += DMAUTILS_ALIGN_CEIL(sizeof (DmaUtilsAutoInc3d_ChannelContext), 128);
    }

    if ( memLocation > initParams->contextSize)
    {
        DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, " DmaUtilsAutoInc3d_setupContext : Failed \n");
        retVal = UDMA_EINVALID_PARAMS;
    }

    return retVal;
}

int32_t DmaUtilsAutoInc3d_init(void * autoIncrementContext , DmaUtilsAutoInc3d_InitParam * initParams, DmaUtilsAutoInc3d_ChannelInitParam chInitParams[])
{
  uint32_t size;
  int32_t     retVal = UDMA_SOK;
  int32_t i;
  uint32_t                chType;
  uint32_t                eventId;
  Udma_ChPrms       chPrms;
  Udma_ChUtcPrms  utcPrms;
  DmaUtilsAutoInc3d_Context              * dmautilsContext;
  DmaUtilsAutoInc3d_ChannelContext * channelContext;
  Udma_ChHandle channelHandle;
  //__ESTP_S = 800;
  if ( initParams == NULL)
  {
    retVal = UDMA_EBADARGS;
    goto Exit;
  }

  if ( autoIncrementContext == NULL)
  {
    retVal = UDMA_EBADARGS;
    goto Exit;
  }
  //__ESTP_S = 801;
  size = DmaUtilsAutoInc3d_getContextSize(initParams->numChannels);

  if ( size != initParams->contextSize )
  {
    retVal = UDMA_EINVALID_PARAMS;
    goto Exit;
  }
  /* Reset internal variables of autoincrement context */
  DmaUtilsAutoInc3d_initializeContext(autoIncrementContext);
  //__ESTP_S = 802;
  
  dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

  retVal = DmaUtilsAutoInc3d_setupContext(autoIncrementContext, initParams);
  if   (UDMA_SOK != retVal)
  {
    goto Exit;
  }
  //__ESTP_S = 803;
  /* Initialize the channel params to default */
   chType = UDMA_CH_TYPE_UTC;
   UdmaChPrms_init(&chPrms, chType);
   chPrms.utcId = UDMA_UTC_ID_MSMC_DRU0;

  UdmaChUtcPrms_init(&utcPrms);
  //__ESTP_S = 804;
  for ( i = 0; i < initParams->numChannels; i++)
  {
      channelContext = dmautilsContext->channelContext[i];

      if ( chInitParams[i].druOwner == DMAUTILSAUTOINC3D_DRUOWNER_DIRECT_TR )
      {
          chPrms.fqRingPrms.ringMem      = NULL;
          chPrms.cqRingPrms.ringMem     = NULL;
          chPrms.tdCqRingPrms.ringMem = NULL;
          chPrms.fqRingPrms.elemCnt     = 0U;
          chPrms.cqRingPrms.elemCnt     = 0U;
          chPrms.tdCqRingPrms.elemCnt  = 0U;

          utcPrms.druOwner = CSL_DRU_OWNER_DIRECT_TR;
      }
      else
      {
          chPrms.fqRingPrms.ringMem     = &channelContext->ringMem;
          chPrms.cqRingPrms.ringMem    = &channelContext->responseRingMem;
          chPrms.tdCqRingPrms.ringMem = NULL;
          chPrms.fqRingPrms.ringMemSize = sizeof(uint64_t);
          chPrms.cqRingPrms.ringMemSize = sizeof(uint64_t);
          chPrms.tdCqRingPrms.ringMemSize = 0;
          chPrms.fqRingPrms.elemCnt      = 1U;/* We have only one element per ring */
          chPrms.cqRingPrms.elemCnt     = 1U;/* We have only one element per ring */
          chPrms.tdCqRingPrms.elemCnt  = 0U;/* We have only one element per ring */

          utcPrms.druOwner = CSL_DRU_OWNER_UDMAC_TR;
      }

      channelHandle = &(channelContext->chHandle);
      //__ESTP_S = 805;
      retVal = Udma_chOpen(initParams->udmaDrvHandle, channelHandle, chType, &chPrms);
      //__ESTP_S = 806;
      if(UDMA_SOK != retVal)
      {
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "Udma_chOpen : Failed \n");
         goto Exit;
      }

      /* Config UTC channel */
      utcPrms.druQueueId  =chInitParams[i].dmaQueNo;
      //__ESTP_S = 807;
      retVal = Udma_chConfigUtc(channelHandle, &utcPrms);
      //__ESTP_S = 808;
      if(UDMA_SOK != retVal)
      {
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "Udma_chConfigUtc : Failed \n");
          goto Exit;
      }
      //__ESTP_S = 809;
      /* Enable The channel */

      retVal = Udma_chEnable(channelHandle);

      //__ESTP_S = 810;
      if(UDMA_SOK != retVal)
      {
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "Udma_chEnable : Failed \n");
          goto Exit;
      }

      channelContext->druChannelId = Udma_chGetNum(channelHandle);

      //:TODO: Currently its assumed that dru channel id is where the dru event will be generated
      eventId = channelContext->druChannelId;
      //__ESTP_S = 815;
      channelContext->swTriggerPointer = Udma_druGetTriggerRegAddr(channelHandle);
      //:TODO: Currently it is assumed that DRU local events are routed to 32 event of c7x. This needs to be done cleanly
      channelContext->waitWord =  ((uint64_t)1U << (32 + eventId) );
      //__ESTP_S = 820;
  }

Exit:
    return retVal;

}

int32_t DmaUtilsAutoInc3d_getTrMemReq(int32_t numTRs)
{
    int32_t isRingBasedFlowReq = 0;
    int32_t trMemReq = 0;

    if ( numTRs > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
      isRingBasedFlowReq = 1;
    }

    if ( isRingBasedFlowReq )
    {
         //:TODO: Check how to make sure align required
         /* This indicates ring accelerator mode and hence will need memory for TR descriptor */
        trMemReq = sizeof(CSL_UdmapCppi5TRPD) + /* Number of Bytes for TR descriptor */
                               sizeof(CSL_UdmapTR) + /* Padding required to bring start of TR request to natural alignment for memory fetch efficiency */
                               numTRs * sizeof(CSL_UdmapTR) + /* Memory for Transfer Records */
                               numTRs * sizeof(uint32_t);/* Memory for Transfer Response Records */
    }
    else
    {
      trMemReq = numTRs * sizeof(CSL_UdmapTR);
    }

    return trMemReq;
}


int32_t DmaUtilsAutoInc3d_prepareTr(DmaUtilsAutoInc3d_TrPrepareParam * trPrepParam ,
                                            DmaUtilsAutoInc3d_TransferProp transferProp[])
{
    int32_t size;
    int32_t     retVal = UDMA_SOK;
    int32_t isRingBasedFlowReq = 0;
    CSL_UdmapTR * pTrArray;
    int32_t i;

    if ( trPrepParam == NULL )
    {
      retVal = UDMA_EBADARGS;
      goto Exit;
    }

    size = DmaUtilsAutoInc3d_getTrMemReq(trPrepParam->numTRs);

    if ( trPrepParam->trMemSize < size )
    {
      retVal = UDMA_EINVALID_PARAMS;
      goto Exit;
    }

    if ( trPrepParam->trMem == NULL )
    {
      retVal = UDMA_EBADARGS;
      goto Exit;
    }

    if ( trPrepParam->numTRs > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
        isRingBasedFlowReq = 1;
    }

    pTrArray = (CSL_UdmapTR *)trPrepParam->trMem;

    if ( isRingBasedFlowReq == 1 )
    {
      /* This needs to be updated with correct value during configure */
      uint32_t cqRingNum = 0;
      /* Setup TR descriptor */

      CSL_UdmapCppi5TRPD * pTrpd = (CSL_UdmapCppi5TRPD *)trPrepParam->trMem;
      CSL_UdmapTR           *pTr = (CSL_UdmapTR *)(trPrepParam->trMem + sizeof(CSL_UdmapTR));

      UdmaUtils_makeTrpd(pTrpd, UDMA_TR_TYPE_9, trPrepParam->numTRs, cqRingNum);
      pTrArray = pTr;

    }

    for ( i = 0; i < trPrepParam->numTRs ; i++)
    {
        DmaUtilsAutoInc3d_setupTr(&pTrArray[i], &transferProp[i]);
    }


Exit:

    return retVal;

}


int32_t DmaUtilsAutoInc3d_prepareTrWithPhysicalAddress(void * autoIncrementContext,
                                           DmaUtilsAutoInc3d_TrPrepareParam * trPrepParam ,
                                           DmaUtilsAutoInc3d_TransferProp transferProp[])
{
    int32_t     retVal = UDMA_SOK;
    uint32_t convertMask = ( DMAUTILSAUTOINC3D_ADDRCONVERTMASK_SRCADDR | DMAUTILSAUTOINC3D_ADDRCONVERTMASK_DSTADDR);
    retVal = DmaUtilsAutoInc3d_prepareTr(trPrepParam, transferProp);

    if ( retVal == UDMA_SOK )
    {
        retVal = DmaUtilsAutoInc3d_convertTrVirtToPhyAddr(autoIncrementContext,
                                                        trPrepParam,
                                                        convertMask);
    }
    return retVal;
}


int32_t DmaUtilsAutoInc3d_convertTrVirtToPhyAddr(void * autoIncrementContext,
                                            DmaUtilsAutoInc3d_TrPrepareParam * trPrepParam ,
                                            uint32_t convertMask)
{
    int32_t     retVal = UDMA_SOK;
    int32_t isRingBasedFlowReq = 0;
    CSL_UdmapTR * pTrArray;
    int32_t i;
    DmaUtilsAutoInc3d_Context        * dmautilsContext;
    DmaUtilsAutoInc3d_ChannelContext * channelContext;
    int32_t druChannelNum;

    if ( autoIncrementContext == NULL )
    {
      retVal = UDMA_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_convertTrVirtToPhyAddr : Failed :autoIncrementContext == NULL \n");
      goto Exit;
    }
    dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

    /* Do not call the translation function if the pointer is already NULL */
    if ( dmautilsContext->initParams.udmaDrvHandle->initPrms.virtToPhyFxn != NULL )
    {
        if ( trPrepParam == NULL )
        {
          retVal = UDMA_EBADARGS;
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_convertTrVirtToPhyAddr : Failed :trPrepParam == NULL \n");
          goto Exit;
        }

        if ( trPrepParam->trMem == NULL )
        {
          retVal = UDMA_EBADARGS;
          goto Exit;
        }

        channelContext = dmautilsContext->channelContext[trPrepParam->channelId];

        druChannelNum = channelContext->druChannelId;

        if ( trPrepParam->numTRs > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
        {
            isRingBasedFlowReq = 1;
        }

        pTrArray = (CSL_UdmapTR *)trPrepParam->trMem;

        if ( isRingBasedFlowReq == 1 )
        {
          CSL_UdmapTR           *pTr = (CSL_UdmapTR *)(trPrepParam->trMem + sizeof(CSL_UdmapTR));
          pTrArray = pTr;
        }

        for ( i = 0; i < trPrepParam->numTRs ; i++)
        {
            if (( convertMask & DMAUTILSAUTOINC3D_ADDRCONVERTMASK_SRCADDR) ==
              DMAUTILSAUTOINC3D_ADDRCONVERTMASK_SRCADDR)
            {
                pTrArray[i].addr = DmaUtilsAutoInc3d_getPhysicalAddress(dmautilsContext,
                                                                        pTrArray[i].addr,
                                                                        druChannelNum);
            }
            if (( convertMask & DMAUTILSAUTOINC3D_ADDRCONVERTMASK_DSTADDR) ==
              DMAUTILSAUTOINC3D_ADDRCONVERTMASK_DSTADDR)
            {
                pTrArray[i].daddr = DmaUtilsAutoInc3d_getPhysicalAddress(dmautilsContext,
                                                                        pTrArray[i].daddr,
                                                                        druChannelNum);
            }
        }
    }
Exit:
      return retVal;

}
#if 1
#if defined (__C7120__)
__ulong8 convert_tr_to_ulong8 (CSL_UdmapTR *tr) {
    __ulong8 vdata;

    //0x008 SRC address for the TR SUBMIT1 .SRC_ADDR
    vdata.s1 =
        (tr->addr << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD2_3_SRC_ADDR_SHIFT)
        & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD2_3_SRC_ADDR_MASK;


    //0x010 {ICNT3,ICNT2,DIM1} for the TR SUBMIT2 .ICNT3 .ICNT2 .DIM1
    vdata.s2 =
        (((uint64_t)tr->icnt3 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT3_SHIFT)
         & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT3_MASK)
        | (((uint64_t)tr->icnt2 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT2_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD4_5_ICNT2_MASK)
        | ((tr->dim1 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD4_5_DIM1_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD4_5_DIM1_MASK);


    //0x018{DIM3,DIM2} for the TR SUBMIT3 .SDIM3 .SDIM2
    vdata.s3 =
        (((uint64_t)tr->dim3 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM3_SHIFT)
         & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM3_MASK)
        | ((tr->dim2 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM2_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD6_7_DIM2_MASK);



    //0x020 {DDIM1,FORMAT_FLAGS} for the TR SUBMIT4 .FMTFLAGS .DDIM1
    vdata.s4 =
        (((uint64_t)tr->fmtflags << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD8_9_FMTFLAGS_SHIFT)
         & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD8_9_FMTFLAGS_MASK)
        | (((uint64_t)tr->ddim1 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD8_9_DDIM1_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD8_9_DDIM1_MASK);


    //0x028 DST address for the TR SUBMIT5 .DADDR
    vdata.s5 =
        ((tr->daddr << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD10_11_DADDR_SHIFT)
         & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD10_11_DADDR_MASK);



    //0x030 {DIM3,DIM2} for the TR SUBMIT6  .DDIM3 .DDIM2
    vdata.s6 =
        (((uint64_t)tr->ddim3 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM3_SHIFT)
         & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM3_MASK)
        | ((tr->ddim2 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM2_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD12_13_DDIM2_MASK);

    //0x038 {DICNT3,DICNT2,DICNT1,DICNT0}  SUBMIT7 .DICNT3 .DICNT2 .DICNT1 .DICNT0 Note these are the same as the a,b,c,d cnt
    vdata.s7 =
        (((uint64_t)tr->dicnt0 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT0_SHIFT)
         & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT0_MASK)
        | (((uint64_t)tr->dicnt1 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT1_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT1_MASK)
        | (((uint64_t)tr->dicnt2 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT2_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT2_MASK)
        | (((uint64_t)tr->dicnt3 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT3_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD14_15_DICNT3_MASK);

    //0x000 {ICNT1,ICNT0,FLAGS} SUBMIT0 .ICNT1 ICNT0 .FLAGS
    vdata.s0 =
        (((uint64_t)tr->icnt1 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT1_SHIFT)
         & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT1_MASK)
        | (((uint64_t)tr->icnt0 << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT0_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD0_1_ICNT0_MASK)
        | ((tr->flags << CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD0_1_FLAGS_SHIFT)
                & CSL_DRU_ATOMIC_SUBMIT_CURR_TR_WORD0_1_FLAGS_MASK);


    return vdata;
}
#endif
#endif

int32_t DmaUtilsAutoInc3d_configure(void * autoIncrementContext, int32_t channelId, uint8_t * trMem, int32_t numTr)
{
    int32_t     retVal = UDMA_SOK;
    DmaUtilsAutoInc3d_Context              * dmautilsContext;
    DmaUtilsAutoInc3d_ChannelContext * channelContext;
    uint32_t isRingBasedFlowReq =0;
    Udma_ChHandle channelHandle;

    uint32_t i;

#ifdef HOST_EMULATION
    uint32_t druChannelNum;
#endif
    if ( autoIncrementContext == NULL)
    {
      retVal = UDMA_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed :autoIncrementContext == NULL \n");
      goto Exit;
    }

    if ( trMem == NULL )
    {
      retVal = UDMA_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed : trMem == NULL \n");
      goto Exit;
    }

    dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

    channelContext = dmautilsContext->channelContext[channelId];
    channelHandle = &channelContext->chHandle;

    if ( numTr > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
        isRingBasedFlowReq = 1U;
    }

    if ( isRingBasedFlowReq  == 0U)
    {

        CSL_UdmapTR * tr;

        tr = ( CSL_UdmapTR *)trMem;

        /* Submit the TR using atomic write */
        //:TODO: currently host emulation doesn't handle multiple TR in direct TR mode
        for ( i = 0; i < numTr; i++)
        {
#ifndef HOST_EMULATION
          CSL_DRU_t *pDruRegs = channelHandle->utcInfo->druRegs;
          
          #if defined (__C7120__)
                //printf("%d, %d, 0x%llX\n", channelHandle->extChNum - channelHandle->utcInfo->startCh, channelId, channelHandle->drvHandle->druCoreID, pDruRegs);
                __ulong8 vdata = convert_tr_to_ulong8(tr + i);
                CSL_druChSubmitAtomicTr(pDruRegs, channelId, &vdata);
          #else
                CSL_druChSubmitTr(pDruRegs, channelId, channelHandle->drvHandle->druCoreID, tr + i);
          #endif 
          #if(0)
            Udma_chDruSubmitTr(channelHandle, tr + i);
          #endif
#else
              druChannelNum = Udma_chGetNum(channelHandle);
              hostEmulation_druChSubmitAtomicTr(dmautilsContext->initParams.udmaDrvHandle->utcInfo[UDMA_UTC_ID_MSMC_DRU0].druRegs,
                                                                                druChannelNum , (void *)tr);
#endif
        }
    }
    else
    {
      uint32_t cqRingNum = Udma_chGetCqRingNum(channelHandle);

      CSL_UdmapCppi5TRPD * pTrpd = (CSL_UdmapCppi5TRPD *)trMem;

      /* Update the cq ring number as it was not set correctly during descriptor preperation */
      CSL_udmapCppi5SetReturnPolicy(
              pTrpd,
              CSL_UDMAP_CPPI5_PD_DESCINFO_DTYPE_VAL_TR,
              CSL_UDMAP_CPPI5_PD_PKTINFO2_RETPOLICY_VAL_ENTIRE_PKT,
              CSL_UDMAP_CPPI5_PD_PKTINFO2_EARLYRET_VAL_NO,
              CSL_UDMAP_CPPI5_PD_PKTINFO2_RETPUSHPOLICY_VAL_TO_TAIL,
              cqRingNum);

      Udma_ringQueueRaw(Udma_chGetFqRingHandle(channelHandle),
              (uint64_t)trMem);

#ifdef HOST_EMULATION
      CSL_UdmapTR           *pTr = (CSL_UdmapTR *)(trMem + sizeof(CSL_UdmapTR));

      druChannelNum = (channelHandle->extChNum - channelHandle->utcInfo->startCh);
      hostEmulation_druChSubmitAtomicTr(dmautilsContext->initParams.udmaDrvHandle->utcInfo[UDMA_UTC_ID_MSMC_DRU0].druRegs,
                                                                        druChannelNum,
                                                                        (void *)pTr);

      /* Use this field to track the TR, For the target build this would be handled by hardware */
      /* In real hardware this will not be like this it is done just for host emulation*/
      dmautilsContext->initParams.udmaDrvHandle->utcInfo[UDMA_UTC_ID_MSMC_DRU0].druRegs->CHATOMIC[druChannelNum].DEBUG[1].NEXT_TR_WORD0_1 = 1;

#endif
    }

    dmautilsContext->blkIdx[channelId] = DmaUtilsAutoInc3d_getTotalBlockCount(trMem, numTr);
Exit :

    return retVal;

}


int32_t DmaUtilsAutoInc3d_trigger(void * autoIncrementContext, int32_t channelId)
{
    DmaUtilsAutoInc3d_Context              * dmautilsContext;

    dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

    CSL_druChSetGlobalTrigger0Raw(dmautilsContext->channelContext[channelId]->swTriggerPointer);//:TODO: This should be replaced by something else as we are not suppose to directly use these registers
#ifdef HOST_EMULATION
    hostEmulation_updateTriggerCount(dmautilsContext->initParams.udmaDrvHandle,
                                                     dmautilsContext->channelContext[channelId]->swTriggerPointer);
#endif

    dmautilsContext->blkIdx[channelId]--;

    return dmautilsContext->blkIdx[channelId];

}



void  DmaUtilsAutoInc3d_wait(void * autoIncrementContext, int32_t channelId)
{

    DmaUtilsAutoInc3d_Context              * dmautilsContext;

    dmautilsContext = (DmaUtilsAutoInc3d_Context *)autoIncrementContext;

#ifndef HOST_EMULATION
    volatile uint64_t eflRegisterVal;
    uint64_t waitWord;

    waitWord = dmautilsContext->channelContext[channelId]->waitWord;
    eflRegisterVal = __get_indexed(__EFR,0);
    while((eflRegisterVal & waitWord ) != waitWord )
    {
      eflRegisterVal = __get_indexed(__EFR,0);
    }
    __set_indexed(__EFCLR,0, waitWord);
#else
    /* Do the actual Transfer for host emulation*/
    hostEmulation_triggerDMA(dmautilsContext->initParams.udmaDrvHandle);
#endif

    return;

}


int32_t DmaUtilsAutoInc3d_deconfigure(void * autoIncrementContext, int32_t channelId, uint8_t * trMem, int32_t numTr)
{
    int32_t     retVal = UDMA_SOK;
    DmaUtilsAutoInc3d_Context              * dmautilsContext;
    DmaUtilsAutoInc3d_ChannelContext * channelContext;
    uint32_t isRingBasedFlowReq =0;
    Udma_ChHandle channelHandle;

    if ( autoIncrementContext == NULL)
    {
      retVal = UDMA_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed :autoIncrementContext == NULL \n");
      goto Exit;
    }

    if ( trMem == NULL )
    {
      retVal = UDMA_EBADARGS;
      DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed : trMem == NULL \n");
      goto Exit;
    }

    dmautilsContext = ( DmaUtilsAutoInc3d_Context *)autoIncrementContext;

    channelContext = dmautilsContext->channelContext[channelId];
    channelHandle = &channelContext->chHandle;


    /* disable  The channel */
    if ( numTr > DMAUTILS_MAX_NUM_TR_DIRECT_TR_MODE)
    {
        isRingBasedFlowReq = 1U;
    }

    if ( isRingBasedFlowReq  == 1 )
    {
       uint64_t    pDesc = 0;
      retVal = Udma_ringDequeueRaw(Udma_chGetCqRingHandle(channelHandle), &pDesc);
      if(UDMA_SOK != retVal)
      {
          DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_deconfigure : Failed : Udma_ringDequeueRaw\n");
          retVal = UDMA_EFAIL;
          goto Exit;
      }
    }

Exit:
    return retVal;

}


int32_t DmaUtilsAutoInc3d_deinit(void * autoIncrementContext)
{
    int32_t     retVal = UDMA_SOK;
    DmaUtilsAutoInc3d_Context              * dmautilsContext;
    DmaUtilsAutoInc3d_ChannelContext * channelContext;
    Udma_ChHandle channelHandle;
    int32_t i;
    if ( autoIncrementContext == NULL)
    {
        retVal = UDMA_EBADARGS;
        DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_configure : Failed :autoIncrementContext == NULL \n");
        goto Exit;
    }

    dmautilsContext = ( DmaUtilsAutoInc3d_Context *)autoIncrementContext;
    for ( i = 0; i < dmautilsContext->initParams.numChannels; i++)
     {
         channelContext = dmautilsContext->channelContext[i];
         channelHandle = &(channelContext->chHandle);

#if !HOST_EMULATION
         /* Avoid calling chDisable API for host emulation as it depends on some of the hardware sequence
         which are not emulated in host emulation */
         retVal = Udma_chDisable(channelHandle, UDMA_DEFAULT_CH_DISABLE_TIMEOUT);
#endif
         if(UDMA_SOK != retVal)
         {
             DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_deconfigure : Failed : Udma_chDisable\n");
             retVal = UDMA_EFAIL;
             goto Exit;
         }

         retVal = Udma_chClose(channelHandle);
         if(UDMA_SOK != retVal)
         {
             DmaUtilsAutoInc3d_printf(autoIncrementContext, 0, "DmaUtilsAutoInc3d_deinit : Udma_chClose : Failed \n");
            goto Exit;
         }
    }
Exit:

    return retVal;

}

