/*
 *  Copyright (c) Texas Instruments Incorporated 2018-2020
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
 *  \ingroup DRV_UDMA_MODULE
 *  \defgroup DRV_UDMA_CH_MODULE UDMA Driver Channel API
 *            This is UDMA driver channel related configuration parameters and
 *            API
 *
 *  @{
 */

/**
 *  \file udma_ch.h
 *
 *  \brief UDMA Channel related parameters and API.
 */

#ifndef UDMA_CH_H_
#define UDMA_CH_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief Macro used to specify that DMA Channel ID is invalid.
 * Used in the API #Udma_chOpen.
 */
#define UDMA_DMA_CH_INVALID             ((uint32_t) 0xFFFF0000U)
/**
 * \brief Macro used to specify any available DMA Channel while requesting
 * one. Used in the API #Udma_chOpen.
 */
#define UDMA_DMA_CH_ANY                 ((uint32_t) 0xFFFF0001U)
/**
 * \brief Macro used to specify that the DMA Channel is not applicable for a
 * particular mode.
 */
#define UDMA_DMA_CH_NA                  ((uint32_t) 0xFFFF0002U)
/** \brief Macro used to specify that the UTC ID is invalid. */
#define UDMA_UTC_ID_INVALID             ((uint32_t) 0xFFFF0003U)
/** \brief Macro used to specify that the Mapped Channel Group is invalid. */
#define UDMA_MAPPED_GROUP_INVALID       ((uint32_t) 0xFFFF0004U)

/** \brief DMSC Extended Channel Type Flag for BCDMA Block Copy */
#define UDMA_DMSC_EXTENDED_CH_TYPE_BCDMA_BLK_CPY     ((uint8_t) 1U)

/** \brief DMSC Extended Channel Type Flag for BCDMA split TR TX channels */
#define UDMA_DMSC_EXTENDED_CH_TYPE_BCDMA_SPLIT_TR_TX ((uint8_t) 0U)

/**
 *  \anchor Udma_ChFlag
 *  \name UDMA Channel Flag
 *
 *  UDMA channel flags bit field used to form the channel type.
 *
 *  @{
 */
/** \brief TX channel flag */
#define UDMA_CH_FLAG_TX                 ((uint32_t) 0x0001U)
/** \brief RX channel flag */
#define UDMA_CH_FLAG_RX                 ((uint32_t) 0x0002U)
/** \brief Block copy mode channel flag */
#define UDMA_CH_FLAG_BLK_COPY           ((uint32_t) 0x0004U)
/** \brief PDMA channel flag */
#define UDMA_CH_FLAG_PDMA               ((uint32_t) 0x0008U)
/** \brief PSIL channel flag meant for periperals like Ethernet, SA2UL */
#define UDMA_CH_FLAG_PSIL               ((uint32_t) 0x0010U)
/** \brief UTC channel flag */
#define UDMA_CH_FLAG_UTC                ((uint32_t) 0x0020U)
/** \brief High capacity channel flag */
#define UDMA_CH_FLAG_HC                 ((uint32_t) 0x0040U)
/** \brief Ultra high capacity channel flag */
#define UDMA_CH_FLAG_UHC                ((uint32_t) 0x0080U)
/** \brief Mapped TX/RX channel flag */
#define UDMA_CH_FLAG_MAPPED             ((uint32_t) 0x0100U)
/* @} */

/**
 *  \anchor Udma_ChType
 *  \name UDMA Channel Type
 *
 *  UDMA channel type formed based on channel flags.
 *
 *  @{
 */
/** \brief TR block copy type - TX/RX pair */
#define UDMA_CH_TYPE_TR_BLK_COPY        (UDMA_CH_FLAG_BLK_COPY |        \
                                         UDMA_CH_FLAG_TX |              \
                                         UDMA_CH_FLAG_RX)
/** \brief High capacity TR block copy type - TX/RX pair */
#define UDMA_CH_TYPE_TR_BLK_COPY_HC     (UDMA_CH_FLAG_BLK_COPY |        \
                                         UDMA_CH_FLAG_TX |              \
                                         UDMA_CH_FLAG_RX |              \
                                         UDMA_CH_FLAG_HC)
/** \brief Ultra high capacity TR block copy type - TX/RX pair */
#define UDMA_CH_TYPE_TR_BLK_COPY_UHC    (UDMA_CH_FLAG_BLK_COPY |        \
                                         UDMA_CH_FLAG_TX |              \
                                         UDMA_CH_FLAG_RX |              \
                                         UDMA_CH_FLAG_UHC)
/** \brief TX channel type */
#define UDMA_CH_TYPE_TX                 (UDMA_CH_FLAG_TX | UDMA_CH_FLAG_PSIL)
/** \brief High capacity TX channel type */
#define UDMA_CH_TYPE_TX_HC              (UDMA_CH_FLAG_TX | UDMA_CH_FLAG_PSIL | UDMA_CH_FLAG_HC)
/** \brief Ultra high capacity TX channel type */
#define UDMA_CH_TYPE_TX_UHC             (UDMA_CH_FLAG_TX | UDMA_CH_FLAG_PSIL | UDMA_CH_FLAG_UHC)

/** \brief RX channel type */
#define UDMA_CH_TYPE_RX                 (UDMA_CH_FLAG_RX | UDMA_CH_FLAG_PSIL)
/** \brief High capacity RX channel type */
#define UDMA_CH_TYPE_RX_HC              (UDMA_CH_FLAG_RX | UDMA_CH_FLAG_PSIL | UDMA_CH_FLAG_HC)
/** \brief Ultra high capacity RX channel type */
#define UDMA_CH_TYPE_RX_UHC             (UDMA_CH_FLAG_RX | UDMA_CH_FLAG_PSIL | UDMA_CH_FLAG_UHC)

