//***********************************************************************************
//**+-----------------------------------------------------------------------------+**
//**|                              ******                                         |**
//**|                              ******     o                                   |**
//**|                              *******__////__****                            |**
//**|                              ***** /_ //___/ ***                            |**
//**|                           ********* ////__ ******                           |**
//**|                             *******(_____/ ******                           |**
//**|                                 **********                                  |**
//**|                                   ******                                    |**
//**|                                      ***                                    |**
//**|                                                                             |**
//**|            Copyright (c) 2019 Texas Instruments Incorporated                |**
//**|                           ALL RIGHTS RESERVED                               |**
//**|                                                                             |**
//**|    Permission is hereby granted to licensees of Texas Instruments           |**
//**|    Incorporated (TI) products to use this computer program for the sole     |**
//**|    purpose of implementing a licensee product based on TI products.         |**
//**|    No other rights to reproduce, use, or disseminate this computer          |**
//**|    program, whether in part or in whole, are granted.                       |**
//**|                                                                             |**
//**|    TI makes no representation or warranties with respect to the             |**
//**|    performance of this computer program, and specifically disclaims         |**
//**|    any responsibility for any damages, special or consequential,            |**
//**|    connected with the use of this program.                                  |**
//**|                                                                             |**
//**+-----------------------------------------------------------------------------+**
//***********************************************************************************
// file:     switch_mem_map.h
//
// brief:    Contains memory map for Ethernet Switch.
//           This file is shared by firmware and driver.

#ifndef ____switch_mem_map_h
#define ____switch_mem_map_h 1

#include "switch_mmap_defines.h"

//************************************************************************************
//
// Memory Usage of : SHARED_MEMORY
//
//************************************************************************************

