/**********************************************************************
* Copyright (C) 2012-2022 Cadence Design Systems, Inc.
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* 3. Neither the name of the copyright holder nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
**********************************************************************
* WARNING: This file is auto-generated using api-generator utility.
*          api-generator: 12.03.9e11b77(origin/DRV-3827_extract_sanity_to_c_file)
*          Do not edit it manually.
**********************************************************************
* Cadence Core Driver for the Cadence DisplayPort (DP) core. This header
* file lists the Supporting structures for the DP core driver
**********************************************************************/

#ifndef DP_SIDEBAND_MSG_IF_H
#define DP_SIDEBAND_MSG_IF_H

/* parasoft-begin-suppress MISRA2012-RULE-1_1_a_c90-2 "C90 - limits, DRV-3906" */
/* parasoft-begin-suppress MISRA2012-RULE-1_1_b_c90-2 "C90 - limits, DRV-3906" */

#include "cdn_stdtypes.h"
#include "custom_types.h"

/** @defgroup ConfigInfo  Configuration and Hardware Operation Information
 *  The following definitions specify the driver operation environment that
 *  is defined by hardware configuration or client code. These defines are
 *  located in the header file of the core driver.
 *  @{
 */

/**********************************************************************
* Defines
**********************************************************************/
/** Maximum number of I2C Transactions */
#define SBM_DP_REMOTE_I2C_READ_MAX_TRANSACTIONS (4U)

/** Maximum number of SDP streams */
#define SBM_DRM_DP_MAX_SDP_STREAMS (16U)

/**
 *  @}
 */

/** @defgroup DataStructure Dynamic Data Structures
 *  This section defines the data structures used by the driver to provide
 *  hardware information, modification and dynamic operation of the driver.
 *  These data structures are defined in the header file of the core driver
 *  and utilized by the API.
 *  @{
 */

/**********************************************************************
* Forward declarations
**********************************************************************/
typedef struct SBM_drm_dp_nak_reply_s SBM_drm_dp_nak_reply;
typedef struct SBM_drm_dp_link_addr_reply_port_s SBM_drm_dp_link_addr_reply_port;
typedef struct SBM_drm_dp_link_address_ack_reply_s SBM_drm_dp_link_address_ack_reply;
typedef struct SBM_drm_dp_remote_dpcd_read_ack_reply_s SBM_drm_dp_remote_dpcd_read_ack_reply;
typedef struct SBM_drm_dp_remote_dpcd_write_ack_reply_s SBM_drm_dp_remote_dpcd_write_ack_reply;
typedef struct SBM_drm_dp_remote_dpcd_write_nak_reply_s SBM_drm_dp_remote_dpcd_write_nak_reply;
typedef struct SBM_drm_dp_remote_i2c_read_ack_reply_s SBM_drm_dp_remote_i2c_read_ack_reply;
typedef struct SBM_drm_dp_remote_i2c_read_nak_reply_s SBM_drm_dp_remote_i2c_read_nak_reply;
typedef struct SBM_drm_dp_remote_i2c_write_ack_reply_s SBM_drm_dp_remote_i2c_write_ack_reply;
typedef struct SBM_drm_dp_allocate_payload_s SBM_drm_dp_allocate_payload;
typedef struct SBM_drm_dp_allocate_payload_ack_reply_s SBM_drm_dp_allocate_payload_ack_reply;
typedef struct SBM_drm_dp_connection_status_notify_s SBM_drm_dp_connection_status_notify;
typedef struct SBM_drm_dp_remote_dpcd_read_s SBM_drm_dp_remote_dpcd_read;
typedef struct SBM_drm_dp_remote_dpcd_write_s SBM_drm_dp_remote_dpcd_write;
typedef struct SBM_drm_dp_transactions_s SBM_drm_dp_transactions;
typedef struct SBM_drm_dp_remote_i2c_read_s SBM_drm_dp_remote_i2c_read;
typedef struct SBM_drm_dp_remote_i2c_write_s SBM_drm_dp_remote_i2c_write;
typedef struct SBM_drm_dp_port_number_req_s SBM_drm_dp_port_number_req;
typedef struct SBM_drm_dp_enum_path_resources_ack_reply_s SBM_drm_dp_enum_path_resources_ack_reply;
typedef struct SBM_drm_dp_port_number_rep_s SBM_drm_dp_port_number_rep;
typedef struct SBM_drm_dp_resource_status_notify_s SBM_drm_dp_resource_status_notify;
typedef struct SBM_ack_req_s SBM_ack_req;
typedef struct SBM_drm_dp_sideband_msg_req_body_s SBM_drm_dp_sideband_msg_req_body;
typedef struct SBM_ack_replies_s SBM_ack_replies;
typedef struct SBM_drm_dp_sideband_msg_reply_body_s SBM_drm_dp_sideband_msg_reply_body;
typedef struct SBM_drm_dp_sideband_msg_tx_s SBM_drm_dp_sideband_msg_tx;
typedef struct SBM_drm_dp_sideband_msg_hdr_s SBM_drm_dp_sideband_msg_hdr;
typedef struct SBM_drm_dp_sideband_msg_rx_s SBM_drm_dp_sideband_msg_rx;

/**
 *  @}
 */

/* parasoft-end-suppress MISRA2012-RULE-1_1_b_c90-2 */
/* parasoft-end-suppress MISRA2012-RULE-1_1_a_c90-2 */

#endif  /* DP_SIDEBAND_MSG_IF_H */
