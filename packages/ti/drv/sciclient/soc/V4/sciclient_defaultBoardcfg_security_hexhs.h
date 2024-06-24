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


#define SCICLIENT_BOARDCFG_SECURITY_SIZE_IN_BYTES (1991U)

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
    0x67068230U,     0x4f048230U,     0x010203a0U,     0x0b140202U, \
    0x3462f0dcU,     0xd10e40fcU,     0x9aa91458U,     0x64c06be7U, \
    0x30c24083U,     0x2a09060dU,     0xf7864886U,     0x0d01010dU, \
    0x81300005U,     0x300b318bU,     0x55030609U,     0x02130604U, \
    0x0b315355U,     0x03060930U,     0x0c080455U,     0x31435302U, \
    0x060d300fU,     0x07045503U,     0x6144060cU,     0x73616c6cU, \
    0x1f302131U,     0x04550306U,     0x54180c0aU,     0x73617865U, \
    0x736e4920U,     0x6d757274U,     0x73746e65U,     0x49202c2eU, \
    0x312e636eU,     0x060a300cU,     0x0b045503U,     0x4250030cU, \
    0x300f3155U,     0x5503060dU,     0x060c0304U,     0x65626c41U, \
    0x1c317472U,     0x09061a30U,     0x8648862aU,     0x09010df7U, \
    0x410d1601U,     0x7265626cU,     0x69744074U,     0x6d6f632eU, \
    0x0d171e30U,     0x36303432U,     0x33303331U,     0x30343234U, \
    0x320d175aU,     0x31373034U,     0x34333033U,     0x5a303432U, \
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
    0x65014886U,     0x03020403U,     0xd2494004U,     0xe97552c8U, \
    0x3a76561fU,     0xa44a89b0U,     0x3e831ebcU,     0x8b02e4d0U, \
    0x575fd8fbU,     0x9ca235f4U,     0x04f509e7U,     0xe08d7557U, \
    0xa864f7a9U,     0x7278fa63U,     0x1711b033U,     0x1678afe8U, \
    0x64f25dcaU,     0x3a907fb0U,     0x0202c9beU,     0x18305d01U, \
    0x062b0906U,     0x82010401U,     0x04230126U,     0x0409300bU, \
    0x00000004U,     0x02010200U,     0x03061d30U,     0x040e1d55U, \
    0x04140416U,     0x84b3bbdfU,     0x0c257714U,     0xa4332ecbU, \
    0x59854d7dU,     0x30e5fb12U,     0x2a09060dU,     0xf7864886U, \
    0x0d01010dU,     0x82030005U,     0x21000102U,     0xec46deb9U, \
    0xb4afc9ebU,     0xe331c7faU,     0x74be512eU,     0xaa821e66U, \
    0x1dbabe7dU,     0xd9f3e164U,     0x98142405U,     0xda2545a1U, \
    0xa2549294U,     0xc53b0adcU,     0xc34f8bf2U,     0x983cce7eU, \
    0xf73ca513U,     0x57f96b2dU,     0x66a8c5e5U,     0x2b9342caU, \
    0x3c6a13a6U,     0xaba873b4U,     0x15fc7d74U,     0x9e9a768fU, \
    0x6e60e759U,     0x09c3c3e7U,     0xb95ce556U,     0x6bf0ae4eU, \
    0x7ade71a7U,     0xf527d479U,     0x0f07b076U,     0x12c5ea65U, \
    0x31d6d9d8U,     0xa86659e6U,     0x54090683U,     0xe47e64f6U, \
    0xd9fcecafU,     0x8bb8e7adU,     0xb4d6bfedU,     0x737c252cU, \
    0x41a5072fU,     0x52c4bb61U,     0x84e727f2U,     0xaf072d78U, \
    0x83b6c3acU,     0xecff77b8U,     0x83174587U,     0x8fbd8750U, \
    0x410d7acbU,     0x082dd521U,     0x5ddf88a9U,     0x7b0c6839U, \
    0x49fe9356U,     0x3051b273U,     0x0c2db826U,     0xcdf998cfU, \
    0x2ff9fc9fU,     0xfd48f280U,     0x158bae58U,     0x478f4f1fU, \
    0xc2a8e7f7U,     0x6fb465eeU,     0x9e3b3030U,     0xb176234bU, \
    0x38267432U,     0xdbc05aecU,     0x8fbe9a7bU,     0x69bb662fU, \
    0x8e0a424eU,     0xe5b05158U,     0xc47747b4U,     0xf41a5f5dU, \
    0x79c8cd2cU,     0x9f1a32e6U,     0xb8ff67b5U,     0x0621e03fU, \
    0x90e01a9eU,     0x1db53f26U,     0x8d77450bU,     0xc9d2ac7fU, \
    0xf368f7c7U,     0x091899c4U,     0xfdea1bf4U,     0x79c81b28U, \
    0xf6a418e4U,     0x56d09590U,     0x92aa4c0dU,     0x7bd0c42fU, \
    0x4dbdeef9U,     0x9b88d5f2U,     0x0538a386U,     0x1e2161c6U, \
    0x4f05c5f3U,     0xef30d5d6U,     0x8b8e130bU,     0x68039e89U, \
    0x04d5f08aU,     0x2f03fc7aU,     0x873251faU,     0xd16ba6ffU, \
    0x3301d8f2U,     0x4ef86b11U,     0x92caf85bU,     0x496e1659U, \
    0xf324c484U,     0x37f413faU,     0x3febf9eeU,     0xdbd6a74fU, \
    0xcf381959U,     0xa3b5626dU,     0xc87007d5U,     0xa556bc4dU, \
    0xc7c81027U,     0x051e8fecU,     0xb8471e93U,     0xab1b6ad2U, \
    0x71054266U,     0x77f5b8c7U,     0x17d494aaU,     0xba7c24efU, \
    0xf508c76bU,     0xa044d581U,     0xdcd07b67U,     0x86f1655aU, \
    0x0c5f84edU,     0xacf61785U,     0xb30a3e4eU,     0x810edc5bU, \
    0xecbe0a75U,     0x40531883U,     0x00180203U,     0xa4f1ea01U, \
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
    0x005a0000U,     0x23be0000U,     0x00000000U,     0x42af0000U, \
    0x00000010U,     0x00000000U,     0x00000000U,     0x00000000U, \
