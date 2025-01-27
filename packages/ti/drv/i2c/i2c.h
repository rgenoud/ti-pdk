/*
 * Copyright (C) 2014-2024 Texas Instruments Incorporated - http://www.ti.com/
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

/**
 *  \defgroup DRV_I2C_MODULE I2C Driver
 *
 *  @{
 */
/* @} */

/**
 *  \ingroup DRV_I2C_MODULE
 *  \defgroup DRV_I2C_API_MODULE I2C Driver API
 *            I2C driver interface
 *
 *  @{
 */

/** ============================================================================
 *  @file       drv/i2c/i2c.h
 *
 *  @brief      I2C driver interface
 *
 *  The I2C header file should be included in an application as follows:
 *  @code
 *  #include <ti/drv/i2c/i2c.h>
 *  @endcode
 *
 *  # Operation #
 *  The I2C driver operates as a master or a slave on a single-master I2C bus,
 *  in either I2C_MODE_BLOCKING or I2C_MODE_CALLBACK.
 *  In blocking mode, the task's execution is blocked during the I2C
 *  transaction. When the transfer has completed, code execution will resume.
 *  In callback mode, the task's execution is not blocked, allowing for other
 *  transactions to be queued up or to process some other code. When the
 *  transfer has completed, the I2C driver will call a user-specified callback
 *  function (from a HWI context).
 *
 *  The APIs in this driver serve as an interface to a typical TI-RTOS
 *  application. The specific peripheral implementations are responsible to
 *  create all the SYS/BIOS specific primitives to allow for thread-safe
 *  operation.
 *
 *  ## Opening the driver #
 *
 *  @code
 *  I2C_Handle      handle;
 *  I2C_Params      params;
 *  I2C_Transaction i2cTransaction;
 *
 *  I2C_Params_init(&params);
 *  params.transferMode  = I2C_MODE_CALLBACK;
 *  params.transferCallbackFxn = someI2CCallbackFunction;
 *  handle = I2C_open(someI2C_configIndexValue, &params);
 *  if (!handle) {
 *      System_printf("I2C did not open");
 *  }
 *  @endcode
 *
 *  ## Transferring data #
 *  A I2C transaction with a I2C peripheral is started by calling
 *  I2C_transfer(). The details of the I2C transaction is specified with a
 *  I2C_Transaction data structure. This structure allows for any of the three
 *  types of transactions: Write, Read, or Write/Read. Each transfer is
 *  performed atomically with the I2C master or slave peripheral.
 *
 *  @code
 *  I2C_Transaction i2cTransaction;
 *
 *  i2cTransaction.writeBuf = someWriteBuffer;
 *  i2cTransaction.writeCount = numOfBytesToWrite;
 *
 *  i2cTransaction.readBuf = someReadBuffer;
 *  i2cTransaction.readCount = numOfBytesToRead;
 *
 *  i2cTransaction.slaveAddress = some7BitI2CSlaveAddress;
 *
 *  ret = I2C_transfer(handle, &i2cTransaction);
 *  if (!ret) {
 *      System_printf("Unsuccessful I2C transfer");
 *  }
 *  @endcode
 *
 *  # Implementation #
 *
 *  This module serves as the main interface for TI-RTOS
 *  applications. Its purpose is to redirect the module's APIs to specific
 *  peripheral implementations which are specified using a pointer to a
 *  I2C_FxnTable.
 *
 *  The I2C driver interface module is joined (at link time) to a
 *  NULL-terminated array of I2C_Config data structures named *I2C_config*.
 *  *I2C_config* is implemented in the application with each entry being an
 *  instance of a I2C peripheral. Each entry in *I2C_config* contains a:
 *  - (I2C_FxnTable *) to a set of functions that implement a I2C peripheral
 *  - (void *) data object that is associated with the I2C_FxnTable
 *  - (void *) hardware attributes that are associated to the I2C_FxnTable
 *
 *  # Instrumentation #
 *  The I2C driver interface produces log statements if instrumentation is
 *  enabled.
 *
 *  ============================================================================
 */

