#include <stdint.h>
#include <stdarg.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_i2c.h>
#include <ti/csl/cslr_pmmc.h>
#if defined(SOC_J7200)
#include <ti/board/src/j7200_evm/include/board_cfg.h>
#include <ti/board/src/j7200_evm/include/board_pll.h>
#include <ti/board/src/j7200_evm/include/board_ddr.h>
#endif
#include <ti/drv/lpm/include/io_retention/dmsc_cm.h>
#include <ti/drv/pmic/src/pmic_fsm_priv.h>

/* ========================================================================== */
/*                               Debug Options                                */
/* ========================================================================== */

/**
 * Uncomment the define of DEBUG_SRAM_S2R enables the debug messages during
 * suspend sequence.
 * Additional debug messages can be added using the flag DEBUG_FULL_SRAM_S2R.
 * By default debug messages are printed on MCU_UART0, but they can be
 * redirected by enabling DEBUG_UART_MAIN flag.
 * A compilation is needed for each modification.
 */
#define DEBUG_SRAM_S2R
#define DEBUG_FULL_SRAM_S2R
//#define DEBUG_UART_MAIN

#ifdef DEBUG_UART_MAIN
#define UART_DEBUG_ADDR CSL_UART0_BASE
#else
#define UART_DEBUG_ADDR CSL_MCU_UART0_BASE
#endif

#ifdef BUILD_MCU1_0
static const char mcu_str[] = "MCU1_0";
#else
#ifdef BUILD_MCU1_1
static const char mcu_str[] = "MCU1_1";
#else
#ifdef BUILD_MCU2_0
static const char mcu_str[] = "MCU2_0";
#else
#ifdef BUILD_MCU2_1
static const char mcu_str[] = "MCU2_1";
#else
static const char mcu_str[] = "UNKNOW";
#endif
#endif
#endif
#endif

#if defined(DEBUG_SRAM_S2R) && defined(DEBUG_FULL_SRAM_S2R)
#define Lpm_debugFullPrintf Lpm_debugPrintf
#define Lpm_debugReadPmicA  Lpm_readPmicA
#define Lpm_debugReadPmicB  Lpm_readPmicB
#else
#define Lpm_debugFullPrintf(...) do {} while(0)
#define Lpm_debugReadPmicA(...)  do {} while(0)
#define Lpm_debugReadPmicB(...)  do {} while(0)
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define CSL_PLL0_CFG_RD(r)     CSL_REG32_RD_OFF(CSL_PLL0_CFG_BASE, r)
#define CSL_PLL0_CFG_WR(r, v)  CSL_REG32_WR_OFF(CSL_PLL0_CFG_BASE, r, v)
#define CSL_PLL0_CFG_SET(r, m) CSL_PLL0_CFG_WR(r, CSL_PLL0_CFG_RD(r) | m)
#define CSL_PLL0_CFG_CLR(r, m) CSL_PLL0_CFG_WR(r, CSL_PLL0_CFG_RD(r) & ~(m))

#define CSL_WKUP_CTRL_MMR0_CFG0_RD(r)     CSL_REG32_RD_OFF(CSL_WKUP_CTRL_MMR0_CFG0_BASE, r)
#define CSL_WKUP_CTRL_MMR0_CFG0_WR(r, v)  CSL_REG32_WR_OFF(CSL_WKUP_CTRL_MMR0_CFG0_BASE, r, v)
#define CSL_WKUP_CTRL_MMR0_CFG0_SET(r, m) CSL_WKUP_CTRL_MMR0_CFG0_WR(r, CSL_WKUP_CTRL_MMR0_CFG0_RD(r) | m)
#define CSL_WKUP_CTRL_MMR0_CFG0_CLR(r, m) CSL_WKUP_CTRL_MMR0_CFG0_WR(r, CSL_WKUP_CTRL_MMR0_CFG0_RD(r) & ~(m))

