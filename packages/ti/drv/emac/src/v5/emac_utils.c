/**
 *  \file   emac_utils.c
 *
 *  \brief  EMAC Driver utility file.
 *
 *   This file contains helper functions internal to EMAC driver.
 */

/*
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdint.h>
#include <ti/drv/emac/emac_drv.h>
#include <ti/drv/emac/src/v5/emac_drv_v5.h>
#include <ti/drv/emac/emac_ioctl.h>


/* utility to return lower 16 bits of 32 bit crc on array of 8 bytes */
uint16_t emac_util_crc64( uint8_t input[8])
{
    int32_t i;
    uint16_t res = 0x0000;
    int32_t j;
    int32_t k=0;

    uint8_t d[64];
    uint8_t emac_next_c[64];

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            d[k] =  (input[i] & (1<<j)) ?  1 : 0;
            k+=1;
        }
    }

    emac_next_c[ 0] = d[63] ^ d[57] ^ d[54] ^ d[53] ^ d[51] ^ d[47] ^ d[39] ^ d[38] ^ d[37] ^
                      d[35] ^ d[34] ^ d[33] ^ d[32] ^ d[31] ^ d[29] ^ d[26] ^ d[19] ^ d[18] ^
                      d[16] ^ d[15] ^ d[13] ^ d[10] ^ d[ 9] ^ d[ 8] ^ d[ 5] ^ d[ 3] ^ d[ 2] ^
                      d[ 0];
    emac_next_c[ 1] = d[63] ^ d[62] ^ d[57] ^ d[56] ^ d[54] ^ d[52] ^ d[51] ^ d[50] ^ d[47] ^
                      d[46] ^ d[39] ^ d[36] ^ d[35] ^ d[30] ^ d[29] ^ d[28] ^ d[26] ^ d[25] ^
                      d[19] ^ d[17] ^ d[16] ^ d[14] ^ d[13] ^ d[12] ^ d[10] ^ d[ 7] ^ d[ 5] ^
                      d[ 4] ^ d[ 3] ^ d[ 1] ^ d[ 0];
    emac_next_c[ 2] = d[63] ^ d[62] ^ d[61] ^ d[57] ^ d[56] ^ d[55] ^ d[54] ^ d[50] ^ d[49] ^
                      d[47] ^ d[46] ^ d[45] ^ d[39] ^ d[37] ^ d[33] ^ d[32] ^ d[31] ^ d[28] ^
                      d[27] ^ d[26] ^ d[25] ^ d[24] ^ d[19] ^ d[12] ^ d[11] ^ d[10] ^ d[ 8] ^
                      d[ 6] ^ d[ 5] ^ d[ 4];
    emac_next_c[ 3] = d[62] ^ d[61] ^ d[60] ^ d[56] ^ d[55] ^ d[54] ^ d[53] ^ d[49] ^ d[48] ^
                      d[46] ^ d[45] ^ d[44] ^ d[38] ^ d[36] ^ d[32] ^ d[31] ^ d[30] ^ d[27] ^
                      d[26] ^ d[25] ^ d[24] ^ d[23] ^ d[18] ^ d[11] ^ d[10] ^ d[ 9] ^ d[ 7] ^
                      d[ 5] ^ d[ 4] ^ d[ 3];
    emac_next_c[ 4] = d[63] ^ d[61] ^ d[60] ^ d[59] ^ d[57] ^ d[55] ^ d[52] ^ d[51] ^ d[48] ^
                      d[45] ^ d[44] ^ d[43] ^ d[39] ^ d[38] ^ d[34] ^ d[33] ^ d[32] ^ d[30] ^
                      d[25] ^ d[24] ^ d[23] ^ d[22] ^ d[19] ^ d[18] ^ d[17] ^ d[16] ^ d[15] ^
                      d[13] ^ d[ 6] ^ d[ 5] ^ d[ 4] ^ d[ 0];
    emac_next_c[ 5] = d[62] ^ d[60] ^ d[59] ^ d[58] ^ d[57] ^ d[56] ^ d[53] ^ d[50] ^ d[44] ^
                      d[43] ^ d[42] ^ d[39] ^ d[35] ^ d[34] ^ d[26] ^ d[24] ^ d[23] ^ d[22] ^
                      d[21] ^ d[19] ^ d[17] ^ d[14] ^ d[13] ^ d[12] ^ d[10] ^ d[ 9] ^ d[ 8] ^
                      d[ 4] ^ d[ 2] ^ d[ 0];
    emac_next_c[ 6] = d[62] ^ d[61] ^ d[59] ^ d[58] ^ d[57] ^ d[56] ^ d[55] ^ d[52] ^ d[49] ^
                      d[43] ^ d[42] ^ d[41] ^ d[38] ^ d[34] ^ d[33] ^ d[25] ^ d[23] ^ d[22] ^
                      d[21] ^ d[20] ^ d[18] ^ d[16] ^ d[13] ^ d[12] ^ d[11] ^ d[ 9] ^ d[ 8] ^
                      d[ 7] ^ d[ 3] ^ d[ 1];
    emac_next_c[ 7] = d[63] ^ d[61] ^ d[60] ^ d[58] ^ d[56] ^ d[55] ^ d[53] ^ d[48] ^ d[47] ^
                      d[42] ^ d[41] ^ d[40] ^ d[39] ^ d[38] ^ d[35] ^ d[34] ^ d[31] ^ d[29] ^
                      d[26] ^ d[24] ^ d[22] ^ d[21] ^ d[20] ^ d[18] ^ d[17] ^ d[16] ^ d[13] ^
                      d[12] ^ d[11] ^ d[ 9] ^ d[ 7] ^ d[ 6] ^ d[ 5] ^ d[ 3];
    emac_next_c[ 8] = d[63] ^ d[62] ^ d[60] ^ d[59] ^ d[55] ^ d[53] ^ d[52] ^ d[51] ^ d[46] ^
                      d[41] ^ d[40] ^ d[35] ^ d[32] ^ d[31] ^ d[30] ^ d[29] ^ d[28] ^ d[26] ^
                      d[25] ^ d[23] ^ d[21] ^ d[20] ^ d[18] ^ d[17] ^ d[13] ^ d[12] ^ d[11] ^
                      d[ 9] ^ d[ 6] ^ d[ 4] ^ d[ 3] ^ d[ 0];
    emac_next_c[ 9] = d[62] ^ d[61] ^ d[59] ^ d[58] ^ d[54] ^ d[52] ^ d[51] ^ d[50] ^ d[45] ^
                      d[40] ^ d[39] ^ d[34] ^ d[31] ^ d[30] ^ d[29] ^ d[28] ^ d[27] ^ d[25] ^
                      d[24] ^ d[22] ^ d[20] ^ d[19] ^ d[17] ^ d[16] ^ d[12] ^ d[11] ^ d[10] ^
                      d[ 8] ^ d[ 5] ^ d[ 3] ^ d[ 2];
    emac_next_c[10] = d[63] ^ d[61] ^ d[60] ^ d[58] ^ d[54] ^ d[50] ^ d[49] ^ d[47] ^ d[44] ^
                      d[37] ^ d[35] ^ d[34] ^ d[32] ^ d[31] ^ d[30] ^ d[28] ^ d[27] ^ d[24] ^
                      d[23] ^ d[21] ^ d[13] ^ d[11] ^ d[ 8] ^ d[ 7] ^ d[ 5] ^ d[ 4] ^ d[ 3] ^
                      d[ 1] ^ d[ 0];
    emac_next_c[11] = d[63] ^ d[62] ^ d[60] ^ d[59] ^ d[54] ^ d[51] ^ d[49] ^ d[48] ^ d[47] ^
                      d[46] ^ d[43] ^ d[39] ^ d[38] ^ d[37] ^ d[36] ^ d[35] ^ d[32] ^ d[30] ^
                      d[27] ^ d[23] ^ d[22] ^ d[20] ^ d[19] ^ d[18] ^ d[16] ^ d[15] ^ d[13] ^
                      d[12] ^ d[ 9] ^ d[ 8] ^ d[ 7] ^ d[ 6] ^ d[ 5] ^ d[ 4];
    emac_next_c[12] = d[63] ^ d[62] ^ d[61] ^ d[59] ^ d[58] ^ d[57] ^ d[54] ^ d[51] ^ d[50] ^
                      d[48] ^ d[46] ^ d[45] ^ d[42] ^ d[39] ^ d[36] ^ d[33] ^ d[32] ^ d[22] ^
                      d[21] ^ d[17] ^ d[16] ^ d[14] ^ d[13] ^ d[12] ^ d[11] ^ d[10] ^ d[ 9] ^
                      d[ 7] ^ d[ 6] ^ d[ 4] ^ d[ 2] ^ d[ 0];
    emac_next_c[13] = d[61] ^ d[60] ^ d[58] ^ d[57] ^ d[56] ^ d[53] ^ d[50] ^ d[49] ^ d[47] ^
                      d[45] ^ d[44] ^ d[41] ^ d[38] ^ d[35] ^ d[32] ^ d[31] ^ d[21] ^ d[20] ^
                      d[16] ^ d[15] ^ d[13] ^ d[12] ^ d[11] ^ d[10] ^ d[ 9] ^ d[ 8] ^ d[ 6] ^
                      d[ 5] ^ d[ 3] ^ d[ 1];
    emac_next_c[14] = d[61] ^ d[60] ^ d[59] ^ d[57] ^ d[56] ^ d[55] ^ d[52] ^ d[49] ^ d[48] ^
                      d[46] ^ d[44] ^ d[43] ^ d[40] ^ d[37] ^ d[34] ^ d[31] ^ d[30] ^ d[20] ^
                      d[19] ^ d[15] ^ d[14] ^ d[12] ^ d[11] ^ d[10] ^ d[ 9] ^ d[ 8] ^ d[ 7] ^
                      d[ 5] ^ d[ 4] ^ d[ 2] ^ d[ 0];
    emac_next_c[15] = d[60] ^ d[59] ^ d[58] ^ d[56] ^ d[55] ^ d[54] ^ d[51] ^ d[48] ^ d[47] ^
                      d[45] ^ d[43] ^ d[42] ^ d[39] ^ d[36] ^ d[33] ^ d[30] ^ d[29] ^ d[19] ^
                      d[18] ^ d[14] ^ d[13] ^ d[11] ^ d[10] ^ d[ 9] ^ d[ 8] ^ d[ 7] ^ d[ 6] ^
                      d[ 4] ^ d[ 3] ^ d[ 1];

  /* assign crc_result = emac_next_c[15:0]; */
  /* so we walk the lower 16 bytes and pack into 16 bits */
    for(i=0;i<16;i++)
    {
        res |= (emac_next_c[i] ? (1<<i): 0) ;
    }
    return res;
}