#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <ti/drv/i2c/src/csl/csl_i2c.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * Common I2C_control command code reservation offset.
 * I2C driver implementations should offset command codes with I2C_CMD_RESERVED
 * growing positively
 *
 * Example implementation specific command codes:
 * @code
 * #define I2CXYZ_COMMAND0          I2C_CMD_RESERVED + 0
 * #define I2CXYZ_COMMAND1          I2C_CMD_RESERVED + 1
 * @endcode
 */
#define I2C_CMD_RESERVED             32

/**
 * I2C probe IOCTL. This IOCTL returns I2C_STATUS_SUCCESS if the device
 * is present. Returns I2C_STATUS_ERROR otherwise.
 * The argument to this IOCTL is the uint32_t * of the device address.
 */
#define I2C_CMD_PROBE               (0U)

/**
 * This command sets the i2c bus speed dynamically.
 * This command returns I2C_STATUS_SUCCESS if the device
 * is present. Returns I2C_STATUS_ERROR otherwise.
 * The argument to this accepts the two macros I2C_100kHz, I2C_400kHz.
 */
#define I2C_CMD_SET_BUS_FREQUENCY   (1U)

/**
 * This command performs bus recovery in case of timeout error.
 * This command returns I2C_STATUS_SUCCESS if the device
 * is present. Returns I2C_STATUS_ERROR otherwise.
 * The argument to this accepts the delay value.
 */
#define I2C_CMD_RECOVER_BUS         (2U)

/**
 * This command performs SMBUS command and code setup.
 * This command returns I2C_STATUS_SUCCESS if a valid
 * smbus cmd is passed. Returns I2C_STATUS_ERROR otherwise.
 * The argument to this accepts the SMBUS command and its 
 * subcode.
 */
#define I2C_CMD_SMBUS_TYPE          (3U)

/**
 * Common I2C_control status code reservation offset.
 * I2C driver implementations should offset status codes with
 * I2C_STATUS_RESERVED growing negatively.
 *
 * Example implementation specific status codes:
 * @code
 * #define I2CXYZ_STATUS_ERROR0     I2C_STATUS_RESERVED - 0
 * #define I2CXYZ_STATUS_ERROR1     I2C_STATUS_RESERVED - 1
 * #define I2CXYZ_STATUS_ERROR2     I2C_STATUS_RESERVED - 2
 * @endcode
 */
#define I2C_STATUS_RESERVED         (-((int32_t)32))

/**
 * \brief   Successful status code returned by I2C_control().
 *
 * I2C_control() returns I2C_STATUS_SUCCESS if the control code was executed
 * successfully.
 */
#define I2C_STATUS_SUCCESS          ((int32_t)(0))

/**
 * \brief   Generic error status code returned by I2C_control().
 *
 * I2C_control() returns I2C_STATUS_ERROR if the control code was not executed
 * successfully.
 */
#define I2C_STATUS_ERROR           (-((int32_t)1))

/**
 * \brief   An error status code returned by I2C_control() for undefined
 * command codes.
 *
 * I2C_control() returns I2C_STATUS_UNDEFINEDCMD if the control code is not
 * recognized by the driver implementation.
 */
#define I2C_STATUS_UNDEFINEDCMD    (-((int32_t)2))


/**
 * \brief   A status code returned by I2C_transfer().
 *
 * I2C_transfer() returns I2C_STS_SUCCESS if the transfer is succesful.
 */
#define I2C_STS_SUCCESS           ((int16_t)(1))

/**
 * \brief   A restart status code returned by I2C transfer callback
 *
 * I2C transfer callback function returns I2C_STS_RESTART if the restart
 * condition is detected. This status is only valid in slave mode.
 */
#define I2C_STS_RESTART           ((int16_t)(2))

/**
 * \brief   A error status code returned by I2C_transfer().
 *
 * I2C_transfer() returns I2C_STS_ERR if the transfer is failed.
 */
