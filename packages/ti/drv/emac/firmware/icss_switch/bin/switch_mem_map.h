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
#define FDB_SA_MAC_ADDRESS                                 0x000C    //Used internally by FW for learning
#define FDB_SA_MAC_ADDRESS_SIZE                            0x8
#define FDB_FID_FIDC2_OFFSET                               0x0014    //Used internally by FW for learning
#define FDB_FID_FIDC2_OFFSET_SIZE                          0x4
#define FDB_BUCKET_OFFSET                                  0x0018    //Used internally by FW for learning
#define FDB_BUCKET_OFFSET_SIZE                             0x4
#define FDB_AGEING_LAST_USED_OFFSET                        0x001C    //Used internally by FW for learning
#define FDB_AGEING_LAST_USED_OFFSET_SIZE                   0x4
#define TX_TS_COOKIE0_OFFSET                               0x0020    //Used internally by FW to store Tx timestamp slice0
#define TX_TS_COOKIE0_OFFSET_SIZE                          0x4
#define TX_TS_SPARE0_OFFSET                                0x0024    //not used
#define TX_TS_SPARE0_OFFSET_SIZE                           0x4
#define TX_TS_COOKIE1_OFFSET                               0x0028    //Used internally by FW to stash cookie slice1
#define TX_TS_COOKIE1_OFFSET_SIZE                          0x4
#define HOST_PORT_DF_VLAN_OFFSET                           0x002C    //default VLAN tag for Host Port
#define HOST_PORT_DF_VLAN_OFFSET_SIZE                      0x4
#define EMAC_ICSSG_SWITCH_PORT0_DEFAULT_VLAN_OFFSET        HOST_PORT_DF_VLAN_OFFSET    //Same as HOST_PORT_DF_VLAN_OFFSET
#define P1_PORT_DF_VLAN_OFFSET                             0x0030    //default VLAN tag for P1 Port
#define P1_PORT_DF_VLAN_OFFSET_SIZE                        0x4
#define EMAC_ICSSG_SWITCH_PORT1_DEFAULT_VLAN_OFFSET        P1_PORT_DF_VLAN_OFFSET    //Same as P1_PORT_DF_VLAN_OFFSET
#define P2_PORT_DF_VLAN_OFFSET                             0x0034    //default VLAN tag for P2 Port
#define P2_PORT_DF_VLAN_OFFSET_SIZE                        0x4
#define EMAC_ICSSG_SWITCH_PORT2_DEFAULT_VLAN_OFFSET        P2_PORT_DF_VLAN_OFFSET    //Same as P2_PORT_DF_VLAN_OFFSET
#define RX_TS_STASHED_SLICE0                               0x0038    //Used internally by FW for stashed Rx timestamp
#define RX_TS_STASHED_SLICE0_SIZE                          0x8
#define RX_TS_STASHED_SLICE1                               0x0040    //Used internally by FW for stashed Rx timestamp
#define RX_TS_STASHED_SLICE1_SIZE                          0x8
#define MGR_CMD_SLICE0_OFFSET                              0x0048    //Management command from Host to RTU0
#define MGR_CMD_SLICE0_OFFSET_SIZE                         0x20
#define MGR_CMD_RET_SLICE0                                 0x0068    //Management reply to Host from RTU0
#define MGR_CMD_RET_SLICE0_SIZE                            0xc
#define MGR_CMD_STATE_SLICE0                               0x0074    //0 - idle; 1 - todo; 2 - executing
#define MGR_CMD_STATE_SLICE0_SIZE                          0x1
//Padding of 3 bytes
#define MGR_CMD_RXPRU_STATUS_SLICE0                        0x0078    //Used internally by FW to communicate from RTU0 to PRU0
#define MGR_CMD_RXPRU_STATUS_SLICE0_SIZE                   0x2
#define MGR_CMD_TXPRU_STATUS_SLICE0                        0x007A    //Used internally by FW to communicate from RTU0 to PRU1
#define MGR_CMD_TXPRU_STATUS_SLICE0_SIZE                   0x2
#define MGR_CMD_RTU_STATUS_SLICE0                          0x007C    //Used internally by FW to communicate from RTU0 to RTU0
#define MGR_CMD_RTU_STATUS_SLICE0_SIZE                     0x2
//Padding of 2 bytes
#define MGR_CMD_BUFF_PTR_SLICE0                            0x0080    //Used for storing buffer pointers
#define MGR_CMD_BUFF_PTR_SLICE0_SIZE                       0x4
#define MGR_CMD_SLICE1_OFFSET                              0x0084    //Management command from Host to RTU0
#define MGR_CMD_SLICE1_OFFSET_SIZE                         0x20
#define MGR_CMD_RET_SLICE1                                 0x00A4    //Management reply to Host from RTU0
#define MGR_CMD_RET_SLICE1_SIZE                            0xc
#define MGR_CMD_STATE_SLICE1                               0x00B0    //0 - idle; 1 - todo; 2 - executing
#define MGR_CMD_STATE_SLICE1_SIZE                          0x1
//Padding of 3 bytes
#define MGR_CMD_RXPRU_STATUS_SLICE1                        0x00B4    //Used internally by FW to communicate from RTU0 to PRU0
#define MGR_CMD_RXPRU_STATUS_SLICE1_SIZE                   0x2
#define MGR_CMD_TXPRU_STATUS_SLICE1                        0x00B6    //Used internally by FW to communicate from RTU0 to PRU1
#define MGR_CMD_TXPRU_STATUS_SLICE1_SIZE                   0x2
#define MGR_CMD_RTU_STATUS_SLICE1                          0x00B8    //Used internally by FW to communicate from RTU0 to RTU0
#define MGR_CMD_RTU_STATUS_SLICE1_SIZE                     0x2
//Padding of 2 bytes
#define MGR_CMD_BUFF_PTR_SLICE1                            0x00BC    //Used for storing buffer pointers
#define MGR_CMD_BUFF_PTR_SLICE1_SIZE                       0x4
#define MGR_CMD_END_OFFSET                                 0x00C0    //End of Management command region
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
#define MGR_PKT_PULL_SLICE0                                0x8864    //Command buffers for slice0 
#define MGR_PKT_PULL_SLICE0_SIZE                           0xa0
#define MGR_PKT_PULL_SLICE1                                0x8904    //Command buffers for slice0 
#define MGR_PKT_PULL_SLICE1_SIZE                           0xa0
#define SHARED_MEMORY_END_OFFSET                           0x89A4

