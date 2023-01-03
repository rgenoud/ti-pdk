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
void setup_pmic(void);
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

/* Extracted from various places in the PDK. Used for IO retention. */

#define MAIN_CTRL_BASE                                              (0x00100000U)

#define CSL_WKUP_CTRL_MMR0_CFG0_BASE                                (0x43000000U)
#define CSL_WKUP_CTRL_MMR_CFG0_MCU_GEN_WAKE_CTRL                    (0x00018310U)
#define CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL                    (0x00018300U)

#define CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START      (0x44130000U)
#define CSL_PMMCCONTROL_PMCTRL_IO                                   (0x84U)
#define CSL_PMMCCONTROL_PMCTRL_DDR                                  (0x88U)

#define CSL_NAVSS0_SPINLOCK_BASE                                    (0x30e00000UL)
#define SOC_NUM_SPINLOCKS                                           (256U)
#define MMR_LOCK0_KICK0                                             (0x01008)
#define MMR_LOCK0_KICK0_UNLOCK_VAL                                  (0x68EF3490)
#define MMR_LOCK0_KICK1_UNLOCK_VAL                                  (0xD172BC5A)
#define SOC_LOCK_MMR_UNLOCK                                         (0U)

#define IO_TIMEOUT                                                  (150)

/* Not used in SPL */
#define CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL                       (0x00018160U)
#define DMSC_CM_FW_CTRL_OUT0_SET                                    (0x44U)
#define DMSC_CM_LOCK0_KICK0                                         (0x020U)
#define DMSC_CM_LOCK0_KICK1                                         (0x024U)

/* This only gets used to access registers. The original version from the PDK
 * handled the full memory range and had redirects. */
static volatile uint32_t *mkptr(uint32_t base, uint32_t offset)
{
	return (volatile uint32_t*)(base+offset);
}

static void busy_wait_10us(void)
{
	volatile unsigned int i = 0;
	for(i = 0; i < IO_TIMEOUT; i++);
}

static void main_io_pm_seq(void)
{
	uint32_t read_data = 0;

	/* Configure MAIN_MCAN0_TX PADCONF */
	*mkptr(MAIN_CTRL_BASE, 0x1c020) = 0x20050000;

	/* Configure MAIN_MCAN1_RX PADCONF */
	*mkptr(MAIN_CTRL_BASE, 0x1c02c) = 0x20050000;

	/* Configure PMIC_WAKE */
	*mkptr(MAIN_CTRL_BASE, 0x1c124) = 0x38038000;

	/* Unlock DMSC reg */
	*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK0) = 0x8a6b7cda;
	*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK1) = 0x823caef9;

	/* Enable fw_ctrl_out[0] */
	*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_FW_CTRL_OUT0_SET) |= 0x2;
	read_data = *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL);
	*mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL) = read_data | 0x100;

	/* Enable Wakeup_enable */
	read_data =  *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR);
	*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR) = read_data | 0x10000;

	/* Enable ISOIN */
	read_data =  *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR);
	*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR) = read_data | 0x1000000;
	busy_wait_10us();

	/* Check ISOIN status. Unsure if read has a side-effect; it is present in
	 * the original code. */
	read_data = *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_DDR);
}

static void main_configure_can_uart_lock_dmsc(void)
{
	main_io_pm_seq();

	/* Load the Magic word */
	*mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL) = 0x55555554;
	*mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_CANUART_WAKE_CTRL) = 0x55555555;

	/* re-lock DMSC reg */
	*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK0) = 0x0;
	*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK1) = 0x0;
}