#define I2C_STS_ERR               ((int16_t)(0))

/**
 * \brief   A error status code returned by I2C_transfer().
 *
 * I2C_transfer() returns I2C_STS_ERR_TIMEOUT if the timeout error is occured
 * during the transfer.
 */
#define I2C_STS_ERR_TIMEOUT          (-(int16_t)(1))
/**
 * \brief   I2C bus busy error 
 */
#define I2C_STS_ERR_BUS_BUSY         (-(int16_t)(2))
/**
 * \brief   I2C no ack error when no acknowledgement is received 
 */
#define I2C_STS_ERR_NO_ACK           (-(int16_t)(3))
/**
 * \brief   I2C Arbitration lost error
 */
#define I2C_STS_ERR_ARBITRATION_LOST (-(int16_t)(4))
/**
 * \brief   I2C Bus Access error
 */
#define I2C_STS_ERR_ACCESS_ERROR     (-(int16_t)(5))
/**
 * \brief   I2C FW Command Access Failure
 */
#define I2C_STS_ERR_COMMAND_FAILURE  (-(int16_t)(6))
/**
 * \brief   I2C FW Invalid Command passed
 */
#define I2C_STS_ERR_INVALID_COMMAND  (-(int16_t)(7))

/**
 *  @brief      A handle that is returned from a I2C_open() call.
 */
typedef struct I2C_Config_s      *I2C_Handle;

 /**
  * \brief   I2C_TRANSACTION valid parameter bit fields.
  *
  * Valid bit fields supported
  *
  * I2C_TRANS_VALID_PARAM_MASTER_MODE
  * I2C_TRANS_VALID_PARAM_EXPAND_SA
  *
  */
#define I2C_TRANS_VALID_PARAM_MASTER_MODE           (0x00000001U)
#define I2C_TRANS_VALID_PARAM_EXPAND_SA             (0x00000002U)

/**<
 *  @brief  I2C transaction
 *
 *  This structure defines the nature of the I2C transaction.
 *
 *  I2C master mode:
 *  This structure specifies the buffer and buffer's size that is to be
 *  written to or read from the I2C slave peripheral.
 *
 *  I2C slave mode:
 *  This structure specifies the buffer and buffer's size that is to be
 *  read from or written to the I2C master. In restart condition,
 *  readBuf/writeBuf and readCount/writeCount are used repeatedly for
 *  every start in one transfer. When each restart happens, driver will
 *  call back to application with the restart transfer status, and
 *  application should save the data transferred in the previous start,
 *  and provide the new data to the current start. When all the starts
 *  complete (stop condition), driver will call back to application with
 *  transfer success status, and readBuf/writeBuf and readCount/writeCount
 *  will only record the data transferred in the last start condition.
 *
 *  arg is an optional user supplied argument that will be passed
 *  to the callback function when the I2C driver is in I2C_MODE_CALLBACK.
 *  nextPtr is to be only used by the I2C driver.
 */
typedef struct I2C_Transaction_s {
    uint32_t            validParams;        /**< Valid transaction parameter bit fields, to keep backward compatibility
                                                 if supported bit field of validParams is 0: the driver will use the
                                                 default configurations, if it is not 0: the driver will use the configuration
                                                 that is set by the bit field */
    void                *writeBuf;          /**< master mode: buffer containing data to be written to slave
                                                 slave mode: buffer containing data to be written to master */
                                            /*   User input (requested write count) and output (actual write count) fields */
    size_t              writeCount;         /**< master mode: number of bytes to be written to the slave
                                                 slave mode: number of bytes to be written to the master */

    void                *readBuf;           /**< master mode: buffer to which data from slave is to be read into
                                                 slave mode: buffer to which data from master is to be read into */
                                            /*   User input (requested read count) and output (actual read count) fields */
    size_t              readCount;          /**< master mode: number of bytes to be read from the slave
                                                  slave mode: number of bytes to be read to the master */

    uint32_t            slaveAddress;       /**< master mode: input field from user to set the address of I2C
                                                 slave device;
                                                 slave mode: output field from driver to report the address
                                                 of a slave channel when multi-slave channels are supported,
                                                 if only one channel is supported, this field is ignored */

    void                *arg;               /**< argument to be passed to the callback function */
    void                *nextPtr;           /**< used for queuing in I2C_MODE_CALLBACK mode */
    uint32_t            timeout;            /**< Timeout value for i2c transaction */

    bool                masterMode;         /**< I2C master or slave mode */
    bool                expandSA;           /**< Expand slave address:
                                                 BTRUE: 10-bit address mode, BFALSE: 7-bit address mode */
} I2C_Transaction;

