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
    0x67068230U,     0x4f048230U,     0x010203a0U,     0x60140202U, \
    0x7078fae0U,     0x116afc8bU,     0x95768188U,     0x548ce6b6U, \
    0x30806bb9U,     0x2a09060dU,     0xf7864886U,     0x0d01010dU, \
=======
    0x67068230U,     0x4f048230U,     0x010203a0U,     0x52140202U, \
    0x330923a9U,     0xb30eafc3U,     0xd2ea0c19U,     0xeb008d24U, \
    0x30f325b1U,     0x2a09060dU,     0xf7864886U,     0x0d01010dU, \
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
    0x0d171e30U,     0x36303432U,     0x33303331U,     0x39353234U, \
    0x320d175aU,     0x31373034U,     0x34333033U,     0x5a393532U, \
=======
    0x0d171e30U,     0x36303432U,     0x34313630U,     0x39333434U, \
    0x320d175aU,     0x30373034U,     0x34343136U,     0x5a393334U, \
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
    0x0d01010dU,     0x82030005U,     0xa5000102U,     0x87bf52c9U, \
    0xcda1c4b0U,     0xa67a5a44U,     0xcbd1a751U,     0x6ea3207dU, \
    0x1e8a1eb8U,     0x6b33015cU,     0xbeb103e9U,     0xe64004bfU, \
    0x882d009cU,     0xdc2171d9U,     0xa20c54d6U,     0x0d79a3ecU, \
    0xb14d2010U,     0xfb093833U,     0xf452576bU,     0x39de279cU, \
    0xdc04e08eU,     0xa2abf254U,     0xcdc546bbU,     0xcd5269cdU, \
    0xf5395b9fU,     0x7b6b2934U,     0xf153afb0U,     0xbb59ddc4U, \
    0x12c78bbcU,     0xa7c74e21U,     0x68bd97c3U,     0xfa8f6f60U, \
    0x29f666a3U,     0x6e7aade2U,     0x4268732dU,     0x7efc9552U, \
    0x926c5278U,     0xee16f884U,     0x7fc1cf2eU,     0x275cefbcU, \
    0x70dceb5fU,     0x4c77b459U,     0x30f3547dU,     0x8af272eeU, \
    0x306e5429U,     0xc1f24449U,     0xa097da91U,     0x9c42342bU, \
    0x1a671ba4U,     0x617748fdU,     0xdf443e4fU,     0xc29dcb7eU, \
    0xfd9bb0f0U,     0x4a690ff8U,     0xace8b7abU,     0xb1637515U, \
    0x015add6eU,     0x211f83dfU,     0x8900f601U,     0x3f453bfbU, \
    0xb0943f3fU,     0xb8f735baU,     0x545303a3U,     0xef2a1993U, \
    0xa8fbd834U,     0xd4659ee3U,     0x4a315d01U,     0x091dffe8U, \
    0x43e5c87eU,     0xe5857704U,     0x7f346f36U,     0x19d93756U, \
    0x652bbfb0U,     0xab23cd96U,     0x47d744f1U,     0x82acd04fU, \
    0x0c626c04U,     0x7ab757c3U,     0x6ad9ce00U,     0x57044528U, \
    0xc5ec5ef8U,     0x8465dcdbU,     0x7e6d99aeU,     0x954b699aU, \
    0x44187b6cU,     0x886a1c6bU,     0x06a9fd7dU,     0x990c952dU, \
    0xa70c9cb0U,     0xd702c58bU,     0x31cf5f27U,     0x728a4731U, \
    0xb6772bedU,     0x068da692U,     0x2dd9d8b7U,     0x61b732ccU, \
    0x51711d14U,     0x51773c9eU,     0xf9d2a6ddU,     0x6f7070a9U, \
    0xb936a243U,     0xd3cf8cc1U,     0x7951d65bU,     0xd496f8ffU, \
    0xfbdab9a1U,     0xeb2ded50U,     0x858ac23fU,     0xa57bb127U, \
    0x74d849a3U,     0xbebd7f9bU,     0x0bb91ce2U,     0x390289f4U, \
    0x24ca6229U,     0xeaebaae0U,     0x9c95b4adU,     0x47670e67U, \
    0x7c0995eeU,     0x373ff777U,     0xc4fdc1efU,     0x529ba085U, \
    0xaa4e97d3U,     0xa5e90eabU,     0xff6c7495U,     0x41526833U, \
    0xb30311faU,     0x5ce10995U,     0x8e7b26e3U,     0xbfbbe500U, \
    0x1411ac9cU,     0x44c70ac5U,     0x0096f2c5U,     0xa4f1ea01U, \