/** \brief PDMA TX channel type */
#define UDMA_CH_TYPE_PDMA_TX            (UDMA_CH_FLAG_TX | UDMA_CH_FLAG_PDMA)
/** \brief High capacity PDMA TX channel type */
#define UDMA_CH_TYPE_PDMA_TX_HC         (UDMA_CH_FLAG_TX | UDMA_CH_FLAG_PDMA | UDMA_CH_FLAG_HC)
/** \brief Ultra high capacity PDMA TX channel type */
#define UDMA_CH_TYPE_PDMA_TX_UHC        (UDMA_CH_FLAG_TX | UDMA_CH_FLAG_PDMA | UDMA_CH_FLAG_UHC)

/** \brief PDMA RX channel type */
#define UDMA_CH_TYPE_PDMA_RX            (UDMA_CH_FLAG_RX | UDMA_CH_FLAG_PDMA)
/** \brief High capacity PDMA RX channel type */
#define UDMA_CH_TYPE_PDMA_RX_HC         (UDMA_CH_FLAG_RX | UDMA_CH_FLAG_PDMA | UDMA_CH_FLAG_HC)
/** \brief Ultra high capacity PDMA RX channel type */
#define UDMA_CH_TYPE_PDMA_RX_UHC        (UDMA_CH_FLAG_RX | UDMA_CH_FLAG_PDMA | UDMA_CH_FLAG_UHC)

/**
 *  \brief Mapped TX channel.
 *  This could be different type of mapped TX channels.
 *  See \ref Udma_MappedTxGrpSoc for differnt types of SOC specific mapped TX channels.
 */
#define UDMA_CH_TYPE_TX_MAPPED          (UDMA_CH_FLAG_TX | UDMA_CH_FLAG_PSIL | UDMA_CH_FLAG_MAPPED)
/**
 *  \brief Mapped RX channel.
 *  This could be different type of mapped RX channels.
 *  See \ref Udma_MappedRxGrpSoc for differnt types of SOC specific mapped RX channels.
 */
#define UDMA_CH_TYPE_RX_MAPPED          (UDMA_CH_FLAG_RX | UDMA_CH_FLAG_PSIL | UDMA_CH_FLAG_MAPPED)

/**
 *  \brief UTC channel. This could be
 *      - UTC with descriptor posted through UDMA external channel like VPAC/DMPAC
 *      - DRU channel with direct mode with descriptor posted through direct
 *        DRU register writes or with indirect mode through External channel
 */
#define UDMA_CH_TYPE_UTC                (UDMA_CH_FLAG_UTC)
/* @} */

/**
 *  \anchor Udma_PdmaElemSize
 *  \name UDMA PDMA element size
 *
 *  @{
 */
/** \brief 8-bits Element size */
#define UDMA_PDMA_ES_8BITS              ((uint32_t) 0x00U)
/** \brief 16-bits Element size */
#define UDMA_PDMA_ES_16BITS             ((uint32_t) 0x01U)
/** \brief 24-bits Element size */
#define UDMA_PDMA_ES_24BITS             ((uint32_t) 0x02U)
/** \brief 32-bits Element size */
#define UDMA_PDMA_ES_32BITS             ((uint32_t) 0x03U)
/** \brief 64-bits Element size */
#define UDMA_PDMA_ES_64BITS             ((uint32_t) 0x04U)
/** \brief Set this for MCAN element size - not applicable */
#define UDMA_PDMA_ES_DONTCARE           ((uint32_t) 0x00U)
/* @} */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 *  \brief UDMA channel open parameters.
 */
typedef struct
{
    uint32_t                chNum;
    /**< [IN] UDMAP channel to allocate.
     *
     *   Set to #UDMA_DMA_CH_ANY  if the channel to allocate and open
     *   could be any from the free pool.
     *   Set to the actual DMA channel when specific DMA channel need to be
     *   allocated. This channel number is relative to the channel type
     *   (TX, RX or External). The driver will internally calculate the
     *   respective offset to get the actual UDMAP channel number.
     */
    uint32_t                peerChNum;
    /**< [IN] The peer channel to link the #chNum using PSILCFG.
     *
     *   Incase of PDMA peripherals this represent the PDMA channel to which the
     *   UDMA channel should pair with. Refer \ref Udma_PdmaCh macros.
     *
     *   Incase of other PSIL master peripherals this represent the thread ID
     *   to which the UDMA channel should pair with. Refer \ref Udma_PsilCh macros.
     *
     *   Incase of Block copy channel type (#UDMA_CH_TYPE_TR_BLK_COPY), set
     *   this to #UDMA_DMA_CH_NA, as the corresponding RX channel (same
     *   index as TX channel) is assumed to be paired with and the driver
     *   internally sets this up. The #UdmaChPrms_init API takes care of
     *   this.
     *
     *   Incase of UTC channel type (#UDMA_CH_TYPE_UTC), set this to
     *   #UDMA_DMA_CH_NA.
     */
    uint32_t                utcId;
    /**< [IN] The UTC instance to use when channel type is #UDMA_CH_TYPE_UTC.
     *   Refer \ref Udma_UtcIdSoc macro for details.
     *
     *   For other channel type set to #UDMA_UTC_ID_INVALID
     */
    uint32_t                mappedChGrp;
    /**< [IN] The Mapped channel group to use when channel type is
     *   #UDMA_CH_TYPE_TX_MAPPED or #UDMA_CH_TYPE_RX_MAPPED.
     *   Refer \ref Udma_MappedTxGrpSoc macro for details about mapped TX channel groups
     *   or \ref Udma_MappedRxGrpSoc macro for details about mapped RX channel groups.
     *
     *   For other channel type set to #UDMA_MAPPED_GROUP_INVALID
     */
    void                   *appData;
    /**< [IN] Application/caller context pointer passed back in all the channel
     *    callback functions. This could be used by the caller to identify
     *    the channel for which the callback is called.
     *    This can be set to NULL, if not required by caller. */
    Udma_RingPrms           fqRingPrms;
    /**< [IN] Free queue ring params where descriptors are queued */
    Udma_RingPrms           cqRingPrms;
    /**< [IN] Completion queue ring params where descriptors are dequeued
     *   This is not used for AM64x kind of devices, but even if the application
     *   sets this it will be ignored. But its not required to be set.
     */
    Udma_RingPrms           tdCqRingPrms;
    /**< [IN] Teardown completion queue ring params where teardown
     *   response and TR response incase of direct TR mode are received from
     *   UDMA
     *   This is not used for AM64x kind of devices, but even if the application
     *   sets this it will be ignored. But its not required to be set.
     */
} Udma_ChPrms;