/**
 *  @brief  I2C transfer mode
 *
 *  I2C_MODE_BLOCKING block task execution while a I2C transfer is in progress
 *  I2C_MODE_CALLBACK does not block task execution; but calls a callback
 *  function when the I2C transfer has completed
 */
typedef enum I2C_TransferMode_e {
    I2C_MODE_BLOCKING,  /**< I2C_transfer blocks execution*/
    I2C_MODE_CALLBACK   /**< I2C_transfer queues transactions and does not block */
} I2C_TransferMode;

/**
 *  @brief  I2C callback function
 *
 *  User definable callback function prototype. The I2C driver will call the
 *  defined function and pass in the I2C driver's handle, the pointer to the I2C
 *  transaction that just completed, and the return value of I2C_transfer.
 *
 *  In slave mode, when there is a restart condtion,the driver calls back
 *  to the application with received data and I2C_STS_RESTART transfer status,
 *  application needs to provide the restart transmit data in I2C_Transaction
 *  rsWrToMstBuf. Restart condition only works in callback mode.
 *
 *  @param  I2C_Handle          I2C_Handle

 *  @param  I2C_Transaction*    Address of the I2C_Transaction performed

 *  @param  bool                Results of the I2C transaction
 */
typedef void (*I2C_CallbackFxn)(I2C_Handle handle, I2C_Transaction * msg, int16_t transferStatus);

/**
 *  @brief  I2C bitRate
 *
 *  Specify one of the standardized I2C bus bit rates for I2C communications.
 *  The default is I2C_100kHz.
 */
typedef enum I2C_BitRate_e {
    I2C_100kHz = 0,
    I2C_400kHz = 1,
    I2C_1P0Mhz = 2,
    I2C_3P4Mhz = 3
} I2C_BitRate;

/**
 *  @brief  I2C Parameters
 *
 *  I2C parameters are used to with the I2C_open() call. Default values for
 *  these parameters are set using I2C_Params_init().
 *
 *  If I2C_TransferMode is set to I2C_MODE_BLOCKING then I2C_transfer function
 *  calls will block thread execution until the transaction has completed.
 *
 *  If I2C_TransferMode is set to I2C_MODE_CALLBACK then I2C_transfer will not
 *  block thread execution and it will call the function specified by
 *  transferCallbackFxn. Sequential calls to I2C_transfer in I2C_MODE_CALLBACK
 *  mode will put the designated transaction onto an internal queue that
 *  automatically starts queued transactions after the previous transaction has
 *  completed. (regardless of error state).
 *
 *  I2C_BitRate specifies the I2C bus rate used for I2C communications.
 *
 *  @sa     I2C_Params_init()
 */
typedef struct I2C_Params_s {
    I2C_TransferMode    transferMode; /**< Blocking or Callback mode */

    /* done to get rid of misra warning MISRA.CAST.FUNC_PTR, it complains later where the function address is assigned */
    void (*transferCallbackFxn)(I2C_Handle i2cHnd, I2C_Transaction * msg, int16_t transferStatus);
    /* I2C_CallbackFxn     transferCallbackFxn; !< Callback function pointer */
    I2C_BitRate         bitRate; /**< I2C bus bit rate */
    void               *custom;  /**< Custom argument used by driver
                                      implementation */
} I2C_Params;