// total SHARED_MEMORY memory usage : 34.41015625 KB from total of 64.0KB 

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
#define ICSS_FIRMWARE_VERSION_OFFSET                       0x0000    //ICSSG Firmware version details
#define ICSS_FIRMWARE_VERSION_OFFSET_SIZE                  0xc
#define TAS_CONFIG_CHANGE_TIME                             0x000C    //New list is copied at this time
#define TAS_CONFIG_CHANGE_TIME_SIZE                        0x8
#define TAS_CONFIG_CHANGE_ERROR_COUNTER                    0x0014    //config change error counter
#define TAS_CONFIG_CHANGE_ERROR_COUNTER_SIZE               0x4
#define TAS_CONFIG_PENDING                                 0x0018    //TAS List update pending flag
#define TAS_CONFIG_PENDING_SIZE                            0x1
#define TAS_CONFIG_CHANGE                                  0x0019    //TAS list update trigger flag
#define TAS_CONFIG_CHANGE_SIZE                             0x1
#define TAS_ADMIN_LIST_LENGTH                              0x001A    //List length for new TAS schedule
#define TAS_ADMIN_LIST_LENGTH_SIZE                         0x1
#define TAS_ACTIVE_LIST_INDEX                              0x001B    //Currently active TAS list index
#define TAS_ACTIVE_LIST_INDEX_SIZE                         0x1
#define TAS_ADMIN_CYCLE_TIME                               0x001C    //Cycle time for the new TAS schedule
#define TAS_ADMIN_CYCLE_TIME_SIZE                          0x4
#define TAS_CONFIG_CHANGE_CYCLE_COUNT                      0x0020    //Cycle counts remaining till the TAS list update
#define TAS_CONFIG_CHANGE_CYCLE_COUNT_SIZE                 0x4
#define PSI_L_REGULAR_FLOW_ID_BASE_OFFSET                  0x0024    //Base Flow ID for sending packets to Host for Slice0
#define PSI_L_REGULAR_FLOW_ID_BASE_OFFSET_SIZE             0x2
#define EMAC_ICSSG_SWITCH_PSI_L_REGULAR_FLOW_ID_BASE_OFFSET PSI_L_REGULAR_FLOW_ID_BASE_OFFSET    //Same as PSI_L_REGULAR_FLOW_ID_BASE_OFFSET
#define PSI_L_MGMT_FLOW_ID_OFFSET                          0x0026    //Base Flow ID for sending mgmt and Tx TS to Host for Slice0
#define PSI_L_MGMT_FLOW_ID_OFFSET_SIZE                     0x2
#define EMAC_ICSSG_SWITCH_PSI_L_MGMT_FLOW_ID_BASE_OFFSET   PSI_L_MGMT_FLOW_ID_OFFSET    //Same as PSI_L_MGMT_FLOW_ID_OFFSET
#define SPL_PKT_DEFAULT_PRIORITY                           0x0028    //Queue number for Special packets written here. Only 1B is used
#define SPL_PKT_DEFAULT_PRIORITY_SIZE                      0x2
#define QUEUE_NUM_UNTAGGED                                 0x002A    //Port1/Port2 Default Queue number for untagged packets
#define QUEUE_NUM_UNTAGGED_SIZE                            0x2
#define PORT_Q_PRIORITY_REGEN_OFFSET                       0x002C    //Stores the table used for priority regeneration. 1B per PCP/Queue
#define PORT_Q_PRIORITY_REGEN_OFFSET_SIZE                  0x8
#define EXPRESS_PRE_EMPTIVE_Q_MAP                          0x0034    //For marking packet as priority/express (this feature is disabled) or cut-through/S&F. One per slice
#define EXPRESS_PRE_EMPTIVE_Q_MAP_SIZE                     0x8
#define PORT_Q_PRIORITY_MAPPING_OFFSET                     0x003C    //Stores the table used for priority mapping. 1B per PCP/Queue
#define PORT_Q_PRIORITY_MAPPING_OFFSET_SIZE                0x8
#define TAS_GATE_MASK_LIST0                                0x0100    //TAS gate mask for windows list0
#define TAS_GATE_MASK_LIST0_SIZE                           (TAS_NUM_WINDOWS) //0x10
#define TAS_WINDOW_END_TIME_LIST0                          0x0110    //TAS window end time list0
#define TAS_WINDOW_END_TIME_LIST0_SIZE                     (TAS_NUM_WINDOWS*4) //0x40
#define TAS_GATE_CLOSE_TIME_LIST0                          0x0150    //TAS gate close time[window][queue] list0
#define TAS_GATE_CLOSE_TIME_LIST0_SIZE                     (TAS_NUM_WINDOWS*TAS_NUM_QUEUES*4) //0x200
#define TAS_GATE_MASK_LIST1                                0x0350    //TAS gate mask for windows list1
#define TAS_GATE_MASK_LIST1_SIZE                           (TAS_NUM_WINDOWS) //0x10
#define TAS_WINDOW_END_TIME_LIST1                          0x0360    //TAS window end time list1
#define TAS_WINDOW_END_TIME_LIST1_SIZE                     (TAS_NUM_WINDOWS*4) //0x40
#define TAS_GATE_CLOSE_TIME_LIST1                          0x03A0    //TAS gate close time[window][queue] list1
#define TAS_GATE_CLOSE_TIME_LIST1_SIZE                     (TAS_NUM_WINDOWS*TAS_NUM_QUEUES*4) //0x200
#define PRE_EMPTION_ENABLE_TX                              0x05A0    //Memory to Enable/Disable Preemption on TX side
#define PRE_EMPTION_ENABLE_TX_SIZE                         0x1
#define PRE_EMPTION_ACTIVE_TX                              0x05A1    //Active State of Preemption on TX side
#define PRE_EMPTION_ACTIVE_TX_SIZE                         0x1
#define PRE_EMPTION_ENABLE_VERIFY                          0x05A2    //Memory to Enable/Disable Verify State Machine Preemption
#define PRE_EMPTION_ENABLE_VERIFY_SIZE                     0x1
#define PRE_EMPTION_VERIFY_STATUS                          0x05A3    //Verify Status of State Machine
#define PRE_EMPTION_VERIFY_STATUS_SIZE                     0x1
#define PRE_EMPTION_ADD_FRAG_SIZE_REMOTE                   0x05A4    //Non Final Fragment Size supported by Link Partner
#define PRE_EMPTION_ADD_FRAG_SIZE_REMOTE_SIZE              0x2
#define PRE_EMPTION_ADD_FRAG_SIZE_LOCAL                    0x05A6    //Non Final Fragment Size supported by Firmware
#define PRE_EMPTION_ADD_FRAG_SIZE_LOCAL_SIZE               0x1
//Padding of 1 bytes
#define PRE_EMPTION_VERIFY_TIME                            0x05A8    //Time in ms the State machine waits for respond packet
#define PRE_EMPTION_VERIFY_TIME_SIZE                       0x2
#define DMEM0_END_OFFSET                                   0x05AA