static void wkup_io_pm_seq(void)
{
    uint32_t read_data = 0;

    /* CONFIGURE MCU_MCAN0_TX with internal pull up resistor */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0B8) = 0x20060000;

    /* CONFIGURE MCU_MCAN1_TX with internal pull up resistor */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0D0) = 0x20060000;

    /* Configure PMIC_WAKE1 */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C190) = 0x38038000;

    // UART_printf("MCAN1_TX (0x4301C0D0) immediately after pad value is set : 0x%x\n", *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0D0));
    // UART_printf("MCAN0_TX (0x4301C0B8) immediately after pad value is set : 0x%x\n", *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0B8));

    /* Bypass IO Isolation for I2C Pins. Those pins go to a mux behind which is the PMIC. */
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C100) = 0x00840000; // WKUP_I2C0_SCL, F20
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C104) = 0x00840000; // WKUP_I2C0_SDA, H21

    /* Bypass IO Isolation for UART Pins so that we can print after entering IO Isolation */
    /* REMOVE THIS IF YOU WOULD LIKE TO WAKEUP FROM THE UART PINS */
    // *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0E8) = 0x00840000;
    // *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0EC) = 0x00840000;
    // *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0F0) = 0x00840000;
    // *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0F4) = 0x00840000;
    // *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0F8) = 0x00840000;
    // *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 0x1C0FC) = 0x00840000;

    /* Unlock DMSC reg */
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK0) = 0x8a6b7cda;
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK1) = 0x823caef9;

    /* Enable fw_ctrl_out[0] */
    read_data = *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_FW_CTRL_OUT0_SET);
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_FW_CTRL_OUT0_SET) = read_data | 0x1;

    read_data = *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL);
    *mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_DEEPSLEEP_CTRL) = read_data | 0x1;

    /* Enable Wakeup_enable */
    read_data = *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO);
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO) = read_data | 0x10000;

    /* Enable ISOIN */
    read_data = *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO);
    *mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, CSL_PMMCCONTROL_PMCTRL_IO) = read_data | 0x1000000 | (0x1 << 6);

    busy_wait_10us();
}

static void wkup_configure_can_uart_lock_dmsc(void)
{
	wkup_io_pm_seq();

	/* Load the Magic Word */
	*mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_MCU_GEN_WAKE_CTRL) = 0x55555554;
	*mkptr(CSL_WKUP_CTRL_MMR0_CFG0_BASE, CSL_WKUP_CTRL_MMR_CFG0_MCU_GEN_WAKE_CTRL) = 0x55555555;

	/* re-lock DMSC reg */
	*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK0) = 0x0;
	*mkptr(CSL_STD_FW_WKUP_DMSC0_PWRCTRL_0_DMSC_PWR_MMR_PWR_START, DMSC_CM_LOCK0_KICK1) = 0x0;
}

/* SOC_lock, SOC_unlock, Lpm_mmr_isLocked and Lpm_mmr_unlock are extracted from
 * the PDK lpm. */
static int32_t SOC_lock(uint32_t lockNum)
{
	volatile uint32_t *spinLockReg;

	if (lockNum >= SOC_NUM_SPINLOCKS)
		return -1;

	spinLockReg = mkptr(CSL_NAVSS0_SPINLOCK_BASE, 0x800);

	while (spinLockReg[lockNum] != 0x0);

	return 0;
}

static int32_t SOC_unlock(uint32_t lockNum)
{
	volatile uint32_t *spinLockReg;

	if (lockNum >= SOC_NUM_SPINLOCKS)
		return -1;

	spinLockReg = mkptr(CSL_NAVSS0_SPINLOCK_BASE, 0x800);
	spinLockReg[lockNum] = 0x0;

	return 0;
}

static int Lpm_mmr_isLocked(uintptr_t base, uint32_t partition)
{
	volatile uint32_t * lock = mkptr(base, partition * 0x4000 + MMR_LOCK0_KICK0);

	return (*lock & 0x1u) ? 0 : 1;
}

static void Lpm_mmr_unlock(uintptr_t base, uint32_t partition)
{
	volatile uint32_t * lock = mkptr(base, partition * 0x4000 + MMR_LOCK0_KICK0);

	if (!Lpm_mmr_isLocked(base, partition)) {
		return;
	} else {
		SOC_lock(SOC_LOCK_MMR_UNLOCK);
		lock[0] = MMR_LOCK0_KICK0_UNLOCK_VAL;
		lock[1] = MMR_LOCK0_KICK1_UNLOCK_VAL;
		SOC_unlock(SOC_LOCK_MMR_UNLOCK);
	}
}

