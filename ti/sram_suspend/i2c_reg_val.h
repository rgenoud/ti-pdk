/* Copy only the macro from ti/csl/src/ip/i2c/V2/i2c.h */

#ifndef I2C_H_
#define I2C_H_

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/*
 * \name Values that can be passed to  I2CMasterControl API as command to
 * configure mode of operation of I2C in Master mode.
 *  @{
 */
/**
 * \brief I2C_CFG_MST_TX               - Master transmit mode.
 */
#define     I2C_CFG_MST_TX              (((uint32_t) I2C_CON_TRX_MASK) | \
                                         (uint32_t) (I2C_CON_MST_MASK))
/**
 * \brief I2C_CFG_MST_RX               - Matter receive mode.
 */
#define     I2C_CFG_MST_RX              ((uint32_t) I2C_CON_MST_MASK)
/**
 * \brief I2C_CFG_STOP                 - Stop condition.
 */
#define     I2C_CFG_STOP                ((uint32_t) I2C_CON_STP_MASK)
/**
 * \brief I2C_CFG_N0RMAL_MODE          - Normal mode.
 */
#define     I2C_CFG_N0RMAL_MODE         ((uint32_t) 0 << I2C_CON_STB_SHIFT)
/**
 * \brief I2C_CFG_SRT_BYTE_MODE        - Start byte mode.
 */
#define     I2C_CFG_SRT_BYTE_MODE       ((uint32_t) I2C_CON_STB_MASK)
/**
 * \brief I2C_CFG_7BIT_SLAVE_ADDR      - 7 bit slave address.
 */
#define     I2C_CFG_7BIT_SLAVE_ADDR     ((uint32_t) 0 << I2C_CON_XSA_SHIFT)
/**
 * \brief I2C_CFG_10BIT_SLAVE_ADDR     - 10 bit slave address.
 */
#define     I2C_CFG_10BIT_SLAVE_ADDR    ((uint32_t) I2C_CON_XSA_MASK)
/**
 * \brief I2C_CFG_10BIT_OWN_ADDR_0     - Master mode 10 bit own address 0
 */
#define     I2C_CFG_10BIT_OWN_ADDR_0    ((uint32_t) I2C_CON_XOA0_MASK)
/**
 * \brief I2C_CFG_10BIT_OWN_ADDR_1     - Master mode 10 bit own address 1
 */
#define     I2C_CFG_10BIT_OWN_ADDR_1    ((uint32_t) I2C_CON_XOA1_MASK)
/**
 * \brief I2C_CFG_10BIT_OWN_ADDR_2     - Master mode 10 bit own address 2
 */
#define     I2C_CFG_10BIT_OWN_ADDR_2    ((uint32_t) I2C_CON_XOA2_MASK)
/**
 * \brief I2C_CFG_10BIT_OWN_ADDR_3     - Master mode 10 bit own address 3
 */
#define     I2C_CFG_10BIT_OWN_ADDR_3    ((uint32_t) I2C_CON_XOA3_MASK)
/**
 * \brief I2C_CFG_7BIT_OWN_ADDR_0     - Master mode 7 bit own address 0
 */
#define     I2C_CFG_7BIT_OWN_ADDR_0     ((uint32_t) 0 << I2C_CON_XOA0_SHIFT)
/**
 * \brief I2C_CFG_7BIT_OWN_ADDR_1     - Master mode 7 bit own address 1
 */
#define     I2C_CFG_7BIT_OWN_ADDR_1     ((uint32_t) 0 << I2C_CON_XOA1_SHIFT)
/**
 * \brief I2C_CFG_7BIT_OWN_ADDR_2     - Master mode 7 bit own address 2
 */
#define     I2C_CFG_7BIT_OWN_ADDR_2     ((uint32_t) 0 << I2C_CON_XOA2_SHIFT)
/**
 * \brief I2C_CFG_7BIT_OWN_ADDR_3     - Master mode 7 bit own address 3
 */
#define     I2C_CFG_7BIT_OWN_ADDR_3     ((uint32_t) 0 << I2C_CON_XOA3_SHIFT)
/**
 * \brief I2C_CFG_MST_ENABLE          - I2C module enable
 */