// total DMEM0 memory usage : 1.416015625 KB from total of 8.0KB 

//************************************************************************************
//
// Memory Usage of : DMEM1
//
//************************************************************************************

#define DMEM1_START_OFFSET                                 0x0000
#define ICSS_FIRMWARE_VERSION_OFFSET                       0x0000    //ICSSG Firmware version details
#define ICSS_FIRMWARE_VERSION_OFFSET_SIZE                  0xc
#define TAS_CONFIG_CHANGE_TIME                             0x000C    //New list is copied at this time
#define TAS_CONFIG_CHANGE_TIME_SIZE                        0x8
#define TAS_CONFIG_CHANGE_ERROR_COUNTER                    0x0014    //config change error counter
#define TAS_CONFIG_CHANGE_ERROR_COUNTER_SIZE               0x4
#define TAS_CONFIG_PENDING                                 0x0018    //TAS List update pending flag
#define TAS_CONFIG_PENDING_SIZE                            0x1
#define TAS_CONFIG_CHANGE                                  0x0019    //TAS list update trigger flag
#define TAS_CONFIG_CHANGE_SIZE                             0x1
#define TAS_ADMIN_LIST_LENGTH                              0x001A    //List length for new TAS schedule
#define TAS_ADMIN_LIST_LENGTH_SIZE                         0x1
#define TAS_ACTIVE_LIST_INDEX                              0x001B    //Currently active TAS list index
#define TAS_ACTIVE_LIST_INDEX_SIZE                         0x1
#define TAS_ADMIN_CYCLE_TIME                               0x001C    //Cycle time for the new TAS schedule
#define TAS_ADMIN_CYCLE_TIME_SIZE                          0x4
#define TAS_CONFIG_CHANGE_CYCLE_COUNT                      0x0020    //Cycle counts remaining till the TAS list update
#define TAS_CONFIG_CHANGE_CYCLE_COUNT_SIZE                 0x4
#define PSI_L_REGULAR_FLOW_ID_BASE_OFFSET                  0x0024    //Base Flow ID for sending packets to Host for Slice0
#define PSI_L_REGULAR_FLOW_ID_BASE_OFFSET_SIZE             0x2
#define PSI_L_MGMT_FLOW_ID_OFFSET                          0x0026    //Base Flow ID for sending mgmt and Tx TS to Host for Slice0
#define PSI_L_MGMT_FLOW_ID_OFFSET_SIZE                     0x2
#define SPL_PKT_DEFAULT_PRIORITY                           0x0028    //Queue number for Special packets written here. Only 1B is used
#define SPL_PKT_DEFAULT_PRIORITY_SIZE                      0x2
#define QUEUE_NUM_UNTAGGED                                 0x002A    //Port1/Port2 Default Queue number for untagged packets
#define QUEUE_NUM_UNTAGGED_SIZE                            0x2
#define PORT_Q_PRIORITY_REGEN_OFFSET                       0x002C    //Stores the table used for priority regeneration. 1B per PCP/Queue
#define PORT_Q_PRIORITY_REGEN_OFFSET_SIZE                  0x8
#define EXPRESS_PRE_EMPTIVE_Q_MAP                          0x0034    //For marking packet as priority/express (this feature is disabled) or cut-through/S&F. One per slice
#define EXPRESS_PRE_EMPTIVE_Q_MAP_SIZE                     0x8
#define PORT_Q_PRIORITY_MAPPING_OFFSET                     0x003C    //Stores the table used for priority mapping. 1B per PCP/Queue
#define PORT_Q_PRIORITY_MAPPING_OFFSET_SIZE                0x8
#define PSI_TX_PKT_DATA_OFFSET_SLICE0                      0x0044    //Used Internally by FW. 
#define PSI_TX_PKT_DATA_OFFSET_SLICE0_SIZE                 0x24
#define PSI_TX_PKT_DATA_OFFSET_SLICE1                      0x0068    //Used Internally by FW. 
#define PSI_TX_PKT_DATA_OFFSET_SLICE1_SIZE                 0x24
#define LEARNING_WR_RD_COUNT_OFFSET                        0x008C    //Used Internally by FW to synchronize FDB Learning between RTU0 and PRU0 
#define LEARNING_WR_RD_COUNT_OFFSET_SIZE                   0x4
#define DEBUG_FDB_COMPARISON_MAC_VLAN                      0x0090    //Used for debugging FDB lookups, write the MAC and VLAN combination that is suspect. Currently disabled
#define DEBUG_FDB_COMPARISON_MAC_VLAN_SIZE                 0x8
#define DEBUG_FDB_RESULTS                                  0x0098    //The results of FBD lookup for Local injection are dumped here
#define DEBUG_FDB_RESULTS_SIZE                             0xc
#define FDB_AGEING_TIMEOUT_OFFSET                          0x00A4    //Time after which FDB entries are checked for aged out values. Value in nanoseconds
#define FDB_AGEING_TIMEOUT_OFFSET_SIZE                     0x8
#define VERIFY_FRAME_RECEIVE_OFFSET                        0x00AC    //Used Internally by FW. Memory updated by RX PRU when verify frame is received
#define VERIFY_FRAME_RECEIVE_OFFSET_SIZE                   0x1
//Padding of 3 bytes
#define VERIFY_FRAME_SEND_OFFSET                           0x00B0    //Used Internally by FW. Memory updated by TX PRU to inform the state machine that the verify frame has been sent
#define VERIFY_FRAME_SEND_OFFSET_SIZE                      0x1
//Padding of 3 bytes
#define RESPOND_FRAME_RECEIVE_OFFSET                       0x00B4    //Used Internally by FW.Memory updated by RX PRU when respond frame is received
#define RESPOND_FRAME_RECEIVE_OFFSET_SIZE                  0x1
//Padding of 3 bytes
#define RESPOND_FRAME_SEND_OFFSET                          0x00B8    //Used Internally by FW.Memory updated by TX PRU to inform the state machine that the respond frame has been sent
#define RESPOND_FRAME_SEND_OFFSET_SIZE                     0x1
//Padding of 3 bytes
#define PRE_EMPTION_CONTEXT_SLICE0_OFFSET                  0x00BC    //Backup of active Tx and Q context
#define PRE_EMPTION_CONTEXT_SLICE0_OFFSET_SIZE             0x18
#define PRE_EMPTION_CONTEXT_SLICE1_OFFSET                  0x00D4    //Backup of active Tx and Q context
#define PRE_EMPTION_CONTEXT_SLICE1_OFFSET_SIZE             0x18
#define TAS_GATE_MASK_LIST0                                0x0100    //TAS gate mask for windows list0
#define TAS_GATE_MASK_LIST0_SIZE                           (TAS_NUM_WINDOWS) //0x10
#define TAS_WINDOW_END_TIME_LIST0                          0x0110    //TAS window end time list0
#define TAS_WINDOW_END_TIME_LIST0_SIZE                     (TAS_NUM_WINDOWS*4) //0x40
#define TAS_GATE_CLOSE_TIME_LIST0                          0x0150    //TAS gate close time[window][queue] list0
#define TAS_GATE_CLOSE_TIME_LIST0_SIZE                     (TAS_NUM_WINDOWS*TAS_NUM_QUEUES*4) //0x200
#define TAS_GATE_MASK_LIST1                                0x0350    //TAS gate mask for windows list1
#define TAS_GATE_MASK_LIST1_SIZE                           (TAS_NUM_WINDOWS) //0x10
#define TAS_WINDOW_END_TIME_LIST1                          0x0360    //TAS window end time list1
#define TAS_WINDOW_END_TIME_LIST1_SIZE                     (TAS_NUM_WINDOWS*4) //0x40
#define TAS_GATE_CLOSE_TIME_LIST1                          0x03A0    //TAS gate close time[window][queue] list1
#define TAS_GATE_CLOSE_TIME_LIST1_SIZE                     (TAS_NUM_WINDOWS*TAS_NUM_QUEUES*4) //0x200
#define PRE_EMPTION_ENABLE_TX                              0x05A0    //Memory to Enable/Disable Preemption on TX side
#define PRE_EMPTION_ENABLE_TX_SIZE                         0x1
#define PRE_EMPTION_ACTIVE_TX                              0x05A1    //Active State of Preemption on TX side
#define PRE_EMPTION_ACTIVE_TX_SIZE                         0x1
#define PRE_EMPTION_ENABLE_VERIFY                          0x05A2    //Memory to Enable/Disable Verify State Machine Preemption
#define PRE_EMPTION_ENABLE_VERIFY_SIZE                     0x1
#define PRE_EMPTION_VERIFY_STATUS                          0x05A3    //Verify Status of State Machine
#define PRE_EMPTION_VERIFY_STATUS_SIZE                     0x1
#define PRE_EMPTION_ADD_FRAG_SIZE_REMOTE                   0x05A4    //Non Final Fragment Size supported by Link Partner
#define PRE_EMPTION_ADD_FRAG_SIZE_REMOTE_SIZE              0x2
#define PRE_EMPTION_ADD_FRAG_SIZE_LOCAL                    0x05A6    //Non Final Fragment Size supported by Firmware
#define PRE_EMPTION_ADD_FRAG_SIZE_LOCAL_SIZE               0x1
//Padding of 1 bytes
#define PRE_EMPTION_VERIFY_TIME                            0x05A8    //Time in ms the State machine waits for respond packet
#define PRE_EMPTION_VERIFY_TIME_SIZE                       0x2
#define DMEM1_END_OFFSET                                   0x05AA

