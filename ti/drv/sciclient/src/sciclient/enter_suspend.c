//#define DEBUG_SUSPEND
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include <ti/csl/arch/r5/csl_arm_r5.h>
#include <ti/drv/sciclient/src/sciclient/sram_s2r.h>

#define TCMB_USED_SIZE 0xd50
extern void HwiP_save_task(void);
static int* resumepxCurrentTCB  = (int*)0xa050ac30;
extern int* pxCurrentTCB;
extern void vPortRestoreTaskContext( void );
void CSL_armR5StartupCacheEnableAllCache( uint32_t enable );
void _freertosresetvectors (void);

/* BL31 TF-A is in the SRAM */
#define BL31_START 0x70000000

/* this address belongs to the space rserve fro the DM firmware for
 * the point of view of Linux, U-boot SPL must suse the same address
 * to restore TF-A and resume entry point address */
#define LPM_SAVE  0xa0600000

/* This is acually the while size of the SRAM */
#define BL31_SIZE    0x20000

/* Adress in BT SRA% where to load the code that will take care of the
 * DDR retention and PMIC S2R programmation*/
#define SRAM	    0x41011000

/* Adresss to point the sp register in SRAM */
#define SP_SRAM	    0x41014000
#define SP_STORE    0x41014004

unsigned char UART_buff[9];
#ifdef DEBUG_SUSPEND
#define debug_printf UART_printf
#define WKUP_UART_THR 0x40a00000
#define WKUP_UART_LSR_UART 0x40a00014

void write_WKUP_UART(char val) {
    *(unsigned int *)WKUP_UART_THR = val;
    while ((*(volatile unsigned int *)WKUP_UART_LSR_UART & 0x60) !=0x60) {}
}

void debug_ll(void) {
    unsigned int iter_chars;

    for(iter_chars = 0; iter_chars < 8; iter_chars++){
        write_WKUP_UART((int)UART_buff[iter_chars]);
    }
    write_WKUP_UART(10);
    write_WKUP_UART(13);
}
#else
void debug_printf(const char *pcString, ...) {};
void debug_ll(void) {};
#endif

#include <ti/board/board.h>
#include <ti/board/src/j7200_evm/include/board_internal.h>
I2C_Handle gPmicI2cHandle  = NULL;

static int32_t i2cInitPMIC(void)
{

    int32_t retVal = 0;
    I2C_Params i2cParams;

    /* Initialize i2c core instances */
    I2C_init();
    uint8_t i2c_instance = 0U;
    uint32_t baseAddr = CSL_WKUP_I2C0_CFG_BASE;

    I2C_HwAttrs i2cCfg;
    I2C_socGetInitCfg(i2c_instance, &i2cCfg);
    i2cCfg.baseAddr   = baseAddr;
    i2cCfg.enableIntr = 0U;
    I2C_socSetInitCfg(i2c_instance, &i2cCfg);

    /* Configured i2cParams.bitRate with standard I2C_100kHz */
    I2C_Params_init(&i2cParams);
    gPmicI2cHandle = I2C_open(i2c_instance, &i2cParams);
    if(NULL == gPmicI2cHandle)
    {
        debug_printf("ERROR: I2C_open failed!\n");
        retVal = -1;
    }
    else
        debug_printf("I2C_open successeded!\n");

    return retVal;
}

void clean_all_dcache(void)
{
	uint32_t set, way;

	for (way = 0; way < 4 ; way ++)
		for (set = 0; set < 0x200; set++)
			CSL_armR5CacheCleanDcacheSetWay(set, way);
}

void go_retention(uint32_t core_resume_addr)
{
	debug_printf("time = %s\n", __TIME__);

	*(uint32_t *)(LPM_SAVE + BL31_SIZE) = core_resume_addr;
	debug_printf("resume address stored= 0x%x\n", core_resume_addr);

	i2cInitPMIC();

	clean_all_dcache();

	/* load DDR retention code and PMIC S2R into SRAM */
	memcpy((void*)SRAM, (void*)sram_s2r_bin, sram_s2r_bin_len);

	if (*(int*)sram_s2r_bin != *(int*)SRAM)
	{
		strcpy(UART_buff, "resuming");
		debug_ll();
		return;
	}
	else {
		debug_printf("suspending\n");
		asm volatile("str sp, [%0]" : : "r" (SP_STORE));
		asm volatile("mov sp, %0" : : "r" (SP_SRAM));
		asm volatile("blx %0" : : "r" (SRAM));
	}
	/* Nerver reach this point */
}