#define SHARED_MEMORY_START_OFFSET                         0x0000
#define PRE_EMPTION_CONTEXT_OFFSET                         0x0000    //Backup of active Tx and Q context. The offset is not used
#define PRE_EMPTION_CONTEXT_OFFSET_SIZE                    0x8
#define FW_HOST_HANDSHAKE_MAGIC_VAL_OFFSET                 0x0008    //Firmware host handshake
#define FW_HOST_HANDSHAKE_MAGIC_VAL_OFFSET_SIZE            0x4
#define PSI_L_REGULAR_FLOW_ID_BASE_SLICE0_OFFSET           0x000C    //Base Flow ID for sending packets to Host for Slice0
#define PSI_L_REGULAR_FLOW_ID_BASE_SLICE0_OFFSET_SIZE      0x2
#define EMAC_ICSSG_SWITCH_PSI_L_REGULAR_FLOW_ID_BASE_OFFSET PSI_L_REGULAR_FLOW_ID_BASE_SLICE0_OFFSET    //Same as PSI_L_REGULAR_FLOW_ID_BASE_SLICE0_OFFSET
#define PSI_L_MGMT_FLOW_ID_SLICE0_OFFSET                   0x000E    //Base Flow ID for sending mgmt and Tx TS to Host for Slice0
#define PSI_L_MGMT_FLOW_ID_SLICE0_OFFSET_SIZE              0x2
#define EMAC_ICSSG_SWITCH_PSI_L_MGMT_FLOW_ID_BASE_OFFSET   PSI_L_MGMT_FLOW_ID_SLICE0_OFFSET    //Same as PSI_L_MGMT_FLOW_ID_SLICE0_OFFSET
#define PSI_L_REGULAR_FLOW_ID_BASE_SLICE1_OFFSET           0x0010    //Base Flow ID for sending packets to Host for Slice1
#define PSI_L_REGULAR_FLOW_ID_BASE_SLICE1_OFFSET_SIZE      0x2
#define PSI_L_MGMT_FLOW_ID_SLICE1_OFFSET                   0x0012    //Base Flow ID for sending mgmt and Tx TS to Host for Slice1
#define PSI_L_MGMT_FLOW_ID_SLICE1_OFFSET_SIZE              0x2
#define SPL_PKT_DEFAULT_PRIORITY                           0x0014    //Queue number for Special packets written here. Only 1B is used
#define SPL_PKT_DEFAULT_PRIORITY_SIZE                      0x4
#define FDB_SA_MAC_ADDRESS                                 0x0018    //Used internally by FW for learning
#define FDB_SA_MAC_ADDRESS_SIZE                            0x8
#define FDB_FID_FIDC2_OFFSET                               0x0020    //Used internally by FW for learning
#define FDB_FID_FIDC2_OFFSET_SIZE                          0x4
#define FDB_BUCKET_OFFSET                                  0x0024    //Used internally by FW for learning
#define FDB_BUCKET_OFFSET_SIZE                             0x4
#define FDB_AGEING_LAST_USED_OFFSET                        0x0028    //Used internally by FW for learning
#define FDB_AGEING_LAST_USED_OFFSET_SIZE                   0x4
#define TX_TS_COOKIE0_OFFSET                               0x002C    //Used internally by FW to store Tx timestamp slice0
#define TX_TS_COOKIE0_OFFSET_SIZE                          0x4
#define TX_TS_SPARE0_OFFSET                                0x0030    //not used
#define TX_TS_SPARE0_OFFSET_SIZE                           0x4
#define TX_TS_COOKIE1_OFFSET                               0x0034    //Used internally by FW to stash cookie slice1
#define TX_TS_COOKIE1_OFFSET_SIZE                          0x4
#define HOST_PORT_DF_VLAN_OFFSET                           0x0038    //default VLAN tag for Host Port
#define HOST_PORT_DF_VLAN_OFFSET_SIZE                      0x4
#define EMAC_ICSSG_SWITCH_PORT0_DEFAULT_VLAN_OFFSET        HOST_PORT_DF_VLAN_OFFSET    //Same as HOST_PORT_DF_VLAN_OFFSET
#define P1_PORT_DF_VLAN_OFFSET                             0x003C    //default VLAN tag for P1 Port
#define P1_PORT_DF_VLAN_OFFSET_SIZE                        0x4
#define EMAC_ICSSG_SWITCH_PORT1_DEFAULT_VLAN_OFFSET        P1_PORT_DF_VLAN_OFFSET    //Same as P1_PORT_DF_VLAN_OFFSET
#define P2_PORT_DF_VLAN_OFFSET                             0x0040    //default VLAN tag for P2 Port
#define P2_PORT_DF_VLAN_OFFSET_SIZE                        0x4
#define EMAC_ICSSG_SWITCH_PORT2_DEFAULT_VLAN_OFFSET        P2_PORT_DF_VLAN_OFFSET    //Same as P2_PORT_DF_VLAN_OFFSET
#define RX_TS_STASHED_SLICE0                               0x0044    //Used internally by FW for stashed Rx timestamp
#define RX_TS_STASHED_SLICE0_SIZE                          0x8
#define RX_TS_STASHED_SLICE1                               0x004C    //Used internally by FW for stashed Rx timestamp
#define RX_TS_STASHED_SLICE1_SIZE                          0x8
#define MGR_CMD_OFFSET                                     0x0054    //Management command from Host to RTU0
#define MGR_CMD_OFFSET_SIZE                                0x20
#define MGR_CMD_RET                                        0x0074    //Management reply to Host from RTU0
#define MGR_CMD_RET_SIZE                                   0xc
#define MGR_CMD_STATE                                      0x0080    //0 - idle; 1 - todo; 2 - executing
#define MGR_CMD_STATE_SIZE                                 0x1
//Padding of 3 bytes
#define MGR_CMD_PRU0_STATUS                                0x0084    //Used internally by FW to communicate from RTU0 to PRU0
#define MGR_CMD_PRU0_STATUS_SIZE                           0x2
#define MGR_CMD_PRU1_STATUS                                0x0086    //Used internally by FW to communicate from RTU0 to PRU1
#define MGR_CMD_PRU1_STATUS_SIZE                           0x2
#define MGR_CMD_RTU0_STATUS                                0x0088    //Used internally by FW to communicate from RTU0 to RTU0
#define MGR_CMD_RTU0_STATUS_SIZE                           0x2
#define MGR_CMD_RTU1_STATUS                                0x008A    //Used internally by FW to for management state machine
#define MGR_CMD_RTU1_STATUS_SIZE                           0x42
#define MGR_CMD_END_OFFSET                                 0x00CC    //End of Management command region
#define P1_QUEUE_NUM_UNTAGGED                              0x00CC    //Port1 Default Queue number for untagged packets
#define P1_QUEUE_NUM_UNTAGGED_SIZE                         0x1
#define P2_QUEUE_NUM_UNTAGGED                              0x00CD    //Port2 Default Queue number for untagged packets
#define P2_QUEUE_NUM_UNTAGGED_SIZE                         0x1
#define BUFFER_POOL_0_ADDR_SLICE0_OFFSET                   0x0100    //HW Buffer Pool0 base address Slice0
#define BUFFER_POOL_0_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_0_LEN_SLICE0_OFFSET                    0x0104    //HW Buffer Pool0 length Slice0
#define BUFFER_POOL_0_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_1_ADDR_SLICE0_OFFSET                   0x0108    //HW Buffer Pool1 base address Slice0
#define BUFFER_POOL_1_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_1_LEN_SLICE0_OFFSET                    0x010C    //HW Buffer Pool1 length Slice0
#define BUFFER_POOL_1_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_2_ADDR_SLICE0_OFFSET                   0x0110    //HW Buffer Pool2 base address Slice0
#define BUFFER_POOL_2_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_2_LEN_SLICE0_OFFSET                    0x0114    //HW Buffer Pool2 length Slice0
#define BUFFER_POOL_2_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_3_ADDR_SLICE0_OFFSET                   0x0118    //HW Buffer Pool3 base address Slice0
#define BUFFER_POOL_3_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_3_LEN_SLICE0_OFFSET                    0x011C    //HW Buffer Pool3 length Slice0
#define BUFFER_POOL_3_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_4_ADDR_SLICE0_OFFSET                   0x0120    //HW Buffer Pool4 base address Slice0
#define BUFFER_POOL_4_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_4_LEN_SLICE0_OFFSET                    0x0124    //HW Buffer Pool4 length Slice0
#define BUFFER_POOL_4_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_5_ADDR_SLICE0_OFFSET                   0x0128    //HW Buffer Pool5 base address Slice0
#define BUFFER_POOL_5_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_5_LEN_SLICE0_OFFSET                    0x012C    //HW Buffer Pool5 length Slice0
#define BUFFER_POOL_5_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_6_ADDR_SLICE0_OFFSET                   0x0130    //HW Buffer Pool6 base address Slice0
#define BUFFER_POOL_6_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_6_LEN_SLICE0_OFFSET                    0x0134    //HW Buffer Pool6 length Slice0
#define BUFFER_POOL_6_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_7_ADDR_SLICE0_OFFSET                   0x0138    //HW Buffer Pool7 base address Slice0
#define BUFFER_POOL_7_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_7_LEN_SLICE0_OFFSET                    0x013C    //HW Buffer Pool7 length Slice0
#define BUFFER_POOL_7_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_8_ADDR_SLICE0_OFFSET                   0x0140    //HW Buffer Pool8 base address Slice0
#define BUFFER_POOL_8_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_8_LEN_SLICE0_OFFSET                    0x0144    //HW Buffer Pool8 length Slice0
#define BUFFER_POOL_8_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_9_ADDR_SLICE0_OFFSET                   0x0148    //HW Buffer Pool9 base address Slice0
#define BUFFER_POOL_9_ADDR_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_9_LEN_SLICE0_OFFSET                    0x014C    //HW Buffer Pool9 length Slice0
#define BUFFER_POOL_9_LEN_SLICE0_OFFSET_SIZE               0x4
#define BUFFER_POOL_10_ADDR_SLICE0_OFFSET                  0x0150    //HW Buffer Pool10 base address Slice0
#define BUFFER_POOL_10_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_10_LEN_SLICE0_OFFSET                   0x0154    //HW Buffer Pool10 length Slice0
#define BUFFER_POOL_10_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_11_ADDR_SLICE0_OFFSET                  0x0158    //HW Buffer Pool11 base address Slice0
#define BUFFER_POOL_11_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_11_LEN_SLICE0_OFFSET                   0x015C    //HW Buffer Pool11 length Slice0
#define BUFFER_POOL_11_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_12_ADDR_SLICE0_OFFSET                  0x0160    //HW Buffer Pool12 base address Slice0
#define BUFFER_POOL_12_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_12_LEN_SLICE0_OFFSET                   0x0164    //HW Buffer Pool12 length Slice0
#define BUFFER_POOL_12_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_13_ADDR_SLICE0_OFFSET                  0x0168    //HW Buffer Pool13 base address Slice0
#define BUFFER_POOL_13_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_13_LEN_SLICE0_OFFSET                   0x016C    //HW Buffer Pool13 length Slice0
#define BUFFER_POOL_13_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_14_ADDR_SLICE0_OFFSET                  0x0170    //HW Buffer Pool14 base address Slice0
#define BUFFER_POOL_14_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_14_LEN_SLICE0_OFFSET                   0x0174    //HW Buffer Pool14 length Slice0
#define BUFFER_POOL_14_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_15_ADDR_SLICE0_OFFSET                  0x0178    //HW Buffer Pool15 base address Slice0
#define BUFFER_POOL_15_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_15_LEN_SLICE0_OFFSET                   0x017C    //HW Buffer Pool15 length Slice0
#define BUFFER_POOL_15_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_16_ADDR_SLICE0_OFFSET                  0x0180    //HW Buffer Pool16 base address Slice0
#define BUFFER_POOL_16_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_16_LEN_SLICE0_OFFSET                   0x0184    //HW Buffer Pool16 length Slice0
#define BUFFER_POOL_16_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_17_ADDR_SLICE0_OFFSET                  0x0188    //HW Buffer Pool17 base address Slice0
#define BUFFER_POOL_17_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_17_LEN_SLICE0_OFFSET                   0x018C    //HW Buffer Pool17 length Slice0
#define BUFFER_POOL_17_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_18_ADDR_SLICE0_OFFSET                  0x0190    //HW Buffer Pool18 base address Slice0
#define BUFFER_POOL_18_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_18_LEN_SLICE0_OFFSET                   0x0194    //HW Buffer Pool18 length Slice0
#define BUFFER_POOL_18_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_19_ADDR_SLICE0_OFFSET                  0x0198    //HW Buffer Pool19 base address Slice0
#define BUFFER_POOL_19_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_19_LEN_SLICE0_OFFSET                   0x019C    //HW Buffer Pool19 length Slice0
#define BUFFER_POOL_19_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_20_ADDR_SLICE0_OFFSET                  0x01A0    //HW Buffer Pool20 base address Slice0
#define BUFFER_POOL_20_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_20_LEN_SLICE0_OFFSET                   0x01A4    //HW Buffer Pool20 length Slice0
#define BUFFER_POOL_20_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_21_ADDR_SLICE0_OFFSET                  0x01A8    //HW Buffer Pool21 base address Slice0
#define BUFFER_POOL_21_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_21_LEN_SLICE0_OFFSET                   0x01AC    //HW Buffer Pool21 length Slice0
#define BUFFER_POOL_21_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_22_ADDR_SLICE0_OFFSET                  0x01B0    //HW Buffer Pool22 base address Slice0
#define BUFFER_POOL_22_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_22_LEN_SLICE0_OFFSET                   0x01B4    //HW Buffer Pool22 length Slice0
#define BUFFER_POOL_22_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_23_ADDR_SLICE0_OFFSET                  0x01B8    //HW Buffer Pool23 base address Slice0
#define BUFFER_POOL_23_ADDR_SLICE0_OFFSET_SIZE             0x4
#define BUFFER_POOL_23_LEN_SLICE0_OFFSET                   0x01BC    //HW Buffer Pool23 length Slice0
#define BUFFER_POOL_23_LEN_SLICE0_OFFSET_SIZE              0x4
#define BUFFER_POOL_0_ADDR_SLICE1_OFFSET                   0x01C0    //HW Buffer Pool0 base address Slice0
#define BUFFER_POOL_0_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_0_LEN_SLICE1_OFFSET                    0x01C4    //HW Buffer Pool0 length Slice0
#define BUFFER_POOL_0_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_1_ADDR_SLICE1_OFFSET                   0x01C8    //HW Buffer Pool1 base address Slice0
#define BUFFER_POOL_1_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_1_LEN_SLICE1_OFFSET                    0x01CC    //HW Buffer Pool1 length Slice0
#define BUFFER_POOL_1_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_2_ADDR_SLICE1_OFFSET                   0x01D0    //HW Buffer Pool2 base address Slice0
#define BUFFER_POOL_2_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_2_LEN_SLICE1_OFFSET                    0x01D4    //HW Buffer Pool2 length Slice0
#define BUFFER_POOL_2_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_3_ADDR_SLICE1_OFFSET                   0x01D8    //HW Buffer Pool3 base address Slice0
#define BUFFER_POOL_3_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_3_LEN_SLICE1_OFFSET                    0x01DC    //HW Buffer Pool3 length Slice0
#define BUFFER_POOL_3_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_4_ADDR_SLICE1_OFFSET                   0x01E0    //HW Buffer Pool4 base address Slice0
#define BUFFER_POOL_4_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_4_LEN_SLICE1_OFFSET                    0x01E4    //HW Buffer Pool4 length Slice0
#define BUFFER_POOL_4_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_5_ADDR_SLICE1_OFFSET                   0x01E8    //HW Buffer Pool5 base address Slice0
#define BUFFER_POOL_5_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_5_LEN_SLICE1_OFFSET                    0x01EC    //HW Buffer Pool5 length Slice0
#define BUFFER_POOL_5_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_6_ADDR_SLICE1_OFFSET                   0x01F0    //HW Buffer Pool6 base address Slice0
#define BUFFER_POOL_6_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_6_LEN_SLICE1_OFFSET                    0x01F4    //HW Buffer Pool6 length Slice0
#define BUFFER_POOL_6_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_7_ADDR_SLICE1_OFFSET                   0x01F8    //HW Buffer Pool7 base address Slice0
#define BUFFER_POOL_7_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_7_LEN_SLICE1_OFFSET                    0x01FC    //HW Buffer Pool7 length Slice0
#define BUFFER_POOL_7_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_8_ADDR_SLICE1_OFFSET                   0x0200    //HW Buffer Pool8 base address Slice0
#define BUFFER_POOL_8_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_8_LEN_SLICE1_OFFSET                    0x0204    //HW Buffer Pool8 length Slice0
#define BUFFER_POOL_8_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_9_ADDR_SLICE1_OFFSET                   0x0208    //HW Buffer Pool9 base address Slice0
#define BUFFER_POOL_9_ADDR_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_9_LEN_SLICE1_OFFSET                    0x020C    //HW Buffer Pool9 length Slice0
#define BUFFER_POOL_9_LEN_SLICE1_OFFSET_SIZE               0x4
#define BUFFER_POOL_10_ADDR_SLICE1_OFFSET                  0x0210    //HW Buffer Pool10 base address Slice0
#define BUFFER_POOL_10_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_10_LEN_SLICE1_OFFSET                   0x0214    //HW Buffer Pool10 length Slice0
#define BUFFER_POOL_10_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_11_ADDR_SLICE1_OFFSET                  0x0218    //HW Buffer Pool11 base address Slice0
#define BUFFER_POOL_11_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_11_LEN_SLICE1_OFFSET                   0x021C    //HW Buffer Pool11 length Slice0
#define BUFFER_POOL_11_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_12_ADDR_SLICE1_OFFSET                  0x0220    //HW Buffer Pool12 base address Slice0
#define BUFFER_POOL_12_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_12_LEN_SLICE1_OFFSET                   0x0224    //HW Buffer Pool12 length Slice0
#define BUFFER_POOL_12_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_13_ADDR_SLICE1_OFFSET                  0x0228    //HW Buffer Pool13 base address Slice0
#define BUFFER_POOL_13_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_13_LEN_SLICE1_OFFSET                   0x022C    //HW Buffer Pool13 length Slice0
#define BUFFER_POOL_13_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_14_ADDR_SLICE1_OFFSET                  0x0230    //HW Buffer Pool14 base address Slice0
#define BUFFER_POOL_14_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_14_LEN_SLICE1_OFFSET                   0x0234    //HW Buffer Pool14 length Slice0
#define BUFFER_POOL_14_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_15_ADDR_SLICE1_OFFSET                  0x0238    //HW Buffer Pool15 base address Slice0
#define BUFFER_POOL_15_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_15_LEN_SLICE1_OFFSET                   0x023C    //HW Buffer Pool15 length Slice0
#define BUFFER_POOL_15_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_16_ADDR_SLICE1_OFFSET                  0x0240    //HW Buffer Pool16 base address Slice0
#define BUFFER_POOL_16_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_16_LEN_SLICE1_OFFSET                   0x0244    //HW Buffer Pool16 length Slice0
#define BUFFER_POOL_16_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_17_ADDR_SLICE1_OFFSET                  0x0248    //HW Buffer Pool17 base address Slice0
#define BUFFER_POOL_17_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_17_LEN_SLICE1_OFFSET                   0x024C    //HW Buffer Pool17 length Slice0
#define BUFFER_POOL_17_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_18_ADDR_SLICE1_OFFSET                  0x0250    //HW Buffer Pool18 base address Slice0
#define BUFFER_POOL_18_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_18_LEN_SLICE1_OFFSET                   0x0254    //HW Buffer Pool18 length Slice0
#define BUFFER_POOL_18_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_19_ADDR_SLICE1_OFFSET                  0x0258    //HW Buffer Pool19 base address Slice0
#define BUFFER_POOL_19_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_19_LEN_SLICE1_OFFSET                   0x025C    //HW Buffer Pool19 length Slice0
#define BUFFER_POOL_19_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_20_ADDR_SLICE1_OFFSET                  0x0260    //HW Buffer Pool20 base address Slice0
#define BUFFER_POOL_20_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_20_LEN_SLICE1_OFFSET                   0x0264    //HW Buffer Pool20 length Slice0
#define BUFFER_POOL_20_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_21_ADDR_SLICE1_OFFSET                  0x0268    //HW Buffer Pool21 base address Slice0
#define BUFFER_POOL_21_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_21_LEN_SLICE1_OFFSET                   0x026C    //HW Buffer Pool21 length Slice0
#define BUFFER_POOL_21_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_22_ADDR_SLICE1_OFFSET                  0x0270    //HW Buffer Pool22 base address Slice0
#define BUFFER_POOL_22_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_22_LEN_SLICE1_OFFSET                   0x0274    //HW Buffer Pool22 length Slice0
#define BUFFER_POOL_22_LEN_SLICE1_OFFSET_SIZE              0x4
#define BUFFER_POOL_23_ADDR_SLICE1_OFFSET                  0x0278    //HW Buffer Pool23 base address Slice0
#define BUFFER_POOL_23_ADDR_SLICE1_OFFSET_SIZE             0x4
#define BUFFER_POOL_23_LEN_SLICE1_OFFSET                   0x027C    //HW Buffer Pool23 length Slice0
#define BUFFER_POOL_23_LEN_SLICE1_OFFSET_SIZE              0x4
#define HOST_RX_PRE_RD_PTR_OFFSET                          0x0280    //Host Egress Q MSMC Read pointer (for Pre-emptive queue) stored here
#define HOST_RX_PRE_RD_PTR_OFFSET_SIZE                     0x4
#define EMAC_ICSSG_SWITCH_HOST_QUEUE_READ_PTR_OFFSET       HOST_RX_PRE_RD_PTR_OFFSET    //Same as HOST_RX_PRE_RD_PTR_OFFSET
#define HOST_RX_PRE_WR_PTR_OFFSET                          0x0284    //Host Egress Q MSMC Write pointer (for Pre-emptive queue) stored here
#define HOST_RX_PRE_WR_PTR_OFFSET_SIZE                     0x4
#define HOST_RX_PRE_RD_PTR_OFFSET_1                        0x0288    //Host Egress Q MSMC Read pointer (for Pre-emptive queue) stored here
#define HOST_RX_PRE_RD_PTR_OFFSET_1_SIZE                   0x4
#define EMAC_ICSSG_SWITCH_HOST_QUEUE_READ_PTR_OFFSET_1     HOST_RX_PRE_RD_PTR_OFFSET_1    //Same as HOST_RX_PRE_RD_PTR_OFFSET_1
#define HOST_RX_PRE_WR_PTR_OFFSET_1                        0x028C    //Host Egress Q MSMC Write pointer (for Pre-emptive queue) stored here
#define HOST_RX_PRE_WR_PTR_OFFSET_1_SIZE                   0x4
#define VLAN_STATIC_REG_TABLE_OFFSET                       0x0290    //VLAN-FID Table offset. 4096 VIDs. 2B per VID = 8KB = 0x2000
#define VLAN_STATIC_REG_TABLE_OFFSET_SIZE                  0x2000
#define EMAC_ICSSG_SWITCH_DEFAULT_VLAN_TABLE_OFFSET        VLAN_STATIC_REG_TABLE_OFFSET    //VLAN-FID Table offset for EMAC
#define SMEM_VLAN_END_OF_MEM                               0x2290    //End of VLAN-FID table marker
#define SMEM_VLAN_END_OF_MEM_SIZE                          0x4
#define HOST_RX_Q_PRE_CONTEXT_SLICE0_OFFSET                0x2294    //16B for Host Egress MSMC Q (Pre-emptible) Slice0 context
#define HOST_RX_Q_PRE_CONTEXT_SLICE0_OFFSET_SIZE           (NRT_QUEUE_CONTEXT_SIZE) //0x10
#define DEFAULT_MSMC_Q_SLICE0_OFFSET                       (HOST_RX_Q_PRE_CONTEXT_SLICE0_OFFSET+12)    //2k memory reserved for default writes by Slice0
#define HOST_RX_Q_PRE_CONTEXT_SLICE1_OFFSET                0x22A4    //16B for Host Egress MSMC Q (Pre-emptible) Slice1 context
#define HOST_RX_Q_PRE_CONTEXT_SLICE1_OFFSET_SIZE           (NRT_QUEUE_CONTEXT_SIZE) //0x10
#define DEFAULT_MSMC_Q_SLICE1_OFFSET                       (HOST_RX_Q_PRE_CONTEXT_SLICE1_OFFSET+12)    //2k memory reserved for default writes by Slice1
#define XXPD_DESC_START                                    0x22B4    //packet descriptor Q reserved memory start offset
#define PORT_DESC0_HI                                      0x22B4    //packet descriptor Q reserved memory
#define PORT_DESC0_HI_SIZE                                 (NRT_PORT_DESC_SMEM_SIZE) //0xe68
#define PORT_DESC0_LO                                      0x311C    //packet descriptor Q reserved memory
#define PORT_DESC0_LO_SIZE                                 (NRT_PORT_DESC_SMEM_SIZE) //0xe68
#define PORT_DESC1_HI                                      0x3F84    //packet descriptor Q reserved memory
#define PORT_DESC1_HI_SIZE                                 (NRT_PORT_DESC_SMEM_SIZE) //0xe68
#define PORT_DESC1_LO                                      0x4DEC    //packet descriptor Q reserved memory
#define PORT_DESC1_LO_SIZE                                 (NRT_PORT_DESC_SMEM_SIZE) //0xe68
#define HOST_DESC0_HI                                      0x5C54    //packet descriptor Q reserved memory
#define HOST_DESC0_HI_SIZE                                 (NRT_HOST_DESC_SMEM_SIZE) //0x468
#define HOST_DESC0_LO                                      0x60BC    //packet descriptor Q reserved memory
#define HOST_DESC0_LO_SIZE                                 (NRT_HOST_DESC_SMEM_SIZE) //0x468
#define HOST_DESC1_HI                                      0x6524    //packet descriptor Q reserved memory
#define HOST_DESC1_HI_SIZE                                 (NRT_HOST_DESC_SMEM_SIZE) //0x468
#define HOST_DESC1_LO                                      0x698C    //packet descriptor Q reserved memory
#define HOST_DESC1_LO_SIZE                                 (NRT_HOST_DESC_SMEM_SIZE) //0x468
#define XXPD_DESC_END                                      0x6DF4    //packet descriptor Q reserved memory end offset
#define HOST_RX_DESC_Q_PRE_OFFSET                          0x6DF4    //packet descriptor Q reserved memory for Host Egress (Pre-emptible) queues
#define HOST_RX_DESC_Q_PRE_OFFSET_SIZE                     (NRT_PORT_DESC_QUEUE_SIZE) //0x734
#define HOST_RX_DESC_Q_EXP_OFFSET                          0x7528    //packet descriptor Q reserved memory for Host Egress (Pre-emptible) queues. redundant
#define HOST_RX_DESC_Q_EXP_OFFSET_SIZE                     (NRT_PORT_DESC_QUEUE_SIZE) //0x734
#define SPPD_DESC_START                                    0x7C5C    //special packet descriptor Q reserved memory start offset
#define HOST_SPPD0                                         0x7C5C    //special packet descriptor Q reserved memory
#define HOST_SPPD0_SIZE                                    (NRT_SPECIAL_PD_SMEM_SIZE) //0x400
#define HOST_SPPD1                                         0x805C    //special packet descriptor Q reserved memory
#define HOST_SPPD1_SIZE                                    (NRT_SPECIAL_PD_SMEM_SIZE) //0x400
#define SPPD_DESC_END                                      0x845C    //special packet descriptor Q reserved memory end offset
#define HOST_RX_EXP_RD_PTR_OFFSET                          0x845C    //Reserved for Future Use
#define HOST_RX_EXP_RD_PTR_OFFSET_SIZE                     0x4
#define HOST_RX_EXP_WR_PTR_OFFSET                          0x8460    //Reserved for Future Use
#define HOST_RX_EXP_WR_PTR_OFFSET_SIZE                     0x4
#define NRT_DESC_SLICE0                                    0x8464    //FIMXE : REVIEW this offset. this is used in PG11 to save the descriptor
#define NRT_DESC_SLICE0_SIZE                               0x200
#define NRT_DESC_SLICE1                                    0x8664    //FIMXE : REVIEW this offset. this is used in PG11 to save the descriptor
#define NRT_DESC_SLICE1_SIZE                               0x200
#define SHARED_MEMORY_END_OFFSET                           0x8864