// total DMEM1 memory usage : 1.416015625 KB from total of 8.0KB 

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

// total PRU0_BSRAM memory usage : 0.21875 KB from total of 2.0KB 

//************************************************************************************
//
// Memory Usage of : PRU1_BSRAM
//
//************************************************************************************

#define PRU1_BSRAM_START_OFFSET                            0x0000
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
#define PRU1_BSRAM_END_OFFSET                              0x0007

// total PRU1_BSRAM memory usage : 0.21875 KB from total of 2.0KB 

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

// total RTU0_BSRAM memory usage : 0.65625 KB from total of 2.0KB 

//************************************************************************************
//
// Memory Usage of : RTU1_BSRAM
//
//************************************************************************************

#define RTU1_BSRAM_START_OFFSET                            0x0000
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
#define PSI_DATA_THR0_SLOT_RTU0                            0x0012    //Stash local injection data for thread 0
#define PSI_DATA_THR0_SLOT_RTU0_SIZE                       0x1
#define PSI_DATA_THR1_SLOT_RTU0                            0x0013    //Stash local injection data for thread 1
#define PSI_DATA_THR1_SLOT_RTU0_SIZE                       0x1
#define PSI_DATA_THR2_SLOT_RTU0                            0x0014    //Stash local injection data for thread 2
#define PSI_DATA_THR2_SLOT_RTU0_SIZE                       0x1
#define PSI_DATA_THR3_SLOT_RTU0                            0x0015    //Stash local injection data for thread 3
#define PSI_DATA_THR3_SLOT_RTU0_SIZE                       0x1
#define PSI_CTX_THR0_SLOT_RTU0                             0x0016    //Stash local injection context for thread 0
#define PSI_CTX_THR0_SLOT_RTU0_SIZE                        0x1
#define PSI_CTX_THR1_SLOT_RTU0                             0x0017    //Stash local injection context for thread 1
#define PSI_CTX_THR1_SLOT_RTU0_SIZE                        0x1
#define PSI_CTX_THR2_SLOT_RTU0                             0x0018    //Stash local injection context for thread 2
#define PSI_CTX_THR2_SLOT_RTU0_SIZE                        0x1
#define PSI_CTX_THR3_SLOT_RTU0                             0x0019    //Stash local injection context for thread 3
#define PSI_CTX_THR3_SLOT_RTU0_SIZE                        0x1
#define RTU1_BSRAM_END_OFFSET                              0x001A

// total RTU1_BSRAM memory usage : 0.8125 KB from total of 2.0KB 

//************************************************************************************
//
// Memory Usage of : TXPRU0_BSRAM
//
//************************************************************************************

#define TXPRU0_BSRAM_START_OFFSET                          0x0000
#define P1_FIRST_32B_PACKET_DATA                           0x0000    //redundant
#define P1_FIRST_32B_PACKET_DATA_SIZE                      0x1
#define TAS_PERSISTENT_CONTEXT_OFFSET                      0x0001    //TAS persistent registers
#define TAS_PERSISTENT_CONTEXT_OFFSET_SIZE                 0x1
#define PORT_Q0_CONTEXT_SLOT_PRU1                          0x0002    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q0_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q1_CONTEXT_SLOT_PRU1                          0x0003    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q1_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q2_CONTEXT_SLOT_PRU1                          0x0004    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q2_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q3_CONTEXT_SLOT_PRU1                          0x0005    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q3_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q4_CONTEXT_SLOT_PRU1                          0x0006    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q4_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q5_CONTEXT_SLOT_PRU1                          0x0007    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q5_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q6_CONTEXT_SLOT_PRU1                          0x0008    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q6_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q7_CONTEXT_SLOT_PRU1                          0x0009    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q7_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q0_CONTEXT_SLOT_PRU1                          0x000A    //Combined context (MSMC + Desc) for Port Tx queue
#define HOST_Q0_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q1_CONTEXT_SLOT_PRU1                          0x000B    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q1_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q2_CONTEXT_SLOT_PRU1                          0x000C    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q2_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q3_CONTEXT_SLOT_PRU1                          0x000D    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q3_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q4_CONTEXT_SLOT_PRU1                          0x000E    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q4_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q5_CONTEXT_SLOT_PRU1                          0x000F    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q5_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q6_CONTEXT_SLOT_PRU1                          0x0010    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q6_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q7_CONTEXT_SLOT_PRU1                          0x0011    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q7_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PSI_TXTS_INFO_SLOT_PRU1                            0x0012    //Store Info chunk for Tx TS PSI transaction
#define PSI_TXTS_INFO_SLOT_PRU1_SIZE                       0x1
#define PRU1_BS_OFFSETS_END                                0x0013    //_Small_Description_
#define TXPRU0_BSRAM_END_OFFSET                            0x0013

