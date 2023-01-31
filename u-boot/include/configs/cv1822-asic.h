/*
 * Configuration for Versatile Express. Parts were derived from other ARM
 *   configurations.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CV1822_ASIC_H
#define __CV1822_ASIC_H
/* partition definitions header which is created by mkcvipart.py */
/* please do not modify header manually */
#include "cvipart.h"
#include "cvi_panels/cvi_panel_diffs.h"

#define CONFIG_ARMV8_SWITCH_TO_EL1

#define CONFIG_REMAKE_ELF

#define CONFIG_SUPPORT_RAW_INITRD

/* Link Definitions */
/* ATF loads u-boot here for BASE_FVP model */
#define CONFIG_SYS_TEXT_BASE		0x83080000
#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_SDRAM_BASE + 0x03f00000)

#define CONFIG_SYS_BOOTM_LEN (64 << 20)      /* Increase max gunzip size */

/* default address for bootm command without arguments */
#define CONFIG_SYS_LOAD_ADDR		0x80080000

/* Generic Interrupt Controller Definitions */
#define GICD_BASE			(0x01F01000)
#define GICC_BASE			(0x01F02000)

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (8 << 20))

/* For network descriptor, should be enabled when mmu is okay */
#define CONFIG_SYS_NONCACHED_MEMORY	BIT(20)	/* 1 MiB */

/* 16550 Serial Configuration */
#define CONFIG_CONS_INDEX		1
#define CONFIG_SYS_NS16550_COM1		0x04140000
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_MEM32
#define CONFIG_SYS_NS16550_CLK		25000000
/* include/generated/autoconf.h would define CONFIG_BAUDRATE from drivers/serial/Kconfig (default 115200) */

/*#define CONFIG_MENU_SHOW*/

/* BOOTP options */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_PXE

/* Physical Memory Map */
#define PHYS_SDRAM_1		0x80000000
#define PHYS_SDRAM_1_SIZE	CONFIG_SYS_BOOTMAPSZ
#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM_1

#define BM_UPDATE_FW_START_ADDR             (PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)
#define BM_UPDATE_FW_SIZE		            (0x70000000)
#define BM_UPDATE_FW_FILLBUF_SIZE           (1024 * 512)

#define CONFIG_NR_DRAM_BANKS		1

/* Enable memtest */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_1 + PHYS_SDRAM_1_SIZE)

/* Enable watchdog */
#define CONFIG_HW_WATCHDOG
#define CONFIG_DESIGNWARE_WATCHDOG
#define CONFIG_WATCHDOG_TIMEOUT_MSECS 42000 // options: 1s, 2s, 5s, 10s, 21, 42s, 85s

/* Initial environment variables */

#ifndef MTDPARTS_DEFAULT
#define MTDPARTS_DEFAULT ""
#endif

#ifdef RELEASE
/* #define OTHERBOOTARGS "othbootargs=release" */
/* #define CONSOLEDEV "none\0" */
/* #define BOOTARGS_BASE "console=none" */
#define OTHERBOOTARGS   "othbootargs=earlycon release loglevel=1\0"
#define CONSOLEDEV "ttyS0\0"
#else
#define OTHERBOOTARGS   "othbootargs=earlycon loglevel=4\0"
#define CONSOLEDEV "ttyS0\0"
#endif

/* Download related definitions */
#define SD_UPDATE_SRAM_ADDR  0x0e000004
#define USB_UPDATE_SRAM_ADDR 0x0e000004
#define UPGRADE_SRAM_ADDR    0x0e000030
#define ETH_UPGRADE_IP_ADDR  0x0e000034
#define IMG_ADDR 0x80090000
#define HEADER_ADDR 0x80080000
#define USB_UPDATE_MAGIC 0x4D474E31
/*----------------------------------------------------------------------
 * SPI Flash Configuration
 * ---------------------------------------------------------------------
 */

#ifdef CONFIG_SPI_FLASH
	#define CONFIG_CMD_SF		 /* sf read/sf write/sf erase */
	#define CONFIG_SPI_FLASH_CVSFC

	#define CONFIG_CMD_MTDPARTS
	#define CONFIG_MTD_DEVICE
	#define CONFIG_MTD_PARTITIONS
	#define CONFIG_FLASH_CFI_MTD
	#define CONFIG_SYS_MAX_FLASH_BANKS 1

	#define MTDIDS_DEFAULT                  "nor1=flash-0"

	#define CONFIG_SPI_FLASH_MTD
