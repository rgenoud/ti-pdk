/*
 *  Copyright (C) 2021 Texas Instruments Incorporated
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

/**
*  \file lpm_s2r.h
*
*  \brief File containing the Binary in a C array.
*
*/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#ifndef LPM_S2R_H_
#define LPM_S2R_H_


#define LPM_SRAM_S2R_SIZE_IN_BYTES (1270U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

#define LPM_SRAM_S2R { \
    0xf44f2000U,     0x39017100U,     0x8f5ff3bfU,     0x2f5aee07U, \
    0x2f56ee07U,     0x8f4ff3bfU,     0x3001d1f5U,     0xd1f02804U, \
    0xf243b082U,     0xf64b4290U,     0xf6c6435aU,     0xf2cd02efU, \
    0xf2401372U,     0xf24c2010U,     0xf2c00110U,     0xf2452099U, \
    0xf2c00508U,     0xf2c00168U,     0x600a0511U,     0x602a604bU, \
    0x2500606bU,     0x20e8f8d0U,     0x138af44fU,     0x2201f042U, \
    0x3280f442U,     0x20e8f8c0U,     0x9500601dU,     0x2a639a00U, \
    0x9a00d805U,     0x92003201U,     0x2a649a00U,     0x681ad3f9U, \
    0x7580f442U,     0x0204f244U,     0x0211f2c0U,     0x6fd3601dU, \
    0x6303ea5fU,     0x690bd5fbU,     0x4300f043U,     0x690b610bU, \
    0x3ffff1b3U,     0x6909dc00U,     0x91002100U,     0x2140f244U, \
    0xf2c09b00U,     0x428b010fU,     0x9b00d204U,     0x93003301U, \
    0xe7f89b00U,     0xf8c22101U,     0x681110bcU,     0x6101ea5fU, \
    0x2100d5fbU,     0x138af44fU,     0x10bcf8c2U,     0x72fff64fU, \
    0xf2cf6819U,     0xf42102f0U,     0x60197180U,     0x40116a41U, \
    0x62412251U,     0xf3626801U,     0x6001611eU,     0x1284f8d0U, \
    0x5141ea5fU,     0xf44fd5faU,     0xf6446280U,     0xf8c0714fU, \
    0x6a42228cU,     0x0201ea02U,     0xd1fa428aU,     0xf0002048U, \
    0x2060f8c7U,     0xf0002104U,     0x2048f943U,     0xf8c0f000U, \
    0x21042069U,     0xf93cf000U,     0xf000204cU,     0xf10df8b9U, \
    0x20010106U,     0x72faf44fU,     0xf962f000U,     0xd0010600U, \
    0xe00d2500U,     0x0006f89dU,     0x0186f1a0U,     0xfab13807U, \
    0xfab0f181U,     0xea4ff080U,     0x09401151U,     0x0500ea41U, \
    0xf0002048U,     0x2086f89dU,     0xf0002103U,     0x2048f919U, \
    0xf896f000U,     0x2102b10dU,     0x2066e007U,     0xf0002101U, \
    0x2048f90fU,     0xf88cf000U,     0x20652126U,     0xf908f000U, \
    0xf0002048U,     0x2085f885U,     0xf0002180U,     0x2048f901U, \
    0xf87ef000U,     0x21c02034U,     0xf8faf000U,     0xf0002048U, \
    0x2064f877U,     0xf0002108U,     0x2048f8f3U,     0xf870f000U, \
    0x21f72050U,     0xf8ecf000U,     0xf0002048U,     0x2051f869U, \
    0xf000213fU,     0x2048f8e5U,     0xf862f000U,     0x21ff204fU, \
    0xf8def000U,     0xf000204cU,     0x2032f85bU,     0xf0002101U, \
    0x204cf8d7U,     0xf854f000U,     0x21012033U,     0xf8d0f000U, \
    0xf000204cU,     0xf10df84dU,     0x203d0107U,     0x32fff04fU, \
    0xf8f6f000U,     0x4007f89dU,     0xf044204cU,     0xf0000602U, \
    0xb2f1f83fU,     0xf000203dU,     0x204cf8bbU,     0x0406f044U, \
    0xf836f000U,     0x203db2e4U,     0xf0004621U,     0x204cf8b1U, \
    0xf82ef000U,     0x01fbf006U,     0xf000203dU,     0x204cf8a9U, \
    0xf826f000U,     0x203d4621U,     0xf8a2f000U,     0x204cb16dU, \
    0xf81ef000U,     0x21802085U,     0xf89af000U,     0xf0002048U, \
    0x2085f817U,     0xf0002180U,     0x2048f893U,     0xf810f000U, \
    0x21ba20cbU,     0xf88cf000U,     0xf0002048U,     0x2086f809U, \
    0xf0002100U,     0xb002f885U,     0x0000e7feU,     0x00000000U, \
    0x4190f243U,     0x03f8f24cU,     0x01eff6c6U,     0x425af64bU, \
    0x3301f2c4U,     0x1272f2cdU,     0x1f10f8c3U,     0x010cf24dU, \
    0x3101f2c4U,     0x2210600aU,     0xf2c46819U,     0xf4412212U, \
    0x60192180U,     0xf4416859U,     0x60592180U,     0xf0416811U, \
    0x60110102U,     0xf0416811U,     0x60110108U,     0x1094f8d2U, \
    0x4100f441U,     0x1094f8c2U,     0x1080f8d2U,     0x71c1ea5fU, \
    0xf8d2d0faU,     0x230710a0U,     0x0107f363U,     0xf8c22309U, \
    0xf8d210a0U,     0xf36310a4U,     0xf8c20107U,     0xf8d210a4U, \
    0xf36310a8U,     0xf64c0107U,     0xf8c27303U,     0xf8d210a8U, \
    0x43991094U,     0x73fff64fU,     0x1094f8c2U,     0x1088f8d2U, \
    0xf2484399U,     0xf8c20380U,     0xf8d21088U,     0x43991084U, \
    0xf8c223b4U,     0xf8d21084U,     0xf3631098U,     0xf8c20109U, \
    0xf8d21098U,     0xf4411094U,     0xf8c24100U,     0xf8d21094U, \
    0xea5f1080U,     0xd0fa71c1U,     0x109cf8d2U,     0x33fff240U, \
    0x0c40f244U,     0x180b4399U,     0x219b20a1U,     0x309cf8c2U, \
    0xc084f8c2U,     0xb804f000U,     0x00000000U,     0x00000000U, \
    0x2224b510U,     0x2212f2c4U,     0xea5f6813U,     0xd4fb43c3U, \
    0x24002302U,     0x0c10f04fU,     0xf8d26753U,     0xf4433080U, \
    0xf02363c0U,     0xf8c20302U,     0xf8d23080U,     0xf0433080U, \
    0xf8c20e03U,     0x6813e080U,     0x63c3ea5fU,     0xb11cd5fbU, \
    0xf8c26791U,     0xe000c004U,     0x34016790U,     0xd1f22c02U, \
    0xea5f6810U,     0xd5fb7040U,     0x60506810U,     0x0000bd10U, \
    0xf240b510U,     0xf1020c24U,     0xf2c40e01U,     0x23002c12U, \
    0x4000f8dcU,     0xd50304e4U,     0x459e3301U,     0x4673d1f8U, \
    0xd25d4293U,     0xf8cc2301U,     0xf8dc3074U,     0xf4433080U, \
    0xf02363c0U,     0xf8cc0302U,     0xf8dc3080U,     0xf0433080U, \
    0x23000401U,     0x4080f8ccU,     0x4000f8dcU,     0xd40306e4U, \
    0x459e3301U,     0x4673d1f8U,     0xd2414293U,     0xf8cc2310U, \
    0x20000078U,     0x3004f8ccU,     0x3000f8dcU,     0xd403075bU, \
    0x45863001U,     0x4670d1f8U,     0xd2314290U,     0x0000f8dcU, \
    0xf8cc2302U,     0xf8dc0004U,     0xf3630080U,     0x2301204aU, \
    0x0080f8ccU,     0x3074f8ccU,     0x0080f8dcU,     0x0303f040U, \
    0xf8cc2000U,     0xf8dc3080U,     0x071b3000U,     0x3001d403U, \
    0xd1f84586U,     0x42904670U,     0xf8dcd212U,     0x700b3078U, \
    0x1000f8dcU,     0xd4030749U,     0x45863001U,     0x4670d1f8U, \
    0xd2054290U,     0x1000f8dcU,     0xf8cc2000U,     0xbd101004U, \
    0x30fff04fU,     0x0000bd10U\
} /* 1270 bytes */

#endif