/**
 *  \brief UDMA TX channel parameters.
 */
typedef struct
{
    uint8_t                 pauseOnError;
    /**< [IN] Bool: When set (UTRUE), pause channel on error */
    uint8_t                 filterEinfo;
    /**< [IN] Bool: When set (UTRUE), filter out extended info */
    uint8_t                 filterPsWords;
    /**< [IN] Bool: When set (UTRUE), filter out protocl specific words */
    uint8_t                 addrType;
    /**< [IN] Address type for this channel.
     *   Refer \ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_atype */
    uint8_t                 chanType;
    /**< [IN] Channel type. Refer \ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_chan_type */
    uint16_t                fetchWordSize;
    /**< [IN] Descriptor/TR Size in 32-bit words */
    uint8_t                 busPriority;
    /**< [IN] 3-bit priority value (0=highest, 7=lowest) */
    uint8_t                 busQos;
    /**< [IN] 3-bit qos value (0=highest, 7=lowest) */
    uint8_t                 busOrderId;
    /**< [IN] 4-bit orderid value */
    uint8_t                 dmaPriority;
    /**< [IN] This field selects which scheduling bin the channel will be
     *   placed in for bandwidth allocation of the Tx DMA units.
     *   Refer \ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_sched_priority */
    uint8_t                 txCredit;
    /**< [IN] TX credit for external channels */
    uint16_t                fifoDepth;
    /**< [IN] The fifo depth is used to specify how many FIFO data phases
     *   deep the Tx per channel FIFO will be for the channel.
     *   While the maximum depth of the Tx FIFO is set at design time,
     *   the FIFO depth can be artificially reduced in order to control the
     *   maximum latency which can be introduced due to buffering effects.
     *
     *   The maximum FIFO depth suppported depends on the channel type as
     *   given below:
     *   Normal Capacity Channel        - CSL_NAVSS_UDMAP_TX_CHANS_FDEPTH (128 bytes)
     *   High Capacity Channel          - CSL_NAVSS_UDMAP_TX_HC_CHANS_FDEPTH (1024 bytes)
     *   Ultra High Capacity Channel    - CSL_NAVSS_UDMAP_TX_UHC_CHANS_FDEPTH (4096 bytes)
     *
     *   The default init API will set this paramater as per the channel type.
     */
    uint8_t                 burstSize;
    /**< [IN] Specifies the nominal burst size and alignment for data transfers
     *   on this channel.
     *   Refer \ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_burst_size.
     *   Note1: This parameter should be set less than or equal to the FIFO
     *   depth parameter set for UTC channel i.e.
     *          fifoDepth >= burstSize
     *   Note2: In case of packet mode TX channels, the Tx fifoDepth must be at
     *   least 2 PSI-L data phases (32 bytes) larger than the burst size given
     *   in this field in order to hold the packet info and extended packet info
     *   header which is placed at the front of the data packet in addition
     *   to the payload i.e.
     *          fifoDepth >= (burstSize + 32 bytes)
     *
     *   Below are the supported burst sizes for various channel types
     *   Normal Capacity Channel        - 64 bytes
     *   High Capacity Channel          - 64, 128 or 256 bytes
     *   Ultra High Capacity Channel    - 64, 128 or 256 bytes
     */
    uint8_t                 supressTdCqPkt;
    /**< [IN] Bool: Specifies whether or not the channel should suppress
     *   sending the single data phase teardown packet when teardown is
     *   complete.
     *      UFALSE = TD packet is sent
     *      UTRUE = Suppress sending TD packet
     *   TODO: Should we allocate tdCq based on this flag?
     */
} Udma_ChTxPrms;

/**
 *  \brief UDMA RX channel parameters.
 */
