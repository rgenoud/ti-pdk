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
*  \file sciclient_defaultBoardcfg_security_hexhs.h
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

#ifndef SCICLIENT_DEFAULTBOARDCFG_SECURITY_HEXHS_H_
#define SCICLIENT_DEFAULTBOARDCFG_SECURITY_HEXHS_H_


#define SCICLIENT_BOARDCFG_SECURITY_SIZE_IN_BYTES (1992U)

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

#define SCICLIENT_BOARDCFG_SECURITY { \
<<<<<<< HEAD
    0x67068230U,     0x4f048230U,     0x010203a0U,     0x49140202U, \
    0xef2ad425U,     0x8a8ef2ffU,     0x688e6b3eU,     0x27a376c6U, \
    0x300ca81cU,     0x2a09060dU,     0xf7864886U,     0x0d01010dU, \
=======
    0x67068230U,     0x4f048230U,     0x010203a0U,     0x0f140202U, \
    0x81053e7eU,     0x91950045U,     0x88591c5eU,     0x5ef93755U, \
    0x30bd1962U,     0x2a09060dU,     0xf7864886U,     0x0d01010dU, \
>>>>>>> dev
    0x81300005U,     0x300b318bU,     0x55030609U,     0x02130604U, \
    0x0b315355U,     0x03060930U,     0x0c080455U,     0x31435302U, \
    0x060d300fU,     0x07045503U,     0x6144060cU,     0x73616c6cU, \
    0x1f302131U,     0x04550306U,     0x54180c0aU,     0x73617865U, \
    0x736e4920U,     0x6d757274U,     0x73746e65U,     0x49202c2eU, \
    0x312e636eU,     0x060a300cU,     0x0b045503U,     0x4250030cU, \
    0x300f3155U,     0x5503060dU,     0x060c0304U,     0x65626c41U, \
    0x1c317472U,     0x09061a30U,     0x8648862aU,     0x09010df7U, \
    0x410d1601U,     0x7265626cU,     0x69744074U,     0x6d6f632eU, \
<<<<<<< HEAD
    0x0d171e30U,     0x36303432U,     0x33303331U,     0x31323234U, \
    0x320d175aU,     0x31373034U,     0x34333033U,     0x5a313232U, \
=======
    0x0d171e30U,     0x36303432U,     0x34313630U,     0x30333634U, \
    0x320d175aU,     0x30373034U,     0x34343136U,     0x5a303336U, \
