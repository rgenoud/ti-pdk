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
    0x67068230U,     0x4f048230U,     0x010203a0U,     0x1f140202U, \
    0xea5e7b81U,     0x9403dea8U,     0x6e0b5e07U,     0xcb49fbd9U, \
    0x301076acU,     0x2a09060dU,     0xf7864886U,     0x0d01010dU, \
=======
    0x67068230U,     0x4f048230U,     0x010203a0U,     0x09140202U, \
    0x6f878167U,     0x87d56918U,     0xb1277601U,     0xa819612cU, \
    0x301af5a6U,     0x2a09060dU,     0xf7864886U,     0x0d01010dU, \
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
    0x0d171e30U,     0x36303432U,     0x33303331U,     0x32303234U, \
    0x320d175aU,     0x31373034U,     0x34333033U,     0x5a323032U, \
=======
    0x0d171e30U,     0x36303432U,     0x34313630U,     0x31353534U, \
    0x320d175aU,     0x30373034U,     0x34343136U,     0x5a313535U, \
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
    0x0d01010dU,     0x82030005U,     0x5b000102U,     0xe403cb18U, \
    0x91b4cbbaU,     0x71fd2abbU,     0xd6686a02U,     0xf94aa7b5U, \
    0x49c76689U,     0xc437bd36U,     0x6cabeca5U,     0x9f8c839bU, \
    0x03a8886aU,     0xbcd723dcU,     0x220c90f4U,     0xc6fece0aU, \
    0x7e333766U,     0x8aa13065U,     0x3acbafaeU,     0x008260afU, \
    0xa5861405U,     0x0cfbb872U,     0xd3b46452U,     0xadadcb6dU, \
    0x5043b1eaU,     0x3a258dfbU,     0x5e17039aU,     0x9b986de3U, \
    0xb74c2629U,     0x38a41b55U,     0x49da6cbfU,     0x18181548U, \
    0xf8af7decU,     0xd76ee1b8U,     0x814285f8U,     0x8bcb9455U, \
    0x8911c08eU,     0x8039ff83U,     0x3be04784U,     0xa8f881b3U, \
    0xef61f7a6U,     0x074b19a6U,     0x7b8cba7cU,     0x58ab6828U, \
    0xcd1aa545U,     0x4a72f01eU,     0x33eeb5d8U,     0x7e567e43U, \
    0xfa2b3cfeU,     0xadd6f09aU,     0x299fe807U,     0x2e9b3367U, \
    0x8c1b80eaU,     0xe961f34dU,     0x6fe1aa49U,     0x575a660cU, \
    0x3a3d407bU,     0x1576dd43U,     0x4a573704U,     0x3e2a5db1U, \
    0xf42c45efU,     0xee181492U,     0x90617d91U,     0x9e2cd45aU, \
    0xda71cc7bU,     0x880abcc0U,     0x65fb2142U,     0xdb36f09aU, \
    0xfc2c9087U,     0x07471be5U,     0x886cf1e3U,     0x27b0f2b4U, \
    0x3011bb92U,     0xdf1c52f3U,     0xf104702fU,     0x3fa9f40cU, \
    0x52b5f0caU,     0xec4aa3c4U,     0x1dffc3b5U,     0xfdd585c8U, \
    0xb1db4c6eU,     0x0eb30085U,     0x2931c36eU,     0xf3fc8107U, \
    0xd27a9201U,     0xceb549f8U,     0xb6d2a600U,     0x11753945U, \
    0x9354edd8U,     0x2f2878e0U,     0x61e4a19eU,     0x97472896U, \
    0x01949812U,     0x55d8c500U,     0x76a255b1U,     0x06a7a025U, \
    0x027f6e0dU,     0xb41a6a5eU,     0xe200b546U,     0x8be49195U, \
    0xf9a7ea52U,     0x91c3cfefU,     0x133956eeU,     0x71cbea81U, \
    0xd31a5663U,     0xcc2584d6U,     0xb1a639fcU,     0xff383c84U, \
    0x95258a34U,     0x8ba6b10fU,     0x8d5b254fU,     0x0d930ec1U, \
    0x08260cdbU,     0x60cadd89U,     0x7cac909bU,     0xb838257cU, \
    0xf17ac328U,     0x7b08dd7eU,     0x564596f0U,     0xdc5665bdU, \
    0xd5282fefU,     0xfb6730fdU,     0xe7966218U,     0x9f034a5fU, \
    0x63b19ab3U,     0xe89e8e0aU,     0xa7acfeabU,     0x453cbcc2U, \
    0xe3ad11b1U,     0xaf91f6a2U,     0x00819e0aU,     0xa4f1ea01U, \