// total SHARED_MEMORY memory usage : 34.09765625 KB from total of 64.0KB 

//************************************************************************************
//
// Memory Usage of : MSMC
//
//************************************************************************************

#define MSMC_START_OFFSET                                  0x0000
#define MSMC_END_OFFSET                                    0x0000

// total MSMC memory usage : 0.0 KB from total of 2048.0KB 

//************************************************************************************
//
// Memory Usage of : DMEM0
//
//************************************************************************************

#define DMEM0_START_OFFSET                                 0x0000
#define PORT_Q_PRIORITY_REGEN_OFFSET                       0x0000    //Stores the table used for priority regeneration. 4B per PCP/Queue. Only 1B is used
#define PORT_Q_PRIORITY_REGEN_OFFSET_SIZE                  0x20
#define EXPRESS_PRE_EMPTIVE_Q_MAP                          0x0020    //For marking packet as priority/express (this feature is disabled) or cut-through/S&F. One per slice
#define EXPRESS_PRE_EMPTIVE_Q_MAP_SIZE                     0x20
#define TAS_CONFIG_CHANGE_TIME                             0x0040    //New list is copied at this time
#define TAS_CONFIG_CHANGE_TIME_SIZE                        0x8
#define TAS_CONFIG_CHANGE_ERROR_COUNTER                    0x0048    //config change error counter
#define TAS_CONFIG_CHANGE_ERROR_COUNTER_SIZE               0x4
#define TAS_CONFIG_PENDING                                 0x004C    //TAS List update pending flag
#define TAS_CONFIG_PENDING_SIZE                            0x1
#define TAS_CONFIG_CHANGE                                  0x004D    //TAS list update trigger flag
#define TAS_CONFIG_CHANGE_SIZE                             0x1
//Padding of 2 bytes
#define TAS_ADMIN_CYCLE_TIME                               0x0050    //Cycle time for the new TAS schedule
#define TAS_ADMIN_CYCLE_TIME_SIZE                          0x4
#define TAS_CONFIG_CHANGE_CYCLE_COUNT                      0x0054    //Cycle counts remaining till the TAS list update
#define TAS_CONFIG_CHANGE_CYCLE_COUNT_SIZE                 0x4
#define PORT_Q_PRIORITY_MAPPING_OFFSET                     0x0058    //Stores the table used for priority mapping. 1B per PCP/Queue
#define PORT_Q_PRIORITY_MAPPING_OFFSET_SIZE                0x8
#define TAS_SHADOW_EXPIRY_LIST_GATE0                       0x0100    //TAS gate expiry list for gate0
#define TAS_SHADOW_EXPIRY_LIST_GATE0_SIZE                  0x20
#define TAS_SHADOW_EXPIRY_LIST_GATE1                       0x0120    //TAS gate expiry list for gate1
#define TAS_SHADOW_EXPIRY_LIST_GATE1_SIZE                  0x20
#define TAS_SHADOW_EXPIRY_LIST_GATE2                       0x0140    //TAS gate expiry list for gate2
#define TAS_SHADOW_EXPIRY_LIST_GATE2_SIZE                  0x20
#define TAS_SHADOW_EXPIRY_LIST_GATE3                       0x0160    //TAS gate expiry list for gate3
#define TAS_SHADOW_EXPIRY_LIST_GATE3_SIZE                  0x20
#define TAS_SHADOW_EXPIRY_LIST_GATE4                       0x0180    //TAS gate expiry list for gate4
#define TAS_SHADOW_EXPIRY_LIST_GATE4_SIZE                  0x20
#define TAS_SHADOW_EXPIRY_LIST_GATE5                       0x01A0    //TAS gate expiry list for gate5
#define TAS_SHADOW_EXPIRY_LIST_GATE5_SIZE                  0x20
#define TAS_SHADOW_EXPIRY_LIST_GATE6                       0x01C0    //TAS gate expiry list for gate6
#define TAS_SHADOW_EXPIRY_LIST_GATE6_SIZE                  0x20
#define TAS_SHADOW_EXPIRY_LIST_GATE7                       0x01E0    //TAS gate expiry list for gate7
#define TAS_SHADOW_EXPIRY_LIST_GATE7_SIZE                  0x20
#define PRE_EMPTION_ENABLE_TX                              0x0200    //Memory to Enable/Disable Preemption on TX side
#define PRE_EMPTION_ENABLE_TX_SIZE                         0x1
#define PRE_EMPTION_ACTIVE_TX                              0x0201    //Active State of Preemption on TX side
#define PRE_EMPTION_ACTIVE_TX_SIZE                         0x1
#define PRE_EMPTION_ENABLE_VERIFY                          0x0202    //Memory to Enable/Disable Verify State Machine Preemption
#define PRE_EMPTION_ENABLE_VERIFY_SIZE                     0x1
#define PRE_EMPTION_VERIFY_STATUS                          0x0203    //Verify Status of State Machine
#define PRE_EMPTION_VERIFY_STATUS_SIZE                     0x1
#define PRE_EMPTION_ADD_FRAG_SIZE_REMOTE                   0x0204    //Non Final Fragment Size supported by Link Partner
#define PRE_EMPTION_ADD_FRAG_SIZE_REMOTE_SIZE              0x2
#define PRE_EMPTION_ADD_FRAG_SIZE_LOCAL                    0x0206    //Non Final Fragment Size supported by Firmware
#define PRE_EMPTION_ADD_FRAG_SIZE_LOCAL_SIZE               0x1
//Padding of 1 bytes
#define PRE_EMPTION_VERIFY_TIME                            0x0208    //Time in ms the State machine waits for respond packet
#define PRE_EMPTION_VERIFY_TIME_SIZE                       0x2
#define DMEM0_END_OFFSET                                   0x020A