// total TXPRU0_BSRAM memory usage : 0.59375 KB from total of 2.0KB 

//************************************************************************************
//
// Memory Usage of : TXPRU1_BSRAM
//
//************************************************************************************

#define TXPRU1_BSRAM_START_OFFSET                          0x0000
#define P1_FIRST_32B_PACKET_DATA                           0x0000    //redundant
#define P1_FIRST_32B_PACKET_DATA_SIZE                      0x1
#define TAS_PERSISTENT_CONTEXT_OFFSET                      0x0001    //TAS persistent registers
#define TAS_PERSISTENT_CONTEXT_OFFSET_SIZE                 0x1
#define PORT_Q0_CONTEXT_SLOT_PRU1                          0x0002    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q0_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q1_CONTEXT_SLOT_PRU1                          0x0003    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q1_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q2_CONTEXT_SLOT_PRU1                          0x0004    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q2_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q3_CONTEXT_SLOT_PRU1                          0x0005    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q3_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q4_CONTEXT_SLOT_PRU1                          0x0006    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q4_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q5_CONTEXT_SLOT_PRU1                          0x0007    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q5_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q6_CONTEXT_SLOT_PRU1                          0x0008    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q6_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PORT_Q7_CONTEXT_SLOT_PRU1                          0x0009    //Combined context (MSMC + Desc) for Port Tx queue
#define PORT_Q7_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q0_CONTEXT_SLOT_PRU1                          0x000A    //Combined context (MSMC + Desc) for Port Tx queue
#define HOST_Q0_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q1_CONTEXT_SLOT_PRU1                          0x000B    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q1_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q2_CONTEXT_SLOT_PRU1                          0x000C    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q2_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q3_CONTEXT_SLOT_PRU1                          0x000D    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q3_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q4_CONTEXT_SLOT_PRU1                          0x000E    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q4_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q5_CONTEXT_SLOT_PRU1                          0x000F    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q5_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q6_CONTEXT_SLOT_PRU1                          0x0010    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q6_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define HOST_Q7_CONTEXT_SLOT_PRU1                          0x0011    //Combined context (MSMC + Desc) for Host Tx queue
#define HOST_Q7_CONTEXT_SLOT_PRU1_SIZE                     0x1
#define PSI_TXTS_INFO_SLOT_PRU1                            0x0012    //Store Info chunk for Tx TS PSI transaction
#define PSI_TXTS_INFO_SLOT_PRU1_SIZE                       0x1
#define PRU1_BS_OFFSETS_END                                0x0013    //_Small_Description_
#define TXPRU1_BSRAM_END_OFFSET                            0x0013

