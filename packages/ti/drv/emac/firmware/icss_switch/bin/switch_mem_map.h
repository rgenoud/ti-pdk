/*
 * switch_mem_map.h
 *
 * Contains memory map for Ethernet Switch.
 * This file is used by Ethernet Switch driver.
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/
 *
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
#ifndef ____switch_mem_map_h
#define ____switch_mem_map_h 1

#include "switch_mmap_defines.h"

/*
 *
 * Memory Usage of : SHARED_MEMORY
 *
 */

/*default VLAN tag for Host Port*/
#define HOST_PORT_DF_VLAN_OFFSET                           0x0018
/*Same as HOST_PORT_DF_VLAN_OFFSET*/
#define EMAC_ICSSG_SWITCH_PORT0_DEFAULT_VLAN_OFFSET        HOST_PORT_DF_VLAN_OFFSET
/*default VLAN tag for P1 Port*/
#define P1_PORT_DF_VLAN_OFFSET                             0x001C
/*Same as P1_PORT_DF_VLAN_OFFSET*/
#define EMAC_ICSSG_SWITCH_PORT1_DEFAULT_VLAN_OFFSET        P1_PORT_DF_VLAN_OFFSET
/*default VLAN tag for P2 Port*/
#define P2_PORT_DF_VLAN_OFFSET                             0x0020
/*Same as P2_PORT_DF_VLAN_OFFSET*/
#define EMAC_ICSSG_SWITCH_PORT2_DEFAULT_VLAN_OFFSET        P2_PORT_DF_VLAN_OFFSET
/*VLAN-FID Table offset. 4096 VIDs. 2B per VID = 8KB = 0x2000*/
#define VLAN_STATIC_REG_TABLE_OFFSET                       0x0100
/*VLAN-FID Table offset for EMAC*/
#define EMAC_ICSSG_SWITCH_DEFAULT_VLAN_TABLE_OFFSET        VLAN_STATIC_REG_TABLE_OFFSET
/*packet descriptor Q reserved memory*/
#define PORT_DESC0_HI                                      0x2104
/*packet descriptor Q reserved memory*/
#define PORT_DESC0_LO                                      0x2F6C
/*packet descriptor Q reserved memory*/
#define PORT_DESC1_HI                                      0x3DD4
/*packet descriptor Q reserved memory*/
#define PORT_DESC1_LO                                      0x4C3C
/*packet descriptor Q reserved memory*/
#define HOST_DESC0_HI                                      0x5AA4
/*packet descriptor Q reserved memory*/
#define HOST_DESC0_LO                                      0x5F0C
/*packet descriptor Q reserved memory*/
#define HOST_DESC1_HI                                      0x6374
/*packet descriptor Q reserved memory*/
#define HOST_DESC1_LO                                      0x67DC
/*special packet descriptor Q reserved memory*/
#define HOST_SPPD0                                         0x7AAC
/*special packet descriptor Q reserved memory*/
#define HOST_SPPD1                                         0x7EAC

/*
 *
 * Memory Usage of : MSMC
 *
 */


/*
 *
 * Memory Usage of : DMEM0
 *
 */