>>>>>>> dev
    0x318b8130U,     0x0609300bU,     0x06045503U,     0x53550213U, \
    0x09300b31U,     0x04550306U,     0x53020c08U,     0x300f3143U, \
    0x5503060dU,     0x060c0704U,     0x6c6c6144U,     0x21317361U, \
    0x03061f30U,     0x0c0a0455U,     0x78655418U,     0x49207361U, \
    0x7274736eU,     0x6e656d75U,     0x2c2e7374U,     0x636e4920U, \
    0x300c312eU,     0x5503060aU,     0x030c0b04U,     0x31554250U, \
    0x060d300fU,     0x03045503U,     0x6c41060cU,     0x74726562U, \
    0x1a301c31U,     0x862a0906U,     0x0df78648U,     0x16010901U, \
    0x626c410dU,     0x40747265U,     0x632e6974U,     0x82306d6fU, \
    0x0d302202U,     0x862a0906U,     0x0df78648U,     0x05010101U, \
    0x02820300U,     0x8230000fU,     0x82020a02U,     0xbf000102U, \
    0xd849ae14U,     0x6bd3727fU,     0x48ebcd23U,     0x22dc650eU, \
    0x4f0ef24dU,     0xb5edf682U,     0x7cdbddf2U,     0x596efa91U, \
    0xb6f7d5ffU,     0x8a1d04deU,     0xd995d2ccU,     0xc1c4e0d1U, \
    0xffbf50f8U,     0x22910c48U,     0x7b4c9a50U,     0x0a96f38bU, \
    0xa4b32628U,     0x55a9e0d9U,     0x3efb1a41U,     0xbf6c275bU, \
    0xaf71c0caU,     0xee22722fU,     0x62250146U,     0x04c73eadU, \
    0xb618b1f6U,     0x6e12c02cU,     0x3e9be20fU,     0xa8a0a6e5U, \
    0x41034506U,     0x1f164e17U,     0x84d674a9U,     0xa779d64eU, \
    0xa911b810U,     0x251f920eU,     0xf2b17fddU,     0x68f2b9d1U, \
    0x4b5933d8U,     0xcc777d82U,     0x23fa9cd1U,     0x8858fbb4U, \
    0xd5eacdf2U,     0x752cf216U,     0xc362fa2dU,     0xe06e09c1U, \
    0xb5e07006U,     0x62990907U,     0xe7e4d6d9U,     0x82c86d6cU, \
    0xf7935007U,     0xd1edd8e2U,     0x9ed0e35fU,     0xd95493cfU, \
    0xce5ddd5fU,     0xabf16037U,     0x7b048a14U,     0x7fbaa765U, \
    0x7c4545dfU,     0xae5ba14bU,     0x3d94c64eU,     0xd2874e8cU, \
    0xf3a43c94U,     0xf2fcda9fU,     0x0de77c36U,     0x37425aadU, \
    0xd0812af1U,     0x67a7a16eU,     0xed871e03U,     0x4a73bb00U, \
    0xa2312868U,     0x04a39a82U,     0xff87e8c1U,     0xc1aa7e45U, \
    0x053bd49fU,     0x21fd83c7U,     0x7fbdfe71U,     0x1916c938U, \
    0x03e60e52U,     0x1e1d8d33U,     0xcd1c36c9U,     0x29829d4eU, \
    0x2a9bcd88U,     0x7b5f6cbeU,     0x793ab2b2U,     0xf57d6a00U, \
    0x1e9d1aadU,     0xcf2a58cdU,     0x804ef45eU,     0xdd4f3babU, \
    0x34ded4f8U,     0xd920c4a2U,     0x852d1959U,     0x681f5e02U, \
    0xb98d4cb1U,     0x2de90611U,     0x8c58b576U,     0x6e37a850U, \
    0x836f7866U,     0x344d4630U,     0x4a18b49fU,     0x7bfabbb9U, \
    0x32d6aec5U,     0x6c848410U,     0x33809a3fU,     0xbc4dfc35U, \
    0x54606ed5U,     0x6d7ecf50U,     0xfa049780U,     0xfd200b8fU, \
    0xa12b98bdU,     0xfd59bd37U,     0xa145ec4aU,     0xc9178b09U, \
    0xb7331472U,     0x5d125e05U,     0xce1d5ae2U,     0xe1f65421U, \
    0xaa55d5eaU,     0x094deb27U,     0x824019dfU,     0x1789662eU, \
    0xb36ed965U,     0x8d4e38d6U,     0x74d61661U,     0x5f16ded4U, \
    0x42d51951U,     0xc8d283b8U,     0x69a94bdeU,     0x028db697U, \
    0x01000103U,     0x30c081a3U,     0x0c30bd81U,     0x1d550306U, \
    0x30050413U,     0xff010103U,     0x09061230U,     0x0401062bU, \
    0x01268201U,     0x30050403U,     0x01010203U,     0x09066030U, \
    0x0401062bU,     0x01268201U,     0x30530422U,     0x60090651U, \
    0x65014886U,     0x03020403U,     0x22134004U,     0xc7049072U, \
    0xd48b8448U,     0x855dcb78U,     0x7891849eU,     0xfa1211f1U, \
    0xc4079793U,     0xe65de268U,     0x04f65868U,     0x15887135U, \
    0x6f739c52U,     0x393116b0U,     0xe7494cc0U,     0x178e2a92U, \
    0x41c5c816U,     0x746c85eaU,     0x0202e1f8U,     0x18305d01U, \
    0x062b0906U,     0x82010401U,     0x04230126U,     0x0409300bU, \
    0x00000004U,     0x02010200U,     0x03061d30U,     0x040e1d55U, \
    0x04140416U,     0x84b3bbdfU,     0x0c257714U,     0xa4332ecbU, \
    0x59854d7dU,     0x30e5fb12U,     0x2a09060dU,     0xf7864886U, \
