/*
 *  Copyright (C) 2021-2022 Texas Instruments Incorporated
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

/**
 *  \file   SafeRTOS_mpu_r5f.c
 *
 *  \brief The file implements the safertos R5F MPU configuration.
 * 
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* Generic headers */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <ti/osal/SafeRTOS_MPU.h>

/* SafeRTOS includes */
#include "SafeRTOS_API.h"
#include "mpuARM.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

__attribute__((section(".startupCode"))) \
static portUInt32Type xConfigureMPUAccessCtrl(xMPU_CONFIG_ACCESS *xMPUconfigAccess);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/**
 * \brief  TEX[2:0], C and B values.
 *         CSL_ArmR5MemAttr is used as intex here.
 *         gMemAttr[x][0]: TEX[2:0] values
 *         gMemAttr[x][1]: C bit value
 *         gMemAttr[x][2]: B bit value
 */
__attribute__((section(".startupData"))) \
static uint32_t gMemAttr[(portUInt32Type)CSL_ARM_R5_MEM_ATTR_MAX][3U] =
{
/*    TEX[2:0], C,     B bits */
    {   0x0U,   0x0U,  0x0U,}, /* Strongly-ordered.*/
    {   0x0U,   0x0U,  0x1U,}, /* Shareable Device.*/
    {   0x0U,   0x1U,  0x0U,}, /* Outer and Inner write-through, no write-allocate. */
    {   0x0U,   0x1U,  0x1U,}, /* Outer and Inner write-back, no write-allocate. */
    {   0x1U,   0x0U,  0x0U,}, /* Outer and Inner Non-cacheable. */
    {   0x1U,   0x1U,  0x1U,}, /* Outer and Inner write-back, write-allocate.*/
    {   0x2U,   0x0U,  0x0U,}, /* Non-shareable Device.*/
};

__attribute__((section(".startupData"))) __attribute__((weak)) \
xMPU_CONFIG_PARAMETERS  gMPUConfigParms[CSL_ARM_R5F_MPU_REGIONS_MAX] =
{
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
        /* Region 0 configuration: second half of 2 GB */
        /* ulRegionNumber */
        .ulRegionNumber         = 2U,
        /* Starting address */
        .ulRegionBeginAddress   = portmpuLARGEST_REGION_SIZE_ACTUAL,
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
        .ulRegionNumber         = 3U,
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
        /* ulRegionSize */
        .ulRegionSize           = 128U,
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 2 configuration: 1MB MCU MSRAM */
        /* ulRegionNumber */
        .ulRegionNumber         = 4U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x41C00000U,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 1U,
            .ulcachePolicy      = CSL_ARM_R5_CACHE_POLICY_WB_WA,
            .ulmemAttr          = 0U,
        },
        /* Size is 512KB */

#if defined (SOC_J721E) || defined (SOC_J7200) || defined (SOC_J721S2) || defined (SOC_J784S4)
        /* Size is 1MB */
        .ulRegionSize           = (1024U * 1024U),
#else
        .ulRegionSize           = (512U * 1024U),
#endif
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 3 configuration: MCMS3 RAM */
        /* ulRegionNumber */
        .ulRegionNumber         = 5U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x70000000U,
        /* Access permission */
        {
            .ulexeNeverControl  = 0U,
            .ulaccessPermission = CSL_ARM_R5_ACC_PERM_PRIV_USR_RD_WR,
            .ulshareable        = 0U,
            .ulcacheable        = 1U,
            .ulcachePolicy      = CSL_ARM_R5_CACHE_POLICY_WB_WA,
            .ulmemAttr          = 0U,
        },
#if defined (SOC_J721E) || defined (SOC_J784S4)
        /* Size is 8MB */
        .ulRegionSize           = (8U * 1024U * 1024U),
#endif
#if defined (SOC_J7200)
        /* Size is 1MB */
        .ulRegionSize           = (1U * 1024U * 1024U),
#endif
#if defined (SOC_J721S2) 
        /* Size is 4MB */
        .ulRegionSize           = (4U * 1024U * 1024U),