#endif /* CONFIG_SPI_FLASH */

/*-----------------------------------------------------------------------
 * SPI NAND Flash Configuration
 *----------------------------------------------------------------------
 */

#ifdef CONFIG_NAND_SUPPORT
	/*#define CONFIG_ENV_IS_IN_NAND*/ /* env in nand flash */
	#define CONFIG_CMD_NAND
	#define CONFIG_SYS_MAX_NAND_DEVICE	 1

	#define CONFIG_NAND_FLASH_CVSNFC
	#define CONFIG_SYS_MAX_NAND_CHIPS 1
	/*#define CONFIG_SYS_NAND_SELF_INIT*/

	#define CONFIG_CMD_MTDPARTS
	#define CONFIG_MTD_DEVICE
	#define CONFIG_MTD_PARTITIONS
	#define MTDIDS_DEFAULT "nand0=cvsnfc"
	/* For CMD_UBI && CMD_UBIFS */
	#define CONFIG_RBTREE
	#define CONFIG_LZO
    #define CONFIG_CMD_UBI
    #define CONFIG_CMD_UBIFS
    #define CONFIG_MTD_UBI_WL_THRESHOLD 4096
    #define CONFIG_MTD_UBI_BEB_LIMIT 20
#endif /* CONFIG_NAND_SUPPORT */

#ifdef CONFIG_NAND_FLASH_CVSNFC
	#define SPI_NAND_TX_DATA_BASE 0x4060060
	#define SPI_NAND_RX_DATA_BASE 0x4060064

	#define SPI_NAND_REG_BASE 0x4060000
	#define CONFIG_SYS_NAND_MAX_CHIPS		1
	#define CONFIG_SYS_NAND_BASE			SPI_NAND_REG_BASE
	#define CONFIG_CVSNFC_MAX_CHIP			CONFIG_SYS_MAX_NAND_DEVICE
	#define CONFIG_CVSNFC_REG_BASE_ADDRESS		SPI_NAND_REG_BASE
	#define CONFIG_CVSNFC_BUFFER_BASE_ADDRESS	SPI_NAND_MEM_BASE
	#define CONFIG_CVSNFC_HARDWARE_PAGESIZE_ECC
	#define CONFIG_SYS_NAND_BASE_LIST		{CONFIG_SYS_NAND_BASE}

#endif /* CONFIG_NAND_SUPPORT */

/* BOOTLOGO */
#ifdef CONFIG_BOOTLOGO
#define SHOWLOGOCMD "run showlogo;"
#define LOGO_RESERVED_ADDR "0x81800000"
#define LOGO_READ_ADDR "0x84080000"

#ifdef CONFIG_NAND_SUPPORT
#define LOAD_LOGO "nand read " LOGO_READ_ADDR " MISC;"
#elif defined(CONFIG_SPI_FLASH)
#define LOAD_LOGO ""
#else
#define LOAD_LOGO "mmc dev 0;mmc read " LOGO_READ_ADDR " ${MISC_PART_OFFSET} ${MISC_PART_SIZE};"
#endif
#define LOGOSIZE "0x80000"
#define SHOWLOGOCOMMAND LOAD_LOGO CVI_JPEG START_VO START_VL SET_VO_BG

#else
#define SHOWLOGOCMD
#endif

/* Config Boot From RAM or NFS */
#define SET_BOOTARGS "setenv bootargs mem=${mem} ${root} ${mtdparts} " \
					"console=$consoledev,$baudrate $othbootargs;"
#ifdef CONFIG_NAND_SUPPORT
#define CONFIG_BOOTCOMMAND	SHOWLOGOCMD "cvi_update || run nandboot"
#ifdef CONFIG_SKIP_RAMDISK
	#define ROOTARGS "ubi.mtd=ROOTFS ubi.block=0,0 root=/dev/ubiblock0_0 rootfstype=squashfs"