// total DMEM0 memory usage : 0.509765625 KB from total of 8.0KB 

//************************************************************************************
//
// Memory Usage of : DMEM1
//
//************************************************************************************

#define DMEM1_START_OFFSET                                 0x0000
#define ICSS_FIRMWARE_VERSION_OFFSET                       0x0000    //ICSSG Firmware version details
#define ICSS_FIRMWARE_VERSION_OFFSET_SIZE                  0xc
#define NRT_FRAME_PREEMPTION_ENABLE_OFFSET                 0x000C    //Memory used for Global enable and disable Frame Preemption
#define NRT_FRAME_PREEMPTION_ENABLE_OFFSET_SIZE            0x4
#define NRT_STASHED_Q_NUM_OFFSET                           0x0010    //Memory used for Stashing queue number during Host Egress in BG Task
#define NRT_STASHED_Q_NUM_OFFSET_SIZE                      0x4
#define PSI_TX_PKT_DATA_OFFSET_SLICE0                      0x0014    //Used Internally by FW. 
#define PSI_TX_PKT_DATA_OFFSET_SLICE0_SIZE                 0x24
#define PSI_TX_PKT_DATA_OFFSET_SLICE1                      0x0038    //Used Internally by FW. 
#define PSI_TX_PKT_DATA_OFFSET_SLICE1_SIZE                 0x24
#define LEARNING_WR_RD_COUNT_OFFSET                        0x005C    //Used Internally by FW to synchronize FDB Learning between RTU0 and PRU0 
#define LEARNING_WR_RD_COUNT_OFFSET_SIZE                   0x4
#define FDB_G0_M_G1_SLV_OFFSET                             0x0060    //Used Internally by FW to synchronize FDB Learning between two ICSSG's 
#define FDB_G0_M_G1_SLV_OFFSET_SIZE                        0x4
#define FDB_G1_M_G0_SLV_OFFSET                             0x0064    //Used Internally by FW to synchronize FDB Learning between two ICSSG's 
#define FDB_G1_M_G0_SLV_OFFSET_SIZE                        0x4
#define FDB_SYNC_ENTRY                                     0x0068    //Used to store the FDB entry one ICSSG learnt and one that needs to be communicated to other ICSSG 
#define FDB_SYNC_ENTRY_SIZE                                0x10
#define DEBUG_FDB_COMPARISON_MAC_VLAN                      0x0078    //Used for debugging FDB lookups, write the MAC and VLAN combination that is suspect. Currently disabled
#define DEBUG_FDB_COMPARISON_MAC_VLAN_SIZE                 0x8
#define DEBUG_FDB_RESULTS                                  0x0080    //The results of FBD lookup for Local injection are dumped here
#define DEBUG_FDB_RESULTS_SIZE                             0xc
#define FDB_AGEING_TIMEOUT_OFFSET                          0x008C    //Time after which FDB entries are checked for aged out values. Value in nanoseconds
#define FDB_AGEING_TIMEOUT_OFFSET_SIZE                     0x8
#define VERIFY_FRAME_RECEIVE_OFFSET                        0x0094    //Used Internally by FW. Memory updated by RX PRU when verify frame is received
#define VERIFY_FRAME_RECEIVE_OFFSET_SIZE                   0x1
//Padding of 3 bytes
#define VERIFY_FRAME_SEND_OFFSET                           0x0098    //Used Internally by FW. Memory updated by TX PRU to inform the state machine that the verify frame has been sent
#define VERIFY_FRAME_SEND_OFFSET_SIZE                      0x1
//Padding of 3 bytes
#define RESPOND_FRAME_RECEIVE_OFFSET                       0x009C    //Used Internally by FW.Memory updated by RX PRU when respond frame is received
#define RESPOND_FRAME_RECEIVE_OFFSET_SIZE                  0x1
//Padding of 3 bytes
#define RESPOND_FRAME_SEND_OFFSET                          0x00A0    //Used Internally by FW.Memory updated by TX PRU to inform the state machine that the respond frame has been sent
#define RESPOND_FRAME_SEND_OFFSET_SIZE                     0x1
//Padding of 3 bytes
#define PRE_EMPTION_CONTEXT_SLICE0_OFFSET                  0x00A4    //Backup of active Tx and Q context
#define PRE_EMPTION_CONTEXT_SLICE0_OFFSET_SIZE             0x18
#define PRE_EMPTION_CONTEXT_SLICE1_OFFSET                  0x00BC    //Backup of active Tx and Q context
#define PRE_EMPTION_CONTEXT_SLICE1_OFFSET_SIZE             0x18
#define DMEM1_END_OFFSET                                   0x0100