#define CSL_WKUP_I2C0_CFG_RD(r)     CSL_REG32_RD_OFF(CSL_WKUP_I2C0_CFG_BASE, r)
#define CSL_WKUP_I2C0_CFG_WR(r, v)  CSL_REG32_WR_OFF(CSL_WKUP_I2C0_CFG_BASE, r, v)
#define CSL_WKUP_I2C0_CFG_SET(r, m) CSL_WKUP_I2C0_CFG_WR(r, CSL_WKUP_I2C0_CFG_RD(r) | m)
#define CSL_WKUP_I2C0_CFG_CLR(r, m) CSL_WKUP_I2C0_CFG_WR(r, CSL_WKUP_I2C0_CFG_RD(r) & ~(m))

#define CSL_DDRSS0_RD(r)     CSL_REG32_RD_OFF(CSL_STD_FW_COMPUTE_CLUSTER0__VBUSP_DDRSS0_DDRSS0_CTLCFG_CTL_CFG_START, r)
#define CSL_DDRSS0_WR(r, v)  CSL_REG32_WR_OFF(CSL_STD_FW_COMPUTE_CLUSTER0__VBUSP_DDRSS0_DDRSS0_CTLCFG_CTL_CFG_START, r, v)
#define CSL_DDRSS0_SET(r, m) CSL_DDRSS0_WR(r, CSL_DDRSS0_RD(r) | m)
#define CSL_DDRSS0_CLR(r, m) CSL_DDRSS0_WR(r, CSL_DDRSS0_RD(r) & ~(m))

#define CSL_CTRL_MMR0_CFG0_RD(r)      CSL_REG32_RD_OFF(CSL_CTRL_MMR0_CFG0_BASE, r)
#define CSL_CTRL_MMR0_CFG0_WR(r, v)   CSL_REG32_WR_OFF(CSL_CTRL_MMR0_CFG0_BASE, r, v)
#define CSL_CTRL_MMR0_CFG0_SET(r, m)  CSL_CTRL_MMR0_CFG0_WR(r, CSL_CTRL_MMR0_CFG0_RD(r) | m)
#define CSL_CTRL_MMR0_CFG0_CLR(r, m)  CSL_CTRL_MMR0_CFG0_WR(r, CSL_CTRL_MMR0_CFG0_RD(r) & ~(m))

#define SCICLIENT_LPM_GPIO2_CONF (0x32)
#define SCICLIENT_LPM_GPIO3_CONF (0x33)
#define SCICLIENT_LPM_GPIO6_CONF (0x36)
#define SCICLIENT_LPM_INT_TOP    (0x5A)

#define SCICLIENT_LPM_DDR_RET_VAL     (1 << 1)
#define SCICLIENT_LPM_DDR_RET_CLK     (1 << 2)
#define SCICLIENT_LPM_EN_DDR_RET_1V1  (1 << 5)
#define SCICLIENT_LPM_GPIO4_BIT       (1 << 3)
#define SCICLIENT_LPM_OD_SHIFT        1
#define SCICLIENT_LPM_DIR_SHIFT       0
#define SCICLIENT_LPM_SCRATCH_PAD_REG_3 (0xCB)
#define SCICLIENT_LPM_MAGIC_SUSPEND     (0xBA)
#define SCICLIENT_LPM_GPIO1_8_FALL 0xFF
#define SCICLIENT_LPM_GPIO1_8_RISE 0xF7

#define SCICLIENT_LPM_FSM_I2C_TRIGGERS (0x80)

#define SCICLIENT_LPM_DEVICE_ID_PMICB     0x86
#define SCICLIENT_LPM_DEVICE_ID_PMICB_EVM 0x7
#define SCICLIENT_LPM_I2C_DETECT_TIMEOUT  500 /* usually the I2C is ready after 221 loops */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/**
 * A simple UART based printf function supporting \%p, \%x, and \%X.
 *
 * \param pcString is the format string.
 * \param ... are the optional arguments, which depend on the contents of the
 * format string.
 *
 * This function is a partial copy of UART_printf from
 * ti/drv/uart/src/UART_stdio.c.
 * But only the support of \%p, \%x and \%X was kept.
 *
 * \return None.
 */