=======
    0x0d01010dU,     0x82030005U,     0x4f000102U,     0x84dbde02U, \
    0xa2b8f0a4U,     0xa4742b82U,     0x2a4f47e4U,     0xb4117b72U, \
    0xb57c4862U,     0x688b622cU,     0x92886b39U,     0xf605d958U, \
    0xa45502f6U,     0xd9a594a7U,     0x270c382dU,     0x07be2b93U, \
    0x295a461aU,     0x7961ca15U,     0x7143ba3fU,     0xd96fa823U, \
    0x48ea12d0U,     0x1d7b979bU,     0x33b38b35U,     0x1914abdcU, \
    0x3ee90b4cU,     0x47e1107cU,     0xe85bbaedU,     0xb36beaf6U, \
    0xef40d5d5U,     0x7a6782f5U,     0x21bdb3f4U,     0x17062cacU, \
    0x4285b3bdU,     0x29d796a6U,     0x8014aae8U,     0xd8d40b8aU, \
    0x07a3cfb6U,     0xc58b17b5U,     0xa866cc7dU,     0xdc8e6d8dU, \
    0xc49107a2U,     0xff799745U,     0xbe7b47f9U,     0x0edf25aaU, \
    0x831840a3U,     0xfc813b3bU,     0x70ded1d9U,     0x7038795bU, \
    0x3c3c27c6U,     0x5b351534U,     0x5a0f96aeU,     0x37bedcd7U, \
    0x734fbdaaU,     0x28d201b2U,     0x96210421U,     0xa8cebb99U, \
    0xdbce7813U,     0x82309b13U,     0x0ee3b9a2U,     0x8b89f675U, \
    0xdebbdaa4U,     0xd29835f8U,     0x76a99257U,     0x586c6850U, \
    0xf1aadf1eU,     0x7c249689U,     0xb526fb06U,     0xb06d1c96U, \
    0xc2328fa7U,     0x179e0c80U,     0x1458fb42U,     0x161feff4U, \
    0x40b95efcU,     0xe95140f7U,     0xd25dae7dU,     0x7d106181U, \
    0x8c82fddcU,     0x77988beaU,     0xc761bf52U,     0xce94a4a3U, \
    0xd3aaaa04U,     0x5dd2d0b7U,     0x82217e01U,     0x33b88fe4U, \
    0x5716229aU,     0x1fea1886U,     0x39ddd311U,     0xfb9eb0bcU, \
    0xd4bf6bfbU,     0xb5c92fa6U,     0xb1791130U,     0x991d4de8U, \
    0x4dcf4706U,     0x4bd0494cU,     0x925212dcU,     0x8f802beeU, \
    0xc5dc074bU,     0xd5daae9dU,     0xd0f45fb6U,     0x354c2ef9U, \
    0x6cbeb2a4U,     0x4a2093d2U,     0xd85bfb44U,     0x534217b9U, \
    0xe2b34648U,     0xfc50b3a6U,     0xc41b5b1fU,     0x45328160U, \
    0xfac98277U,     0x2534ea7bU,     0x82e87fafU,     0x22c0afe1U, \
    0x8ca1718eU,     0x92a80a5fU,     0xc1fc110aU,     0xf73f8b2cU, \
    0x16960f29U,     0x927b5d7cU,     0x3d763c04U,     0xf16501c9U, \
    0xb72ad2b8U,     0x3c982618U,     0x0e8352f8U,     0xb2e30712U, \
    0xfdc186b0U,     0xcb17ba67U,     0x1387deb3U,     0xf2cccf05U, \
    0x8c1ceaa3U,     0xde6fedb5U,     0x00d73e14U,     0xa4f1ea01U, \
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