#else
	#define ROOTARGS "ubi.mtd=ROOTFS ubi.block=0,0"
#endif
#elif defined(CONFIG_SPI_FLASH)
	#define BOOTARGS "console=ttyS0,115200 earlycon loglevel=8\0"
	#define CONFIG_BOOTCOMMAND	SHOWLOGOCMD "cvi_update || run norboot"
	#ifdef CONFIG_SKIP_RAMDISK
		#define ROOTARGS "rootfstype=squashfs root=" MTD_PART_ROOTFS_DEV
	#else
		#define ROOTARGS ""
	#endif /* CONFIG_SKIP_RAMDISK */
#elif defined(CONFIG_SD_BOOT)
	#define CONFIG_BOOTCOMMAND	SHOWLOGOCMD "run sd_boot"
#else
#define CONFIG_BOOTCOMMAND	SHOWLOGOCMD "cvi_update || run emmcboot"
#endif

/* Config FDT_NO */
#ifndef USE_HOSTCC
#define FDT_NO __stringify(CVICHIP) "_" __stringify(CVIBOARD)
#else
#define FDT_NO ""
#endif

/* UBOOT_VBOOT commands */
#ifdef UBOOT_VBOOT
	#define UBOOT_VBOOT_BOOTM_COMMAND \
				"aes_itb dec_fdt_key 0 ${uimage_addr} ${uimage_addr}; " \
				"if test $? -ne 0; then " \
				"  echo ITB decryption failed; " \
				"else; " \
				"  bootm ${uimage_addr}#config@" FDT_NO ";" \
				"fi;"
#else
	#define UBOOT_VBOOT_BOOTM_COMMAND "bootm ${uimage_addr}#config@" FDT_NO ";"
#endif

#ifdef UBOOT_VBOOT
#define CONFIG_NFSBOOTCOMMAND	""
#else
#define CONFIG_NFSBOOTCOMMAND	"setenv bootargs root=/dev/nfs init=/init rw "			\
					"nfsroot=$serverip:$rootpath,v3,tcp "				\
					"ip=$ipaddr:$serverip:$gatewayip:$netmask:$hostname:$netdev:off " \
					"console=$consoledev,$baudrate $othbootargs;"			\
				"setenv kernel_name Image;"			\
				"setenv kernel_addr 0x100080000;"		\
				"setenv fdt_name cv1835_asic_evb.dtb;"	\
				"setenv fdt_addr 0x102000000;"			\
				"tftp ${kernel_addr} ${kernel_name}; "		\
				"tftp ${fdt_addr} ${fdt_name}; "		\
				"fdt addr ${fdt_addr}; fdt resize; "		\
				"booti ${kernel_addr} - ${fdt_addr}"
#endif

/* 0x4D474E32 For SD Download magic number*/
/* Check itb header for ramboot_mini.itb, magic number 0xedfe0dd0 */
#define CONFIG_RAMBOOTCOMMAND	"setenv bootargs console=$consoledev,$baudrate $othbootargs;" \
				"echo run Ramboot...;" \
				"if test $? -eq 0; then " \
				UBOOT_VBOOT_BOOTM_COMMAND \
				"fi;"

#define CONFIG_MMCBOOTCOMMAND	\
				"setenv bootargs console=$consoledev,$baudrate $othbootargs;"	\
				"mmc dev 1;"		\
				"if test $? -eq 0; then " \
				"fatload mmc 1:1 ${uimage_addr} sdboot.itb;"		\
				"if test $? -eq 0; then "\
				UBOOT_VBOOT_BOOTM_COMMAND \
				"fi;"	\
				"fi;"

#define CONFIG_USBBOOTCOMMAND	\
				"setenv bootargs console=$consoledev,$baudrate $othbootargs;"	\
				"mw.l  0xe00fc04 0x4D474E31;" \
				"cmp.l 0xe00fc08 0xe00fc04 1;" \
				"if test $? -eq 0; then " \
				"echo usbboot...;" \
				"mw.l 0xe00fc00 0x0;" \
				"mw.l 0xe00fc04 0x0;" \
				"mw.l 0xe00fc08 0x0;" \
				"cvi_utask;" \
				UBOOT_VBOOT_BOOTM_COMMAND \
				"fi;"

