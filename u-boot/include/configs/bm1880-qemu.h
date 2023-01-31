/*
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __VEXPRESS_AEMV8A_H
#define __VEXPRESS_AEMV8A_H

#define CONFIG_ARMV8_SWITCH_TO_EL1

#define CONFIG_REMAKE_ELF

#define CONFIG_SUPPORT_RAW_INITRD

/* Link Definitions */
/* ATF loads u-boot here for BASE_FVP model */
#define CONFIG_SYS_TEXT_BASE		0x108000000
#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_SDRAM_BASE + 0x03f00000)

#define CONFIG_SYS_BOOTM_LEN (64 << 20)      /* Increase max gunzip size */

/* default address for bootm command without arguments */
#define CONFIG_SYS_LOAD_ADDR		0x100080000

/* Common peripherals */
#define V2M_UART0			(0x09000000)
#define V2M_UART1			(0x09040000)

/* Generic Interrupt Controller Definitions */
#define GICD_BASE			(0x08000000)
#define GICC_BASE			(0x08010000)

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (8 << 20))

/* PL011 Serial Configuration */
#define CONFIG_CONS_INDEX		0
#define CONFIG_PL01X_SERIAL
#define CONFIG_PL011_SERIAL
#define CONFIG_PL011_CLOCK		1

/*#define CONFIG_MENU_SHOW*/

/* BOOTP options */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_PXE

/* Physical Memory Map */
#define PHYS_SDRAM_1		0x100000000
#define PHYS_SDRAM_1_SIZE	0x40000000
#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM_1

#define BM_UPDATE_FW_START_ADDR             (PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)
#define BM_UPDATE_FW_SIZE		            (0x70000000)
#define BM_UPDATE_FW_FILLBUF_SIZE           (1024 * 512)

#define CONFIG_NR_DRAM_BANKS		1

/* Software root reset */
#define TOP_CTRL_REG			0x50010008
#define WATCHDOG_BASE			0x50026000

/* Enable memtest */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS	\
				"uimage_addr=0x140080000\0"

#define CONFIG_BOOTARGS		"console=ttyAMA0 earlycon "		\
				"debug user_debug=31 loglevel=10 "	\
				"crashkernel=64M"

#define CONFIG_BOOTCOMMAND	"bootm ${uimage_addr}#config@1"

/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE		512	/* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_LONGHELP
#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_MAXARGS		64	/* max command args */


#define CONFIG_ENV_ADDR			PHYS_SDRAM_1
#define CONFIG_ENV_SECT_SIZE		0x00040000
#define CONFIG_ENV_SIZE			CONFIG_ENV_SECT_SIZE
#define CONFIG_ENV_IS_NOWHERE

#endif /* __VEXPRESS_AEMV8A_H */
