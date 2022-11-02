#define DEBUG_SRAM_S2R
#include <stdint.h>
#include <stdarg.h>
#include "LPM_Libraries.h"
#include "i2c_reg_val.h"
#define BOARD_PLL12_LOCK0                (0x68C010U)
#define BOARD_PLL12_LOCK1                (0x68C014U)
#define KICK0_UNLOCK             (0x68EF3490U)
#define KICK1_UNLOCK             (0xD172BC5AU)
#define PMICA_SLAVE_ADDR            (0x48U)
#define PMICB_SLAVE_ADDR            (0x4CU)
#define DDR_RET_VAL (1 << 1) /* BIT(1) */
#define DDR_RET_CLK (1 << 2) /* BIT(2) */
#define UART_THR		(0x00U)
#define UART_LSR		(0x14U)
#define UART_LSR_TX_SR_E_MASK	(0x40U)
#define UART_LSR_TX_FIFO_E_MASK	(0x20U)

static const char *const g_pcHex = "0123456789abcdef";
static int ddr_retention(void);
int32_t setup_pmic(int ioret);
void clean_all_dcache(void);
void DDR_freq_change(unsigned int x);
void my_exit_DDR_ret();

#ifdef DEBUG_SRAM_S2R
static void uart_puts(const char *pTxBuffer);
#ifdef DEBUG_FULL_SRAM_S2R
void debug_printf(const char *pcString, ...);
#else
static inline void debug_printf(const char *pcString, ...) {}
#endif
#else
static inline void uart_puts(const char *pTxBuffer) {}
static inline void debug_printf(const char *pcString, ...) {}
#endif

void enter_retention(void)
{
	/* 1 => ioret 0 => deep sleep */
	int ioret = 0;

	uart_puts(__func__);
	uart_puts(", time=");
	uart_puts(__TIME__);
	uart_puts("\n\r");

	/* Make sure that nothing remains in cache before going to retention */
	clean_all_dcache();

	if (ioret)
		uart_puts("=> I/O retention\n\r");
	else
		uart_puts("=> full DDR retention\n\r");

	debug_printf("%s %s\n", __func__,  __TIME__);
	if (!ioret) {
		ddr_retention();
		debug_printf("DDRSS_CTL_141: 0x%08x\n", *( unsigned int *)DDRSS_CTL_141);
		debug_printf("DDR retention done!\n");
	}
	setup_pmic(ioret);
	uart_puts("done ! Going to wait now \n\r");

	while(1){};
}

void clean_all_dcache(void)
{
	unsigned int set, way;

	for (way = 0; way < 4 ; way ++)
		for (set = 0; set < 0x200; set++) {
			unsigned int val = set << 4 | way << 30;
			asm("    dmb");
			__asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 2\t\n": "=r"(val));
			__asm__ __volatile__ ("mcr p15, 0, %0, c7, c6, 2\t\n": "=r"(val));
			asm("    dsb");
		}
}