#ifdef CONFIG_NAND_SUPPORT
/* For spi nand boot, need to reset DMA and its setting before exiting uboot */
/* 0x4330058 : DMA reset */
/* 0x3000154 : restore DMA remap to 0 */

#define NANDBOOT_V2
#define CONFIG_NANDBOOTCOMMAND \
				SET_BOOTARGS \
				"nand read ${uimage_addr} BOOT;" \
				"mw.l 4330058 1 1; md.l 4330058 1; mw.l 3000154 0 1;" \
				UBOOT_VBOOT_BOOTM_COMMAND
#elif defined(CONFIG_SPI_FLASH)
#define CONFIG_NORBOOTCOMMAND \
				SET_BOOTARGS \
				"sf probe;sf read ${uimage_addr} ${BOOT_PART_OFFSET} ${BOOT_PART_SIZE};" \
				UBOOT_VBOOT_BOOTM_COMMAND
#elif defined(CONFIG_SD_BOOT)
#define CONFIG_SDBOOTCOMMAND \
				SET_BOOTARGS \
				"fatload mmc 1:1 ${uimage_addr} boot.sd;" \
				UBOOT_VBOOT_BOOTM_COMMAND
#else
#define CONFIG_EMMCBOOTCOMMAND \
				SET_BOOTARGS \
				"mmc dev 0 ;"		\
				"mmc read ${uimage_addr} ${BOOT_PART_OFFSET} ${BOOT_PART_SIZE} ;"		\
				UBOOT_VBOOT_BOOTM_COMMAND
#endif
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
#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_MAXARGS		64	/* max command args */

#define CONFIG_ENV_ADDR			PHYS_SDRAM_1
#define CONFIG_ENV_SECT_SIZE		0x00040000
#define CONFIG_FAT_WRITE
#define CONFIG_ENV_OVERWRITE

#ifndef CONFIG_NAND_SUPPORT
/* #define CONFIG_MMC_HS200_SUPPORT */
/* #define CONFIG_MMC_SUPPORTS_TUNING */
#endif
/* #define CONFIG_USB_DWC2 */
/* #define CONFIG_USB_DWC2_REG_ADDR	0x04340000 */
/* Enable below CONFIG for fastboot */

#define CONFIG_CMD_FASTBOOT
#define CONFIG_FASTBOOT
#define CONFIG_FASTBOOT_FLASH

/* To use usb fastboot, you need to enable below Kconfig
 * CONFIG_USB, CONFIG_USB_GADGET and CONFIG_USB_GADGET_DWC2_OTG
 */

#ifdef CONFIG_USB_GADGET
#define CONFIG_USB_FUNCTION_FASTBOOT
#define CONFIG_USB_GADGET_DOWNLOAD
#define CONFIG_G_DNL_MANUFACTURER "Cvitek"
#define CONFIG_G_DNL_VENDOR_NUM   0x18d1
#define CONFIG_G_DNL_PRODUCT_NUM 0x4ee0
#endif

#define CONFIG_UDP_FUNCTION_FASTBOOT
#define CONFIG_FASTBOOT_FLASH_MMC_DEV 0
#define CONFIG_FASTBOOT_BUF_ADDR 0x98000000
#define CONFIG_FASTBOOT_BUF_SIZE 0x8000000

#ifndef MTDIDS_DEFAULT
#define MTDIDS_DEFAULT
#endif
#ifndef ROOTARGS
#define ROOTARGS
#endif

#define CONFIG_EXTRA_ENV_SETTINGS	\
	"netdev=eth0\0"		\
	"consoledev=" CONSOLEDEV  \
	"baudrate=115200\0" \
	"mtdparts=" MTDPARTS_DEFAULT "\0" \
	"mtdids=" MTDIDS_DEFAULT "\0" \
	"nor1=flash-0\0"\
	"partition=nor0,0\0" \
	"uimage_addr=0x81200000\0" \
	"mem=" __stringify(CONFIG_SYS_BOOTMAPSZ) "\0" \
	"root=" ROOTARGS "\0" \
	OTHERBOOTARGS \
	PARTS_ENV
#endif /* __CV1822_ASIC_H */