#define     I2C_CFG_MST_ENABLE          ((uint32_t) I2C_CON_I2C_EN_MASK)
/**
 * \brief I2C_CFG_START               - Start condition, initiate I2C transfer
 */
#define     I2C_CFG_START               ((uint32_t) I2C_CON_STT_MASK)
/**
 * \brief I2C_CFG_MST                 - I2C configure master mode.
 */
#define     I2C_CFG_MST                 ((uint32_t) I2C_CON_MST_MASK)
/**
 * \brief I2C_CFG_HS_MODE             - High speed operation mode
 */
#define     I2C_CFG_HS_MOD              ((uint32_t) CSL_I2C_CON_OPMODE_HSI2C << CSL_I2C_CON_OPMODE_SHIFT)

/* @} */

/*
 * \name Values that can be passed to  I2CMasterIntEnableEx API as intFlag to Enable
 * interrupts.
 * @{
*/
/**
 * \brief I2C_INT_ARBITRATION_LOST     - Arbitration lost interrupt
 */
#define     I2C_INT_ARBITRATION_LOST     ((uint32_t) I2C_IRQSTATUS_AL_MASK)
/**
 * \brief I2C_INT_NO_ACK               - No acknowledgement interrupt
 */
#define     I2C_INT_NO_ACK               ((uint32_t) I2C_IRQSTATUS_NACK_MASK)
/**
 * \brief I2C_INT_ADRR_READY_ACESS     - Register access ready interrupt
 */
#define     I2C_INT_ADRR_READY_ACESS     ((uint32_t) I2C_IRQSTATUS_ARDY_MASK)
/**
 * \brief I2C_INT_RECV_READY           - Receive data ready interrupt
 */
#define     I2C_INT_RECV_READY           ((uint32_t) I2C_IRQSTATUS_RRDY_MASK)
/**
 * \brief I2C_INT_TRANSMIT_READY       - Transmit data ready interrupt
 */
#define     I2C_INT_TRANSMIT_READY       ((uint32_t) I2C_IRQSTATUS_XRDY_MASK)
/**
 * \brief I2C_INT_GENERAL_CALL         - General call Interrupt
 */
#define     I2C_INT_GENERAL_CALL         ((uint32_t) I2C_IRQSTATUS_GC_MASK)
/**
 * \brief I2C_INT_START                - Start Condition interrupt
 */
#define     I2C_INT_START                ((uint32_t) I2C_IRQSTATUS_STC_MASK)
/**
 * \brief I2C_INT_ACCESS_ERROR         - Access Error interrupt
 */
#define     I2C_INT_ACCESS_ERROR         ((uint32_t) I2C_IRQSTATUS_AERR_MASK)
/**
 * \brief I2C_INT_STOP_CONDITION       - Bus Free interrupt
 */
#define     I2C_INT_STOP_CONDITION       ((uint32_t) I2C_IRQSTATUS_BF_MASK)
/**
 * \brief I2C_INT_ADRR_SLAVE           - Addressed as Slave interrupt
 */
#define     I2C_INT_ADRR_SLAVE           ((uint32_t) I2C_IRQSTATUS_AAS_MASK)
/**
 * \brief I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit underflow interrupt
 */
#define     I2C_INT_TRANSMIT_UNDER_FLOW  ((uint32_t) I2C_IRQSTATUS_XUDF_MASK)
/**
 * \brief I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt
 */
#define     I2C_INT_RECV_OVER_RUN        ((uint32_t) I2C_IRQSTATUS_ROVR_MASK)
/**
 * \brief I2C_INT_RECV_DRAIN           - Receive Draining interrupt
 */
#define     I2C_INT_RECV_DRAIN           ((uint32_t) I2C_IRQSTATUS_RDR_MASK)
/**
 * \brief I2C_INT_TRANSMIT_DRAIN       - Transmit Draining interrupt
 */
#define     I2C_INT_TRANSMIT_DRAIN       ((uint32_t) I2C_IRQSTATUS_XDR_MASK)
/**
 * \brief I2C_INT_BUS_BUSY             - Bus busy interrupt raw status
 */
#define     I2C_INT_BUS_BUSY             ((uint32_t) I2C_IRQSTATUS_RAW_BB_MASK)
/**
 * \brief I2C_INT_BUS_FREE             - Bus free interrupt raw status
 */