void DDR_freq_change(unsigned int x) {
	unsigned int val;
	volatile unsigned int t;

	*(unsigned int *)CTRLMMR_LOCK5_KICK0 = KICK0_UNLOCK;
	*(unsigned int *)CTRLMMR_LOCK5_KICK1 = KICK1_UNLOCK;

	*(volatile unsigned int *)DDRSS_CTL_190 |= 0x01010100;
	debug_printf("DDRSS_CTL_190: 0x%08X\n\n", *(volatile unsigned int *)DDRSS_CTL_190);

	debug_printf("req_type: %d\n",x);
	*(volatile unsigned int *)CTRLMMR_CHNG_DDR4_FSP_REQ = x;  // set REQ_TYPE to x
	for(t = 0; t< 100; t++) {}
	*(volatile unsigned int *)CTRLMMR_CHNG_DDR4_FSP_REQ |= 0x100;  // assert req

	val = *(volatile unsigned int *)CTRLMMR_DDR4_FSP_CLKCHNG_REQ;
	while((val & 0x80) != 0x80) {
		val = *(volatile unsigned int *)CTRLMMR_DDR4_FSP_CLKCHNG_REQ;
	}

	if(x == 0) {
		*(volatile unsigned int *)PLL12_CTRL |= 0x80000000;
		val = *( volatile unsigned int *)PLL12_CTRL;
		debug_printf("PLL12_CTRL =%x\n", val);
		if ((val & 0x80000000) == 0x80000000) {
			val = *( volatile unsigned int *)PLL12_CTRL;
		}

	} else if((x == 1) || (x==2)) {
		*(volatile unsigned int *)PLL12_CTRL &= ~0x80000000;
		val = *( volatile unsigned int *)PLL12_CTRL;
		if ((val & 0x80000000) == 0x80000000) {
			val = *( volatile unsigned int *)PLL12_CTRL;
		}
		val = (*(volatile unsigned int *)PLL12_HSDIV0 & ~0xFF);
		*(unsigned int *)PLL12_HSDIV0 = (val | 0x03);
		val = *( volatile unsigned int *)PLL12_HSDIV0;
		if ((val & 0xFF) != 0x03) {
			val = *( volatile unsigned int *)PLL12_HSDIV0;
		}
	}

	for(t = 0; t< 1000000; t++) {}
	*(volatile unsigned int *)CTRLMMR_DDR4_FSP_CLKCHNG_ACK = 1;

	val = *(volatile unsigned int *)CTRLMMR_CHNG_DDR4_FSP_ACK;
	while((val & 0x80) != 0x80) {
		val = *(volatile unsigned int *)CTRLMMR_CHNG_DDR4_FSP_ACK;
	}

	*(unsigned int *)CTRLMMR_DDR4_FSP_CLKCHNG_ACK = 0;
	*(unsigned int *)CTRLMMR_CHNG_DDR4_FSP_REQ &= ~0x100;  // de-assert req
}

void enter_DDR_retention(void) {

	unsigned int n;

	/* try going to a new fsp (boot freq) before entering retention (11/3/21) */
	DDR_freq_change(0);
	debug_printf("Readout PHY regs in boot freq prior to entry into DDR RET\n");
	/* disable auto entry / exit */
	*( unsigned int *)DDRSS_CTL_141 &= ~((0xF << 24) | (0xF << 16));
	n = *( unsigned int *)DDRSS_CTL_132 &= ~(0x7F << 24);
	/* set low power mode to 0x31 (alternatively could use 0x51??)*/
	*( unsigned int *)DDRSS_CTL_132 = (n | (0x51 << 24));
	/* wait until low power operation has been completed */
	while((*( unsigned int *)DDRSS_CTL_293 & (0x1 << 10)) == 0) {};
	/*clear flag by writing t to DDRSS_CTL_295[10] */
	*( unsigned int *)DDRSS_CTL_295 = (0x1 << 10);
	/* bit 6 / 14 -- lp_state valid; bits 13:8 / 5:0 0x0F SRPD Long with Mem Clk Gating */
	while((*( unsigned int *)DDRSS_CTL_141 & 0x4F4F) != 0x4F4F) {};

	debug_printf("DDRSS_CTL_141: 0x%08x\n", *( unsigned int *)DDRSS_CTL_141);
	debug_printf("DDRSS_CTL_132: 0x%08x\n", *( unsigned int *)DDRSS_CTL_132);
	debug_printf("DDRSS_CTL_293: 0x%08x\n", *( unsigned int *)DDRSS_CTL_293);
	debug_printf("\npi interrupt status: 0x%08x\n", *(unsigned int *)DDRSS_PI_79);
}

static void unlock_pll_ddr(void)
{
	*(unsigned int *)BOARD_PLL12_LOCK0 = KICK0_UNLOCK;
	*(unsigned int *)BOARD_PLL12_LOCK1 = KICK1_UNLOCK;
}