// total DMEM1 memory usage : 0.25 KB from total of 8.0KB 

//************************************************************************************
//
// Memory Usage of : PRU0_BSRAM
//
//************************************************************************************

#define PRU0_BSRAM_START_OFFSET                            0x0000
#define PSI_TX_INFO_SLOT_PRU0                              0x0000    //Store PSI template for INFO chunk
#define PSI_TX_INFO_SLOT_PRU0_SIZE                         0x1
#define HOST_RX_PACKET_DESC_SLOT_PRU0                      0x0001    //Stores the PSI descriptor for packet being sent to Host
#define HOST_RX_PACKET_DESC_SLOT_PRU0_SIZE                 0x1
#define HOST_RX_PRE_CONTEXT_RD_SLOT_PRU0                   0x0002    //Contains context info for Host Egress Queue (pre-emptible). Used by read task
#define HOST_RX_PRE_CONTEXT_RD_SLOT_PRU0_SIZE              0x1
#define HOST_RX_PRE_CONTEXT_WR_SLOT_PRU0                   0x0003    //Contains context info for Host Egress Queue (pre-emptible). Used by write task
#define HOST_RX_PRE_CONTEXT_WR_SLOT_PRU0_SIZE              0x1
#define HOST_RX_EXP_CONTEXT_RD_SLOT_PRU0                   0x0004    //Contains context info for Host Egress Queue (express). redundant
#define HOST_RX_EXP_CONTEXT_RD_SLOT_PRU0_SIZE              0x1
#define HOST_RX_EXP_CONTEXT_WR_SLOT_PRU0                   0x0005    //Contains context info for Host Egress Queue (express). redundant
#define HOST_RX_EXP_CONTEXT_WR_SLOT_PRU0_SIZE              0x1
#define P0_FIRST_32B_PACKET_DATA                           0x0006    //Used to store 32B at the start of SOF
#define P0_FIRST_32B_PACKET_DATA_SIZE                      0x1
#define PRU0_BSRAM_END_OFFSET                              0x0007