typedef struct
{
    uint8_t                 pauseOnError;
    /**< [IN] Bool: When set (UTRUE), pause channel on error */
    uint8_t                 addrType;
    /**< [IN] Address type for this channel.
     *   Refer \ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_atype */
    uint8_t                 chanType;
    /**< [IN] Channel type. Refer \ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_chan_type */
    uint16_t                fetchWordSize;
    /**< [IN] Descriptor/TR Size in 32-bit words */
    uint8_t                 busPriority;
    /**< [IN] 3-bit priority value (0=highest, 7=lowest) */
    uint8_t                 busQos;
    /**< [IN] 3-bit qos value (0=highest, 7=lowest) */
    uint8_t                 busOrderId;
    /**< [IN] 4-bit orderid value */
    uint8_t                 dmaPriority;
    /**< [IN] This field selects which scheduling bin the channel will be
     *   placed in for bandwidth allocation of the Tx DMA units.
     *   Refer \ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_sched_priority */
    uint16_t                flowIdFwRangeStart;
    /**< [IN] Starting flow ID value for firewall check */
    uint16_t                flowIdFwRangeCnt;
    /**< [IN] Number of valid flow ID's starting from flowIdFwRangeStart
     *   for firewall check */
    uint8_t                flowEInfoPresent;
    /**< [IN] default flow config parameter for EPIB
     *   Refer \ref tisci_msg_rm_udmap_flow_cfg_req::rx_einfo_present */
    uint8_t                flowPsInfoPresent;
    /**< [IN] default flow config parameter for psInfo
     *   Refer \ref tisci_msg_rm_udmap_flow_cfg_req::rx_psinfo_present */
    uint8_t                flowErrorHandling;
    /**< [IN] default flow config parameter for Error Handling
     *   Refer \ref tisci_msg_rm_udmap_flow_cfg_req::rx_error_handling */
    uint8_t                flowSopOffset;
    /**< [IN] default flow config parameter for SOP offset
     *   Refer \ref tisci_msg_rm_udmap_flow_cfg_req::rx_sop_offset */
    uint8_t                 ignoreShortPkts;
    /**< [IN] Bool: This field controls whether or not short packets will be
     *   treated as exceptions (UFALSE) or ignored (UTRUE) for the channel.
     *   This field is only used when the channel is in split UTC mode. */
    uint8_t                 ignoreLongPkts;
    /**< [IN] Bool: This field controls whether or not long packets will be
     *   treated as exceptions (UFALSE) or ignored (UTRUE) for the channel.
     *   This field is only used when the channel is in split UTC mode. */
    uint32_t                configDefaultFlow;
    /**< [IN] Bool: This field controls whether or not to program the default
     *   flow.
     *   UTRUE - Configures the default flow equal to the RX channel number
     *   UFALSE - Doesn't configure the default flow of channel.
     *   The caller can allocate and use other generic flows or get the
     *   default flow handle and configure the flow using #Udma_flowConfig
     *   API at a later point of time */
    uint8_t                 burstSize;
    /**< [IN] Specifies the nominal burst size and alignment for data transfers
     *   on this channel.
     *   Refer \ref tisci_msg_rm_udmap_rx_ch_cfg_req::rx_burst_size.
     *   Note1: This parameter should be set less than or equal to the FIFO
     *   depth parameter set for UTC channel i.e.
     *          fifoDepth >= burstSize
     *   Note2: In case of packet mode TX channels, the Tx fifoDepth must be at
     *   least 2 PSI-L data phases (32 bytes) larger than the burst size given
     *   in this field in order to hold the packet info and extended packet info
     *   header which is placed at the front of the data packet in addition
     *   to the payload i.e.
     *          fifoDepth >= (burstSize + 32 bytes)
     *
     *   Below are the supported burst sizes for various channel types
     *   Normal Capacity Channel        - 64 bytes
     *   High Capacity Channel          - 64, 128 or 256 bytes
     *   Ultra High Capacity Channel    - 64, 128 or 256 bytes
     */
} Udma_ChRxPrms;

/**
 *  \brief UDMA UTC channel parameters.
 */
typedef struct
{
    uint8_t                 pauseOnError;
    /**< [IN] Bool: When set (UTRUE), pause channel on error */
    uint8_t                 addrType;
    /**< [IN] Address type for this channel.
     *   Refer \ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_atype */
    uint8_t                 chanType;
    /**< [IN] Channel type. Refer \ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_chan_type */
    uint16_t                fetchWordSize;
    /**< [IN] Descriptor/TR Size in 32-bit words */
    uint8_t                 busPriority;
    /**< [IN] 3-bit priority value (0=highest, 7=lowest) */
    uint8_t                 busQos;
    /**< [IN] 3-bit qos value (0=highest, 7=lowest) */
    uint8_t                 busOrderId;
    /**< [IN] 4-bit orderid value */
    uint8_t                 dmaPriority;
    /**< [IN] This field selects which scheduling bin the channel will be
     *   placed in for bandwidth allocation of the Tx DMA units.
     *   Refer \ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_sched_priority */
    uint8_t                 burstSize;
    /**< [IN] Specifies the nominal burst size and alignment for data transfers
     *   on this channel.
     *   Refer \ref tisci_msg_rm_udmap_tx_ch_cfg_req::tx_burst_size.
     *   Note1: This parameter should be set less than or equal to the FIFO
     *   depth parameter set i.e.
     *          fifoDepth >= burstSize
     *
     *   Below are the supported burst sizes for various channel types
     *   Normal Capacity Channel        - 64 or 128 bytes
     *   High Capacity Channel          - 64, 128 or 256 bytes
     *   Ultra High Capacity Channel    - 64, 128 or 256 bytes
     */
    uint8_t                 supressTdCqPkt;
    /**< [IN] Bool: Specifies whether or not the channel should suppress
     *   sending the single data phase teardown packet when teardown is
     *   complete.
     *      UFALSE = TD packet is sent
     *      UTRUE = Suppress sending TD packet
     *   TODO: Should we allocate tdCq based on this flag?
     */
#if (UDMA_NUM_UTC_INSTANCE > 0)
    /* Below fields are applicable only for DRU UTC */
    uint64_t                druOwner;
    /**< [IN] This field controls how the TR is received by the DRU.
     *   Refer \ref CSL_DruOwner. This only applicable for DRU UTC type
     *   Note: This mode once set cannot be changed after a channel is enabled.
     *   One can't switch the submission mode dynamically when the channel is
     *   enabled. It can changed only after a successful teardown/disable
     *   sequence.
     */
    uint32_t                druQueueId;
    /**< [IN] Channel scheduling queue to be used. Refer \ref CSL_DruQueueId.
     *        This only applicable for DRU UTC type
     *        All the DRUs only have 5 queues implemented in the current design.
     *        1 Priority queue and 4 round robin queues.
     *        The priority queue is queue 0 the round robin
     *        queues are queues 1 - 4.
     */
#endif
} Udma_ChUtcPrms;

/**
 *  \brief UDMA PDMA channel Static TR parameters.
 */