#define     I2C_INT_BUS_FREE             ((uint32_t) I2C_IRQSTATUS_RAW_BF_MASK)
/**
 * \brief I2C_INT_ALL                  - Enable all interrupt
 */
#define     I2C_INT_ALL                  ((uint32_t) 0x7FFFU)
/* @} */

/*
 * \name Values that can be passed to I2CFIFOThersholdConfig/I2CFIFOClear API as
 * flag to select receive or transmit mode.
 * @{
 */
/**
 * \brief I2C_TX_MODE     - Transmit mode.
 */
#define     I2C_TX_MODE                  ((uint32_t) 1U)
/**
 * \brief I2C_RX_MODE     - Receive mode.
 */
#define     I2C_RX_MODE                  ((uint32_t) 0U)
/* @} */

/*
 * \name Values that can be passed to I2CBufferStatus API as flag to get status
 * of the internal buffer.
 * @{
 */
/**
 * \brief I2C_TX_BUFFER_STATUS     - TX buffer status flag
 */
#define     I2C_TX_BUFFER_STATUS         ((uint32_t) 0U)
/**
 * \brief I2C_RX_BUFFER_STATUS     - RX buffer status flag
 */
#define     I2C_RX_BUFFER_STATUS         ((uint32_t) 1U)
/**
 * \brief I2C_FIFO_DEPTH           - Internal FIFO depth flag
 */
#define     I2C_FIFO_DEPTH               ((uint32_t) 2U)
/* @} */

/*
 * \name Values that can be passed to I2CWakeUpEnable  API as eventFlag to select
 * the type of wakeup signal to be Enabled.
 * @{
 */
/**
 * \brief I2C_WAKE_UP_ARBITRATION_LOST    - Arbitration lost IRQ wakeup set
 */
#define     I2C_WAKE_UP_ARBITRATION_LOST  (I2C_WE_AL_MASK)
/**
 * \brief I2C_WAKE_UP_NO_ACK              - No acknowledgment IRQ wakeup set
 */
#define     I2C_WAKE_UP_NO_ACK            (I2C_WE_NACK_MASK)
/**
 * \brief I2C_WAKE_UP_ADRR_RDY_ACCESS     - Register access ready IRQ wakeup set
 */
#define     I2C_WAKE_UP_ADRR_RDY_ACCESS   (I2C_WE_ARDY_MASK)
/**
 * \brief I2C_WAKE_UP_GENERAL_CALL        - General call IRQ wakeup set
 */
#define     I2C_WAKE_UP_GENERAL_CALL      (I2C_WE_GC_MASK)
/**
 * \brief I2C_WAKE_UP_START               - Start Condition IRQ wakeup set
 */
#define     I2C_WAKE_UP_START             (I2C_WE_STC_MASK)
/**
 * \brief I2C_WAKE_UP_STOP_CONDITION      - Bus Free IRQ wakeup set
 */
#define     I2C_WAKE_UP_STOP_CONDITION    (I2C_WE_BF_MASK)
/**
 * \brief I2C_WAKE_UP_ADRR_SLAVE          - Address as slave IRQ wakeup set
 */
#define     I2C_WAKE_UP_ADRR_SLAVE        (I2C_WE_AAS_MASK)
/**
 * \brief I2C_WAKE_UP_TX_UNDER_FLOW       - Transmit underflow wakeup set
 */
#define     I2C_WAKE_UP_TX_UNDER_FLOW     (I2C_WE_XUDF_MASK)
/**
 * \brief I2C_WAKE_UP_RECV_OVER_RUN       - Receive overrun wakeup set
 */
#define     I2C_WAKE_UP_RECV_OVER_RUN     (I2C_WE_ROVR_MASK)
/**
 * \brief I2C_WAKE_UP_RECV_DRAIN          - Receive Draining wakeup set
 */
#define     I2C_WAKE_UP_RECV_DRAIN        (I2C_WE_RDR_MASK)
/**
 * \brief I2C_WAKE_UP_TRANSMIT_DRAIN      - Transmit Draining wakeup set
 */