// total TXPRU1_BSRAM memory usage : 0.59375 KB from total of 2.0KB 

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
#define NRT_RTU0_PACKET_DROPPED_SLICE0_PASTATID            0x0088    //PRU diagnostic error counter which increments when RTU0 drops a locally injected packet due to port disabled or rule violation
#define NRT_RTU0_PACKET_DROPPED_SLICE0_PASTATID_SIZE       0x4
#define NRT_RTU0_PACKET_DROPPED_SLICE1_PASTATID            0x008C    //PRU diagnostic error counter which increments when RTU1 drops a locally injected packet due to port disabled or rule violation
#define NRT_RTU0_PACKET_DROPPED_SLICE1_PASTATID_SIZE       0x4
#define NRT_PORT1_Q0_OVERFLOW_PASTATID                     0x0090    //Port1 Tx Q Overflow Counters
#define NRT_PORT1_Q0_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT2_Q0_OVERFLOW_PASTATID                     0x0094    //Port2 Tx Q Overflow Counters
#define NRT_PORT2_Q0_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT1_Q1_OVERFLOW_PASTATID                     0x0098    //Port1 Tx Q Overflow Counters
#define NRT_PORT1_Q1_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT2_Q1_OVERFLOW_PASTATID                     0x009C    //Port2 Tx Q Overflow Counters
#define NRT_PORT2_Q1_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT1_Q2_OVERFLOW_PASTATID                     0x00A0    //Port1 Tx Q Overflow Counters
#define NRT_PORT1_Q2_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT2_Q2_OVERFLOW_PASTATID                     0x00A4    //Port2 Tx Q Overflow Counters
#define NRT_PORT2_Q2_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT1_Q3_OVERFLOW_PASTATID                     0x00A8    //Port1 Tx Q Overflow Counters
#define NRT_PORT1_Q3_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT2_Q3_OVERFLOW_PASTATID                     0x00AC    //Port2 Tx Q Overflow Counters
#define NRT_PORT2_Q3_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT1_Q4_OVERFLOW_PASTATID                     0x00B0    //Port1 Tx Q Overflow Counters
#define NRT_PORT1_Q4_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT2_Q4_OVERFLOW_PASTATID                     0x00B4    //Port2 Tx Q Overflow Counters
#define NRT_PORT2_Q4_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT1_Q5_OVERFLOW_PASTATID                     0x00B8    //Port1 Tx Q Overflow Counters
#define NRT_PORT1_Q5_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT2_Q5_OVERFLOW_PASTATID                     0x00BC    //Port2 Tx Q Overflow Counters
#define NRT_PORT2_Q5_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT1_Q6_OVERFLOW_PASTATID                     0x00C0    //Port1 Tx Q Overflow Counters
#define NRT_PORT1_Q6_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT2_Q6_OVERFLOW_PASTATID                     0x00C4    //Port2 Tx Q Overflow Counters
#define NRT_PORT2_Q6_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT1_Q7_OVERFLOW_PASTATID                     0x00C8    //Port1 Tx Q Overflow Counters
#define NRT_PORT1_Q7_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_PORT2_Q7_OVERFLOW_PASTATID                     0x00CC    //Port2 Tx Q Overflow Counters
#define NRT_PORT2_Q7_OVERFLOW_PASTATID_SIZE                0x4
#define NRT_HOST_Q0_OVERFLOW_PASTATID                      0x00D0    //Host Tx Q Overflow Counters
#define NRT_HOST_Q0_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q1_OVERFLOW_PASTATID                      0x00D4    //Host Tx Q Overflow Counters
#define NRT_HOST_Q1_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q2_OVERFLOW_PASTATID                      0x00D8    //Host Tx Q Overflow Counters
#define NRT_HOST_Q2_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q3_OVERFLOW_PASTATID                      0x00DC    //Host Tx Q Overflow Counters
#define NRT_HOST_Q3_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q4_OVERFLOW_PASTATID                      0x00E0    //Host Tx Q Overflow Counters
#define NRT_HOST_Q4_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q5_OVERFLOW_PASTATID                      0x00E4    //Host Tx Q Overflow Counters
#define NRT_HOST_Q5_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q6_OVERFLOW_PASTATID                      0x00E8    //Host Tx Q Overflow Counters
#define NRT_HOST_Q6_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_Q7_OVERFLOW_PASTATID                      0x00EC    //Host Tx Q Overflow Counters
#define NRT_HOST_Q7_OVERFLOW_PASTATID_SIZE                 0x4
#define NRT_HOST_EGRESS_Q_PRE_OVERFLOW_PASTATID            0x00F0    //Host Egress Q (Pre-emptible) Overflow Counter
#define NRT_HOST_EGRESS_Q_PRE_OVERFLOW_PASTATID_SIZE       0x4
#define NRT_HOST_EGRESS_Q_EXP_OVERFLOW_PASTATID            0x00F4    //Host Egress Q (Express) Overflow Counter. redundant
#define NRT_HOST_EGRESS_Q_EXP_OVERFLOW_PASTATID_SIZE       0x4
#define NRT_DROPPED_PKT_SLICE0_PASTATID                    0x00F8    //Incremented if a packet is dropped at PRU0 because of a rule violation
#define NRT_DROPPED_PKT_SLICE0_PASTATID_SIZE               0x4
#define NRT_DROPPED_PKT_SLICE1_PASTATID                    0x00FC    //Incremented if a packet is dropped at PRU1 because of a rule violation
#define NRT_DROPPED_PKT_SLICE1_PASTATID_SIZE               0x4
#define NRT_RX_ERROR_SLICE0_PASTATID                       0x0100    //Incremented if there was a CRC error or Min/Max frame error at PRU0
#define NRT_RX_ERROR_SLICE0_PASTATID_SIZE                  0x4
#define NRT_RX_ERROR_SLICE1_PASTATID                       0x0104    //Incremented if there was a CRC error or Min/Max frame error at PRU1
#define NRT_RX_ERROR_SLICE1_PASTATID_SIZE                  0x4
#define RX_EOF_RTU_DS_INVALID_SLICE0_PASTATID              0x0108    //RTU0 diagnostic counter increments when RTU detects Data Status invalid condition
#define RX_EOF_RTU_DS_INVALID_SLICE0_PASTATID_SIZE         0x4
#define RX_EOF_RTU_DS_INVALID_SLICE1_PASTATID              0x010C    //RTU1 diagnostic counter increments when RTU detects Data Status invalid condition
#define RX_EOF_RTU_DS_INVALID_SLICE1_PASTATID_SIZE         0x4
#define RX_B1_NRT_ENTRY_SLICE0_PASTATID                    0x0110    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 diagnostic counter which increments when NRT path of RX_B1 handling is invoked
#define RX_B1_NRT_ENTRY_SLICE0_PASTATID_SIZE               0x4
#define RX_B1_NRT_ENTRY_SLICE1_PASTATID                    0x0114    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 diagnostic counter which increments when NRT path of RX_B1 handling is invoked
#define RX_B1_NRT_ENTRY_SLICE1_PASTATID_SIZE               0x4
#define RX_Bn_NRT_ENTRY_SLICE0_PASTATID                    0x0118    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 diagnostic counter which increments when NRT path of RX_Bn handling is invoked
#define RX_Bn_NRT_ENTRY_SLICE0_PASTATID_SIZE               0x4
#define RX_Bn_NRT_ENTRY_SLICE1_PASTATID                    0x011C    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 diagnostic counter which increments when NRT path of RX_Bn handling is invoked
#define RX_Bn_NRT_ENTRY_SLICE1_PASTATID_SIZE               0x4
#define RX_EOF_NRT_ENTRY_SLICE0_PASTATID                   0x0120    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 diagnostic counter which increments when NRT path of RX_EOF handling is invoked
#define RX_EOF_NRT_ENTRY_SLICE0_PASTATID_SIZE              0x4
#define RX_EOF_NRT_ENTRY_SLICE1_PASTATID                   0x0124    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 diagnostic counter which increments when NRT path of RX_EOF handling is invoked
#define RX_EOF_NRT_ENTRY_SLICE1_PASTATID_SIZE              0x4
#define NRT_TX_PORT1_DROPPED_PACKET_PASTATID               0x0128    //Counter for packets dropped via NRT TX Port1
#define NRT_TX_PORT1_DROPPED_PACKET_PASTATID_SIZE          0x4
#define NRT_TX_PORT2_DROPPED_PACKET_PASTATID               0x012C    //Counter for packets dropped via NRT TX Port2
#define NRT_TX_PORT2_DROPPED_PACKET_PASTATID_SIZE          0x4
#define NRT_TX_PORT1_TS_DROPPED_PACKET_PASTATID            0x0130    //Counter for packets with TS flag dropped via NRT TX Port1
#define NRT_TX_PORT1_TS_DROPPED_PACKET_PASTATID_SIZE       0x4
#define NRT_TX_PORT2_TS_DROPPED_PACKET_PASTATID            0x0134    //Counter for packets with TS flag dropped via NRT TX Port2
#define NRT_TX_PORT2_TS_DROPPED_PACKET_PASTATID_SIZE       0x4
#define NRT_INF_PORT_DISABLED_SLICE0_PASTATID              0x0138    //PRU0 diagnostic error counter which increments when RX frame is dropped due to port is disabled
#define NRT_INF_PORT_DISABLED_SLICE0_PASTATID_SIZE         0x4
#define NRT_INF_PORT_DISABLED_SLICE1_PASTATID              0x013C    //PRU1 diagnostic error counter which increments when RX frame is dropped due to port is disabled
#define NRT_INF_PORT_DISABLED_SLICE1_PASTATID_SIZE         0x4
#define NRT_INF_SAV_SLICE0_PASTATID                        0x0140    //PRU0 diagnostic error counter which increments when RX frame is dropped due to SA violation
#define NRT_INF_SAV_SLICE0_PASTATID_SIZE                   0x4
#define NRT_INF_SAV_SLICE1_PASTATID                        0x0144    //PRU1 diagnostic error counter which increments when RX frame is dropped due to SA violation
#define NRT_INF_SAV_SLICE1_PASTATID_SIZE                   0x4
#define NRT_INF_SA_BL_SLICE0_PASTATID                      0x0148    //PRU0 diagnostic error counter which increments when RX frame is dropped due to SA black listed
#define NRT_INF_SA_BL_SLICE0_PASTATID_SIZE                 0x4
#define NRT_INF_SA_BL_SLICE1_PASTATID                      0x014C    //PRU1 diagnostic error counter which increments when RX frame is dropped due to SA black listed
#define NRT_INF_SA_BL_SLICE1_PASTATID_SIZE                 0x4
#define NRT_INF_PORT_BLOCKED_SLICE0_PASTATID               0x0150    //PRU0 diagnostic error counter which increments when RX frame is dropped due to port blocked and not a special frame
#define NRT_INF_PORT_BLOCKED_SLICE0_PASTATID_SIZE          0x4
#define NRT_INF_PORT_BLOCKED_SLICE1_PASTATID               0x0154    //PRU1 diagnostic error counter which increments when RX frame is dropped due to port blocked and not a special frame
#define NRT_INF_PORT_BLOCKED_SLICE1_PASTATID_SIZE          0x4
#define NRT_INF_AFT_DROP_TAGGED_SLICE0_PASTATID            0x0158    //PRU0 diagnostic error counter which increments when RX frame is dropped due to tagged
#define NRT_INF_AFT_DROP_TAGGED_SLICE0_PASTATID_SIZE       0x4
#define NRT_INF_AFT_DROP_TAGGED_SLICE1_PASTATID            0x015C    //PRU1 diagnostic error counter which increments when RX frame is dropped due to tagged
#define NRT_INF_AFT_DROP_TAGGED_SLICE1_PASTATID_SIZE       0x4
#define NRT_INF_AFT_DROP_PRIOTAGGED_SLICE0_PASTATID        0x0160    //PRU0 diagnostic error counter which increments when RX frame is dropped due to priority tagged
#define NRT_INF_AFT_DROP_PRIOTAGGED_SLICE0_PASTATID_SIZE   0x4
#define NRT_INF_AFT_DROP_PRIOTAGGED_SLICE1_PASTATID        0x0164    //PRU1 diagnostic error counter which increments when RX frame is dropped due to priority tagged
#define NRT_INF_AFT_DROP_PRIOTAGGED_SLICE1_PASTATID_SIZE   0x4
#define NRT_INF_AFT_DROP_NOTAG_SLICE0_PASTATID             0x0168    //PRU0 diagnostic error counter which increments when RX frame is dropped due to untagged
#define NRT_INF_AFT_DROP_NOTAG_SLICE0_PASTATID_SIZE        0x4
#define NRT_INF_AFT_DROP_NOTAG_SLICE1_PASTATID             0x016C    //PRU1 diagnostic error counter which increments when RX frame is dropped due to untagged
#define NRT_INF_AFT_DROP_NOTAG_SLICE1_PASTATID_SIZE        0x4
#define NRT_INF_AFT_DROP_NOTMEMBER_SLICE0_PASTATID         0x0170    //PRU0 diagnostic error counter which increments when RX frame is dropped due to port not member of VLAN
#define NRT_INF_AFT_DROP_NOTMEMBER_SLICE0_PASTATID_SIZE    0x4
#define NRT_INF_AFT_DROP_NOTMEMBER_SLICE1_PASTATID         0x0174    //PRU1 diagnostic error counter which increments when RX frame is dropped due to port not member of VLAN
#define NRT_INF_AFT_DROP_NOTMEMBER_SLICE1_PASTATID_SIZE    0x4
#define NRT_FDB_NO_SPACE_TO_LEARN                          0x0178    //PRU diagnostic error counter which increments when an entry couldn't be learned
#define NRT_FDB_NO_SPACE_TO_LEARN_SIZE                     0x4
#define NRT_FDB_LAST_ENTRY_OVERWRITTEN_FOR_LEARNING        0x017C    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU diagnostic error counter which increments when the fourth entry is overwritten to accomodate leart MAC
#define NRT_FDB_LAST_ENTRY_OVERWRITTEN_FOR_LEARNING_SIZE   0x4
#define NRT_PREEMPT_BAD_FRAG_SLICE0_PASTATID               0x0180    //PRU0 Bad fragment Error Counter
#define NRT_PREEMPT_BAD_FRAG_SLICE0_PASTATID_SIZE          0x4
#define NRT_PREEMPT_BAD_FRAG_SLICE1_PASTATID               0x0184    //PRU1 Bad fragment Error Counter
#define NRT_PREEMPT_BAD_FRAG_SLICE1_PASTATID_SIZE          0x4
#define NRT_PREEMPT_ASSEMBLY_ERROR_SLICE0_PASTATID         0x0188    //PRU0 Fragment assembly Error Counter
#define NRT_PREEMPT_ASSEMBLY_ERROR_SLICE0_PASTATID_SIZE    0x4
#define NRT_PREEMPT_ASSEMBLY_ERROR_SLICE1_PASTATID         0x018C    //PRU1 Fragment assembly Error Counter
#define NRT_PREEMPT_ASSEMBLY_ERROR_SLICE1_PASTATID_SIZE    0x4
#define NRT_PREEMPT_FRAG_COUNT_TX_SLICE0_PASTATID          0x0190    //PRU0 Fragment count in TX
#define NRT_PREEMPT_FRAG_COUNT_TX_SLICE0_PASTATID_SIZE     0x4
#define NRT_PREEMPT_FRAG_COUNT_TX_SLICE1_PASTATID          0x0194    //PRU1 Fragment count in TX
#define NRT_PREEMPT_FRAG_COUNT_TX_SLICE1_PASTATID_SIZE     0x4
#define NRT_PREEMPT_ASSEMBLY_OK_SLICE0_PASTATID            0x0198    //PRU0 Assembly Completed
#define NRT_PREEMPT_ASSEMBLY_OK_SLICE0_PASTATID_SIZE       0x4
#define NRT_PREEMPT_ASSEMBLY_OK_SLICE1_PASTATID            0x019C    //PRU1 Assembly Completed
#define NRT_PREEMPT_ASSEMBLY_OK_SLICE1_PASTATID_SIZE       0x4
#define NRT_PREEMPT_FRAG_COUNT_RX_SLICE0_PASTATID          0x01A0    //PRU0 Fragments received
#define NRT_PREEMPT_FRAG_COUNT_RX_SLICE0_PASTATID_SIZE     0x4
#define NRT_PREEMPT_FRAG_COUNT_RX_SLICE1_PASTATID          0x01A4    //PRU1 Fragments received
#define NRT_PREEMPT_FRAG_COUNT_RX_SLICE1_PASTATID_SIZE     0x4
#define NRT_PREEMPT_DEBUG_GLOBAL_ERROR_SLICE0_PASTATID     0x01A8    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 Global Debug Error Counter
#define NRT_PREEMPT_DEBUG_GLOBAL_ERROR_SLICE0_PASTATID_SIZE 0x4
#define NRT_PREEMPT_DEBUG_GLOBAL_ERROR_SLICE1_PASTATID     0x01AC    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 Global Debug Error Counter
#define NRT_PREEMPT_DEBUG_GLOBAL_ERROR_SLICE1_PASTATID_SIZE 0x4
#define NRT_PREEMPT_DEBUG_SMDCx_SLICE0_PASTATID            0x01B0    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 Debug counter SMDCx
#define NRT_PREEMPT_DEBUG_SMDCx_SLICE0_PASTATID_SIZE       0x4
#define NRT_PREEMPT_DEBUG_SMDCx_SLICE1_PASTATID            0x01B4    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 Debug counter SMDCx
#define NRT_PREEMPT_DEBUG_SMDCx_SLICE1_PASTATID_SIZE       0x4
#define NRT_PREEMPT_DEBUG_SMDSx_SLICE0_PASTATID            0x01B8    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 Debug counter SMDSx
#define NRT_PREEMPT_DEBUG_SMDSx_SLICE0_PASTATID_SIZE       0x4
#define NRT_PREEMPT_DEBUG_SMDSx_SLICE1_PASTATID            0x01BC    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 Debug counter SMDSx
#define NRT_PREEMPT_DEBUG_SMDSx_SLICE1_PASTATID_SIZE       0x4
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAG0_ERROR_SLICE0_PASTATID 0x01C0    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 Debug counter - Error in SMDSx
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAG0_ERROR_SLICE0_PASTATID_SIZE 0x4
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAG0_ERROR_SLICE1_PASTATID 0x01C4    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 Debug counter - Error in SMDSx
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAG0_ERROR_SLICE1_PASTATID_SIZE 0x4
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAGX_ERROR_SLICE0_PASTATID 0x01C8    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 Debug counter - Error in SMDCx
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAGX_ERROR_SLICE0_PASTATID_SIZE 0x4
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAGX_ERROR_SLICE1_PASTATID 0x01CC    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 Debug counter - Error in SMDCx
#define NRT_PREEMPT_DEBUG_EOF_MPKT_FRAGX_ERROR_SLICE1_PASTATID_SIZE 0x4
#define NRT_RECYCLE_TXPRU_COUNTER_SLICE0_PASTATID          0x01D0    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - TXPRU recycle counter Slice0
#define NRT_RECYCLE_TXPRU_COUNTER_SLICE0_PASTATID_SIZE     0x4
#define NRT_RECYCLE_TXPRU_COUNTER_SLICE1_PASTATID          0x01D4    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - TXPRU recycle counter Slice1
#define NRT_RECYCLE_TXPRU_COUNTER_SLICE1_PASTATID_SIZE     0x4
#define NRT_RECYCLE_RXERR_RTU_COUNTER_SLICE0_PASTATID      0x01D8    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - RTU recycle on RXERR counter Slice0
#define NRT_RECYCLE_RXERR_RTU_COUNTER_SLICE0_PASTATID_SIZE 0x4
#define NRT_RECYCLE_RXERR_RTU_COUNTER_SLICE1_PASTATID      0x01DC    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - RTU recycle on RXERR counter Slice1
#define NRT_RECYCLE_RXERR_RTU_COUNTER_SLICE1_PASTATID_SIZE 0x4
#define NRT_RECYCLE_BG_RTU_COUNTER_SLICE0_PASTATID         0x01E0    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - RTU recycle from BG task counter Slice0
#define NRT_RECYCLE_BG_RTU_COUNTER_SLICE0_PASTATID_SIZE    0x4
#define NRT_RECYCLE_BG_RTU_COUNTER_SLICE1_PASTATID         0x01E4    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] Debug counter - RTU recycle from BG task counter Slice1
#define NRT_RECYCLE_BG_RTU_COUNTER_SLICE1_PASTATID_SIZE    0x4
#define RX_EOF_SHORT_FRAMEERR_SLICE0_PASTATID              0x01E8    //PRU0 diagnostic error counter which increments if EOF task is scheduled without seeing RX_B1
#define RX_EOF_SHORT_FRAMEERR_SLICE0_PASTATID_SIZE         0x4
#define RX_EOF_SHORT_FRAMEERR_SLICE1_PASTATID              0x01EC    //PRU1 diagnostic error counter which increments if EOF task is scheduled without seeing RX_B1
#define RX_EOF_SHORT_FRAMEERR_SLICE1_PASTATID_SIZE         0x4
#define RX_B1_ENTRY_SLICE0_PASTATID                        0x01F0    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 diagnostic counter which increments when RX_B1 handling is invoked
#define RX_B1_ENTRY_SLICE0_PASTATID_SIZE                   0x4
#define RX_B1_ENTRY_SLICE1_PASTATID                        0x01F4    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 diagnostic counter which increments when RX_B1 handling is invoked
#define RX_B1_ENTRY_SLICE1_PASTATID_SIZE                   0x4
#define RX_Bn_ENTRY_SLICE0_PASTATID                        0x01F8    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 diagnostic counter which increments when RX_Bn handling is invoked
#define RX_Bn_ENTRY_SLICE0_PASTATID_SIZE                   0x4
#define RX_Bn_ENTRY_SLICE1_PASTATID                        0x01FC    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 diagnostic counter which increments when RX_Bn handling is invoked
#define RX_Bn_ENTRY_SLICE1_PASTATID_SIZE                   0x4
#define RX_EOF_ENTRY_SLICE0_PASTATID                       0x0200    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU0 diagnostic counter which increments when RX_EOF handling is invoked
#define RX_EOF_ENTRY_SLICE0_PASTATID_SIZE                  0x4
#define RX_EOF_ENTRY_SLICE1_PASTATID                       0x0204    //[DEBUG_L2_DIAGNOSTICS |  not in release binary] PRU1 diagnostic counter which increments when RX_EOF handling is invoked
#define RX_EOF_ENTRY_SLICE1_PASTATID_SIZE                  0x4
#define PA_STAT_END_OFFSET                                 0x0208

// total PA_STAT memory usage : 0.5078125 KB from total of 2.0KB 


#endif // ____switch_mem_map_h