<<<<<<< HEAD
    0x0d01010dU,     0x82030005U,     0x6f000102U,     0xb3550cf3U, \
    0x9497749bU,     0x8d51cfdfU,     0xc0038c90U,     0x7a8914bbU, \
    0x71d9a206U,     0x288afdf9U,     0x68811fc3U,     0xcc49c5ceU, \
    0x9946c447U,     0x2dc69b70U,     0x44bda3e3U,     0xfbfa0a05U, \
    0x6858e6cfU,     0xaabc566eU,     0x6fa3d1e6U,     0x0c2468c4U, \
    0x2b3fe90eU,     0xec3a0d1cU,     0x3e5f328eU,     0x54579fa9U, \
    0x0e1fedd8U,     0x568b6595U,     0xaa38e328U,     0xf0ce8f3fU, \
    0x96a8fa30U,     0xbbcc5f89U,     0xd352ff38U,     0xf4ade50dU, \
    0x9b449e78U,     0xcb490c62U,     0x42b74e6bU,     0xd264d9fcU, \
    0xbd367df9U,     0x8af94041U,     0xb4c45f98U,     0x1093ca99U, \
    0x592cc482U,     0xa58d78afU,     0x583a2b10U,     0xa1a19e05U, \
    0x18ee4843U,     0x6c713fb4U,     0x255b69b5U,     0xc1357c02U, \
    0x8c098b5cU,     0x130561c9U,     0x6cec6e54U,     0x10d6a9e4U, \
    0x44e47c71U,     0x3793b7beU,     0x3c4e5ab6U,     0x6cb72e51U, \
    0x046b2296U,     0x504ddb71U,     0x429cf954U,     0xab9dfe0dU, \
    0x9d08bf02U,     0xf8bf1e92U,     0x89d2e5bfU,     0x714f2cb1U, \
    0xd2e440deU,     0x6aa2ef47U,     0x622cdf83U,     0x04332398U, \
    0x35cfb427U,     0x6147850eU,     0xc916968bU,     0xaeb2b2c6U, \
    0x901c8e4eU,     0xc23b75b7U,     0xffbaf9d7U,     0x98b7a899U, \
    0x7de83bc5U,     0x6fcb92a5U,     0xa90c44f6U,     0x3413424cU, \
    0x61a72f61U,     0x02ef2a15U,     0x7ed9b1c8U,     0x5eb9d93eU, \
    0x5dfde3e3U,     0xd88d966cU,     0x5e7e2d22U,     0x5e90f8f4U, \
    0x6b06c231U,     0xd8023ed1U,     0xc09e7f89U,     0x08c388ebU, \
    0xbd49741bU,     0x72982f76U,     0x067096a7U,     0x587cacc2U, \
    0x877a4a86U,     0x96950dcdU,     0x180c0671U,     0x06cd7fe3U, \
    0xb6b0f1acU,     0xb1dbb8fcU,     0x4a7ab753U,     0xa0aacb29U, \
    0x0ad4d2beU,     0x0e5c92b5U,     0x4c008822U,     0xb625c47fU, \
    0xa89bc25cU,     0x6c45eb4dU,     0x527f177dU,     0x756442bdU, \
    0x6660fb99U,     0x3bcab243U,     0xbe299538U,     0x056fcd0cU, \
    0xc5e90dafU,     0xc68b9174U,     0x7a991034U,     0xb44b0f6bU, \
    0x5dac4872U,     0x53f80605U,     0xc155a466U,     0xf4ebe6a7U, \
    0x2ac8d03bU,     0x9ebe850fU,     0xee88747dU,     0xfb592e8cU, \
    0xbdb91526U,     0x8f714ce9U,     0x00308d2cU,     0xa4f1ea01U, \