void enter_retention(void)
{
	uart_puts(__func__);
	uart_puts(", time=");
	uart_puts(__TIME__);
	uart_puts("\n\r");

	/* Make sure that nothing remains in cache before going to retention */
	clean_all_dcache();

	Lpm_mmr_unlock(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 6);
	Lpm_mmr_unlock(CSL_WKUP_CTRL_MMR0_CFG0_BASE, 7);
	Lpm_mmr_unlock(MAIN_CTRL_BASE, 7);

	debug_printf("%s %s\n", __func__,  __TIME__);
	ddr_retention();
	debug_printf("DDRSS_CTL_141: 0x%08x\n", *( unsigned int *)DDRSS_CTL_141);
	debug_printf("DDR retention done!\n");

	uart_puts("=> I/O retention\n\r");

	main_configure_can_uart_lock_dmsc();
	wkup_configure_can_uart_lock_dmsc();

	debug_printf("%s %s\n", __func__,  __TIME__);

	setup_pmic();
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

/* Taken from Lpm_pmicStateChangeActiveToIORetention, with some changes to
 * FSM_I2C_TRIGGERS for DDRRET support. Explaination on this change is still
 * obscure. */
void setup_pmic(void)
{
	/* Write 0x02 to FSM_NSLEEP_TRIGGERS register
	   This should happen before clearing the interrupts */

	/* If you clear the interrupts before you write the NSLEEP bits,
	 * it will transition to S2R state.
	 * This is because as soon as you write NSLEEP2 to 0x0,
	 * the trigger is present to move to S2R state.
	 * By setting the NSLEEP bits before you clear the interrupts,
	 * you can configure both NSLEEP bits before the PMIC reacts to the change.
	 */

	uint8_t buf;

	/* Change FSM_NSLEEP_TRIGGERS: NSLEEP1=high, NSLEEP2=high */
	write_pmicA(0x86, 0x03);
	debug_printf("%s %d: Write FSM_NSLEEP_TRIGGERS = 0x%x\n", __FUNCTION__, __LINE__, 0x03);
	read_pmicA(0x86);

	/* Clear INT_STARTUP: clear ENABLE pin interrupt */
	write_pmicA(0x65, 0x02);
	debug_printf("%s %d: Write INT_STARTUP = 0x%x\n", __FUNCTION__, __LINE__, 0x02);
	read_pmicA(0x65);

	/* Configure GPIO4_CONF: input, no pull, signal LP_WKUP1 */
	write_pmicA(0x34, 0xc0);
	debug_printf("%s %d: Write GPIO4_CONF = 0x%x\n", __FUNCTION__, __LINE__, 0xc0);
	read_pmicA(0x34);

	/* Configure INT_GPIO1_8 (enable GPIO4 interrupt): clear GPIO4_INT */
	write_pmicA(0x64, 0x08);
	debug_printf("%s %d: Write INT_GPIO1_8 = 0x%x\n", __FUNCTION__, __LINE__, 0x08);
	read_pmicA(0x64);

	/* Configure MASK_GPIO1_8_FALL (configure GPIO4 falling edge interrupt): enable INT on GPIO4 */
	write_pmicA(0x4F, 0xF7);
	debug_printf("%s %d: Write MASK_GPIO1_8_FALL = 0x%x\n", __FUNCTION__, __LINE__, 0xF7);
	read_pmicA(0x4F);

	// GPIO_OUT_1
	buf = read_pmicB(0x3D) | DDR_RET_VAL; // 1<<1, GPIO2_OUT on
	write_pmicB(0x3D, buf);
	write_pmicB(0x3D, buf | DDR_RET_CLK);  // 1<<2, GPIO3_OUT on
	write_pmicB(0x3D, buf & ~DDR_RET_CLK); // 1<<2, GPIO3_OUT off
	write_pmicB(0x3D, buf | DDR_RET_CLK);  // 1<<2, GPIO3_OUT on

	/* Change FSM_I2C_TRIGGERS: trigger TRIGGER_I2C_6 */
	write_pmicA(0x85, 0x40 | 0x80); // TRIGGER_I2C_6
	debug_printf("%s %d: Write FSM_I2C_TRIGGERS = 0x%x\n", __FUNCTION__, __LINE__, 0x40);
	read_pmicA(0x85);

	/* Change FSM_I2C_TRIGGERS - PMICB: trigger TRIGGER_I2C_6 */
	write_pmicB(0x85, 0x40 | 0x80);
	debug_printf("%s %d: Write FSM_NSLEEP_TRIGGERS = 0x%x\n", __FUNCTION__, __LINE__, 0x40);
	read_pmicA(0x85);

	/* Change FSM_NSLEEP_TRIGGERS: NSLEEP1=low, NSLEEP2=low */
	write_pmicA(0x86, 0x00);
	debug_printf("%s %d: Write FSM_NSLEEP_TRIGGERS = 0x%x\n", __FUNCTION__, __LINE__, 0x00);
	read_pmicA(0x86);
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