// total PRU0_BSRAM memory usage : 0.21875 KB from total of 4.0KB 

//************************************************************************************
//
// Memory Usage of : PRU1_BSRAM
//
//************************************************************************************

#define PRU1_BSRAM_START_OFFSET                            0x0000
#define P1_FIRST_32B_PACKET_DATA                           0x0000    //redundant
#define P1_FIRST_32B_PACKET_DATA_SIZE                      0x1
#define TAS_BSRAM_EXPIRY_LIST0_GATE0                       0x0001    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST0_GATE0_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST0_GATE1                       0x0002    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST0_GATE1_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST0_GATE2                       0x0003    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST0_GATE2_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST0_GATE3                       0x0004    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST0_GATE3_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST0_GATE4                       0x0005    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST0_GATE4_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST0_GATE5                       0x0006    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST0_GATE5_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST0_GATE6                       0x0007    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST0_GATE6_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST0_GATE7                       0x0008    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST0_GATE7_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST1_GATE0                       0x0009    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST1_GATE0_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST1_GATE1                       0x000A    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST1_GATE1_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST1_GATE2                       0x000B    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST1_GATE2_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST1_GATE3                       0x000C    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST1_GATE3_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST1_GATE4                       0x000D    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST1_GATE4_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST1_GATE5                       0x000E    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST1_GATE5_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST1_GATE6                       0x000F    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST1_GATE6_SIZE                  0x1
#define TAS_BSRAM_EXPIRY_LIST1_GATE7                       0x0010    //32B total for one gate.
#define TAS_BSRAM_EXPIRY_LIST1_GATE7_SIZE                  0x1
#define PORT_Q0_CONTEXT_SLOT_PRU1                          0x0011    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q0_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q1_CONTEXT_SLOT_PRU1                          0x0012    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q1_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q2_CONTEXT_SLOT_PRU1                          0x0013    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q2_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q3_CONTEXT_SLOT_PRU1                          0x0014    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q3_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q4_CONTEXT_SLOT_PRU1                          0x0015    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q4_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q5_CONTEXT_SLOT_PRU1                          0x0016    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q5_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q6_CONTEXT_SLOT_PRU1                          0x0017    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q6_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q7_CONTEXT_SLOT_PRU1                          0x0018    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q7_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q0_CONTEXT_SLOT_PRU1                          0x0019    //Combined context (MSMC + Desc) for Port Tx queue
#define HOST_Q0_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q1_CONTEXT_SLOT_PRU1                          0x001A    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q1_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q2_CONTEXT_SLOT_PRU1                          0x001B    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q2_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q3_CONTEXT_SLOT_PRU1                          0x001C    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q3_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q4_CONTEXT_SLOT_PRU1                          0x001D    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q4_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q5_CONTEXT_SLOT_PRU1                          0x001E    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q5_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q6_CONTEXT_SLOT_PRU1                          0x001F    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q6_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q7_CONTEXT_SLOT_PRU1                          0x0020    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q7_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PSI_TXTS_INFO_SLOT_PRU1                            0x0021    //Store Info chunk for Tx TS PSI transaction
#define PSI_TXTS_INFO_SLOT_PRU1_SIZE                       0x1
#define PRU1_BS_OFFSETS_END                                0x0022    //_Small_Description_
#define PRU1_BSRAM_END_OFFSET                              0x0022

// total PRU1_BSRAM memory usage : 1.0625 KB from total of 4.0KB 

//************************************************************************************
//
// Memory Usage of : RTU0_BSRAM
//
//************************************************************************************