typedef struct
{
    uint32_t                elemSize;
    /**< [IN] Element size. This field specifies how much data is transferred
     *   in each write which is performed by the PDMA.
     *   This is the X static TR parameter of PDMA.
     *
     *   In case of MCAN TX/RX PDMA channel, this is not used and should be
     *   set to 0.
     *
     *   Refer \ref Udma_PdmaElemSize for supported values. */
    uint32_t                elemCnt;
    /**< [IN] Element count. This field specifies how many elements to
     *   transfer each time a trigger is received on the PDMA channel.
     *   This is the Y static TR parameter of PDMA.
     *
     *   In case of MCAN PDMA channel, this represents the buffer size.
     *   In case of MCAN TX, this field specifies how many bytes should be
     *   written to an MCAN TX buffer. This field includes the 8 byte MCAN
     *   header on the initial packet fragment. The PDMA will break up the
     *   source packet into fragments of this buffer size, copying the 8 byte
     *   MCAN header for the initial fragment, and then skipping it for each
     *   additional fragment and thus reusing the header from the first
     *   fragment. A buffer size less than 16 is treated as 16, and a buffer
     *   size greater than 72 is treated as 72.
     *   In case of MCAN RX, this field specifies how many bytes should be
     *   read from an MCAN RX buffer. This field includes the 8 byte MCAN
     *   header on the initial packet fragment. A buffer size less than 16
     *   is treated as 16, and a buffer size greater than 72 is treated as 72.
     */
    uint32_t                fifoCnt;
    /**< [IN] FIFO count. This field specifies how many full FIFO operations
     *   comprise a complete packet. When the count has been reached, the
     *   PDMA will close the packet with an 'EOP' indication. If this parameter
     *   is set to 0, then no packet delineation is supplied by the PDMA and
     *   all framing is controlled via the UDMA TR.
     *
     *   This is the Z static TR parameter of PDMA.
     *   This is NA for TX and should be set to 0.
     *   In case of MCAN RX, this represents the buffer count. This field
     *   specifies how many MCAN RX buffers should be read before closing the
     *   CPPI packet with an 'EOP' indication. When this count is greater
     *   than 1, multiple MCAN RX buffers will be read into a single CPPI
     *   packet buffer. The 8 byte MCAN header will be skipped on subsequent
     *   MCAN buffer reads. Setting this field to NULL will suppress all
     *   packet delineation, and should be avoided.
     */
} Udma_ChPdmaPrms;

/**
 *  \brief UDMA channel statistics.
 */
typedef struct
{
    uint32_t                packetCnt;
    /**< [OUT] Current completed packet count for the channel */
    uint32_t                completedByteCnt;
    /**< [OUT] Current completed payload byte count for the channel */
    uint32_t                startedByteCnt;
    /**< [OUT] Current started byte count for the channel */
} Udma_ChStats;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief UDMA open channel.
 *
 *  Opens the UDMA channel based on the channel parameters. This also does
 *  the PSILCFG pairing based on the peer thread ID provided.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2578)
 *
 *  \param drvHandle    [IN] UDMA driver handle pointer passed during
 *                           #Udma_init
 *  \param chHandle     [IN/OUT] UDMA channel handle. The caller need to
 *                           allocate memory for this object and pass this
 *                           pointer to all further APIs. The caller should
 *                           not change any parameters as this is owned and
 *                           maintained by the driver.
 *                           This parameter can't be NULL.
 *  \param chType       [IN] UDMA channel type. Refer \ref Udma_ChType.
 *  \param chPrms       [IN] UDMA channel parameters.
 *                           This parameter can't be NULL.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chOpen(Udma_DrvHandle drvHandle,
                    Udma_ChHandle chHandle,
                    uint32_t chType,
                    const Udma_ChPrms *chPrms);

/**
 *  \brief UDMA close channel.
 *
 *  Closes the UDMA channel and frees all associated resources.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2579)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chClose(Udma_ChHandle chHandle);

/**
 *  \brief UDMA configure TX channel.
 *
 *  Configures the TX channel parameters. Note: This is applicable only
 *  when the channel type is TX
 *
 *  Note: This API can't be called after channel enable.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2580)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *  \param txPrms       [IN] UDMA TX channel parameter.
 *                           Refer #Udma_ChTxPrms.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chConfigTx(Udma_ChHandle chHandle, const Udma_ChTxPrms *txPrms);

/**
 *  \brief UDMA configure RX channel.
 *
 *  Configures the RX channel parameters. Note: This is applicable only
 *  when the channel type is RX
 *  In case of BCDMA Block Copy, there is no need to configure RX Channel.
 *  Therfore the function returns gracefully, without doing anything.
 *
 *  Note: This API can't be called after channel enable.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2581)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *  \param rxPrms       [IN] UDMA RX channel parameter.
 *                           Refer #Udma_ChRxPrms.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chConfigRx(Udma_ChHandle chHandle, const Udma_ChRxPrms *rxPrms);

/**
 *  \brief UDMA configure UTC channel.
 *
 *  Configures the UTC channel parameters. Note: This is applicable only
 *  when the channel type is UTC
 *
 *  Note: This API can't be called after channel enable.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2582)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *  \param utcPrms      [IN] UDMA UTC channel parameter.
 *                           Refer #Udma_ChUtcPrms.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chConfigUtc(Udma_ChHandle chHandle, const Udma_ChUtcPrms *utcPrms);

/**
 *  \brief UDMA configure PDMA channel (peerChNum as part of #Udma_ChPrms)
 *  paired with the UDMAP channel.
 *
 *  This configures the PDMA channel static X,Y,Z parameters.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2583)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *  \param pdmaPrms     [IN] UDMA RX channel parameter.
 *                           Refer #Udma_ChPdmaPrms.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chConfigPdma(Udma_ChHandle chHandle,
                          const Udma_ChPdmaPrms *pdmaPrms);

/**
 *  \brief UDMA channel enable API.
 *
 *  This function will enable the UDMA channel.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2584)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chEnable(Udma_ChHandle chHandle);

/**
 *  \brief UDMA channel teardown and disable API.
 *
 *  This function will perform the channel teardown and eventually disables
 *  the UDMA channel.
 *  This initiates the force teardown sequence based on the channel type and
 *  wait for teardown to complete gracefully.
 *  If the teardown doesn't complete within the timeout provided, then this
 *  will initiate a force teardown sequence.
 *
 *  Caution: This API is blocking. Hence cannot be called from ISR context!!
 *
 *  Requirement: DOX_REQ_TAG(PDK-2585)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *  \param timeout      [IN] Timeout in ms.
 *                           Use #UDMA_WAIT_FOREVER to wait forever.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chDisable(Udma_ChHandle chHandle, uint32_t timeout);

/**
 *  \brief UDMA channel pause API.
 *
 *  This function will pause the UDMA channel by setting the pause bit of the
 *  UDMAP runtime register.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2977)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chPause(Udma_ChHandle chHandle);

/**
 *  \brief UDMA channel resume API.
 *
 *  This function will resume the UDMA channel by clearing the pause bit of the
 *  UDMAP runtime register.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2977)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chResume(Udma_ChHandle chHandle);

/**
 *  \brief Returns the channel number offset with in a channel type - TX, RX
 *  and External (UTC) channel types.
 *
 *  In case of UTC type, this returns the relative offset from the start
 *  of UTC it belongs to (and not from the external channel start).
 *
 *  Requirement: TODO
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return Channel number. Returns #UDMA_DMA_CH_INVALID for error.
 */