=======
    0x0d01010dU,     0x82030005U,     0xb2000102U,     0xac22edfdU, \
    0x6ab77c33U,     0x9d60bf23U,     0x355a86baU,     0xf25a20afU, \
    0x11a9c876U,     0xaf6c747aU,     0x52de6998U,     0x98b468c1U, \
    0xb3b2b3adU,     0xd7fc7f1eU,     0xf18fa3ffU,     0x1c17f2f3U, \
    0x2388498fU,     0x1bd949ccU,     0x18770b4aU,     0xd004c013U, \
    0xd8077631U,     0xa1bfaae5U,     0x572e255aU,     0x8b4016efU, \
    0xc042a41fU,     0xca379214U,     0xb968b2aaU,     0x259995a5U, \
    0xa3ad33f8U,     0xe4252ccbU,     0xf37e2975U,     0x3d2ee820U, \
    0x5f289152U,     0xbda49526U,     0xfaaf6ff5U,     0xa9e313f9U, \
    0x44f910ffU,     0x8dc044e1U,     0xf9d9cef9U,     0x928ef27eU, \
    0xe7851164U,     0x67c1793bU,     0xfb2f44baU,     0x853550d4U, \
    0xdbbbc96eU,     0x99160473U,     0xd0099b37U,     0x06f3c80aU, \
    0xcf926a95U,     0x99a47765U,     0x7b75d4faU,     0x78b3bbf5U, \
    0x872a69adU,     0x357aeedbU,     0xd0e78cfdU,     0x35fbac9cU, \
    0x4999fc85U,     0xd8f59ac5U,     0x8a690815U,     0xdfdbb020U, \
    0x7e9b69abU,     0x923fb7f4U,     0xa8d4e0d1U,     0xb725391dU, \
    0xc34a388dU,     0x89c7cd5cU,     0x36249c34U,     0x931d5e75U, \
    0x052acf87U,     0x04c056b4U,     0x120d6641U,     0x40acdaf3U, \
    0xb2aa15b6U,     0x2b5ccd62U,     0x581a9fefU,     0xda137a9bU, \
    0x81997a5cU,     0xd546f25cU,     0x60b949f8U,     0x0aab67b7U, \
    0x424178cfU,     0xb9f479d9U,     0x26b35601U,     0x362dbec7U, \
    0x2bb3846bU,     0xe7e5f130U,     0xeb5af6e9U,     0x7b799b80U, \
    0xf037ef65U,     0x3e8a0fa2U,     0xcda6f4b5U,     0x968db04aU, \
    0x5cbb441cU,     0x5f0249b0U,     0x483774eeU,     0x4ce9fc68U, \
    0x9c72837fU,     0xdb5035dbU,     0x95215dcfU,     0x87a58156U, \
    0xd0c21a93U,     0x33e0a883U,     0xdb4babe7U,     0x275b6c0fU, \
    0x26152edcU,     0x9b218cedU,     0xa0c9c406U,     0x201af465U, \
    0x9fb64520U,     0x6f6dabf2U,     0x53eb3213U,     0x5a0af3d3U, \
    0x198cd79dU,     0x6a251861U,     0xffe89d43U,     0xd0ea3c64U, \
    0xe59e419bU,     0x41f7c066U,     0x432f09c3U,     0x2fb05551U, \
    0x4b890436U,     0xc787b4e6U,     0xa3cc43c1U,     0x43ba07f6U, \
    0x1751e3a0U,     0xc5f56cfeU,     0xa87b729eU,     0x16ac5057U, \
    0xb9d814f2U,     0x18345ebdU,     0x0036afadU,     0xa4f1ea01U, \
>>>>>>> dev
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x448d2700U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x45408100U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x51700000U,     0x0080000cU, \
    0x005a0000U,     0x23be0000U,     0x00000000U,     0x42af045aU, \
    0x00000010U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U\
} /* 1992 bytes */

#endif