#define RTU0_BSRAM_START_OFFSET                            0x0000
#define PSI_MGR_INFO_SLOT_RTU0                             0x0000    //Stores Management Frame PSI Info chunk
#define PSI_MGR_INFO_SLOT_RTU0_SIZE                        0x1
#define PORT_Q0_CONTEXT_SLOT_RTU0                          0x0001    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q0_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define PORT_Q1_CONTEXT_SLOT_RTU0                          0x0002    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q1_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define PORT_Q2_CONTEXT_SLOT_RTU0                          0x0003    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q2_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define PORT_Q3_CONTEXT_SLOT_RTU0                          0x0004    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q3_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define PORT_Q4_CONTEXT_SLOT_RTU0                          0x0005    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q4_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define PORT_Q5_CONTEXT_SLOT_RTU0                          0x0006    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q5_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define PORT_Q6_CONTEXT_SLOT_RTU0                          0x0007    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q6_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define PORT_Q7_CONTEXT_SLOT_RTU0                          0x0008    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q7_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define HOST_Q0_CONTEXT_SLOT_RTU0                          0x0009    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q0_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define HOST_Q1_CONTEXT_SLOT_RTU0                          0x000A    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q1_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define HOST_Q2_CONTEXT_SLOT_RTU0                          0x000B    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q2_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define HOST_Q3_CONTEXT_SLOT_RTU0                          0x000C    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q3_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define HOST_Q4_CONTEXT_SLOT_RTU0                          0x000D    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q4_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define HOST_Q5_CONTEXT_SLOT_RTU0                          0x000E    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q5_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define HOST_Q6_CONTEXT_SLOT_RTU0                          0x000F    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q6_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define HOST_Q7_CONTEXT_SLOT_RTU0                          0x0010    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q7_CONTEXT_SLOT_RTU0_SIZE                     0x1
#define PSI_TXTS_INFO_SLOT_RTU0                            0x0011    //Store Info chunk for Tx TS PSI transaction
#define PSI_TXTS_INFO_SLOT_RTU0_SIZE                       0x1
#define PSI_DATA_THR0_SLOT_RTU0                            0x0012    //Stash li data for thread 0
#define PSI_DATA_THR0_SLOT_RTU0_SIZE                       0x1
#define PSI_DATA_THR1_SLOT_RTU0                            0x0013    //Stash li data for thread 1
#define PSI_DATA_THR1_SLOT_RTU0_SIZE                       0x1
#define PSI_DATA_THR2_SLOT_RTU0                            0x0014    //Stash li data for thread 2
#define PSI_DATA_THR2_SLOT_RTU0_SIZE                       0x1
#define RTU0_BSRAM_END_OFFSET                              0x0015

// total RTU0_BSRAM memory usage : 0.65625 KB from total of 16.0KB 

//************************************************************************************
//
// Memory Usage of : RTU1_BSRAM
//
//************************************************************************************

#define RTU1_BSRAM_START_OFFSET                            0x0000
#define RTU1_BS_OFFSETS_END                                0x0000    //_Small_Description_
#define RTU1_BSRAM_END_OFFSET                              0x0000

// total RTU1_BSRAM memory usage : 0.0 KB from total of 16.0KB 

//************************************************************************************
//
// Memory Usage of : PA_STAT
//
//************************************************************************************