static void Lpm_debugPrintf(const char *pcString, ...);


#ifdef DEBUG_SRAM_S2R
/**
 * \brief   This function writes a byte on the serial console
 *
 * This function is based on UART_putc from ti/drv/uart/src/UART_stdio.c.
 *
 * \param   baseAdd  Address of the UART port to use.
 *          byteTx   The byte to be transmitted.
 *
 */
static void _Lpm_debugPutC(uint32_t baseAdd, uint8_t byteTx)
{
    uint32_t lcrRegValue = CSL_REG32_RD_OFF(baseAdd, UART_LCR);

    CSL_REG32_WR_OFF(baseAdd, UART_LCR, lcrRegValue & 0x7FU);
    /*
    ** Waits indefinitely until the THR and Transmitter Shift Registers are
    ** empty.
    */
    while(((unsigned int) UART_LSR_TX_SR_E_MASK |
           (unsigned int) UART_LSR_TX_FIFO_E_MASK) !=
          (CSL_REG32_RD_OFF(baseAdd, UART_LSR) &
           ((unsigned int) UART_LSR_TX_SR_E_MASK |
            (unsigned int) UART_LSR_TX_FIFO_E_MASK)))
    {
        /* Busy wait */
    }

    CSL_REG32_WR_OFF(baseAdd, UART_THR, byteTx);
    CSL_REG32_WR_OFF(baseAdd, UART_LCR, lcrRegValue);
}

/**
 * \brief  Wrapper function to call _Lpm_debugPutC
 *
 * \param  byteTx The byte to be transmitted.
 *
 */
static void Lpm_debugPutC(uint8_t byteTx)
{
#ifndef DEBUG_UART_MAIN
    static bool Lpm_uartConfigured = false;
    if (Lpm_uartConfigured == false)
    {
        CSL_REG32_WR_OFF(CSL_MCU_UART0_BASE, UART_LCR,
                         UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1 | UART_PARITY_NONE);
	Lpm_uartConfigured = true;
    }
#endif
    _Lpm_debugPutC(UART_DEBUG_ADDR, byteTx);
}

/**
 * \brief  This function writes data from a specified buffer onto the transmitter
 *         FIFO of UART
 *
 * \param  str  Pointer to a buffer to transmit.
 *         len  Number of bytes to be transmitted.
 *
 */
static void Lpm_debugPutS(const char *str, uint32_t len)
{
    unsigned int i;
    for (i = 0; i < len && str[i] != '\0'; i++)
    {
        if (str[i] == '\n')
        {
           Lpm_debugPutC('\r');
        }
        Lpm_debugPutC(str[i]);
    }
}

/**
 * \brief This function calls to the common procedure in Lpm_debugPrintf.
 *        This functions writes the output in hex format.
 *
 * This function is a partial copy of UART_convertVal from
 * ti/drv/uart/src/UART_stdio.c. Only the hexadecimal support was kept.
 *
 * \param ulValue  The value of the resolved variable passed as argument
 *        ulPos    The buffer position of the printed value
 *        ulCount  Total number of character to be printed
 *        cFill    The char to be placed between number
 *        pcBuf    buffer storing all the numbers
 *
 * \return 0.
 *
 */