#define     I2C_WAKE_UP_TRANSMIT_DRAIN    (I2C_WE_XDR_MASK)
/**
 * \brief I2C_WAKE_UP_DATA_RECV_TX_RDY    - Receive/Transmit data ready IRQ wakeup set
 */
#define     I2C_WAKE_UP_DATA_RECV_TX_RDY  (I2C_WE_DRDY_MASK)
/* @} */

/*
 * \name Values that can be passed to I2CWakeUpEnable  API as flag to select
 * the request source to generate asynchronous signal.
 * @{
 */
/**
 * \brief I2C_WAKE_UP_IRQ           - IRQ request source
 */
#define     I2C_WAKE_UP_IRQ               ((uint32_t) 1U)
/**
 * \brief I2C_WAKE_UP_DMA_RECV      - DMA receive request source
 */
#define     I2C_WAKE_UP_DMA_RECV          ((uint32_t) 2U)
/**
 * \brief I2C_WAKE_UP_DMA_TRANSMIT  - DMA transmit request source
 */
#define     I2C_WAKE_UP_DMA_TRANSMIT      ((uint32_t) 3U)
/* @} */

/*
 * \name Values that can be passed to I2CMasterIntStatus/I2CSlaveIntStatus
 * /I2CMasterIntStatusEx/I2CSlaveIntStatusEx API as flag to select
 * RAWIRQSTATUS or IRQSTATUS.
 * @{
 */
/**
 * \brief I2C_STATUS_RAW       - RAW IRQ status
 */
#define     I2C_STATUS_RAW            ((uint32_t) 0U)
/**
 * \brief I2C_STATUS           - IRQ status
 */
#define     I2C_STATUS                ((uint32_t) 1U)

/**
 * \brief HAL_HSI2C_SUCCESS    - I2C success
 */
#define HAL_HSI2C_SUCCESS             ((uint32_t) 0U)
/**
 * \brief HAL_HSI2C_FAIL       - I2C fail
 */
#define HAL_HSI2C_FAIL                ((uint32_t) 1U)
/* @} */

/*
 * \name Values that can be passed to ownAddressSet API as flag to select
 * any one of the I2C own address field .
 * @{
 */
/**
 * \brief I2C_OWN_ADDR_0 - set own address 0
 */
#define     I2C_OWN_ADDR_0               ((uint32_t) 0U)
/**
 * \brief I2C_OWN_ADDR_1 - set own address 1
 */
#define     I2C_OWN_ADDR_1               ((uint32_t) 1U)
/**
 * \brief I2C_OWN_ADDR_2 - set own address 2
 */
#define     I2C_OWN_ADDR_2               ((uint32_t) 2U)
/**
 * \brief I2C_OWN_ADDR_3 - set own address 3
 */
#define     I2C_OWN_ADDR_3               ((uint32_t) 3U)
/* @} */

/*
 * \name MACROS used to enable or disable auto idle mechanism.
 * @{
 */
/**
 * \brief I2C_AUTOIDLE_DISABLE       Disable auto idle mechanism
 */
#define   I2C_AUTOIDLE_DISABLE    (I2C_SYSC_AUTOIDLE_DISABLE)
/**
 * \brief I2C_AUTOIDLE_ENABLE        Enable autoidle mechanism
 */
#define   I2C_AUTOIDLE_ENABLE     ((uint32_t) I2C_SYSC_AUTOIDLE_ENABLE << \
                                   I2C_SYSC_AUTOIDLE_SHIFT)
/* @} */

/*
 * \name MACRO used to select the type of clock activity.
 * @{
 */
/**
 * \brief I2C_CUT_OFF_BOTH_CLK       Both OCP and SYS Clk are cut off.
 */
#define    I2C_CUT_OFF_BOTH_CLK       (I2C_SYSC_CLKACTIVITY_BOOTHOFF)
/**
 * \brief I2C_CUT_OFF_SYS_CLK        system clock is cut off;OCP clock is
 * kept alive
 */
#define    I2C_CUT_OFF_SYS_CLK        ((uint32_t) I2C_SYSC_CLKACTIVITY_OCPON << \
                                       I2C_SYSC_CLKACTIVITY_SHIFT)
/**
 * \brief I2C_CUT_OFF_OCP_CLK        OCP clock is cut off;system clock is
 *  is kept alive
 */
