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
#define CONFIG_SYS_NS16550_CLK		500000000
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
#define PHYS_SDRAM_1_SIZE	0x00D800000
#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM_1

#define BM_UPDATE_FW_START_ADDR             (PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)
#define BM_UPDATE_FW_SIZE		            (0x70000000)
#define BM_UPDATE_FW_FILLBUF_SIZE           (1024 * 512)

#define CONFIG_NR_DRAM_BANKS		1

/* Enable memtest */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)

#define MTDPARTS_DEFAULT     \
				"mtdparts=hpnfc:"    \
				"8m(fip),"         \
				"8m(config),"      \
				"48m(itbImage0),"   \
				"48m(itbImage1)"

/* Initial environment variables */
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"netdev=eth0\0"		\
	"consoledev=ttyS0\0"	\
	"baudrate=115200\0"	\
	"itbimage_offset0=1000000\0"	\
	"itbimage_offset1=4000000\0"	\
	"uimage_addr=10D800000\0"	\
	"othbootargs=earlycon debug user_debug=31 loglevel=10\0 " \
	"checkupdate=fatload mmc 1:1 ${uimage_addr} update;\0 " \
	"loaditb=fatload mmc 1:1 ${uimage_addr} ramboot_mini.itb;\0 " \
	"updatenand= " \
	"if run loaditb; then " \
		"nand erase.part itbImage0; " \
		"nand erase.part itbImage1; " \
		"nand write ${uimage_addr} ${itbimage_offset0} ${itbimage_size}; " \
		"nand write ${uimage_addr} ${itbimage_offset1} ${itbimage_size};  " \
		"fi; \0 " \
	"checkandupdatenand= " \
		"echo start_checkandupdatenand;" \
		"if run checkupdate ; then " \
		"mw.l 0x50027400 30000000 ; mw.l 0x50027404 30000000 ; sleep 1 ; mw.l 0x50027400 0 ; " \
		"run updatenand ; " \
		"while true; do; mw.l 0x50027400 30000000; sleep 1; mw.l 0x50027400 0; sleep 1; done;" \
		"fi; \0" \
	"nandboot0= " \
		"run checkandupdatenand; " \
		"setenv bootargs console=${consoledev},${baudrate} ${othbootargs}, " MTDPARTS_DEFAULT ";" \
		"nand read ${uimage_addr} ${itbimage_offset0} ${itbimage_size}; " \
		"bootm ${uimage_addr}#config@1; \0 " \
	"nandboot1= " \
		"nand read ${uimage_addr} ${itbimage_offset1} ${itbimage_size}; " \
		"bootm ${uimage_addr}#config@1; \0 "

#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OVERWRITE
#define CONFIG_ENV_OFFSET 0x7000000
#define CONFIG_ENV_SIZE   0x100000

/* The size of itb image to be written
 * User can use setenv and saveenv to change this value
 * Default size is 32MB
 */
#define CONFIG_NANDITBIMAGE_SIZE "2000000"

#define CONFIG_SYS_NAND_BASE		0
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_MAX_NAND_CHIPS	1
#define CONFIG_SYS_NAND_SELF_INIT
#define CONFIG_SYS_NAND_ONFI_DETECTION

#define CONFIG_MTD_NAND_CDN_HPNFC

#define CONFIG_CMD_NAND
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define MTDIDS_DEFAULT       "nand0=hpnfc"

/* Config Boot From RAM or NFS */
#define CONFIG_BOOTCOMMAND	"run sdboot || run nandboot0 || run nandboot1"

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
				"bootm ${uimage_addr}#config@1"

#define CONFIG_MMCBOOTCOMMAND	\
				"setenv bootargs console=$consoledev,$baudrate $othbootargs;"	\
				"fatload mmc 1:1 ${uimage_addr} sdboot.itb;"		\
				"if test $? -eq 0; then "\
				"bootm ${uimage_addr}#config@1;"	\
				"fi;"

#define CONFIG_EMMCBOOTCOMMAND  "setenv bootargs console=$consoledev,$baudrate $othbootargs;"	\
				"mmc dev 0 ;"		\
				"mmc read ${uimage_addr} 1 0x77FF ;"		\
				"bootm ${uimage_addr}#config@1"

#define CONFIG_IPADDR			192.168.0.3
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_GATEWAYIP		192.168.0.11
#define CONFIG_SERVERIP			192.168.56.101
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

#define CONFIG_CMD_MISC

#endif /* __VEXPRESS_AEMV8A_H */