/*New list is copied at this time*/
#define TAS_CONFIG_CHANGE_TIME                             0x000C
/*config change error counter*/
#define TAS_CONFIG_CHANGE_ERROR_COUNTER                    0x0014
/*TAS List update pending flag*/
#define TAS_CONFIG_PENDING                                 0x0018
/*TAS list update trigger flag*/
#define TAS_CONFIG_CHANGE                                  0x0019
/*List length for new TAS schedule*/
#define TAS_ADMIN_LIST_LENGTH                              0x001A
/*Currently active TAS list index*/
#define TAS_ACTIVE_LIST_INDEX                              0x001B
/*Cycle time for the new TAS schedule*/
#define TAS_ADMIN_CYCLE_TIME                               0x001C
/*Cycle counts remaining till the TAS list update*/
#define TAS_CONFIG_CHANGE_CYCLE_COUNT                      0x0020
/*Base Flow ID for sending packets to Host for Slice0*/
#define PSI_L_REGULAR_FLOW_ID_BASE_OFFSET                  0x0024
/*Same as PSI_L_REGULAR_FLOW_ID_BASE_OFFSET*/
#define EMAC_ICSSG_SWITCH_PSI_L_REGULAR_FLOW_ID_BASE_OFFSET PSI_L_REGULAR_FLOW_ID_BASE_OFFSET
/*Base Flow ID for sending mgmt and Tx TS to Host for Slice0*/
#define PSI_L_MGMT_FLOW_ID_OFFSET                          0x0026
/*Same as PSI_L_MGMT_FLOW_ID_OFFSET*/
#define EMAC_ICSSG_SWITCH_PSI_L_MGMT_FLOW_ID_BASE_OFFSET   PSI_L_MGMT_FLOW_ID_OFFSET
/*Queue number for Special packets written here*/
#define SPL_PKT_DEFAULT_PRIORITY                           0x0028
/*Express Preemptible Queue Mask*/
#define EXPRESS_PRE_EMPTIVE_Q_MASK                         0x0029
/*Port1/Port2 Default Queue number for untagged packets, only 1B is used*/
#define QUEUE_NUM_UNTAGGED                                 0x002A
/*Stores the table used for priority regeneration. 1B per PCP/Queue*/
#define PORT_Q_PRIORITY_REGEN_OFFSET                       0x002C
/*For marking packet as priority/express (this feature is disabled) or cut-through/S&F. One per slice*/
#define EXPRESS_PRE_EMPTIVE_Q_MAP                          0x0034
/*Stores the table used for priority mapping. 1B per PCP/Queue*/
#define PORT_Q_PRIORITY_MAPPING_OFFSET                     0x003C
/*Set clock descriptor*/
#define TIMESYNC_FW_SETCLOCK_DESC_OFFSET                   0x0088
/*Control variable to generate SYNC1*/
#define TIMESYNC_FW_WC_ISOM_SIG_EN_OFFSET                  0x00CC
/*SystemTime Sync0 periodicity*/
#define TIMESYNC_FW_ST_SYNCOUT_PERIOD_OFFSET               0x00D0
/*IEP count hi roll over count*/
#define TIMESYNC_FW_HI_ROLLOVER_COUNT_OFFSET               0x00D4
/*TAS gate mask for windows list0*/
#define TAS_GATE_MASK_LIST0                                0x0100
/*TAS gate mask for windows list1*/
#define TAS_GATE_MASK_LIST1                                0x0350
/*Memory to Enable/Disable Preemption on TX side*/
#define PRE_EMPTION_ENABLE_TX                              0x05A0
/*Active State of Preemption on TX side*/
#define PRE_EMPTION_ACTIVE_TX                              0x05A1
/*Memory to Enable/Disable Verify State Machine Preemption*/
#define PRE_EMPTION_ENABLE_VERIFY                          0x05A2
/*Verify Status of State Machine*/
#define PRE_EMPTION_VERIFY_STATUS                          0x05A3
/*Non Final Fragment Size supported by Link Partner*/
#define PRE_EMPTION_ADD_FRAG_SIZE_REMOTE                   0x05A4
/*Non Final Fragment Size supported by Firmware*/
#define PRE_EMPTION_ADD_FRAG_SIZE_LOCAL                    0x05A6
/*Time in ms the State machine waits for respond packet*/
#define PRE_EMPTION_VERIFY_TIME                            0x05A8
/*HW Buffer Pool0 base address*/
#define BUFFER_POOL_0_ADDR_OFFSET                          0x05AC
/*16B for Host Egress MSMC Q (Pre-emptible) context*/
#define HOST_RX_Q_PRE_CONTEXT_OFFSET                       0x0674
/*_Small_Description_*/
#define TIMESYNC_FW_COUNT_HI_SW_OFFSET_OFFSET              0x0884
/*_Small_Description_*/
#define TIMESYNC_FW_CYCLECOUNT_OFFSET                      0x0888
/*_Small_Description_*/
#define TIMESYNC_FW_WC_SYNCOUT_REDUCTION_OFFSET            0x0890

/*
 *
 * Memory Usage of : DMEM1
 *
 */

/*Time after which FDB entries are checked for aged out values. Value in nanoseconds*/
#define FDB_AGEING_TIMEOUT_OFFSET                          0x00A0

/*
 *
 * Memory Usage of : PA_STAT
 *
 */

/*Start of 32 bits PA_STAT counters*/
#define PA_STAT_32b_START_OFFSET                           0x0080


#endif /* ____switch_mem_map_h*/