uint32_t Udma_chGetNum(Udma_ChHandle chHandle);

/**
 *  \brief Returns the default free ring handle of the channel.
 *
 *  Requirement: TODO
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return Free ring handle. Returns NULL for error.
 */
Udma_RingHandle Udma_chGetFqRingHandle(Udma_ChHandle chHandle);

/**
 *  \brief Returns the default completion ring handle of the channel.
 *
 *  Requirement: TODO
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return Completion ring handle. Returns NULL for error.
 */
Udma_RingHandle Udma_chGetCqRingHandle(Udma_ChHandle chHandle);

/**
 *  \brief Returns the teardown completion ring handle of the channel.
 *
 *  Requirement: TODO
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return Teardown completion ring handle. Returns NULL for error.
 */
Udma_RingHandle Udma_chGetTdCqRingHandle(Udma_ChHandle chHandle);

/**
 *  \brief Returns the default free ring number to be programmed
 *  in descriptor.
 *
 *  Requirement: TODO
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return Free ring number. Returns #UDMA_RING_INVALID for error.
 */
uint16_t Udma_chGetFqRingNum(Udma_ChHandle chHandle);

/**
 *  \brief Returns the default completion ring number to be programmed in
 *  descriptor.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2586)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return Completion ring number. Returns #UDMA_RING_INVALID for error.
 */
uint16_t Udma_chGetCqRingNum(Udma_ChHandle chHandle);

/**
 *  \brief Returns the default flow handle of the RX channel.
 *
 *  Requirement: TODO
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return Default flow handle. Returns NULL for error.
 */
Udma_FlowHandle Udma_chGetDefaultFlowHandle(Udma_ChHandle chHandle);

/**
 *  \brief UDMA dequeue response from teardown completion ring.
 *
 *  This function will pop the response from the teardown completion ring.
 *  This is non-blocking and will return timeout error #UDMA_ETIMEOUT
 *  when the queue is empty.
 *  Note: When executing a teardown sequence, the teardown ring should be
 *  popped using this API to avoid ring overflow.
 *  Note: In case of devices like AM64x where there is no teardown function,
 *  this API is not supported and will return error.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2589)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *  \param tdResponse   [OUT] Teardown response received in the ring.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chDequeueTdResponse(Udma_ChHandle chHandle,
                                 CSL_UdmapTdResponse *tdResponse);

/**
 *  \brief Returns the global trigger event for the channel
 *
 *  This function will return the appropriate global 0/1 trigger event for the channel.
 *
 *  Notes: Trigger is not supported for external channels
 *         and the function will return #UDMA_EVENT_INVALID.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2594)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 * 
 *  \param trigger      [IN] Global0 or Global 1 Trigger - refer
 *                          \ref CSL_UdmapTrFlagsTrigger
 *                            
 *  \return Global trigger event
 */
uint32_t Udma_chGetTriggerEvent(Udma_ChHandle chHandle, uint32_t trigger);

/**
 *  \brief Returns the software trigger register address for the channel
 *
 *  This function will return the appropriate SW trigger register.
 *  Incase of UDMAP channels, it returns the 32-bit TX SWTRIG register address.
 *  Incase of DRU channels, it returns the 64-bit DRU CHRT_SWTRIG register address.
 *
 *  Notes: SW trigger is not supported for RX channels.
 *         Incase of TX channels, only global trigger 0 is supported.
 *         Incase of DRU channels, global trigger 0/1 and local events are
 *         supported.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2594)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *
 *  \return SW trigger register address
 */
void *Udma_chGetSwTriggerRegister(Udma_ChHandle chHandle);

/**
 *  \brief Sets the software trigger register based on the trigger mode
 *  provided.
 *
 *  This function will set the appropriate SW trigger register.
 *  Incase of UDMAP channels, it will set in the TX SWTRIG register.
 *  Incase of DRU channels, it will set in the DRU CHRT_SWTRIG register.
 *
 *  Notes: SW trigger is not supported for RX channels.
 *         Incase of TX channels, only global trigger 0 is supported.
 *         Incase of DRU channels, global trigger 0/1 and local events are
 *         supported.
 *
 *  Requirement: DOX_REQ_TAG(PDK-2594)
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *  \param trigger      [IN] Global0 or Global 1 Trigger - refer
 *                          \ref CSL_UdmapTrFlagsTrigger
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chSetSwTrigger(Udma_ChHandle chHandle, uint32_t trigger);

/**
 *  \brief Chains the trigger channel with the chained channel.
 *
 *  This programs the trigger channel TR event register (OES) to the global
 *  trigger (0 or 1) event of the chained channel.
 *
 *  Once this is done, the application should set the TR trigger (0 or 1)
 *  of the trigger channel while submitting TR to the trigger channel.
 *  Based on the trigger type (full, ICNT0, INCT1, ICNT3), the trigger
 *  channel will trigger the "chained" channel through the channel OES.
 *
 *  Note: Only global0 and global1 triggers are supported.
 *
 *  Requirement: TODO
 *
 *  \param triggerChHandle  [IN] UDMA channel handle which triggers the chain.
 *                          This parameter can't be NULL.
 *  \param chainedChHandle  [IN] UDMA channel handle which gets triggered.
 *                          This parameter can't be NULL.
 *  \param trigger          [IN] Global0 or Global 1 Trigger - refer
 *                          \ref CSL_UdmapTrFlagsTrigger
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chSetChaining(Udma_ChHandle triggerChHandle,
                           Udma_ChHandle chainedChHandle,
                           uint32_t trigger);

/**
 *  \brief Breaks the chaining by resetting the trigger channel's OES.
 *
 *  Note: Only global0 and global1 triggers are supported.
 *
 *  Requirement: TODO
 *
 *  \param triggerChHandle  [IN] UDMA channel handle which triggers the chain.
 *                          This parameter can't be NULL.
 *  \param chainedChHandle  [IN] UDMA channel handle which gets triggered.
 *                          This parameter can't be NULL.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chBreakChaining(Udma_ChHandle triggerChHandle,
                             Udma_ChHandle chainedChHandle);

/*
 * Structure Init functions
 */