=======
    0x66068230U,     0x4e048230U,     0x010203a0U,     0x48130202U, \
    0x5c4722a2U,     0x443f4dddU,     0xbd216baeU,     0x92e8c847U, \
    0x0d3066afU,     0x862a0906U,     0x0df78648U,     0x050d0101U, \
    0x8b813000U,     0x09300b31U,     0x04550306U,     0x55021306U, \
    0x300b3153U,     0x55030609U,     0x020c0804U,     0x0f314353U, \
    0x03060d30U,     0x0c070455U,     0x6c614406U,     0x3173616cU, \
    0x061f3021U,     0x0a045503U,     0x6554180cU,     0x20736178U, \
    0x74736e49U,     0x656d7572U,     0x2e73746eU,     0x6e49202cU, \
    0x0c312e63U,     0x03060a30U,     0x0c0b0455U,     0x55425003U, \
    0x0d300f31U,     0x04550306U,     0x41060c03U,     0x7265626cU, \
    0x301c3174U,     0x2a09061aU,     0xf7864886U,     0x0109010dU, \
    0x6c410d16U,     0x74726562U,     0x2e697440U,     0x306d6f63U, \
    0x320d171eU,     0x30363034U,     0x34343136U,     0x5a313435U, \
    0x34320d17U,     0x36303730U,     0x35343431U,     0x305a3134U, \
    0x0b318b81U,     0x03060930U,     0x13060455U,     0x31535502U, \
    0x0609300bU,     0x08045503U,     0x4353020cU,     0x0d300f31U, \
    0x04550306U,     0x44060c07U,     0x616c6c61U,     0x30213173U, \
    0x5503061fU,     0x180c0a04U,     0x61786554U,     0x6e492073U, \
    0x75727473U,     0x746e656dU,     0x202c2e73U,     0x2e636e49U, \
    0x0a300c31U,     0x04550306U,     0x50030c0bU,     0x0f315542U, \
    0x03060d30U,     0x0c030455U,     0x626c4106U,     0x31747265U, \
    0x061a301cU,     0x48862a09U,     0x010df786U,     0x0d160109U, \
    0x65626c41U,     0x74407472U,     0x6f632e69U,     0x0282306dU, \
    0x060d3022U,     0x48862a09U,     0x010df786U,     0x00050101U, \
    0x0f028203U,     0x02823000U,     0x0282020aU,     0x14bf0001U, \
    0x7fd849aeU,     0x236bd372U,     0x0e48ebcdU,     0x4d22dc65U, \
    0x824f0ef2U,     0xf2b5edf6U,     0x917cdbddU,     0xff596efaU, \
    0xdeb6f7d5U,     0xcc8a1d04U,     0xd1d995d2U,     0xf8c1c4e0U, \
    0x48ffbf50U,     0x5022910cU,     0x8b7b4c9aU,     0x280a96f3U, \
    0xd9a4b326U,     0x4155a9e0U,     0x5b3efb1aU,     0xcabf6c27U, \
    0x2faf71c0U,     0x46ee2272U,     0xad622501U,     0xf604c73eU, \
    0x2cb618b1U,     0x0f6e12c0U,     0xe53e9be2U,     0x06a8a0a6U, \
    0x17410345U,     0xa91f164eU,     0x4e84d674U,     0x10a779d6U, \
    0x0ea911b8U,     0xdd251f92U,     0xd1f2b17fU,     0xd868f2b9U, \
    0x824b5933U,     0xd1cc777dU,     0xb423fa9cU,     0xf28858fbU, \
    0x16d5eacdU,     0x2d752cf2U,     0xc1c362faU,     0x06e06e09U, \
    0x07b5e070U,     0xd9629909U,     0x6ce7e4d6U,     0x0782c86dU, \
    0xe2f79350U,     0x5fd1edd8U,     0xcf9ed0e3U,     0x5fd95493U, \
    0x37ce5dddU,     0x14abf160U,     0x657b048aU,     0xdf7fbaa7U, \
    0x4b7c4545U,     0x4eae5ba1U,     0x8c3d94c6U,     0x94d2874eU, \
    0x9ff3a43cU,     0x36f2fcdaU,     0xad0de77cU,     0xf137425aU, \
    0x6ed0812aU,     0x0367a7a1U,     0x00ed871eU,     0x684a73bbU, \
    0x82a23128U,     0xc104a39aU,     0x45ff87e8U,     0x9fc1aa7eU, \
    0xc7053bd4U,     0x7121fd83U,     0x387fbdfeU,     0x521916c9U, \
    0x3303e60eU,     0xc91e1d8dU,     0x4ecd1c36U,     0x8829829dU, \
    0xbe2a9bcdU,     0xb27b5f6cU,     0x00793ab2U,     0xadf57d6aU, \
    0xcd1e9d1aU,     0x5ecf2a58U,     0xab804ef4U,     0xf8dd4f3bU, \
    0xa234ded4U,     0x59d920c4U,     0x02852d19U,     0xb1681f5eU, \
    0x11b98d4cU,     0x762de906U,     0x508c58b5U,     0x666e37a8U, \
    0x30836f78U,     0x9f344d46U,     0xb94a18b4U,     0xc57bfabbU, \
    0x1032d6aeU,     0x3f6c8484U,     0x3533809aU,     0xd5bc4dfcU, \
    0x5054606eU,     0x806d7ecfU,     0x8ffa0497U,     0xbdfd200bU, \
    0x37a12b98U,     0x4afd59bdU,     0x09a145ecU,     0x72c9178bU, \
    0x05b73314U,     0xe25d125eU,     0x21ce1d5aU,     0xeae1f654U, \
    0x27aa55d5U,     0xdf094debU,     0x2e824019U,     0x65178966U, \
    0xd6b36ed9U,     0x618d4e38U,     0xd474d616U,     0x515f16deU, \
    0xb842d519U,     0xdec8d283U,     0x9769a94bU,     0x03028db6U, \
    0xa3010001U,     0x8130c081U,     0x060c30bdU,     0x131d5503U, \
    0x03300504U,     0x30ff0101U,     0x2b090612U,     0x01040106U, \
    0x03012682U,     0x03300504U,     0x30010102U,     0x2b090660U, \
    0x01040106U,     0x22012682U,     0x51305304U,     0x86600906U, \
    0x03650148U,     0x04030204U,     0x72221340U,     0x48c70490U, \
    0x78d48b84U,     0x9e855dcbU,     0xf1789184U,     0x93fa1211U, \
    0x68c40797U,     0x68e65de2U,     0x3504f658U,     0x52158871U, \
    0xb06f739cU,     0xc0393116U,     0x92e7494cU,     0x16178e2aU, \
    0xea41c5c8U,     0xf8746c85U,     0x010202e1U,     0x0618305dU, \
    0x01062b09U,     0x26820104U,     0x0b042301U,     0x04040930U, \
    0x00000000U,     0x30020102U,     0x5503061dU,     0x16040e1dU, \
    0xdf041404U,     0x1484b3bbU,     0xcb0c2577U,     0x7da4332eU, \
    0x1259854dU,     0x0d30e5fbU,     0x862a0906U,     0x0df78648U, \
    0x050d0101U,     0x02820300U,     0x382c0001U,     0x8f435b8fU, \
    0xf8c897bcU,     0x05c53270U,     0x181082aaU,     0x1dfe2a14U, \
    0x9215f2ecU,     0xa773abeeU,     0xb625530bU,     0x41b99a6dU, \
    0x209223b5U,     0xfb103723U,     0xc0b672f1U,     0x77a42225U, \
    0x3b1113b5U,     0x50045c72U,     0x4229d6d2U,     0x8896027cU, \
    0x37fc2422U,     0xc16dc11aU,     0x6442c9b1U,     0xe9d85c92U, \
    0xb5c3a701U,     0x6450827cU,     0x027cc89dU,     0x0906f354U, \
    0x5dd1c452U,     0xa6e6519fU,     0xe9e7f529U,     0xc162551bU, \
    0x33b73675U,     0xc9aa0041U,     0x2efbed71U,     0xbef86a00U, \
    0x0c2fd48fU,     0xf32a224cU,     0x858430c8U,     0x3e58856bU, \
    0x24444b00U,     0x22dc9fbaU,     0xed3f1987U,     0x42edf33aU, \
    0x51cada14U,     0xd1e474deU,     0x41db15e7U,     0x4076be7eU, \
    0x3cb71aceU,     0xeba2e7f3U,     0xe9b74a93U,     0xe980ff29U, \
    0x714c6cfcU,     0x84037e75U,     0x0cdc3b65U,     0x246d132eU, \
    0x25d61d8cU,     0x58ebca60U,     0x10b2fd5aU,     0x3dad67d6U, \
    0xcd5b244dU,     0xb6d5d485U,     0xa63a091cU,     0x5e6f7406U, \
    0x2afa0982U,     0xde833d29U,     0xcc8586baU,     0x8b706da8U, \
    0x6112e0c9U,     0x6997c12cU,     0x3811c0c5U,     0x5dcc95e1U, \
    0x2536c3c8U,     0x56659107U,     0xbef0fd36U,     0x41753777U, \
    0x698d29e9U,     0x3940732aU,     0x08da58e6U,     0x2e2ad5dfU, \
    0xfe68a445U,     0xc7df955dU,     0xec2c4399U,     0xb4613146U, \
    0x185cadd6U,     0x9b953835U,     0xb1a1c472U,     0x5448abb3U, \
    0xbe036883U,     0x9e1b7107U,     0xc2dd43b9U,     0xe850e529U, \
    0x0f435b7dU,     0xefb5ceb0U,     0x023673f4U,     0xd228833aU, \
    0xecba1c6fU,     0xb114bf12U,     0x152f85ceU,     0x3e46348eU, \
    0x50fbbfd4U,     0x0252943dU,     0x0b2d809dU,     0x411f97aaU, \
    0x1b9ed2ddU,     0xd370d7ecU,     0x6c0e23f0U,     0xdec6c065U, \
    0x0b401873U,     0xaba006ffU,     0xc8d58cfdU,     0x83919e38U, \
    0xa7b4024dU,     0xf0d3beacU,     0x34e19911U,     0x2618c9fbU, \
    0x3e2e384bU,     0x287d68e0U,     0x0cf12d97U,     0x2a9bae5bU, \
    0x09d758e4U,     0x07ea31c0U,     0x7e9b5fe2U,     0xea3ae5cdU, \
    0x3b922650U,     0x3d5d8696U,     0xe7b964fdU,     0x0e0be827U, \
    0x42e6140fU,     0xd9c21c51U,     0x01002c2eU,     0x00a4f1eaU, \
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
    0x00448d27U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00454081U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
    0x00000000U,     0x00000000U,     0x0c517000U,     0x00008000U, \
    0x00005a00U,     0x0023be00U,     0x5a000000U,     0x1042af04U, \
    0x00000000U,     0x00000000U,     0x00000000U,     0x00000000U, \
>>>>>>> dev
    0x00000000U,     0x00000000U\
} /* 1991 bytes */

#endif