/*************************************************************************************
 * \brief emac_util_fdb_helper: return broad-side slot to use for fdb entry
 *        also return the 8 bit fid to populate as part of the entry
 *
 * \param vlan_table pointer to base of vlan table.
 * \param vlan_id
 * \param mac 6 byte mac address
 * \param p_fid pointer to uint8_t where we ruturn the fid
 *
   \retval return broad-side slot to use for fdb entry
 * NOTE: only supports the 2048 entry x 4 entries/broadside slot fdb configuration
 **************************************************************************************/
uint16_t emac_util_fdb_helper(uintptr_t vlan_table, uint16_t vlan_id,  uint8_t mac[], uint8_t * p_fid)
{
    uint16_t* pTable = (uint16_t*)vlan_table;
    uint8_t input_64[8];  //64 bit input
    *p_fid = (pTable[vlan_id]&0xff00)>>8;

    /* juggle input be->le */
    input_64[0] = mac[0];
    input_64[1] = mac[1];
    input_64[2] = mac[2];
    input_64[3] = mac[3];
    input_64[4] = mac[4];
    input_64[5] = mac[5];

    input_64[6] = *p_fid;
    input_64[7] = 0x00;
    return (0x1ff&emac_util_crc64(input_64));
}

/* commands to program ICSSG R30 registers */
static uint32_t emac_R30_bitmask[EMAC_PORT_MAX_COMMANDS][EMAC_MAC_PORTS_PER_ICSS][EMAC_MAX_ICSS-1][3] =
{
    {    /* EMAC_PORT_DISABLE */
        {{0xffff0004, EMAC_NONE, EMAC_NONE}, {EMAC_NONE, 0xffff0100, 0xffff0100}},
        {{EMAC_NONE, 0xffff0100, 0xffff0100}, {0xffff0004, EMAC_NONE, EMAC_NONE}},
    },
    {   /* EMAC_PORT_BLOCK */
        {{0xfffb0040, EMAC_NONE, EMAC_NONE}, {EMAC_NONE, 0xfeff0200, 0xfeff0200}},
        {{EMAC_NONE, 0xfeff0200, 0xfeff0200}, {0xfffb0040, EMAC_NONE, EMAC_NONE}},
    },
    {   /* EMAC_PORT_FORWARD */
        {{0xffbb0000, EMAC_NONE, EMAC_NONE}, {EMAC_NONE, 0xfcff0000, 0xdcff0000}},
        {{EMAC_NONE, 0xfcff0000, 0xdcff0000}, {0xffbb0000, EMAC_NONE, EMAC_NONE}},
    },
    {   /*EMAC_PORT_FORWARD_WO_LEARNING */
        {{0xffbb0000, EMAC_NONE, EMAC_NONE}, {EMAC_NONE, 0xfcff0000, 0xfcff2000}},
        {{EMAC_NONE, 0xfcff0000, 0xfcff2000}, {0xffbb0000, EMAC_NONE, EMAC_NONE}},
    },
    {   /* ACCEPT ALL */
        {{0xffff0001, EMAC_NONE, EMAC_NONE}, {EMAC_NONE, EMAC_NONE, EMAC_NONE}},
        {{EMAC_NONE, EMAC_NONE, EMAC_NONE}, {0xffff0001, EMAC_NONE, EMAC_NONE}},
    },
    {   /* ACCEPT TAGGED */
        {{0xfffe0002, EMAC_NONE, EMAC_NONE}, {EMAC_NONE, EMAC_NONE, EMAC_NONE}},
        {{EMAC_NONE, EMAC_NONE, EMAC_NONE}, {0xfffe0002, EMAC_NONE, EMAC_NONE}},
    },
    {   /*ACCEPT UNTAGGED and PRIO */
        {{0xfffc0000, EMAC_NONE, EMAC_NONE}, {EMAC_NONE, EMAC_NONE, EMAC_NONE}},
        {{EMAC_NONE, EMAC_NONE, EMAC_NONE}, {0xfffc0000, EMAC_NONE, EMAC_NONE}},
    },
    {   /*TAS Trigger List change */
        {{ EMAC_NONE, EMAC_NONE, EMAC_NONE }, { EMAC_NONE, 0xffff0020, EMAC_NONE}},
        {{ EMAC_NONE, 0xffff0020, EMAC_NONE}, { EMAC_NONE, EMAC_NONE, EMAC_NONE }},
    },
    {   /*TAS set state ENABLE*/
        {{ EMAC_NONE, EMAC_NONE, EMAC_NONE }, { EMAC_NONE, 0xdfff1000, EMAC_NONE}},
        {{ EMAC_NONE, 0xdfff1000, EMAC_NONE}, { EMAC_NONE, EMAC_NONE, EMAC_NONE }},
    },
    {   /*TAS set state RESET*/
        {{ EMAC_NONE, EMAC_NONE, EMAC_NONE }, { EMAC_NONE, 0xefff2000, EMAC_NONE}},
        {{ EMAC_NONE, 0xefff2000, EMAC_NONE}, { EMAC_NONE, EMAC_NONE, EMAC_NONE }},
    },
    {   /*TAS set state DISABLE*/
        {{ EMAC_NONE, EMAC_NONE, EMAC_NONE }, { EMAC_NONE, 0xcfff0000, EMAC_NONE}},
        {{ EMAC_NONE, 0xcfff0000, EMAC_NONE}, { EMAC_NONE, EMAC_NONE, EMAC_NONE }},
    },
    {   /*UC flooding ENABLE*/
        {{ EMAC_NONE, EMAC_NONE, 0xffff0400}, { EMAC_NONE, EMAC_NONE, EMAC_NONE}},
        {{ EMAC_NONE, EMAC_NONE, EMAC_NONE},  { EMAC_NONE, EMAC_NONE, 0xffff0400}},
    },
    {   /*UC flooding DISABLE*/
        {{ EMAC_NONE, EMAC_NONE, 0xfbff0000}, { EMAC_NONE, EMAC_NONE, EMAC_NONE}},
        {{ EMAC_NONE, EMAC_NONE, EMAC_NONE }, { EMAC_NONE, EMAC_NONE, 0xfbff0000}},
    },
    {   /*Premption on Tx ENABLE*/
        {{ EMAC_NONE, EMAC_NONE, EMAC_NONE}, { EMAC_NONE, 0xffff4000, EMAC_NONE}},
        {{ EMAC_NONE, 0xffff4000, EMAC_NONE},  { EMAC_NONE, EMAC_NONE, EMAC_NONE}},
    },
    {   /*Premption on Tx DISABLE*/
        {{ EMAC_NONE, EMAC_NONE, EMAC_NONE}, { EMAC_NONE, 0xbfff0000, EMAC_NONE}},
        {{ EMAC_NONE, 0xbfff0000, EMAC_NONE }, { EMAC_NONE, EMAC_NONE, EMAC_NONE}},
    },
};