#endif
        /* ulSubRegionDisable */
        .ulSubRegionDisable     = mpuREGION_ALL_SUB_REGIONS_ENABLED,
    },
    {
        /* Region 4 configuration: 2 GB DDR RAM */
        /* ulRegionNumber */
        .ulRegionNumber         = 6U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x80000000U,
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
        .ulRegionNumber         = 7U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x41010000U,
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
        .ulRegionNumber         = 8U,
        /* Starting address */
        .ulRegionBeginAddress   = 0x0U,
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
      0U
    },
    {
      0U
    },
    {
      0U
    },
    {
      0U
    },
    {
      0U
    },
    {
      0U
    },
    {
      0U
    },
    {
      0U
    }  
};

/* ========================================================================== */
/*                          Function Defintions                               */
/* ========================================================================== */

__attribute__((section(".startupCode"))) portBaseType xConfigureMPU(void)
{
    portBaseType            xInitMpuResult = pdPASS;
    xMPU_CONFIG_PARAMETERS *xMPUconfig;
    xMPU_CONFIG_ACCESS     *xMPUconfigAccess;
    portUInt32Type          ulRegionAccess;
    uint32_t                loopCnt;

    /* Configure MPU regions only for provided configuration */
    for(loopCnt = 0; loopCnt < CSL_ARM_R5F_MPU_REGIONS_MAX; loopCnt++)
    {
        /* Check if the region is enabled */
        if (CSL_ARM_R5_MPU_REGION_SIZE_32BYTE <= gMPUConfigParms[loopCnt].ulRegionSize)
        {
            ulRegionAccess = 0;
            xMPUconfig = &gMPUConfigParms[loopCnt];

            /* Update access control */
            xMPUconfigAccess = &xMPUconfig->xRegionAccess;

            ulRegionAccess = xConfigureMPUAccessCtrl(xMPUconfigAccess);

            xInitMpuResult = xMPUConfigureGlobalRegion(
                    xMPUconfig->ulRegionNumber,
                    xMPUconfig->ulRegionBeginAddress,
                    ulRegionAccess,
                    xMPUconfig->ulRegionSize,
                    xMPUconfig->ulSubRegionDisable
                    );
            if(pdPASS != xInitMpuResult)
            {
                break;
            }
        }
    }

    return xInitMpuResult;
}

/*---------------------------------------------------------------------------*/

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

__attribute__((section(".startupCode")))  \
static portUInt32Type xConfigureMPUAccessCtrl(xMPU_CONFIG_ACCESS *xMPUconfigAccess)
{
    portUInt32Type accessCtrlRegVal = 0, tex;

    accessCtrlRegVal |= ( xMPUconfigAccess->ulexeNeverControl <<
                           CSL_ARM_R5_MPU_REGION_AC_XN_SHIFT);
    accessCtrlRegVal |= ( xMPUconfigAccess->ulaccessPermission <<
                           CSL_ARM_R5_MPU_REGION_AC_AP_SHIFT);
    accessCtrlRegVal |= ( xMPUconfigAccess->ulshareable <<
                           CSL_ARM_R5_MPU_REGION_AC_S_SHIFT);
    if (1U == xMPUconfigAccess->ulcacheable)
    {
        tex = (1U << 2U);
        tex |= (xMPUconfigAccess->ulcachePolicy);
        accessCtrlRegVal |=
                        ( tex << CSL_ARM_R5_MPU_REGION_AC_TEX_SHIFT);
        accessCtrlRegVal |= ( xMPUconfigAccess->ulcachePolicy <<
                           CSL_ARM_R5_MPU_REGION_AC_CB_SHIFT);
    }
    else
    {
        tex = gMemAttr[xMPUconfigAccess->ulmemAttr][0U];
        accessCtrlRegVal |=
                        ( tex << CSL_ARM_R5_MPU_REGION_AC_TEX_SHIFT);
        accessCtrlRegVal |=
                        ( (portUInt32Type)gMemAttr[(portUInt32Type)xMPUconfigAccess->ulmemAttr][1UL] <<
                        ((portUInt32Type)CSL_ARM_R5_MPU_REGION_AC_B_SHIFT));
        accessCtrlRegVal |=
                        ( (portUInt32Type)gMemAttr[(portUInt32Type)xMPUconfigAccess->ulmemAttr][2UL] <<
                        ((portUInt32Type)CSL_ARM_R5_MPU_REGION_AC_C_SHIFT));
    }
    return accessCtrlRegVal;
}

/*---------------------------------------------------------------------------*/