=======
    0x0d01010dU,     0x82030005U,     0xb0000102U,     0x39277f65U, \
    0x81bfda1dU,     0x19d2d9f8U,     0x5fccb5a6U,     0x79dbf315U, \
    0x011088fcU,     0x571bab8fU,     0x18055cb0U,     0x285906c8U, \
    0xfcf3b35aU,     0x64e7ac3eU,     0x8103b366U,     0x5a1ebf85U, \
    0x9467cec0U,     0xded999f2U,     0x182be8f3U,     0x76e45135U, \
    0x71646ed9U,     0x4abbd7cdU,     0xf13b617fU,     0x416b2585U, \
    0x520af50fU,     0x2997d511U,     0x32f7cf00U,     0x4a12ebddU, \
    0x10796465U,     0x6b5620a9U,     0xa71112e2U,     0x4f281808U, \
    0xec1b0acdU,     0xc2de78afU,     0x4365591cU,     0xed74dbe4U, \
    0x4ed4ed96U,     0xb5385981U,     0xec0c58dfU,     0xdbc58bbfU, \
    0x99d19209U,     0x13cc5435U,     0xac3de2beU,     0xb5081402U, \
    0xa53926d4U,     0x4a3a174fU,     0xa9ad787fU,     0xef52fa64U, \
    0xe7a597a5U,     0xc8dcf263U,     0x453d372bU,     0x16a35240U, \
    0x768c6d91U,     0x709cc514U,     0x6cba4363U,     0xc48f93cdU, \
    0xf25c3dd4U,     0x1493179fU,     0x51301343U,     0xaf7bc00bU, \
    0x699434f8U,     0xf507aad9U,     0x4425d234U,     0x583769eeU, \
    0xa63b8aebU,     0xab69179dU,     0x5669a10cU,     0x2d7e8e21U, \
    0x6c64e93dU,     0x6ca639d5U,     0x8a2740a2U,     0xfcf146a5U, \
    0xe7dd24bcU,     0x6d748e97U,     0x780fb59bU,     0x13bace57U, \
    0xd5c8a8ffU,     0xf39d08e9U,     0xeb715aa7U,     0xa59a4d3eU, \
    0x5fec4680U,     0x30a20efcU,     0x1ebdd8d7U,     0x6d5b84a1U, \
    0x70471926U,     0x9dd64ac2U,     0xa0f4d50fU,     0x884c5218U, \
    0x0d2024bdU,     0x37bcab0fU,     0x031952feU,     0x9dbc5d04U, \
    0xa13fcc48U,     0x916a7db6U,     0xe09cfb4bU,     0xd998d45aU, \
    0xedc5c578U,     0xc41440dbU,     0x1e80b1ddU,     0xbd28f99fU, \
    0x3e90dc79U,     0x1803f02dU,     0xb867d767U,     0x63c05adeU, \
    0xe0486a77U,     0xda00ce4fU,     0x20b9649bU,     0xbe01fc21U, \
    0xbf355662U,     0x756422cdU,     0x860e5965U,     0xf7c0678cU, \
    0xeadb7400U,     0xfe3cb5d1U,     0x591ecabfU,     0x40deb8cbU, \
    0x7f5788c1U,     0x9efa4739U,     0x032827d5U,     0xfe29e5f2U, \
    0xa0ba9680U,     0x553b4d31U,     0xda46f722U,     0x0baa9daeU, \
    0xe1d9380bU,     0x7ec8dbefU,     0x9a7080ffU,     0x9906e086U, \
    0xfe775d96U,     0x8c962436U,     0x008b3ea1U,     0xa4f1ea01U, \
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