/* utility to return command to be sent to FW over PSI management interface */
uint32_t *emac_util_get_R30_info(EMAC_IOctlR30Cmd cmd, uint32_t port, EMAC_IcssgInstance icssg)
{
    return emac_R30_bitmask[cmd][port][icssg];
}

/* commands to program ICSSG R30 registers */
static uint32_t emac_R30_bitmask_v2[EMAC_PORT_MAX_COMMANDS][3] =
{
    { 0xffff0004, 0xffff0100, 0xffff0100 }, /* EMAC_PORT_DISABLE */
    { 0xfffb0040, 0xfeff0200, 0xfeff0200 }, /* EMAC_PORT_BLOCK */
    { 0xffbb0000, 0xfcff0000, 0xdcff0000 }, /* EMAC_PORT_FORWARD */
    { 0xffbb0000, 0xfcff0000, 0xfcff2000 }, /*EMAC_PORT_FORWARD_WO_LEARNING */
    { 0xffff0001, EMAC_NONE,  EMAC_NONE  }, /* ACCEPT ALL */
    { 0xfffe0002, EMAC_NONE,  EMAC_NONE  }, /* ACCEPT TAGGED */
    { 0xfffc0000, EMAC_NONE,  EMAC_NONE  }, /*ACCEPT UNTAGGED and PRIO */
    { EMAC_NONE,  0xffff0020, EMAC_NONE  }, /*TAS Trigger List change */
    { EMAC_NONE,  0xdfff1000, EMAC_NONE  }, /*TAS set state ENABLE*/
    { EMAC_NONE,  0xefff2000, EMAC_NONE  }, /*TAS set state RESET*/
    { EMAC_NONE,  0xcfff0000, EMAC_NONE  }, /*TAS set state DISABLE*/
    { EMAC_NONE,  EMAC_NONE,  0xffff0400 }, /*UC flooding ENABLE*/
    { EMAC_NONE,  EMAC_NONE,  0xfbff0000 }, /*UC flooding DISABLE*/
    { EMAC_NONE,  0xffff4000, EMAC_NONE  }, /*Premption on Tx ENABLE*/
    { EMAC_NONE,  0xbfff0000, EMAC_NONE  }, /*Premption on Tx DISABLE*/
};

uint32_t *emac_util_get_R30_info_v2(EMAC_IOctlR30Cmd cmd)
{
    return emac_R30_bitmask_v2[cmd];
}

/*
 *  ======== emac_hw_mem_write ========
 */
void emac_hw_mem_write(uint32_t addr, const void *ptr, uint32_t element_count)
{
    uint32_t  i;
    volatile uint32_t *dst = (volatile uint32_t *)(uintptr_t)addr;
    uint32_t *src = (uint32_t *)ptr;
    for (i = 0; i < element_count; i++)
    {
        *dst++ = *src++;
    }
}

