/*
*
* Copyright (c) 2021 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef _J7VCL_BASE_ADDR_H_
#define _J7VCL_BASE_ADDR_H_

#define adc0_cfg_base                  (0x40200000)
#define adc0_dma_base                  (0x40208000)
#define adc0_ecc_base                  (0x40707000)
#define adc1_cfg_base                  (0x40210000)
#define adc1_dma_base                  (0x40218000)
#define adc1_ecc_base                  (0x40708000)
#define atl0_cfg_base                  (0x031F0000)
#define cc0_a72core0ecc_base           (0x4D20010400)
#define cc0_a72core1ecc_base           (0x4D20010800)
#define cc0_a72corepacecc_base         (0x4D20010000)
#define cc0_cfgr1_base                 (0x4D10000000)
#define cc0_cfgr2_base                 (0x4D10010000)
#define cc0_cfgr6_base                 (0x4D21000000)
#define cc0_cfgr7_base                 (0x45830000)
#define cc0_cfgr8_base                 (0x45900000)
#define cc0_cfgr9_base                 (0x45A00000)
#define cc0_dbgr0_base                 (0x4C30000000)
#define cc0_dbgr10_base                (0x4C30180000)
#define cc0_dbgr11_base                (0x4C30400000)
#define cc0_dbgr1_base                 (0x4C30100000)
#define cc0_dbgr2_base                 (0x4C30102000)
#define cc0_dbgr3_base                 (0x4C30103000)
#define cc0_dbgr4_base                 (0x4C30104000)
#define cc0_dbgr6_base                 (0x4C30106000)
#define cc0_dbgr7_base                 (0x4C30107000)
#define cc0_dbgr8_base                 (0x4C30109000)
#define cc0_dbgr9_base                 (0x4C30140000)
#define cc0_ddrcfgecc_base             (0x4D200B0800)
#define cc0_ddrctl_base                (0x02990000)
#define cc0_ddrss_base                 (0x02980000)
#define cc0_ecc3_base                  (0x4D200B0000)
#define cc0_ecc4_base                  (0x4D200B0400)
#define cc0_fwr0_base                  (0x45040400)
#define cc0_fwr4_base                  (0x45B10400)
#define cc0_gicecc_base                (0x4D200C0000)
#define cc0_gicr0_base                 (0x01000000)
#define cc0_gicr1_base                 (0x01800000)
#define cc0_gicr2_base                 (0x01810000)
#define cc0_gicr3_base                 (0x01820000)
#define cc0_msmcecc0_base              (0x4D20000000)
#define cc0_msmcecc1_base              (0x4D20000400)
#define cc0_msmcecc2_base              (0x4D20000800)
#define cmpevt_intr0_cfg_base          (0x00A30000)
#define cpsw2g0_ss_base                (0x46000000)
#define cpsw2g0_ss_ecc_base            (0x40709000)
#define cpsw5x0_cfg_base               (0x0C000000)
#define cpsw5x0_ecc_base               (0x02A21000)
#define cpt0_mcu_base                  (0x4C3E000000)
#define cpt1_rc_base                   (0x4C3E100000)
#define cpt2_infra_base                (0x4C3E140000)
#define cpt3_hc_base                   (0x4C3E180000)
#define cpt4_mv_base                   (0x4C3E1C0000)
#define dbgcbass0_err_base             (0x02A86000)
#define dbgcbass0_fw_base              (0x45268000)
#define dbgcbass0_glb_base             (0x45B20800)
#define dbgcbass0_isc_base             (0x458A0000)
#define dbgcbass0_qos_base             (0x45DA0000)
#define dcc0_cfg_base                  (0x40100000)
#define dcc1_cfg_base                  (0x40110000)
#define dcc2_cfg_base                  (0x40120000)
#define dcc3_cfg_base                  (0x00800000)
#define dcc4_cfg_base                  (0x00804000)
#define dcc5_cfg_base                  (0x00808000)
#define dcc6_cfg_base                  (0x0080C000)
#define dcc7_cfg_base                  (0x00810000)
#define dcc8_cfg_base                  (0x00814000)
#define dcc9_cfg_base                  (0x00818000)
#define ddpa0_cfg_base                 (0x42060000)
#define debugss0_cfgr0_base            (0x4C00000000)
#define debugss0_cfgr1_base            (0x4C40000000)
#define debugss0_cfgr2_base            (0x4C20000000)
#define debugss0_cfgr3_base            (0x4C60000000)
#define dftss0_cfg_base                (0x00D10000)
#define dmsc0_ecc_base                 (0x42800000)
#define dmsc0_ssr0_base                (0x44000000)
#define dmsccbass0_fw_base             (0x45080000)
#define dmsccbass0_glb_base            (0x45B00000)
#define dmsccbass0_isc_base            (0x45808000)
#define dmtimer0_cfg_base              (0x40400000)
#define dmtimer10_cfg_base             (0x02400000)
#define dmtimer11_cfg_base             (0x02410000)
#define dmtimer12_cfg_base             (0x02420000)
#define dmtimer13_cfg_base             (0x02430000)
#define dmtimer14_cfg_base             (0x02440000)
#define dmtimer15_cfg_base             (0x02450000)
#define dmtimer16_cfg_base             (0x02460000)
#define dmtimer17_cfg_base             (0x02470000)
#define dmtimer18_cfg_base             (0x02480000)
#define dmtimer19_cfg_base             (0x02490000)
#define dmtimer1_cfg_base              (0x40410000)
#define dmtimer20_cfg_base             (0x024A0000)
#define dmtimer21_cfg_base             (0x024B0000)
#define dmtimer22_cfg_base             (0x024C0000)
#define dmtimer23_cfg_base             (0x024D0000)
#define dmtimer24_cfg_base             (0x024E0000)
#define dmtimer25_cfg_base             (0x024F0000)
#define dmtimer26_cfg_base             (0x02500000)
#define dmtimer27_cfg_base             (0x02510000)
#define dmtimer28_cfg_base             (0x02520000)
#define dmtimer29_cfg_base             (0x02530000)
#define dmtimer2_cfg_base              (0x40420000)
#define dmtimer3_cfg_base              (0x40430000)
#define dmtimer4_cfg_base              (0x40440000)
#define dmtimer5_cfg_base              (0x40450000)
#define dmtimer6_cfg_base              (0x40460000)
#define dmtimer7_cfg_base              (0x40470000)
#define dmtimer8_cfg_base              (0x40480000)
#define dmtimer9_cfg_base              (0x40490000)
#define ecap0_cfg_base                 (0x03100000)
#define ecap1_cfg_base                 (0x03110000)
#define ecap2_cfg_base                 (0x03120000)
#define efuse0_mem_base                (0x40C00000)
#define efuse1_mem_base                (0x053F0000)
#define elm0_cfg_base                  (0x05380000)
#define emmc4i0_cfgr0_base             (0x04FB8000)
#define emmc4i0_cfgr1_base             (0x04FB0000)
#define emmc4i0_ecc0_base              (0x02A26000)
#define emmc4i0_ecc1_base              (0x02A27000)
#define emmc8i0_cfgr0_base             (0x04F88000)
#define emmc8i0_cfgr1_base             (0x04F80000)
#define emmc8i0_ecc0_base              (0x02A24000)
#define emmc8i0_ecc1_base              (0x02A25000)
#define eqep0_cfg_base                 (0x03200000)
#define eqep1_cfg_base                 (0x03210000)
#define eqep2_cfg_base                 (0x03220000)
#define esm0_cfg_base                  (0x42080000)
#define esm1_cfg_base                  (0x40800000)
#define esm2_cfg_base                  (0x00700000)
#define fss0_cfg_base                  (0x47000000)
#define fss0_fsas_cfgr0_base           (0x47010000)
#define fss0_fsas_cfgr1_base           (0x47020000)
#define fss0_hbmc_cfgr0_base           (0x47034000)
#define fss0_hbmc_cfgr1_base           (0x47030000)
#define fss0_hbmc_ecc_base             (0x47060000)
#define fss0_memr0_base                (0x50000000)
#define fss0_memr1_base                (0x58000000)
#define fss0_memr2_base                (0x400000000)
#define fss0_memr3_base                (0x500000000)
#define fss0_memr4_base                (0x600000000)
#define fss0_memr5_base                (0x700000000)
#define fss0_ospi0_cfgr0_base          (0x47044000)
#define fss0_ospi0_cfgr2_base          (0x47040000)
#define fss0_ospi0_ecc_base            (0x47068000)
#define fss0_ospi1_cfgr0_base          (0x47054000)
#define fss0_ospi1_cfgr2_base          (0x47050000)
#define fss0_ospi1_ecc_base            (0x47064000)
#define gpio0_cfg_base                 (0x42110000)
#define gpio1_cfg_base                 (0x42100000)
#define gpio2_cfg_base                 (0x00600000)
#define gpio4_cfg_base                 (0x00610000)
#define gpio6_cfg_base                 (0x00620000)
#define gpio8_cfg_base                 (0x00630000)
#define gpiointr0_cfg_base             (0x42200000)
#define gpiointr1_cfg_base             (0x00A00000)
#define gpmc0_cfgr0_base               (0x20000000)
#define gpmc0_cfgr1_base               (0x05390000)
#define gtc0_cfgr0_base                (0x00A80000)
#define gtc0_cfgr1_base                (0x00A90000)
#define gtc0_cfgr2_base                (0x00AA0000)
#define gtc0_cfgr3_base                (0x00AB0000)
#define hc2cbass0_err_base             (0x02A83000)
#define hc2cbass0_fw_base              (0x4527C000)
#define hc2cbass0_glb_base             (0x45B22800)
#define hc2cbass0_isc_base             (0x45898000)
#define hc2cbass0_qos_base             (0x45D98000)
#define hccfgcbass0_err_base           (0x02A89000)
#define hccfgcbass0_fw_base            (0x45280000)
#define hccfgcbass0_glb_base           (0x45B21000)
#define i2c0_cfg_base                  (0x42120000)
#define i2c1_cfg_base                  (0x40B00000)
#define i2c2_cfg_base                  (0x40B10000)
#define i2c3_cfg_base                  (0x02000000)
#define i2c4_cfg_base                  (0x02010000)
#define i2c5_cfg_base                  (0x02020000)
#define i2c6_cfg_base                  (0x02030000)
#define i2c7_cfg_base                  (0x02040000)
#define i2c8_cfg_base                  (0x02050000)
#define i2c9_cfg_base                  (0x02060000)
#define i3c0_cfgr0_base                (0x40B80000)
#define i3c0_cfgr1_base                (0x40B88000)
#define i3c0_ecc0_base                 (0x40720000)
#define i3c0_ecc1_base                 (0x40721000)
#define i3c1_cfgr0_base                (0x40B90000)
#define i3c1_cfgr1_base                (0x40B98000)
#define i3c1_ecc0_base                 (0x40722000)
#define i3c1_ecc1_base                 (0x40723000)
#define i3c2_cfgr0_base                (0x020A0000)
#define i3c2_cfgr1_base                (0x020A8000)
#define i3c2_ecc0_base                 (0x02A74000)
#define i3c2_ecc1_base                 (0x02A75000)
#define infranonsafe0_err_base         (0x00B04000)
#define infranonsafe0_fw_base          (0x45010000)
#define infranonsafe0_glb_base         (0x45B24000)
#define ipphycbass0_err_base           (0x02A8F000)
#define ipphycbass0_fw_base            (0x45220000)
#define ipphycbass0_glb_base           (0x45B21400)
#define ipphysafe0_err_base            (0x02A94000)
#define ipphysafe0_fw_base             (0x45200000)
#define ipphysafe0_glb_base            (0x45B24400)
#define ipphysafe0_isc_base            (0x45878000)
#define ipphysafe0_qos_base            (0x45D78000)
#define m4dbgsus_cfg_base              (0x4C3D300000)
#define main2mcu_lvl_intr0_cfg_base    (0x00A10000)
#define main2mcu_pls_intr0_cfg_base    (0x00A20000)
#define mainclk2ecc0_r51c0ecc_base     (0x02AF0000)
#define mainclk2ecc10_rcnav_base       (0x02AFA000)
#define mainclk2ecc11_rcnav_base       (0x02AFB000)
#define mainclk2ecc1_r51c1ecc_base     (0x02AF1000)
#define mainclk2ecc4_rcecc_base        (0x02AF4000)
#define mainclk2ecc5_hcecc_base        (0x02AF5000)
#define mainclk2ecc6_ipphyecc_base     (0x02AF6000)
#define maindbgcbass0_err_base         (0x02A80000)
#define mainfwcbass0_err_base          (0x00B08000)
#define maininfra0_err_base            (0x00B00000)
#define maininfra0_fw_base             (0x45000000)
#define maininfra0_glb_base            (0x45B0C000)
#define maininfraclk2ecc0_ecc_base     (0x00C02000)
#define mcan0_ecc_base                 (0x40700000)
#define mcan0_ssr0_base                (0x40520000)
#define mcan0_ssr1_base                (0x40528000)
#define mcan0_ssr3_base                (0x40500000)
#define mcan10_ecc_base                (0x02A40000)
#define mcan10_ssr0_base               (0x02780000)
#define mcan10_ssr1_base               (0x02781000)
#define mcan10_ssr3_base               (0x02788000)
#define mcan11_ecc_base                (0x02A41000)
#define mcan11_ssr0_base               (0x02790000)
#define mcan11_ssr1_base               (0x02791000)
#define mcan11_ssr3_base               (0x02798000)
#define mcan12_ecc_base                (0x02A42000)
#define mcan12_ssr0_base               (0x027A0000)
#define mcan12_ssr1_base               (0x027A1000)
#define mcan12_ssr3_base               (0x027A8000)
#define mcan13_ecc_base                (0x02A43000)
#define mcan13_ssr0_base               (0x027B0000)
#define mcan13_ssr1_base               (0x027B1000)
#define mcan13_ssr3_base               (0x027B8000)
#define mcan14_ecc_base                (0x02A44000)
#define mcan14_ssr0_base               (0x027C0000)
#define mcan14_ssr1_base               (0x027C1000)
#define mcan14_ssr3_base               (0x027C8000)
#define mcan15_ecc_base                (0x02A45000)
#define mcan15_ssr0_base               (0x027D0000)
#define mcan15_ssr1_base               (0x027D1000)
#define mcan15_ssr3_base               (0x027D8000)
#define mcan16_ecc_base                (0x02A46000)
#define mcan16_ssr0_base               (0x02680000)
#define mcan16_ssr1_base               (0x02681000)
#define mcan16_ssr3_base               (0x02688000)
#define mcan17_ecc_base                (0x02A47000)
#define mcan17_ssr0_base               (0x02690000)
#define mcan17_ssr1_base               (0x02691000)
#define mcan17_ssr3_base               (0x02698000)
#define mcan18_ecc_base                (0x02A48000)
#define mcan18_ssr0_base               (0x026A0000)
#define mcan18_ssr1_base               (0x026A1000)
#define mcan18_ssr3_base               (0x026A8000)
#define mcan19_ecc_base                (0x02A49000)
#define mcan19_ssr0_base               (0x026B0000)
#define mcan19_ssr1_base               (0x026B1000)
#define mcan19_ssr3_base               (0x026B8000)
#define mcan1_ecc_base                 (0x40701000)
#define mcan1_ssr0_base                (0x40560000)
#define mcan1_ssr1_base                (0x40568000)
#define mcan1_ssr3_base                (0x40540000)
#define mcan2_ecc_base                 (0x02A78000)
#define mcan2_ssr0_base                (0x02700000)
#define mcan2_ssr1_base                (0x02701000)
#define mcan2_ssr3_base                (0x02708000)
#define mcan3_ecc_base                 (0x02A79000)
#define mcan3_ssr0_base                (0x02710000)
#define mcan3_ssr1_base                (0x02711000)
#define mcan3_ssr3_base                (0x02718000)
#define mcan4_ecc_base                 (0x02A7A000)
#define mcan4_ssr0_base                (0x02720000)
#define mcan4_ssr1_base                (0x02721000)
#define mcan4_ssr3_base                (0x02728000)
#define mcan5_ecc_base                 (0x02A7B000)
#define mcan5_ssr0_base                (0x02730000)
#define mcan5_ssr1_base                (0x02731000)
#define mcan5_ssr3_base                (0x02738000)
#define mcan6_ecc_base                 (0x02A7C000)
#define mcan6_ssr0_base                (0x02740000)
#define mcan6_ssr1_base                (0x02741000)
#define mcan6_ssr3_base                (0x02748000)
#define mcan7_ecc_base                 (0x02A7D000)
#define mcan7_ssr0_base                (0x02750000)
#define mcan7_ssr1_base                (0x02751000)
#define mcan7_ssr3_base                (0x02758000)
#define mcan8_ecc_base                 (0x02A7E000)
#define mcan8_ssr0_base                (0x02760000)
#define mcan8_ssr1_base                (0x02761000)
#define mcan8_ssr3_base                (0x02768000)
#define mcan9_ecc_base                 (0x02A7F000)
#define mcan9_ssr0_base                (0x02770000)
#define mcan9_ssr1_base                (0x02771000)
#define mcan9_ssr3_base                (0x02778000)
#define mcasp0_cfg_base                (0x02B00000)
#define mcasp0_dma_base                (0x02B08000)
#define mcasp1_cfg_base                (0x02B10000)
#define mcasp1_dma_base                (0x02B18000)
#define mcasp2_cfg_base                (0x02B20000)
#define mcasp2_dma_base                (0x02B28000)
#define mcaspg0cbass0_err_base         (0x02A8A000)
#define mcaspg0cbass0_fw_base          (0x45288000)
#define mcaspg0cbass0_glb_base         (0x45B21800)
#define mcucbass0_err_base             (0x47100000)
#define mcucbass0_fw_base              (0x45100000)
#define mcucbass0_glb_base             (0x45B06000)
#define mcucbass0_isc_base             (0x45810000)
#define mcucbass0_qos_base             (0x45D10000)
#define mcuclk8ecc0_ecc_base           (0x47200000)
#define mcudbgcbass0_err_base          (0x47104000)
#define mcufwcbass0_err_base           (0x47108000)
#define mcunav0_ecc0_base              (0x28380000)
#define mcunav0_intr0_cfg_base         (0x28540000)
#define mcunav0_mcrc0_cfg_base         (0x2A264000)
#define mcunav0_modss_dmsc_fw_base     (0x45600000)
#define mcunav0_modss_dmsc_glb_base    (0x45B04000)
#define mcunav0_modss_dmsc_isc_base    (0x45818000)
#define mcunav0_modss_dmsc_qos_base    (0x45D20000)
#define mcunav0_proxy0_buf_base        (0x285A0000)
#define mcunav0_proxy0_cfg_base        (0x2A580000)
#define mcunav0_proxy0_gcfg_base       (0x28590000)
#define mcunav0_proxy0_src0_base       (0x2A500000)
#define mcunav0_psilcfg0_cfg_base      (0x2A268000)
#define mcunav0_ra0_cfg_base           (0x28440000)
#define mcunav0_ra0_fifos_base         (0x2B000000)
#define mcunav0_ra0_gcfg_base          (0x285D0000)
#define mcunav0_ra0_mon_base           (0x2A280000)
#define mcunav0_ra0_rt_base            (0x2B800000)
#define mcunav0_secproxy0_cfg_base     (0x285B0000)
#define mcunav0_secproxy0_rt_base      (0x2A380000)
#define mcunav0_secproxy0_scfg_base    (0x2A400000)
#define mcunav0_secproxy0_src_base     (0x2A480000)
#define mcunav0_udmap0_gcfg_base       (0x285C0000)
#define mcunav0_udmap0_rchan_base      (0x284C0000)
#define mcunav0_udmap0_rchanrt_base    (0x2A800000)
#define mcunav0_udmap0_rflow_base      (0x28400000)
#define mcunav0_udmap0_tchan_base      (0x284A0000)
#define mcunav0_udmap0_tchanrt_base    (0x2AA00000)
#define mcunav0_udmass_ecc0_base       (0x28381000)
#define mcunav0_udmass_inta0_cfg_base  (0x283C0000)
#define mcunav0_udmass_inta0_gcntcfg_base (0x28480000)
#define mcunav0_udmass_inta0_gcntrti_base (0x2A600000)
#define mcunav0_udmass_inta0_imap_base (0x28560000)
#define mcunav0_udmass_inta0_intr_base (0x2A700000)
#define mcunav0_udmass_inta0_l2g_base  (0x28570000)
#define mcunav0_udmass_inta0_mcast_base (0x28580000)
#define mcunav0_udmass_psilss0_cfg_base (0x285E0000)
#define mcunav0_udmass_ra0_isc_base    (0x45820000)
#define mcunavss0_cfg_base             (0x28520000)
#define mcurom0_mem_base               (0x41800000)
#define mmr0_cfg_base                  (0x43000000)
#define mmr1_cfg_base                  (0x40F00000)
#define mmr2_cfg_base                  (0x00100000)
#define msmc0_cfg_base                 (nav0_sramr0_base+0x0E000000)
#define msmc0_clec_cfg_base            (nav0_sramr0_base+0x18000000)
#define msmc0_dru_cfg_base             (nav0_sramr0_base+0x0D000000)
#define msmc0_sram_mem_base            (nav0_sramr0_base+0x10000000)
#define nav0_cfg_base                  (0x310C0000)
#define nav0_cpts0_cfg_base            (0x310D0000)
#define nav0_ddr0_virtid_base          (0x30A02000)
#define nav0_ddr1_virtid_base          (0x30A03000)
#define nav0_ddrr0_base                (0x80000000)
#define nav0_ddrr1_base                (0x800000000)
#define nav0_dma_pvu0_cfg_base         (0x30F81000)
#define nav0_dma_pvu0_tlbif_base       (0x36040000)
#define nav0_intr0_cfg_base            (0x310E0000)
#define nav0_io_pvu0_cfg_base          (0x30F80000)
#define nav0_io_pvu0_tlbif_base        (0x36000000)
#define nav0_mbox0_cfg0_base           (0x31F80000)
#define nav0_mbox0_cfg10_base          (0x31F8A000)
#define nav0_mbox0_cfg11_base          (0x31F8B000)
#define nav0_mbox0_cfg1_base           (0x31F81000)
#define nav0_mbox0_cfg2_base           (0x31F82000)
#define nav0_mbox0_cfg3_base           (0x31F83000)
#define nav0_mbox0_cfg4_base           (0x31F84000)
#define nav0_mbox0_cfg5_base           (0x31F85000)
#define nav0_mbox0_cfg6_base           (0x31F86000)
#define nav0_mbox0_cfg7_base           (0x31F87000)
#define nav0_mbox0_cfg8_base           (0x31F88000)
#define nav0_mbox0_cfg9_base           (0x31F89000)
#define nav0_mcrc0_cfg_base            (0x31F70000)
#define nav0_modss_dmsc_fw_base        (0x45480000)
#define nav0_modss_dmsc_glb_base       (0x45B0A000)
#define nav0_modss_dmsc_isc_base       (0x45840000)
#define nav0_modss_dmsc_qos_base       (0x45D40000)
#define nav0_modss_ecc0_base           (0x31000000)
#define nav0_modss_inta0_cfg_base      (0x30800000)
#define nav0_modss_inta0_imap_base     (0x30900000)
#define nav0_modss_inta0_intr_base     (0x33C00000)
#define nav0_modss_inta1_cfg_base      (0x30801000)
#define nav0_modss_inta1_imap_base     (0x30908000)
#define nav0_modss_inta1_intr_base     (0x33C40000)
#define nav0_nb0_cfg_base              (0x03802000)
#define nav0_nb1_cfg_base              (0x03803000)
#define nav0_nbss_cfg_base             (0x03800000)
#define nav0_nbss_ecc0_base            (0x03801000)
#define nav0_proxy0_buf_base           (0x31130000)
#define nav0_proxy0_cfg_base           (0x33400000)
#define nav0_proxy0_gcfg_base          (0x31120000)
#define nav0_proxy0_src0_base          (0x33000000)
#define nav0_psilcfg0_cfg_base         (0x31F78000)
#define nav0_ra0_cfg_base              (0x31080000)
#define nav0_ra0_fifos_base            (0x38000000)
#define nav0_ra0_gcfg_base             (0x31160000)
#define nav0_ra0_mon_base              (0x32000000)
#define nav0_ra0_rt_base               (0x3C000000)
#define nav0_safeg11_pvu_base          (0x30F90000)
#define nav0_safeg12_pvu_base          (0x30F91000)
#define nav0_secproxy0_cfg_base        (0x31140000)
#define nav0_secproxy0_rt_base         (0x32400000)
#define nav0_secproxy0_scfg_base       (0x32800000)
#define nav0_secproxy0_src_base        (0x32C00000)
#define nav0_spinlock0_cfg_base        (0x30E00000)
#define nav0_sramr0_base               (0x60000000)
#define nav0_tmrmgr0_cfg_base          (0x30E80000)
#define nav0_tmrmgr0_oes_base          (0x30F00000)
#define nav0_tmrmgr0_timers_base       (0x32200000)
#define nav0_tmrmgr1_cfg_base          (0x30E81000)
#define nav0_tmrmgr1_oes_base          (0x30F01000)
#define nav0_tmrmgr1_timers_base       (0x32240000)
#define nav0_udmap0_gcfg_base          (0x31150000)
#define nav0_udmap0_rchan_base         (0x30C00000)
#define nav0_udmap0_rchanrt_base       (0x34000000)
#define nav0_udmap0_rflow_base         (0x30D00000)
#define nav0_udmap0_tchan_base         (0x30B00000)
#define nav0_udmap0_tchanrt_base       (0x35000000)
#define nav0_udmass_dmsc_fw_base       (0x45400000)
#define nav0_udmass_dmsc_glb_base      (0x45B0B000)
#define nav0_udmass_dmsc_isc_base      (0x458D0000)
#define nav0_udmass_ecc0_base          (0x31001000)
#define nav0_udmass_inta0_cfg_base     (0x30802000)
#define nav0_udmass_inta0_gcntcfg_base (0x31040000)
#define nav0_udmass_inta0_gcntrti_base (0x33800000)
#define nav0_udmass_inta0_imap_base    (0x30940000)
#define nav0_udmass_inta0_intr_base    (0x33D00000)
#define nav0_udmass_inta0_l2g_base     (0x31100000)
#define nav0_udmass_inta0_mcast_base   (0x31110000)
#define nav0_udmass_psilss0_cfg_base   (0x31170000)
#define nav0_udmass_ra0_isc_base       (0x45870000)
#define nav0_virtss_dmsc_fw_base       (0x454A0000)
#define nav0_virtss_dmsc_glb_base      (0x45B0B800)
#define nav0_virtss_ecc0_base          (0x31002000)
#define ocmsram0_ecc_base              (0x4070B000)
#define ocmsram0_mem_base              (0x41C00000)
#define ocmsram1_ecc_base              (0x02A2F000)
#define ocmsram1_mem_base              (0x4F02000000)
#define pbist0_cfg_base                (0x40E00000)
#define pbist11_cfg_base               (0x03380000)
#define pbist1_cfg_base                (0x40E10000)
#define pbist2_cfg_base                (0x00D00000)
#define pbist3_cfg_base                (0x40E20000)
#define pbist4_cfg_base                (0x00D20000)
#define pcie1_core_base                (0x0D800000)
#define pcie1_cpts_base                (0x02916000)
#define pcie1_ecc0_base                (0x02915000)
#define pcie1_ecc1_base                (0x02A02000)
#define pcie1_intd_base                (0x02910000)
#define pcie1_memr0_base               (0x18000000)
#define pcie1_memr1_base               (0x4100000000)
#define pcie1_ucfg_base                (0x02917000)
#define pcie1_vmap_base                (0x02914000)
#define pdma0_cfg_base                 (0x03400000)
#define pdma1_cfg_base                 (0x03404000)
#define pdma2_ecc_base                 (0x027E0000)
#define pdma3_ecc_base                 (0x027E1000)
#define pdma4_ecc_base                 (0x027E2000)
#define pllctrl0_cfg_base              (0x42010000)
#define pllctrl1_cfg_base              (0x00410000)
#define pllmmr0_cfg_base               (0x40D00000)
#define pllmmr1_cfg_base               (0x00680000)
#define psc0_cfg_base                  (0x42000000)
#define psc1_cfg_base                  (0x00400000)
#define psram0_mem_base                (0x40280000)
#define psram1_ecc_base                (0x00C01000)
#define psram1_mem_base                (0x00000000)
#define psram2_ecc_base                (0x00C00000)
#define psram2_mem_base                (0x00200000)
#define pulmemcbass0_err_base          (0x02A90000)
#define pulmemcbass0_fw_base           (0x452B0000)
#define pulmemcbass0_glb_base          (0x45B23000)
#define pulmemcbass0_isc_base          (0x458C8000)
#define pulmemcbass0_qos_base          (0x45DC8000)
#define pulsar0_apb_base               (0x4C3D000000)
#define pulsar0_c0atcm0_base           (0x41000000)
#define pulsar0_c0btcm0_base           (0x41010000)
#define pulsar0_c0cfgr1_base           (0x400F0000)
#define pulsar0_c0cfgr2_base           (0x4072F000)
#define pulsar0_c0dcache0_base         (0x5400800000)
#define pulsar0_c0ecc_base             (0x40080000)
#define pulsar0_c0icache0_base         (0x5400000000)
#define pulsar0_c0memr0_base           (pulsar0_c0atcm0_base)
#define pulsar0_c0memr1_base           (pulsar0_c0btcm0_base)
#define pulsar0_c0memr2_base           (pulsar0_c0icache0_base)
#define pulsar0_c0memr3_base           (pulsar0_c0dcache0_base)
#define pulsar0_c1atcm1_base           (0x41400000)
#define pulsar0_c1btcm1_base           (0x41410000)
#define pulsar0_c1cfgr0_base           (0x400C0000)
#define pulsar0_c1dcache1_base         (0x5401800000)
#define pulsar0_c1icache1_base         (0x5401000000)
#define pulsar0_c1memr0_base           (pulsar0_c1atcm1_base)
#define pulsar0_c1memr1_base           (pulsar0_c1btcm1_base)
#define pulsar0_c1memr2_base           (pulsar0_c1icache1_base)
#define pulsar0_c1memr3_base           (pulsar0_c1dcache1_base)
#define pulsar1_apb_base               (0x4C3D400000)
#define pulsar1_c0atcm0_base           (0x05C00000)
#define pulsar1_c0btcm0_base           (0x05C10000)
#define pulsar1_c0cfgr1_base           (0x05B00000)
#define pulsar1_c0cfgr2_base           (0x02A2D000)
#define pulsar1_c0dcache0_base         (0x4E00800000)
#define pulsar1_c0ecc_base             (0x02A68000)
#define pulsar1_c0icache0_base         (0x4E00000000)
#define pulsar1_c0memr0_base           (pulsar1_c0atcm0_base)
#define pulsar1_c0memr1_base           (pulsar1_c0btcm0_base)
#define pulsar1_c0memr2_base           (pulsar1_c0icache0_base)
#define pulsar1_c0memr3_base           (pulsar1_c0dcache0_base)
#define pulsar1_c1atcm1_base           (0x05D00000)
#define pulsar1_c1btcm1_base           (0x05D10000)
#define pulsar1_c1cfgr0_base           (0x05B10000)
#define pulsar1_c1dcache1_base         (0x4E01800000)
#define pulsar1_c1icache1_base         (0x4E01000000)
#define pulsar1_c1memr0_base           (pulsar1_c1atcm1_base)
#define pulsar1_c1memr1_base           (pulsar1_c1btcm1_base)
#define pulsar1_c1memr2_base           (pulsar1_c1icache1_base)
#define pulsar1_c1memr3_base           (pulsar1_c1dcache1_base)
#define pulslvcbass0_err_base          (0x02A91000)
#define pulslvcbass0_fw_base           (0x452B4000)
#define pulslvcbass0_glb_base          (0x45B23400)
#define pwm0_cfg_base                  (0x03000000)
#define pwm0_hr_base                   (0x03008000)
#define pwm1_cfg_base                  (0x03010000)
#define pwm1_hr_base                   (0x03018000)
#define pwm2_cfg_base                  (0x03020000)
#define pwm2_hr_base                   (0x03028000)
#define pwm3_cfg_base                  (0x03030000)
#define pwm3_hr_base                   (0x03038000)
#define pwm4_cfg_base                  (0x03040000)
#define pwm4_hr_base                   (0x03048000)
#define pwm5_cfg_base                  (0x03050000)
#define pwm5_hr_base                   (0x03058000)
#define rccbass0_err_base              (0x02A8C000)
#define rccbass0_fw_base               (0x45240000)
#define rccbass0_glb_base              (0x45B22000)
#define rccbass0_isc_base              (0x45880000)
#define rccbass0_qos_base              (0x45D80000)
#define rccfgcbass0_err_base           (0x02A8D000)
#define rccfgcbass0_fw_base            (0x45250000)
#define rccfgcbass0_glb_base           (0x45B22400)
#define rti0_cfg_base                  (0x40600000)
#define rti1_cfg_base                  (0x40610000)
#define rti2_cfg_base                  (0x023C0000)
#define rti3_cfg_base                  (0x023D0000)
#define rti4_cfg_base                  (0x02200000)
#define rti5_cfg_base                  (0x02210000)
#define sa2_ul0_cfgr0_base             (0x40900000)
#define sa2_ul0_cfgr1_base             (0x40901000)
#define sa2_ul0_cfgr3_base             (0x40910000)
#define sa2_ul0_cfgr4_base             (0x40920000)
#define sa2_ul0_ecc_base               (0x4070C000)
#define safeg0_cfg_base                (0x42900000)
#define safeg10_cfg_base               (0x0260A000)
#define safeg1_cfg_base                (0x40731000)
#define safeg2_cfg_base                (0x40730000)
#define safeg3_cfg_base                (0x40732000)
#define safeg4_cfg_base                (0x40736000)
#define safeg5_cfg_base                (0x40737000)
#define safeg6_cfg_base                (0x00780000)
#define safeg7_cfg_base                (0x02602000)
#define safeg8_cfg_base                (0x02604000)
#define safeg9_cfg_base                (0x02608000)
#define secmmr0_cfgr0_base             (0x45A50000)
#define secmmr0_cfgr2_base             (0x45950000)
#define secmmr1_cfgr0_base             (0x45A40000)
#define secmmr1_cfgr2_base             (0x45944000)
#define serdestrnt1_cfg_base           (0x05060000)
#define socdbgcell0_sys_base           (0x08000000)
#define socdbgcellxx0_cfg_base         (0x4C3C020000)
#define spi0_cfg_base                  (0x40300000)
#define spi10_cfg_base                 (0x02170000)
#define spi1_cfg_base                  (0x40310000)
#define spi2_cfg_base                  (0x40320000)
#define spi3_cfg_base                  (0x02100000)
#define spi4_cfg_base                  (0x02110000)
#define spi5_cfg_base                  (0x02120000)
#define spi6_cfg_base                  (0x02130000)
#define spi7_cfg_base                  (0x02140000)
#define spi8_cfg_base                  (0x02150000)
#define spi9_cfg_base                  (0x02160000)
#define stm0_cfgr0_base                (0x4C3D200000)
#define stm0_cfgr1_base                (0x4C3D201000)
#define stm0_mem_base                  (0x09000000)
#define timesync_intr0_cfg_base        (0x00A40000)
#define usart0_cfg_base                (0x42300000)
#define usart10_cfg_base               (0x02880000)
#define usart11_cfg_base               (0x02890000)
#define usart1_cfg_base                (0x40A00000)
#define usart2_cfg_base                (0x02800000)
#define usart3_cfg_base                (0x02810000)
#define usart4_cfg_base                (0x02820000)
#define usart5_cfg_base                (0x02830000)
#define usart6_cfg_base                (0x02840000)
#define usart7_cfg_base                (0x02850000)
#define usart8_cfg_base                (0x02860000)
#define usart9_cfg_base                (0x02870000)
#define usb3i0_cfgr0wrap_base          (0x04104000)
#define usb3i0_cfgr1ecc0_base          (0x02A13000)
#define usb3i0_cfgr2ecc1_base          (0x02A10000)
#define usb3i0_cfgr3ctlr_base          (0x06000000)
#define usb3i0_phy2_base               (0x04108000)
#define vtm0_cfgr1_base                (0x42040000)
#define vtm0_cfgr2_base                (0x42050000)
#define vtm0_ecc_base                  (0x42810000)
#define wkupcbass0_err_base            (0x42400000)
#define wkupcbass0_fw_base             (0x45020000)
#define wkupcbass0_glb_base            (0x45B02000)
#define wkupclk0_ecc_base              (0x42410000)
#define wkupfwcbass0_err_base          (0x42404000)
#endif