#define PA_STAT_START_OFFSET                               0x0000
#define PA_STAT_64b_START_OFFSET                           0x0000    //Start of 64 bits PA_STAT counters
#define NRT_HOST_RX_BYTE_COUNT_PASTATID                    0x0000    //Number of valid bytes sent by Rx PRU to Host on PSI. Currently disabled
#define NRT_HOST_RX_BYTE_COUNT_PASTATID_SIZE               0x2
#define NRT_HOST_TX_BYTE_COUNT_PASTATID                    0x0002    //Number of valid bytes copied by RTU0 to Tx queues. Currently disabled
#define NRT_HOST_TX_BYTE_COUNT_PASTATID_SIZE               0x2
#define PA_STAT_32b_START_OFFSET                           0x0080    //Start of 32 bits PA_STAT counters
#define NRT_HOST_RX_PKT_COUNT_PASTATID                     0x0080    //Number of valid packets sent by Rx PRU to Host on PSI
#define NRT_HOST_RX_PKT_COUNT_PASTATID_SIZE                0x4
#define NRT_HOST_TX_PKT_COUNT_PASTATID                     0x0084    //Number of valid packets copied by RTU0 to Tx queues
#define NRT_HOST_TX_PKT_COUNT_PASTATID_SIZE                0x4
#define NRT_RTU0_PACKET_DROPPED_PASTATID                   0x0088    //PRU diagnostic error counter which increments when RTU0 drops a locally injected packet due to port disabled or rule violation
#define NRT_RTU0_PACKET_DROPPED_PASTATID_SIZE              0x4
#define NRT_PORT_Q0_OVERFLOW_PASTATID                      0x008C    //Port Tx Q Overflow Counters
#define NRT_PORT_Q0_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_PORT_Q1_OVERFLOW_PASTATID                      0x0090    //Port Tx Q Overflow Counters
#define NRT_PORT_Q1_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_PORT_Q2_OVERFLOW_PASTATID                      0x0094    //Port Tx Q Overflow Counters
#define NRT_PORT_Q2_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_PORT_Q3_OVERFLOW_PASTATID                      0x0098    //Port Tx Q Overflow Counters
#define NRT_PORT_Q3_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_PORT_Q4_OVERFLOW_PASTATID                      0x009C    //Port Tx Q Overflow Counters
#define NRT_PORT_Q4_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_PORT_Q5_OVERFLOW_PASTATID                      0x00A0    //Port Tx Q Overflow Counters
#define NRT_PORT_Q5_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_PORT_Q6_OVERFLOW_PASTATID                      0x00A4    //Port Tx Q Overflow Counters
#define NRT_PORT_Q6_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_PORT_Q7_OVERFLOW_PASTATID                      0x00A8    //Port Tx Q Overflow Counters
#define NRT_PORT_Q7_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q0_OVERFLOW_PASTATID                      0x00AC    //Host Tx Q Overflow Counters
#define NRT_HOST_Q0_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q1_OVERFLOW_PASTATID                      0x00B0    //Host Tx Q Overflow Counters
#define NRT_HOST_Q1_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q2_OVERFLOW_PASTATID                      0x00B4    //Host Tx Q Overflow Counters
#define NRT_HOST_Q2_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q3_OVERFLOW_PASTATID                      0x00B8    //Host Tx Q Overflow Counters
#define NRT_HOST_Q3_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q4_OVERFLOW_PASTATID                      0x00BC    //Host Tx Q Overflow Counters
#define NRT_HOST_Q4_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q5_OVERFLOW_PASTATID                      0x00C0    //Host Tx Q Overflow Counters
#define NRT_HOST_Q5_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q6_OVERFLOW_PASTATID                      0x00C4    //Host Tx Q Overflow Counters
#define NRT_HOST_Q6_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q7_OVERFLOW_PASTATID                      0x00C8    //Host Tx Q Overflow Counters
#define NRT_HOST_Q7_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_EGRESS_Q_PRE_OVERFLOW_PASTATID            0x00CC    //Host Egress Q (Pre-emptible) Overflow Counter
#define NRT_HOST_EGRESS_Q_PRE_OVERFLOW_PASTATID_SIZE       0x4
#define NRT_HOST_EGRESS_Q_EXP_OVERFLOW_PASTATID            0x00D0    //Host Egress Q (Express) Overflow Counter. redundant
#define NRT_HOST_EGRESS_Q_EXP_OVERFLOW_PASTATID_SIZE       0x4
#define NRT_PSI_ABORT_CNT_PASTATID                         0x00D4    //_Small_Description_
#define NRT_PSI_ABORT_CNT_PASTATID_SIZE                    0x4
#define NRT_WRONG_Q_STATUS_PASTATID                        0x00D8    //Not Used, will be removed
#define NRT_WRONG_Q_STATUS_PASTATID_SIZE                   0x4
#define NRT_DROPPED_PKT_PASTATID                           0x00DC    //Incremented if a packet is dropped because of a rule violation
#define NRT_DROPPED_PKT_PASTATID_SIZE                      0x4
#define NRT_RX_ERROR_PASTATID                              0x00E0    //Incremented if there was a CRC error or Min/Max frame error
#define NRT_RX_ERROR_PASTATID_SIZE                         0x4
#define RX_EOF_RTU_DS_INVALID_PASTATID                     0x00E4    //RTU diagnostic counter increments when RTU detects Data Status invalid condition
#define RX_EOF_RTU_DS_INVALID_PASTATID_SIZE                0x4
#define RX_B1_NRT_ENTRY_PASTATID                           0x00E8    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU diagnostic counter which increments when NRT path of RX_B1 handling is invoked
#define RX_B1_NRT_ENTRY_PASTATID_SIZE                      0x4
#define RX_Bn_NRT_ENTRY_PASTATID                           0x00EC    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU diagnostic counter which increments when NRT path of RX_Bn handling is invoked
#define RX_Bn_NRT_ENTRY_PASTATID_SIZE                      0x4
#define RX_EOF_NRT_ENTRY_PASTATID                          0x00F0    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU diagnostic counter which increments when NRT path of RX_EOF handling is invoked
#define RX_EOF_NRT_ENTRY_PASTATID_SIZE                     0x4
#define NRT_TX_DROPPED_PACKET_PASTATID                     0x00F4    //Counter for packets dropped via NRT TX path
#define NRT_TX_DROPPED_PACKET_PASTATID_SIZE                0x4
#define NRT_TX_TS_DROPPED_PACKET_PASTATID                  0x00F8    //Counter for packets with TS flag dropped via NRT TX path
#define NRT_TX_TS_DROPPED_PACKET_PASTATID_SIZE             0x4
#define NRT_INF_PORT_DISABLED_PASTATID                     0x00FC    //PRU diagnostic error counter which increments when RX frame is dropped due to port is disabled
#define NRT_INF_PORT_DISABLED_PASTATID_SIZE                0x4
#define NRT_INF_SAV_PASTATID                               0x0100    //PRU diagnostic error counter which increments when RX frame is dropped due to SA violation
#define NRT_INF_SAV_PASTATID_SIZE                          0x4
#define NRT_INF_SA_BL_PASTATID                             0x0104    //PRU diagnostic error counter which increments when RX frame is dropped due to SA black listed
#define NRT_INF_SA_BL_PASTATID_SIZE                        0x4
#define NRT_INF_PORT_BLOCKED_PASTATID                      0x0108    //PRU diagnostic error counter which increments when RX frame is dropped due to port blocked and not a special frame
#define NRT_INF_PORT_BLOCKED_PASTATID_SIZE                 0x4
#define NRT_INF_AFT_DROP_TAGGED_PASTATID                   0x010C    //PRU diagnostic error counter which increments when RX frame is dropped due to tagged
#define NRT_INF_AFT_DROP_TAGGED_PASTATID_SIZE              0x4
#define NRT_INF_AFT_DROP_PRIOTAGGED_PASTATID               0x0110    //PRU diagnostic error counter which increments when RX frame is dropped due to priority tagged
#define NRT_INF_AFT_DROP_PRIOTAGGED_PASTATID_SIZE          0x4
#define NRT_INF_AFT_DROP_NOTAG_PASTATID                    0x0114    //PRU diagnostic error counter which increments when RX frame is dropped due to untagged
#define NRT_INF_AFT_DROP_NOTAG_PASTATID_SIZE               0x4
#define NRT_INF_AFT_DROP_NOTMEMBER_PASTATID                0x0118    //PRU diagnostic error counter which increments when RX frame is dropped due to port not member of VLAN
#define NRT_INF_AFT_DROP_NOTMEMBER_PASTATID_SIZE           0x4
#define NRT_FDB_NO_SPACE_TO_LEARN                          0x011C    //PRU diagnostic error counter which increments when an entry couldn't be learned
#define NRT_FDB_NO_SPACE_TO_LEARN_SIZE                     0x4
#define NRT_FDB_LAST_ENTRY_OVERWRITTEN_FOR_LEARNING        0x0120    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU diagnostic error counter which increments when the fourth entry is overwritten to accomodate leart MAC
#define NRT_FDB_LAST_ENTRY_OVERWRITTEN_FOR_LEARNING_SIZE   0x4
#define NRT_PREEMPT_BAD_FRAG_PASTATID                      0x0124    //Bad fragment Error Counter
#define NRT_PREEMPT_BAD_FRAG_PASTATID_SIZE                 0x4
#define NRT_PREEMPT_ASSEMBLY_ERROR_PASTATID                0x0128    //Fragment assembly Error Counter
#define NRT_PREEMPT_ASSEMBLY_ERROR_PASTATID_SIZE           0x4
#define NRT_PREEMPT_FRAG_COUNT_TX_PASTATID                 0x012C    //Fragment count in TX
#define NRT_PREEMPT_FRAG_COUNT_TX_PASTATID_SIZE            0x4
#define NRT_PREEMPT_ASSEMBLY_OK_PASTATID                   0x0130    //Assembly Completed
#define NRT_PREEMPT_ASSEMBLY_OK_PASTATID_SIZE              0x4
#define NRT_PREEMPT_FRAG_COUNT_RX_PASTATID                 0x0134    //Fragments received
#define NRT_PREEMPT_FRAG_COUNT_RX_PASTATID_SIZE            0x4
#define NRT_PREEMPT_DEBUG_GLOBAL_ERROR                     0x0138    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Global Debug Error Counter
#define NRT_PREEMPT_DEBUG_GLOBAL_ERROR_SIZE                0x4
#define NRT_PREEMPT_DEBUG_SMDCx_PASTATID                   0x013C    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter SMDCx
#define NRT_PREEMPT_DEBUG_SMDCx_PASTATID_SIZE              0x4
#define NRT_PREEMPT_DEBUG_SMDSx_PASTATID                   0x0140    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter SMDSx
#define NRT_PREEMPT_DEBUG_SMDSx_PASTATID_SIZE              0x4
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAG0_ERROR_PASTATID    0x0144    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - Error in SMDSx
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAG0_ERROR_PASTATID_SIZE 0x4
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAGX_ERROR_PASTATID    0x0148    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - Error in SMDCx
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAGX_ERROR_PASTATID_SIZE 0x4
#define NRT_RECYCLE_TXPRU_COUNTER_SLICE0_PASTATID          0x014C    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - TXPRU recycle counter Slice0
#define NRT_RECYCLE_TXPRU_COUNTER_SLICE0_PASTATID_SIZE     0x4
#define NRT_RECYCLE_TXPRU_COUNTER_SLICE1_PASTATID          0x0150    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - TXPRU recycle counter Slice1
#define NRT_RECYCLE_TXPRU_COUNTER_SLICE1_PASTATID_SIZE     0x4
#define NRT_RECYCLE_RXERR_RTU_COUNTER_SLICE0_PASTATID      0x0154    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - RTU recycle on RXERR counter Slice0
#define NRT_RECYCLE_RXERR_RTU_COUNTER_SLICE0_PASTATID_SIZE 0x4
#define NRT_RECYCLE_RXERR_RTU_COUNTER_SLICE1_PASTATID      0x0158    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - RTU recycle on RXERR counter Slice1
#define NRT_RECYCLE_RXERR_RTU_COUNTER_SLICE1_PASTATID_SIZE 0x4
#define NRT_RECYCLE_BG_RTU_COUNTER_SLICE0_PASTATID         0x015C    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - RTU recycle from BG task counter Slice0
#define NRT_RECYCLE_BG_RTU_COUNTER_SLICE0_PASTATID_SIZE    0x4
#define NRT_RECYCLE_BG_RTU_COUNTER_SLICE1_PASTATID         0x0160    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - RTU recycle from BG task counter Slice1
#define NRT_RECYCLE_BG_RTU_COUNTER_SLICE1_PASTATID_SIZE    0x4
#define RX_EOF_SHORT_FRAMEERR_PASTATID                     0x0164    //PRU diagnostic error counter which increments if EOF task is scheduled without seeing RX_B1
#define RX_EOF_SHORT_FRAMEERR_PASTATID_SIZE                0x4
#define RX_B1_ENTRY_PASTATID                               0x0168    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU diagnostic counter which increments when RX_B1 handling is invoked
#define RX_B1_ENTRY_PASTATID_SIZE                          0x4
#define RX_Bn_ENTRY_PASTATID                               0x016C    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU diagnostic counter which increments when RX_Bn handling is invoked
#define RX_Bn_ENTRY_PASTATID_SIZE                          0x4
#define RX_EOF_ENTRY_PASTATID                              0x0170    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU diagnostic counter which increments when RX_EOF handling is invoked
#define RX_EOF_ENTRY_PASTATID_SIZE                         0x4
#define PA_STAT_END_OFFSET                                 0x0174

// total PA_STAT memory usage : 0.36328125 KB from total of 2.0KB 


#endif // ____switch_mem_map_h