/**
 *  \brief Udma_ChPrms structure init function.
 *
 *  \param chPrms       [IN] Pointer to #Udma_ChPrms structure.
 *  \param chType       [IN] UDMA channel type. Refer \ref Udma_ChType.
 *
 */
void UdmaChPrms_init(Udma_ChPrms *chPrms, uint32_t chType);

/**
 *  \brief Udma_ChTxPrms structure init function.
 *
 *  \param txPrms       [IN] Pointer to #Udma_ChTxPrms structure.
 *  \param chType       [IN] UDMA channel type. Refer \ref Udma_ChType.
 *
 */
void UdmaChTxPrms_init(Udma_ChTxPrms *txPrms, uint32_t chType);

/**
 *  \brief Udma_ChRxPrms structure init function.
 *
 *  \param rxPrms       [IN] Pointer to #Udma_ChRxPrms structure.
 *  \param chType       [IN] UDMA channel type. Refer \ref Udma_ChType.
 *
 */
void UdmaChRxPrms_init(Udma_ChRxPrms *rxPrms, uint32_t chType);

/**
 *  \brief Udma_ChUtcPrms structure init function.
 *
 *  \param utcPrms      [IN] Pointer to #Udma_ChUtcPrms structure.
 *
 */
void UdmaChUtcPrms_init(Udma_ChUtcPrms *utcPrms);

/**
 *  \brief Udma_ChPdmaPrms structure init function.
 *
 *  \param pdmaPrms     [IN] Pointer to #Udma_ChPdmaPrms structure.
 *
 */
void UdmaChPdmaPrms_init(Udma_ChPdmaPrms *pdmaPrms);

/**
 *  \brief Get real-time channel statistics.
 *
 *  Requirement: PRSDK-5609
 *
 *  \param chHandle     [IN] UDMA channel handle.
 *                           This parameter can't be NULL.
 *  \param chStats      [IN] Pointer to #Udma_ChStats.
 *                           This parameter can't be NULL.
 *
 *  \return \ref Udma_ErrorCodes
 */
int32_t Udma_chGetStats(Udma_ChHandle chHandle, Udma_ChStats *chStats);

/* ========================================================================== */
/*                       Static Function Definitions                          */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                  Internal/Private Structure Declarations                   */
/* ========================================================================== */

#if (UDMA_NUM_UTC_INSTANCE > 0)
/**
 *  \brief UDMA UTC instance information.
 *
 *  Note: This is an internal/private driver structure and should not be
 *  used or modified by caller.
 */
typedef struct
{
    uint32_t                utcId;
    /**< The UTC instance ID for which this info is stored.
     *   Refer \ref Udma_UtcIdSoc macro for details. */
    uint32_t                utcType;
    /**< The UTC type for which this info is stored.
     *   Refer \ref Udma_UtcType macro for details. */
    uint32_t                startCh;
    /**< UDMA external channel start number to which this UTC maps to.
     *   This is relative to the external channel start */
    uint32_t                numCh;
    /**< Number of channels present in the UTC */
    uint32_t                startThreadId;
    /**< PSILCFG thread ID for the start channel */
    uint8_t                 txCredit;
    /**< TX credit for external channels */
    CSL_DRU_t              *druRegs;
    /**< DRU register overlay - applicable only for DRU type UTC. Else this
     *   will be set to NULL */
    uint32_t                numQueue;
    /**< Number of queues present in a DRU*/
} Udma_UtcInstInfo;
#endif

/**
 *  \brief UDMA channel object.
 *
 *  Note: This is an internal/private driver structure and should not be
 *  used or modified by caller.
 */
struct Udma_ChObj
{
    uint32_t                chType;
    /**< UDMA channel type. Refer \ref Udma_ChType. */
    Udma_ChPrms             chPrms;
    /**< Object to store the channel params. */
    Udma_DrvHandle          drvHandle;
    /**< Pointer to global driver handle. */
#if (UDMA_NUM_UTC_INSTANCE > 0)
    const Udma_UtcInstInfo *utcInfo;
    /**< Pointer to global UTC instance info. */
#endif

    uint32_t                txChNum;
    /**< Allocated TX channel number - this is relative channel number from
     *   base TX channel. This is valid only when the channel is opened for
     *   TX and block copy mode */
    uint32_t                rxChNum;
    /**< Allocated RX channel number - this is relative channel number from
     *   base RX channel. This is valid only when the channel is opened for
     *   RX and block copy mode */
    uint32_t                extChNum;
    /**< Allocated Ext channel number - this is relative channel number from
     *   base External channel. This is valid only when the channel is opened
     *   for UTC mode */
    uint32_t                pdmaChNum;
    /**< Allocated peer PDMA channel number. This is valid only when the
     *   channel is opened for PDMA mode */
    uint32_t                peerThreadId;
    /**< Peer channel thread ID - this is or'ed with thread offset. */