/**<
 *  @brief    I2C transaction timeout define
 */
#define I2C_WAIT_FOREVER   (~((uint32_t)0U))

/**
 *  @brief      A function pointer to a driver specific implementation of
 *              I2C_close().
 */
typedef void        (*I2C_CloseFxn)    (I2C_Handle handle);

/**
 *  @brief      A function pointer to a driver specific implementation of
 *              I2C_control().
 */
typedef int32_t         (*I2C_ControlFxn)  (I2C_Handle handle,
                                        uint32_t cmd,
                                        void *arg);

/**
 *  @brief      A function pointer to a driver specific implementation of
 *              I2C_init().
 */
typedef void        (*I2C_InitFxn)     (I2C_Handle handle);

/**
 *  @brief      A function pointer to a driver specific implementation of
 *              I2C_open().
 */
typedef I2C_Handle  (*I2C_OpenFxn)     (I2C_Handle handle,
                                        const I2C_Params *params);

/**
 *  @brief      A function pointer to a driver specific implementation of
 *              I2C_transfer().
 */
typedef int16_t        (*I2C_TransferFxn) (I2C_Handle handle,
                                        I2C_Transaction *transaction);

/**
 *  @brief      The definition of a I2C function table that contains the
 *              required set of functions to control a specific I2C driver
 *              implementation.
 */
typedef struct I2C_FxnTable_s {
    /** Function to close the specified peripheral */
    I2C_CloseFxn        closeFxn;

    /** Function to implementation specific control function */
    I2C_ControlFxn      controlFxn;

    /** Function to initialize the given data object */
    I2C_InitFxn         initFxn;

    /** Function to open the specified peripheral */
    I2C_OpenFxn         openFxn;

    /** Function to initiate a I2C data transfer */
    I2C_TransferFxn     transferFxn;
} I2C_FxnTable;

/**
 *  @brief  I2C Global configuration
 *
 *  The I2C_Config structure contains a set of pointers used to characterize
 *  the I2C driver implementation.
 *
 *  This structure needs to be defined before calling I2C_init() and it must
 *  not be changed thereafter.
 *
 *  @sa     I2C_init()
 */
typedef struct I2C_Config_s {
    /** Pointer to a table of driver-specific implementations of I2C APIs */
    I2C_FxnTable const *fxnTablePtr;

    /** Pointer to a driver specific data object */
    void               *object;

    /** Pointer to a driver specific hardware attributes structure */
    void         const *hwAttrs;
} I2C_Config;

#define I2C_MAX_CONFIG_CNT (14U)
typedef I2C_Config I2C_config_list[I2C_MAX_CONFIG_CNT];

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  @brief  Function to close a I2C peripheral specified by the I2C handle
 *
 *  @pre    I2C_open() had to be called first.
 *
 *  @param  i2cHnd  A I2C_Handle returned from I2C_open
 *
 *  @sa     I2C_open()
 */
extern void I2C_close(I2C_Handle i2cHnd);

/**
 *  @brief  Function performs implementation specific features on a given
 *          I2C_Handle.
 *
 *  @pre    I2C_open() has to be called first.
 *
 *  @param  i2cHnd      A I2C handle returned from I2C_open()
 *
 *  @param  cmd         A command value defined by the driver specific
 *                      implementation
 *
 *  @param  arg         An optional R/W (read/write) argument that is
 *                      accompanied with cmd
 *
 *  @return Implementation specific return codes. Negative values indicate
 *          unsuccessful operations.
 *
 *  @sa     I2C_open()
 */
extern int32_t I2C_control(I2C_Handle i2cHnd, uint32_t cmd, void *arg);

/**
 *  @brief  Function to initializes the I2C module
 *
 *  @pre    The I2C_config structure must exist and be persistent before this
 *          function can be called. This function must also be called before
 *          any other I2C driver APIs. This function call does not modify any
 *          peripheral registers.
 */
