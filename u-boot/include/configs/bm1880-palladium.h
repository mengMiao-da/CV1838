/*
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __VEXPRESS_AEMV8A_H
#define __VEXPRESS_AEMV8A_H

/*#define CONFIG_ARMV8_SWITCH_TO_EL1*/

#define CONFIG_REMAKE_ELF

#define CONFIG_SUPPORT_RAW_INITRD

/* Link Definitions */
/* ATF loads u-boot here for BASE_FVP model */
#define CONFIG_SYS_TEXT_BASE		0x108000000
#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_SDRAM_BASE + 0x03f00000)

#define CONFIG_SYS_BOOTM_LEN (64 << 20)      /* Increase max gunzip size */

/* default address for bootm command without arguments */
#define CONFIG_SYS_LOAD_ADDR		0x100080000

/* Generic Interrupt Controller Definitions */
#define GICD_BASE			(0x50001000)
#define GICC_BASE			(0x50002000)

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (8 << 20))

/* For network descriptor, should be enabled when mmu is okay */
#define CONFIG_SYS_NONCACHED_MEMORY	(1 << 20)	/* 1 MiB */

/* 16550 Serial Configuration */
#define CONFIG_CONS_INDEX		1
#define CONFIG_SYS_NS16550_COM1		0x58018000
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_MEM32
#define CONFIG_SYS_NS16550_CLK		153600 //25000000
/* include/generated/autoconf.h would define CONFIG_BAUDRATE from drivers/serial/Kconfig (default 115200) */

/*#define CONFIG_MENU_SHOW*/

/* BOOTP options */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_PXE

/* Physical Memory Map */
#define PHYS_SDRAM_1		0x100000000
#define PHYS_SDRAM_1_SIZE	0x10000000
#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM_1

#define BM_UPDATE_FW_START_ADDR             (PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)
#define BM_UPDATE_FW_SIZE		            (0x70000000)
#define BM_UPDATE_FW_FILLBUF_SIZE           (1024 * 512)

#define CONFIG_NR_DRAM_BANKS		1

/* Enable memtest */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS	\
				"netdev=eth0\0"		\
				"consoledev=ttyS0\0"	\
				"baudrate=9600\0"	\
				"othbootargs=earlycon debug user_debug=31 loglevel=10 crashkernel=64M"

/* Config Boot From RAM or NFS */
#define CONFIG_BOOTCOMMAND	CONFIG_RAMBOOTCOMMAND

#define CONFIG_NFSBOOTCOMMAND	"setenv bootargs root=/dev/nfs init=/init rw "  			\
					"nfsroot=$serverip:$rootpath,v3,tcp "				\
					"ip=$ipaddr:$serverip:$gatewayip:$netmask:$hostname:$netdev:off " \
					"console=$consoledev,$baudrate $othbootargs;"			\
				"setenv kernel_name Image;"			\
				"setenv kernel_addr 0x100080000;"		\
				"setenv fdt_name bm1880_palladium.dtb;" 	\
				"setenv fdt_addr 0x102000000;"			\
				"tftp ${kernel_addr} ${kernel_name}; "		\
				"tftp ${fdt_addr} ${fdt_name}; "		\
				"fdt addr ${fdt_addr}; fdt resize; "		\
				"booti ${kernel_addr} - ${fdt_addr}"

#define CONFIG_RAMBOOTCOMMAND	"setenv bootargs console=$consoledev,$baudrate $othbootargs;"	\
				"setenv uimage_addr 0x110080000;"				\
				"bootm ${uimage_addr}#config@1"

#define CONFIG_MMCBOOTCOMMAND	"setenv bootargs console=$consoledev,$baudrate $othbootargs;"	\
				"setenv uimage_addr 0x110080000;"				\
				"fatload mmc 1:1 ${uimage_addr} ramboot_mini.itb;"		\
				"bootm ${uimage_addr}#config@1"

#define CONFIG_EMMCBOOTCOMMAND  "setenv bootargs console=$consoledev,$baudrate $othbootargs;"	\
				"setenv uimage_addr 0x110080000;"				\
				"mmc dev 0 ;"		\
				"mmc read ${uimage_addr} 1 0x77FF ;"		\
				"bootm ${uimage_addr}#config@1"

#define CONFIG_IPADDR			192.168.0.3
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_GATEWAYIP		192.168.0.11
#define CONFIG_SERVERIP			192.168.0.11
#define CONFIG_HOSTNAME			unknown
#define CONFIG_ROOTPATH			"/home/share/nfsroot"

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
#define CONFIG_FAT_WRITE

#endif /* __VEXPRESS_AEMV8A_H */