    Udma_RingHandle         fqRing;
    /**< Free queue ring handle */
    Udma_RingHandle         cqRing;
    /**< Completion queue ring handle
    *    For AM64x kind of devices, where there is no seperate Completion queue,
    *    this points to fqRing itself.
    */
    Udma_RingHandle         tdCqRing;
    /**< Teardown completion queue ring handle */

    struct Udma_RingObj     fqRingObj;
    /**< Free queue ring object */
    struct Udma_RingObj     cqRingObj;
    /**< Completion queue ring object
    *    Not used for AM64x kind of devices, where there is no seperate Completion queue.
    */
    struct Udma_RingObj     tdCqRingObj;
    /**< Teardown completion queue ring object
    *    Not used for AM64x kind of devices, where teardown function is not present.
    */

    Udma_FlowHandle         defaultFlow;
    /**< Default flow handle */
    struct Udma_FlowObj     defaultFlowObj;
    /**< Default flow object - Flow ID equal to the RX channel is reserved
     *   as the default flow for the channel. This object is used for
     *   providing handle to the caller to re-program the default flow using
     *   the standard flow API's */

    Udma_ChTxPrms           txPrms;
    /**< TX channel parameter passed during channel config. */
    Udma_ChRxPrms           rxPrms;
    /**< RX channel parameter passed during channel config. */
    Udma_ChUtcPrms          utcPrms;
    /**< UTC channel parameter passed during channel config. */


#if (UDMA_SOC_CFG_UDMAP_PRESENT == 1)
    /* Below UDMAP register overlay pointers provided for debug purpose to
     * readily view the registers */
    volatile CSL_udmap_txccfgRegs_chan  *pTxCfgRegs;
    /**< Pointer to UDMAP TX config register overlay */
    volatile CSL_udmap_txcrtRegs_chan   *pTxRtRegs;
    /**< Pointer to UDMAP TX RT config register overlay */
    volatile CSL_udmap_rxccfgRegs_chan  *pRxCfgRegs;
    /**< Pointer to UDMAP RX config register overlay */
    volatile CSL_udmap_rxcrtRegs_chan   *pRxRtRegs;
    /**< Pointer to UDMAP RX RT config register overlay */
    volatile CSL_udmap_txccfgRegs_chan  *pExtCfgRegs;
    /**< Pointer to UDMAP External config register overlay */
    volatile CSL_udmap_txcrtRegs_chan   *pExtRtRegs;
    /**< Pointer to UDMAP External RT config register overlay */
#endif
#if (UDMA_SOC_CFG_BCDMA_PRESENT == 1)
    /* Below BCDMA register overlay pointers provided for debug purpose to
     * readily view the registers */
    volatile CSL_bcdma_bccfgRegs_chan   *pBcdmaBcCfgRegs;
    /**< Pointer to BCDMA Block copy config register overlay */
    volatile CSL_bcdma_bcrtRegs_chan    *pBcdmaBcRtRegs;
    /**< Pointer to BCDMA Block copy RT config register overlay */
    volatile CSL_bcdma_txccfgRegs_chan  *pBcdmaTxCfgRegs;
    /**< Pointer to BCDMA TX config register overlay */
    volatile CSL_bcdma_txcrtRegs_chan   *pBcdmaTxRtRegs;
    /**< Pointer to BCDMA TX RT config register overlay */
    volatile CSL_bcdma_rxccfgRegs_chan  *pBcdmaRxCfgRegs;
    /**< Pointer to BCDMA RX config register overlay */
    volatile CSL_bcdma_rxcrtRegs_chan   *pBcdmaRxRtRegs;
    /**< Pointer to BCDMA RX RT config register overlay */
#endif
#if (UDMA_SOC_CFG_PKTDMA_PRESENT == 1)
    /* Below PKTDMA register overlay pointers provided for debug purpose to
     * readily view the registers */
    volatile CSL_pktdma_txccfgRegs_chan  *pPktdmaTxCfgRegs;
    /**< Pointer to PKTDMA TX config register overlay */
    volatile CSL_pktdma_txcrtRegs_chan   *pPktdmaTxRtRegs;
    /**< Pointer to PKTDMA TX RT config register overlay */
    volatile CSL_pktdma_rxccfgRegs_chan  *pPktdmaRxCfgRegs;
    /**< Pointer to PKTDMA RX config register overlay */
    volatile CSL_pktdma_rxcrtRegs_chan   *pPktdmaRxRtRegs;
    /**< Pointer to PKTDMA RX RT config register overlay */
    volatile CSL_pktdma_txccfgRegs_chan  *pPktdmaExtCfgRegs;
    /**< Pointer to PKTDMA External config register overlay */
    volatile CSL_pktdma_txcrtRegs_chan   *pPktdmaExtRtRegs;
    /**< Pointer to PKTDMA External RT config register overlay */
#endif

#if (UDMA_NUM_UTC_INSTANCE > 0)
    volatile CSL_DRU_CHNRTRegs_CHNRT    *pDruNrtRegs;
    /**< Pointer to DRU Non RT config register overlay */
    volatile CSL_DRU_CHRTRegs_CHRT      *pDruRtRegs;
    /**< Pointer to DRU RT config register overlay */
#endif

    uint32_t                chInitDone;
    /**< Flag to set the channel object is init. */
    uint32_t                chOesAllocDone;
    /**< Flag to check if the channel's OES is allocated. This is required
     *   because the channel OES is used for chaining as well as for
     *   TR event registeration. This allows to check for error when both
     *   are requested by user on the same channel */
    uint32_t                trigger;
    /**< Channel trigger used when chaining channels - needed at the time of
     *   breaking the chaining */
};

#ifdef __cplusplus
}
#endif

#endif /* #ifndef UDMA_CH_H_ */

/* @} */