#define    I2C_CUT_OFF_OCP_CLK        ((uint32_t) I2C_SYSC_CLKACTIVITY_SYSON << \
                                       I2C_SYSC_CLKACTIVITY_SHIFT)
/**
 * \brief I2C_KEEP_ALIVE_BOTH_CLK    BOTH OCP and SYS Clk are kept alive.
 */
#define    I2C_KEEP_ALIVE_BOTH_CLK    ((uint32_t) I2C_SYSC_CLKACTIVITY_BOOTHON << \
                                      I2C_SYSC_CLKACTIVITY_SHIFT)
/* @} */

/*
 * \name MACROS used to enable or disable wake up mechanism.
 * @{
 */
/**
 * \brief I2C_ENAWAKEUP__DISABLE       Disable wakeup mechanism.
 */
#define    I2C_ENAWAKEUP_DISABLE    (I2C_SYSC_ENAWAKEUP_DISABLE)
/**
 * \brief I2C_ENAWAKEUP__ENABLE        Enable wakeup mechanism
 */
#define    I2C_ENAWAKEUP_ENABLE     ((uint32_t) I2C_SYSC_ENAWAKEUP_ENABLE << \
                                     I2C_SYSC_ENAWAKEUP_SHIFT)
/* @} */

/*
 * \name MACROS used to select the type of idle mode operation.
 * @{
 */
/**
 *  \brief I2C_FORCE_IDLE_MODE           selects forced idle mode operation.
 */
#define    I2C_FORCE_IDLE_MODE          (I2C_SYSC_IDLEMODE_FORCEIDLE)
/**
 * \brief I2C_NO_IDLE_MODE              selects no idle mode operation.
 */
#define    I2C_NO_IDLE_MODE             ((uint32_t) I2C_SYSC_IDLEMODE_NOIDLE << \
                                         I2C_SYSC_IDLEMODE_SHIFT)
/**
 * \brief I2C_SMART_IDLE_MODE           selects smart idle mode operation.
 */
#define    I2C_SMART_IDLE_MODE          ((uint32_t) I2C_SYSC_IDLEMODE_SMARTIDLE << \
                                         I2C_SYSC_IDLEMODE_SHIFT)
/**
 * \brief I2C_SMART_IDLE_WAKEUP_MODE    selects smart idle
 * wakeup mode of operation.
 */
#define    I2C_SMART_IDLE_WAKEUP_MODE   ((uint32_t) I2C_SYSC_IDLEMODE_SMARTIDLE_WAKEUP << \
                                         I2C_SYSC_IDLEMODE_SHIFT)
/* @} */

/*
 * \name MACROS used to select F/S mode or HS mode of I2C.
 * @{
 */
/**
 * \brief I2C_OPMODE_FAST_STAND_MODE       Select Fast/Standard mode
 */
#define    I2C_OPMODE_FAST_STAND_MODE    (I2C_CON_OPMODE_FSI2C)
/**
 * \brief I2C_OPMODE_HIGH_SPEED_MODE       Select high speed mode
 */
#define    I2C_OPMODE_HIGH_SPEED_MODE    ((uint32_t) I2C_CON_OPMODE_HSI2C << \
                                          I2C_CON_OPMODE_SHIFT)
/* @} */

/*
 * \name MACROS used to select Start byte or normal mode of I2C.
 * @{
 */
/**
 * \brief I2C_NORMAL_MODE       Select Normal mode.
 */
#define    I2C_NORMAL_MODE   (I2C_CON_STB_NORMAL)
/**
 * \brief I2C_STB_MODE          Select start byte mode
 */
#define    I2C_STB_MODE      ((uint32_t) I2C_CON_STB_STB << I2C_CON_STB_SHIFT)
/* @} */

/*
 * \name MACROS used to slave address 7 or 10 bit mode of I2C.
 * @{
 */
/**
 * \brief I2C_XSA_7BIT        Slave address 7  bit mode.
 */
#define    I2C_XSA_7BIT     (I2C_CON_XSA_B07)
/**
 * \brief I2C_XSA_10BIT       Slave address 10 bit mode
 */
#define    I2C_XSA_10BIT    ((uint32_t) I2C_CON_XSA_B10 << I2C_CON_XSA_SHIFT)
/* @} */

#endif