static int ddr_retention(void)
{
	unlock_pll_ddr();
	enter_DDR_retention();
	uart_puts("Board_DDR_enter_retention done \n");
	return 0;
}

void WKUP_LOCK7(void)  {
	*(unsigned int *)0x4301D008 = KICK0_UNLOCK;
	*(unsigned int *)0x4301D00C = KICK1_UNLOCK;
}

unsigned char i2c_read(char add){
	unsigned char rxd;
	unsigned int n;

	/* wait BB --> 0 */
	while((*(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW & (0x1 << 12)) != 0x00 ){}

	*(unsigned int *)WKUP_I2C0_CNT = 1;
	n = *(unsigned int *)WKUP_I2C0_CON & ~0x2;
	*(unsigned int *)WKUP_I2C0_CON = (n | (3 << 9));
	n = *(unsigned int *)WKUP_I2C0_CON | (1 << 0);
	*(unsigned int *)WKUP_I2C0_CON = n;

	/* wait XRDY --> 1 */
	while((*(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW & (0x1 << 4)) == 0x00){}

	*(unsigned int *)WKUP_I2C0_DATA = add; // write enable to register lock
	*(unsigned int *)WKUP_I2C0_IRQSTATUS = (0x1 << 4); //

	/* wait ARDY --> 1 */
	while((*(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW & (0x1 << 2)) == 0x00){}
	*(unsigned int *)WKUP_I2C0_IRQSTATUS = *(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW;

	n = *(unsigned int *)WKUP_I2C0_CON & ~(0x1 << 9);
	*(unsigned int *)WKUP_I2C0_CON = n | (1 << 10);
	*(unsigned int *)WKUP_I2C0_CNT = 1;
	*(unsigned int *)WKUP_I2C0_CON |= (3 << 0);

	/* wait RRDY --> 1 */
	while((*(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW & (0x1 << 3)) == 0x00){}
	rxd = *(unsigned int *)WKUP_I2C0_DATA;

	/* wait ARDY --> 1 */
	while((*(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW & (0x1 << 2)) == 0x00){}
	*(unsigned int *)WKUP_I2C0_IRQSTATUS = *(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW;

	return rxd;
}

void i2c_write(char add, char data) {
	unsigned int n;

	/* wait BB --> 0 */
	while((*(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW & (0x1 << 12)) != 0x00){}

	*(unsigned int *)WKUP_I2C0_CNT = 2;
	n = *(unsigned int *)WKUP_I2C0_CON & ~0x2;
	*(unsigned int *)WKUP_I2C0_CON = (n | (3 << 9));
	n = *(unsigned int *)WKUP_I2C0_CON;
	*(unsigned int *)WKUP_I2C0_CON = (n | (3 << 0));

	for (n = 0; n < 2; n++) {
		/* wait XRDY --> 1 */
		while((*(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW & (0x1 << 4)) == 0x00){}
		if(n==0) {
			/* write enable to register lock */
			*(unsigned int *)WKUP_I2C0_DATA = add;
		}
		else {
			/* write enable to register lock */
			*(unsigned int *)WKUP_I2C0_DATA = data;
			*(unsigned int *)WKUP_I2C0_IRQSTATUS = (0x1 << 4); //
		}
	}
	/* wait ARDY --> 1 */
	while((*(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW & (0x1 << 2)) == 0x00){}
	*(unsigned int *)WKUP_I2C0_IRQSTATUS = *(unsigned int *)WKUP_I2C0_IRQSTATUS_RAW;
}

void Config_WKUP_I2C(char pmic) {
	unsigned int n;

	WKUP_LOCK7();
// need PADCONFIGs
	*(unsigned int *)CTRLMMR_WKUP_PADCONFIG62 |= (1 << 18);
//    *(unsigned int *)CTRLMMR_WKUP_PADCONFIG62 &= ~(1 << 20);
	*(unsigned int *)CTRLMMR_WKUP_PADCONFIG63 |= (1 << 18);
//    *(unsigned int *)CTRLMMR_WKUP_PADCONFIG63 &= ~(1 << 20);

	/*  reset the I2C */
	*(unsigned int *)WKUP_I2C0_SYSC = (1 << 1);
	n = *(unsigned int *)WKUP_I2C0_SYSC | (1 << 3);
	*(unsigned int *)WKUP_I2C0_SYSC = n;

	/* enable I2C */
	*(unsigned int *)WKUP_I2C0_CON |= (1 << 15);
	while((*(unsigned int *)WKUP_I2C0_SYSS & 0x1) == 0x00){}


	/* set divider = 2 */
	n = *(unsigned int *)WKUP_I2C0_PSC & ~0xFF;
	/* 96/(7+1) = 12MHz */
	*(unsigned int *)WKUP_I2C0_PSC = (n | 0x7);

	/* 9.6MHz/(n1 + n2) = 0.4 -- > n1 + n2 = 24 */
	/* set SCLL 7 + 9 = 16 */
	n = *(unsigned int *)WKUP_I2C0_SCLL & ~0xFF;
	*(unsigned int *)WKUP_I2C0_SCLL = (n | 0x9);
	/* set SCLH 5 + 9 = 14 */
	n = *(unsigned int *)WKUP_I2C0_SCLH & ~0xFF;
	*(unsigned int *)WKUP_I2C0_SCLH = (n | 0x9);

	*(unsigned int *)WKUP_I2C0_CON &= ~0xCF03;
	*(unsigned int *)WKUP_I2C0_CNT &= ~0xFFFF;
	*(unsigned int *)WKUP_I2C0_BUF &= ~0x8080;

	/* set own address = 0xB4 (random) */
	n = *(unsigned int *)WKUP_I2C0_OA & ~0x3FF;
	*(unsigned int *)WKUP_I2C0_OA = (n | 0xb4);

	/* enable I2C */
	*(unsigned int *)WKUP_I2C0_CON |= (1 << 15);
	while((*(unsigned int *)WKUP_I2C0_SYSS & 0x1) == 0x00){}

	/* set PMIC ADDRESS */
	n = *(unsigned int *)WKUP_I2C0_SA & ~0x3FF;
	*(unsigned int *)WKUP_I2C0_SA = (n | pmic);

	/* Set TX / RX threshold to 1 [5:0] = 1-1; [13:8] = 1-1 */
	*(unsigned int *)WKUP_I2C0_BUF = ((1 << 6) | (1 << 14));

	/* write enable */
	i2c_write(0xA1, 0x9B);
}

/* All the following function could be improve by splitting
 * Config_WKUP_I2C in two part: the real initialisation and then jsut
 * the address setting */
void write_pmicA(uint8_t reg, uint8_t val)
{
	Config_WKUP_I2C(PMICA_SLAVE_ADDR);
	i2c_write(reg, val);
	debug_printf("%s reg=0x%x 0x%x\n", __func__, reg, val);
}

void write_pmicB(uint8_t reg, uint8_t val)
{
	Config_WKUP_I2C(PMICB_SLAVE_ADDR);
	i2c_write(reg, val);
	debug_printf("%s reg=0x%x 0x%x\n", __func__, reg, val);
}

uint8_t read_pmicA(uint8_t reg)
{
	unsigned char rxd;
	Config_WKUP_I2C(PMICA_SLAVE_ADDR);
	rxd = i2c_read(reg);
	debug_printf("%s reg=0x%x 0x%x\n", __func__, reg, rxd);
	return rxd;
}

uint8_t read_pmicB(uint8_t reg)
{
	unsigned char rxd;
	Config_WKUP_I2C(PMICB_SLAVE_ADDR);
	rxd = i2c_read(reg);
	debug_printf("%s reg=0x%x 0x%x\n", __func__, reg, rxd);
	return rxd;
}


int32_t setup_pmic(int ioret)
{
	uint8_t out;

	debug_printf("%s ioret=%d\n", __func__, ioret);

	if (ioret) {
		/* force bits 19:16 to 0110b from 1111b */
		*( unsigned int *)CTRLMMR_WKUP_POR_RST_CTRL &= ~(9 << 16);
	}
	read_pmicA(0);
	read_pmicA(0x86);
	/* Set State machine to active on PMIC A */
	write_pmicA(0x86, 0x03);
	read_pmicA(0x86);

	/* Clear Enable Interrupt on PMIC A and PMIC B */
	write_pmicA(0x65, 0x02);
	write_pmicB(0x65, 0x02);
	debug_printf("Clear Enable Interrupt on PMIC A and PMIC B done \n");
	if (!ioret) {
		/* Set Triggers for DDR Retention Mode on PMIC A and PMIC B*/
		write_pmicB(0x85, 0x80);
		write_pmicA(0x85, 0x80);
	}

	/* Configure Wakeup Source on PMIC A.  We are using GPIO4 which is
	 * tied to CAN_WAKE (SW12) on EVM. */
	write_pmicA(0x50, ~(0x01 << 3));
	write_pmicA(0x4F, 0xFF);
	write_pmicA(0x51, 0x3F);
	write_pmicA(0x34, 0xCA);

	/* Clear GPIO Interrupts on PMIC A, write to clear */
	write_pmicA(0x64, read_pmicA(0x64));
	write_pmicA(0x63, read_pmicA(0x63));

	/* Set DDR_RET Signal High on PMIC B*/
	debug_printf("GPIO1_OUT init =  %X\n", read_pmicB(0x3D));
	if (!ioret) {
		out = (read_pmicB(0x3D) & 0xFF) | DDR_RET_VAL;
		write_pmicB(0x3D, out);

		/* Now toggle the CLK of the latch for DDR ret*/
		write_pmicB(0x3D, out | DDR_RET_CLK);
		debug_printf("GPIO1_OUT clk =  %X\n", read_pmicB(0x3D));

		write_pmicB(0x3D, out & ~DDR_RET_CLK);
		debug_printf("GPIO1_OUT final =  %X\n", read_pmicB(0x3D));

	}
	/* set pin to signal we enter in suspend */
	write_pmicB(0x3D, out | DDR_RET_CLK);
	debug_printf("GPIO1_OUT final =  %X\n", read_pmicB(0x3D));

	if (ioret) {
		/* force NSLEEP2B = 1 and NSLEEP1B = 0 => MCU ONLY */
		write_pmicA(0x86, 0x01);
	} else {
		/* Enter Retention/Deep Sleep Power mode on PMIC A*/
		write_pmicA(0x86, 0x00);
	}

	return 0;
}

#ifdef DEBUG_SRAM_S2R
static void _debug_putc(unsigned int baseAdd, uint8_t byteTx)
{
	unsigned int *reg = (unsigned int*)(baseAdd + UART_LSR);
	/*
	** Waits indefinitely until the THR and Transmitter Shift Registers are
	** empty.
	*/
	while (((unsigned int) UART_LSR_TX_SR_E_MASK |
		(unsigned int) UART_LSR_TX_FIFO_E_MASK) !=
	       (*reg & 	((unsigned int) UART_LSR_TX_SR_E_MASK |
		 (unsigned int) UART_LSR_TX_FIFO_E_MASK)))
	{
		/* Do nothing - Busy wait */
	}

	reg = (unsigned int*)(baseAdd + UART_THR);
	*reg = (unsigned int) byteTx;
}

void debug_putc(uint8_t byteTx)
{
	_debug_putc(0x40a00000, byteTx);
}

/* Write the string until a null character */
void uart_puts(const char *pTxBuffer)
{
	unsigned int flag  = 0;
	const char *bufPtr = pTxBuffer;

	while ((char) '\0' != *bufPtr)
	{
		/* Checks if data is a newline character. */
		if ((char) '\n' == *bufPtr)
		{
			/* Ensuring applicability to serial console.*/
			debug_putc(((uint8_t)('\r')));
			debug_putc(((uint8_t)('\n')));
		}
		else
		{
			debug_putc((uint8_t) *bufPtr);
		}
		bufPtr++;
	}
}
#ifdef DEBUG_FULL_SRAM_S2R
int32_t debug_write(const char *pcBuf, unsigned int ulLen)
{
	unsigned int uIdx;

	/* Send the characters */
	for (uIdx = 0; uIdx < ulLen; uIdx++)
	{
		/* If the character to the UART is \n, then add a \r before it so that
		 * \n is translated to \n\r in the output. */
		if (pcBuf[uIdx] == (int8_t) '\n')
		{
			debug_putc('\r');
		}

		/* Send the character to the UART output. */
		debug_putc(pcBuf[uIdx]);
	}

	/* Return the number of characters written. */
	return (uIdx);
}

void debug_printf(const char *pcString, ...)
{
	unsigned int ulIdx, ulValue, ulPos, ulCount, ulBase, ulNeg;
	char    *pcStr, pcBuf[16], cFill;
	va_list  vaArgP;

	/* Start the varargs processing. */
	va_start(vaArgP, pcString);

	/* Loop while there are more characters in the string. */
	while (*pcString)
	{
		/* Find the first non-% character, or the end of the string. */
		for (ulIdx = 0;
		     (pcString[ulIdx] != (int8_t) '%') &&
			     (pcString[ulIdx] != (int8_t) '\0');
		     ulIdx++)
		{}

		/* Write this portion of the string. */
		debug_write(pcString, ulIdx);

		/* Skip the portion of the string that was written. */
		pcString += ulIdx;

		/* See if the next character is a %. */
		if (*pcString == (int8_t) '%')
		{
			/* Skip the %. */
			pcString++;

			/* Set the digit count to zero, and the fill character to space
			 * (i.e. to the defaults). */
			ulCount = 0;
			cFill   = (uint8_t) ' ';

			/* It may be necessary to get back here to process more characters.
			 * Goto's aren't pretty, but effective.  I feel extremely dirty for
			 * using not one but two of the beasts. */
		  again:

			/* Determine how to handle the next character. */
			switch (*pcString++)
			{
				/* Handle the digit characters. */
				case (uint8_t) '0':
				case (uint8_t) '1':
				case (uint8_t) '2':
				case (uint8_t) '3':
				case (uint8_t) '4':
				case (uint8_t) '5':
				case (uint8_t) '6':
				case (uint8_t) '7':
				case (uint8_t) '8':
				case (uint8_t) '9':
				{
					/* If this is a zero, and it is the first digit, then the
					 * fill character is a zero instead of a space. */
					if ((pcString[-1] == (int8_t) '0') && (ulCount == 0))
					{
						cFill = (uint8_t) '0';
					}

					/* Update the digit count. */
					ulCount *= 10;
					ulCount += pcString[-1] - (int8_t) '0';

					/* Get the next character. */
					goto again;
				}

				/* Handle the %c command. */
				case (uint8_t) 'c':
				{
					/* Get the value from the varargs. */
					ulValue = va_arg(vaArgP, unsigned int);

					/* Print out the character. */
					debug_write((char *) &ulValue, 1);

					/* This command has been handled. */
					break;
				}

				/* Handle the %d command. */
				case (uint8_t) 'd':
				{
					/* Get the value from the varargs. */
					ulValue = va_arg(vaArgP, unsigned int);

					/* Reset the buffer position. */
					ulPos = 0;

					/* If the value is negative, make it positive and indicate
					 * that a minus sign is needed. */
					if ((int32_t) ulValue < 0)
					{
						/* Make the value positive. */
						ulValue = -(int32_t) ulValue;

						/* Indicate that the value is negative. */
						ulNeg = 1;
					}
					else
					{
						/* Indicate that the value is positive so that a minus
						 * sign isn't inserted. */
						ulNeg = 0;
					}

					/* Set the base to 10. */
					ulBase = 10;

					/* Convert the value to ASCII. */
					goto convert;
				}

				/* Handle the %s command. */
				case (uint8_t) 's':
				{
					/* Get the string pointer from the varargs. */
					pcStr = va_arg(vaArgP, char *);

					/* Determine the length of the string. */
					for (ulIdx = 0; pcStr[ulIdx] != (int8_t) '\0'; ulIdx++)
					{}

					/* Write the string. */
					debug_write(pcStr, ulIdx);

					/* Write any required padding spaces */
					if (ulCount > ulIdx)
					{
						ulCount -= ulIdx;
						while (ulCount--)
						{
							debug_write(" ", 1);
						}
					}
					/* This command has been handled. */
					break;
				}

				/* Handle the %u command. */
				case (uint8_t) 'u':
				{
					/* Get the value from the varargs. */
					ulValue = va_arg(vaArgP, unsigned int);

					/* Reset the buffer position. */
					ulPos = 0;

					/* Set the base to 10. */
					ulBase = 10;

					/* Indicate that the value is positive so that a minus sign
					 * isn't inserted. */
					ulNeg = 0;

					/* Convert the value to ASCII. */
					goto convert;
				}

				/* Handle the %x and %X commands.  Note that they are treated
				 * identically; i.e. %X will use lower case letters for a-f
				 * instead of the upper case letters is should use.  We also
				 * alias %p to %x. */
				case (uint8_t) 'x':
				case (uint8_t) 'X':
				case (uint8_t) 'p':
				{
					/* Get the value from the varargs. */
					ulValue = va_arg(vaArgP, unsigned int);

					/* Reset the buffer position. */
					ulPos = 0;

					/* Set the base to 16. */
					ulBase = 16;

					/* Indicate that the value is positive so that a minus sign
					 * isn't inserted. */
					ulNeg = 0;

					/* Determine the number of digits in the string version of
					 * the value. */
				  convert:
					for (ulIdx = 1;
					     (((ulIdx * ulBase) <= ulValue) &&
					      (((ulIdx * ulBase) / ulBase) == ulIdx));
					     ulIdx *= ulBase)
					{
						ulCount--;
					}

					/* If the value is negative, reduce the count of padding
					 * characters needed. */
					if (ulNeg)
					{
						ulCount--;
					}

					/* If the value is negative and the value is padded with
					 * zeros, then place the minus sign before the padding. */
					if (ulNeg && (cFill == (int8_t) '0'))
					{
						/* Place the minus sign in the output buffer. */
						pcBuf[ulPos++] = (uint8_t) '-';

						/* The minus sign has been placed, so turn off the
						 * negative flag. */
						ulNeg = 0;
					}

					/* Provide additional padding at the beginning of the
					 * string conversion if needed. */
					if ((ulCount > 1) && (ulCount < 16))
					{
						for (ulCount--; ulCount; ulCount--)
						{
							pcBuf[ulPos++] = cFill;
						}
					}

					/* If the value is negative, then place the minus sign
					 * before the number. */
					if (ulNeg)
					{
						/* Place the minus sign in the output buffer. */
						pcBuf[ulPos++] = (uint8_t) '-';
					}

					/* Convert the value into a string. */
					for (; ulIdx; ulIdx /= ulBase)
					{
						pcBuf[ulPos++] = g_pcHex[(ulValue / ulIdx) % ulBase];
					}

					/* Write the string. */
					debug_write(pcBuf, ulPos);

					/* This command has been handled. */
					break;
				}

				/* Handle the %% command. */
				case (uint8_t) '%':
				{
					/* Simply write a single %. */
					debug_write(pcString - 1, 1);

					/* This command has been handled. */
					break;
				}

				/* Handle all other commands. */
				default:
				{
					/* Indicate an error. */
					debug_write("ERROR", 5);

					/* This command has been handled. */
					break;
				}
			}
		}
	}

	/* End the varargs processing. */
	va_end(vaArgP);

	return;
}
#endif
#endif
