/*
 *  Copyright (c) Texas Instruments Incorporated 2020 - 2022
 *  All rights reserved.
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

#include <stdlib.h>
#include <stdint.h>
#include <ti/csl/arch/r5/csl_arm_r5.h>
#include <ti/csl/arch/r5/csl_arm_r5_mpu.h>
#include <ti/csl/arch/r5/interrupt.h>
#include <ti/csl/arch/r5/csl_cache.h>

/* SafeRTOS includes */
#include "SafeRTOS_API.h"
#include <ti/osal/SafeRTOS_MPU.h>
#include "mpuARM.h"

/*
 * This structure specifies the entries for mpu configuration to override the
 * default MPU configuration which is part of the CSL init.
 */
__attribute__((section(".startupData"))) \
xMPU_CONFIG_PARAMETERS gMPUConfigParms[CSL_ARM_R5F_MPU_REGIONS_MAX] ={
    {
        /* Region 0 configuration: complete 32 bit address space = 4Gbits add one more 2gb */
        /* ulRegionNumber */
        .ulRegionNumber         = 1U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x0U,
        /* Access permission */
        {
            .ulexeNeverControl  = 1U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 0U,
            .ulcachePolicy      = 0U,
            .ulmemAttr          = 0U,
        },
        /* TODO region size is 4GB, but 2GB is largest supported */
        .ulRegionSize           = portmpuLARGEST_REGION_SIZE_ACTUAL,
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 1 configuration: 128 bytes memory for exception vector execution */
        /* ulRegionNumber */
        .ulRegionNumber         = 2U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x0U,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 1U,
            .ulcachePolicy      = CSL_ARM_R5_CACHE_POLICY_WB_WA,
            .ulmemAttr          = 0U,
        },
        /* ulRegionSize 128B */
        .ulRegionSize           = (128U),
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 2 configuration: 1MB MCU MSRAM */
        /* ulRegionNumber */
        .ulRegionNumber         = 3U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x41C00000,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 1U,
            .ulcachePolicy      = CSL_ARM_R5_CACHE_POLICY_WB_WA,
            .ulmemAttr          = 0U,
        },
        /* Size is 1MB */
        .ulRegionSize           = (1024U * 1024U),
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 3 configuration: 4 MB MCMS3 RAM */
        /* ulRegionNumber */
        .ulRegionNumber         = 4U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x70000000,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 1U,
            .ulcachePolicy      = CSL_ARM_R5_CACHE_POLICY_WB_WA,
            .ulmemAttr          = 0U,
        },
        /* Size is 4MB */
        .ulRegionSize           = (4U * 1024U * 1024U),
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 4 configuration: 2 GB DDR RAM */
        /* ulRegionNumber */
        .ulRegionNumber         = 5U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x80000000,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 1U,
            .ulcachePolicy      = CSL_ARM_R5_CACHE_POLICY_WB_WA,
            .ulmemAttr          = 0U,
        },
        /* size is 2GB */
        .ulRegionSize           = portmpuLARGEST_REGION_SIZE_ACTUAL,
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 5 configuration: 32 KB BTCM */
        /* Address of ATCM/BTCM are configured via MCU_SEC_MMR registers
           It can either be '0x0' or '0x41010000'. Application/Boot-loader shall
           take care this configurations and linker command file shall be
           in sync with this. For either of the above configurations,
           MPU configurations will not changes as both regions will have same
           set of permissions in almost all scenarios.
           Application can chose to overwrite this MPU configuration if needed.
           The same is true for the region corresponding to ATCM. */
        /* ulRegionNumber */
        .ulRegionNumber         = 6U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x41010000,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 1U,
            .ulcachePolicy      = CSL_ARM_R5_CACHE_POLICY_NON_CACHEABLE,
            .ulmemAttr          = 0U,
        },
        /* size is 32KB */
        .ulRegionSize           = (32U * 1024U),
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 6 configuration: 32 KB ATCM */
        /* ulRegionNumber */
        .ulRegionNumber         = 7U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x0,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 1U,
            .ulcachePolicy      = CSL_ARM_R5_CACHE_POLICY_NON_CACHEABLE,
            .ulmemAttr          = 0U,
        },
        /* size is 32KB */
        .ulRegionSize           = (32U * 1024U),
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 7 configuration: Covers first 64MB of EVM Flash (FSS DAT0) */
        /* ulRegionNumber */
        .ulRegionNumber         = 8U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x50000000,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 1U,
            .ulcachePolicy      = CSL_ARM_R5_CACHE_POLICY_WB_WA,
            .ulmemAttr          = 0U,
        },
        /* size is 64MB */
        .ulRegionSize           = (64U * 1024U * 1024U),
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 8 configuration: Covers last 256KB of EVM Flash (FSS DAT0) */
        /* OSPI PHY tuning algorithm which runs in DAC mode needs
         * cache to be disabled for this section of FSS data region.
         */
        /* ulRegionNumber */
        .ulRegionNumber         = 9U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x53FC0000,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 0U,
            .ulcachePolicy      = 0U,
            .ulmemAttr          = 0U,
        },
        /* size is 256KB */
        .ulRegionSize           = (256U * 1024U),
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },

};