static int32_t Lpm_debugConvertVal(uint32_t ulValue, uint32_t ulPos, uint32_t ulCount, char cFill, char *pcBuf)
{
    const char *const g_pcHex = "0123456789abcdef";
    uint32_t ulBase = 16;
    uint32_t ulIdx;
    uint32_t count = ulCount;
    uint32_t pos = ulPos;

    for (ulIdx = 1u;
         (((ulIdx * ulBase) <= ulValue) &&
          (((ulIdx * ulBase) / ulBase) == ulIdx));
         (ulIdx = (ulIdx * ulBase)))
    {
        count--;
    }

    /* Provide additional padding at the beginning of the
     * string conversion if needed. */
    if ((count > 1u) && (count < 16u))
    {
        for (count--; count != 0U; count--)
        {
            pcBuf[pos] = cFill;
            pos++;
        }
    }

    /* Convert the value into a string. */
    for (; ulIdx != 0U; ulIdx /= ulBase)
    {
        pcBuf[pos] = g_pcHex[(ulValue / ulIdx) % ulBase];
        pos++;
    }

    /* Write the string. */
    (void)Lpm_debugPutS(pcBuf, pos);

    return 0;
}

static void Lpm_debugPrintf(const char *pcString, ...)
{
    uint32_t ulIdx, ulValue, ulPos, ulCount;
    char    pcBuf[16], cFill;
    va_list  vaArgP;
    const char *pStr = pcString;

    /* Start the varargs processing. */
    (void)va_start(vaArgP, pcString);

    /* write the MCU we are on */
    (void)Lpm_debugPutS(mcu_str, -1);
    (void)Lpm_debugPutS(" ", -1);

    /* Loop while there are more characters in the string. */
    while (*pStr != (char)0U)
    {
        /* Find the first non-% character, or the end of the string. */
        for (ulIdx = 0;
             (pStr[ulIdx] != (char) '%') &&
             (pStr[ulIdx] != (char) '\0');
             ulIdx++)
        {}

        /* Write this portion of the string. */
        (void)Lpm_debugPutS(pStr, ulIdx);

        /* Skip the portion of the string that was written. */
        pStr += ulIdx;

        /* See if the next character is a %. */
        if (*pStr == (char) '%')
        {
            /* Skip the %. */
            pStr++;

            /* Set the digit count to zero, and the fill character to space
             * (i.e. to the defaults). */
            ulCount = 0;
            cFill   = (char) ' ';

            /* Determine how to handle the next character. */ 
            while((*pStr >= (char)'0') && (*pStr <= (char)'9'))
            {
                /* If this is a zero, and it is the first digit, then the
                 * fill character is a zero instead of a space. */
                if ((pStr[-1] == (char) '0') && (ulCount == 0U))
                {
                    cFill = (char) '0';
                }

                /* Update the digit count. */
                ulCount *= 10u;
                ulCount += ((uint32_t)(*pStr)) - (uint32_t) '0';

                /* Get the next character. */
                pStr++;
            }
            switch (*pStr)
            {
                /* Handle the %x and %X commands.  Note that they are treated
                 * identically; i.e. %X will use lower case letters for a-f
                 * instead of the upper case letters is should use.  We also
                 * alias %p to %x. */
                case (char) 'd':
                    (void)Lpm_debugPutS("0x", -1);
		    /* fall through */
                case (char) 'x':
                case (char) 'X':
                case (char) 'p':
                {
                    /* Get the value from the varargs. */
                    ulValue = (uint32_t)va_arg(vaArgP, uint32_t);

                    /* Reset the buffer position. */
                    ulPos = 0;

                    /* Determine the number of digits in the string version of
                     * the value. */
                    (void)Lpm_debugConvertVal(ulValue, ulPos, ulCount, cFill, pcBuf);

                    break;
                }
		case (char) 's':
		{
			char *val = (char *)va_arg(vaArgP, char *);

			(void)Lpm_debugPutS(val, 1000);
			break;
		}

                /* Handle all other commands. */
                default:
                {
                    /* Indicate an error. */
                    (void)Lpm_debugPutS("ERROR", 5u);

                    /* This command has been handled. */
                    break;
                }
            }
            pStr++;
        }
    }

    /* End the varargs processing. */
    va_end(vaArgP);
}

#else
void Lpm_debugPrintf(const char *pcString, ...) {}
#endif /* DEBUG_SRAM_S2R */