extern void I2C_init(void);

/**
 *  @brief  Function to initialize a given I2C peripheral specified by the
 *          particular index value. The parameter specifies which mode the I2C
 *          will operate.
 *
 *  @pre    I2C controller has been initialized
 *
 *  @param  idx           Logical peripheral number for the I2C indexed into
 *                        the I2C_config table
 *
 *  @param  params        Pointer to an parameter block, if NULL it will use
 *                        default values. All the fields in this structure are
 *                        RO (read-only).
 *
 *  @return A I2C_Handle on success or a NULL on an error or if it has been
 *          opened already.
 *
 *  @sa     I2C_init()
 *  @sa     I2C_close()
 */
extern I2C_Handle I2C_open(uint32_t idx, I2C_Params *params);

/**
 *  @brief  Function to initialize the I2C_Params struct to its defaults
 *
 *  @param  params      An pointer to I2C_Params structure for
 *                      initialization
 *
 *  Defaults values are:
 *      transferMode = I2C_MODE_BLOCKING
 *      transferCallbackFxn = NULL
 *      bitRate = I2C_100kHz
 */
extern void I2C_Params_init(I2C_Params *params);

/**
 *  @brief  Function that handles the I2C transfer for SYS/BIOS
 *
 *  This function will start a I2C transfer and can only be called from a Task
 *  context when in I2C_MODE_BLOCKING.
 *  The I2C transfer procedure starts with evaluating how many bytes are to be
 *  written and how many are to be read from the I2C peripheral. Due to common
 *  I2C data transfer processes, to be written will always sent before any data
 *  is read.
 *
 *  The data written to the peripheral is preceded with the peripheral's 7-bit
 *  I2C slave address (with the Write bit set).
 *  After all the data has been transmitted, the driver will evaluate if any
 *  data needs to be read from the device.
 *  If so, a Re-START bit is sent, along with the same 7-bit I2C slave address
 *  (with the Read bit). Else, the transfer is concluded with a STOP bit.
 *  After the specified number of bytes have been read by the I2C, the transfer
 *  is ended with a NACK and STOP bit.
 *
 *  In I2C_MODE_BLOCKING, I2C_transfer will block task execution until the
 *  transaction has completed.
 *
 *  In I2C_MODE_CALLBACK, I2C_transfer does not block task execution and calls a
 *  callback function specified by transferCallbackFxn. If a transfer is already
 *  taking place, the transaction is put on an internal queue. The queue is
 *  serviced in a first come first served basis.
 *  The I2C_Transaction structure must stay persistent until the I2C_transfer
 *  function has completed!
 *
 *  @param  i2cHnd      A I2C_Handle
 *
 *  @param  transaction A pointer to a I2C_Transaction. All of the fields within
 *                      transaction are WO (write-only) unless otherwise noted
 *                      in the driver implementations.
 *
 *  @return true on successful transfer
 *          false on an error, such as a I2C bus fault
 *
 *  @sa     I2C_open
 */
extern int16_t I2C_transfer(I2C_Handle i2cHnd, I2C_Transaction *transaction);

/**<
 *  @brief  Function to initialize the I2C_Transaction struct to its defaults
 *
 *  Defaults values are:
 *  validParams = I2C_TRANS_VALID_PARAM_MASTER_MODE;
 *  writeBuf = NULL;
 *  writeCount = 0;
 *  readBuf = NULL;
 *  readCount = 0;
 *  slaveAddress = 0;
 *  arg = NULL;
 *  nextPtr = NULL;
 *  timeout = I2C_WAIT_FOREVER;
 *  rsWrToMstBuf = NULL;
 *  rsWrToMstCnt = 0;
 *  masterMode = BTRUE;
 *
 *  @return   transaction parameter structure to initialize
 */
extern void I2C_transactionInit(I2C_Transaction *transaction);

#ifdef __cplusplus
}
#endif

#endif /* _I2C_H_ */

/* @} */
