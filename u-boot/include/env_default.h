/*
 * (C) Copyright 2000-2010
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <env_callback.h>

#ifdef DEFAULT_ENV_INSTANCE_EMBEDDED
env_t environment __PPCENV__ = {
	ENV_CRC,	/* CRC Sum */
#ifdef CONFIG_SYS_REDUNDAND_ENVIRONMENT
	1,		/* Flags: valid */
#endif
	{
#elif defined(DEFAULT_ENV_INSTANCE_STATIC)
static char default_environment[] = {
#else
const uchar default_environment[] = {
#endif
#ifdef	CONFIG_ENV_CALLBACK_LIST_DEFAULT
	ENV_CALLBACK_VAR "=" CONFIG_ENV_CALLBACK_LIST_DEFAULT "\0"
#endif
#ifdef	CONFIG_ENV_FLAGS_LIST_DEFAULT
	ENV_FLAGS_VAR "=" CONFIG_ENV_FLAGS_LIST_DEFAULT "\0"
#endif
#ifdef	CONFIG_BOOTARGS
	"bootargs="	CONFIG_BOOTARGS			"\0"
#endif
#ifdef	CONFIG_BOOTCOMMAND
	"bootcmd="	CONFIG_BOOTCOMMAND		"\0"
#endif
#ifdef	CONFIG_RAMBOOTCOMMAND
	"ramboot="	CONFIG_RAMBOOTCOMMAND		"\0"
#endif
#ifdef	CONFIG_NFSBOOTCOMMAND
	"nfsboot="	CONFIG_NFSBOOTCOMMAND		"\0"
#endif
#ifdef	CONFIG_NANDITBIMAGE_SIZE
	"itbimage_size=" CONFIG_NANDITBIMAGE_SIZE	"\0"
#endif
#ifdef	CONFIG_NANDBOOTCOMMAND
	"nandboot="	CONFIG_NANDBOOTCOMMAND		"\0"
#endif
#ifdef CONFIG_SD_BOOT
	"sd_boot="	CONFIG_SDBOOTCOMMAND		"\0"
#endif
#ifdef	CONFIG_UPDATENANDCOMMAND
	"updatenand=" CONFIG_UPDATENANDCOMMAND		"\0"
#endif
#ifdef	CONFIG_NANDBOOTCOMMAND
	"nandboot="	CONFIG_NANDBOOTCOMMAND		"\0"
#endif
#ifdef	CONFIG_MMCBOOTCOMMAND
	"sdboot="	CONFIG_MMCBOOTCOMMAND		"\0"
#endif
#ifdef	CONFIG_EMMCBOOTCOMMAND
	"emmcboot="	CONFIG_EMMCBOOTCOMMAND		"\0"
#endif
#ifdef CONFIG_EMMCBKBOOTCOMMAND
	"emmcboot_backup=" CONFIG_EMMCBKBOOTCOMMAND	"\0"
#endif
#ifdef	CONFIG_NORBOOTCOMMAND
	"norboot="	CONFIG_NORBOOTCOMMAND		"\0"
#endif
#ifdef	CONFIG_BMDLCOMMAND
	"bmdl="	        CONFIG_BMDLCOMMAND		"\0"
#endif
#ifdef	CONFIG_USBBOOTCOMMAND
	"usbboot="	        CONFIG_USBBOOTCOMMAND		"\0"
#endif
#ifdef CONFIG_BOOTLOGO
	"showlogo=" SHOWLOGOCOMMAND		"\0"
#endif
#ifdef	CONFIG_BMTBCOMMAND
	"bmtb="	        CONFIG_BMTBCOMMAND		"\0"
#endif
#ifdef	CONFIG_BMRBCOMMAND
	"bmrb="	        CONFIG_BMRBCOMMAND		"\0"
#endif
#ifdef	CONFIG_BMSQCOMMAND
	"bmsq="	        CONFIG_BMSQCOMMAND		"\0"
#endif
#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
	"bootdelay="	__stringify(CONFIG_BOOTDELAY)	"\0"
#endif
#if defined(CONFIG_BAUDRATE) && (CONFIG_BAUDRATE >= 0)
	"baudrate="	__stringify(CONFIG_BAUDRATE)	"\0"
#endif
#ifdef	CONFIG_LOADS_ECHO
	"loads_echo="	__stringify(CONFIG_LOADS_ECHO)	"\0"
#endif
#ifdef	CONFIG_ETHPRIME
	"ethprime="	CONFIG_ETHPRIME			"\0"
#endif
#ifdef	CONFIG_IPADDR
	"ipaddr="	__stringify(CONFIG_IPADDR)	"\0"
#endif
#ifdef	CONFIG_SERVERIP
	"serverip="	__stringify(CONFIG_SERVERIP)	"\0"
#endif
#ifdef	CONFIG_SYS_AUTOLOAD
	"autoload="	CONFIG_SYS_AUTOLOAD		"\0"
#endif
#ifdef	CONFIG_PREBOOT
	"preboot="	CONFIG_PREBOOT			"\0"
#endif
#ifdef	CONFIG_ROOTPATH
	"rootpath="	CONFIG_ROOTPATH			"\0"
#endif
#ifdef	CONFIG_GATEWAYIP
	"gatewayip="	__stringify(CONFIG_GATEWAYIP)	"\0"
#endif
#ifdef	CONFIG_NETMASK
	"netmask="	__stringify(CONFIG_NETMASK)	"\0"
#endif
#ifdef	CONFIG_HOSTNAME
	"hostname="	__stringify(CONFIG_HOSTNAME)	"\0"
#endif
#ifdef	CONFIG_BOOTFILE
	"bootfile="	CONFIG_BOOTFILE			"\0"
#endif
#ifdef	CONFIG_LOADADDR
	"loadaddr="	__stringify(CONFIG_LOADADDR)	"\0"
#endif
#ifdef	CONFIG_CLOCKS_IN_MHZ
	"clocks_in_mhz=1\0"
#endif
#if defined(CONFIG_PCI_BOOTDELAY) && (CONFIG_PCI_BOOTDELAY > 0)
	"pcidelay="	__stringify(CONFIG_PCI_BOOTDELAY)"\0"
#endif
#ifdef	CONFIG_ENV_VARS_UBOOT_CONFIG
	"arch="		CONFIG_SYS_ARCH			"\0"
#ifdef CONFIG_SYS_CPU
	"cpu="		CONFIG_SYS_CPU			"\0"
#endif
#ifdef CONFIG_SYS_BOARD
	"board="	CONFIG_SYS_BOARD		"\0"
	"board_name="	CONFIG_SYS_BOARD		"\0"
#endif
#ifdef CONFIG_SYS_VENDOR
	"vendor="	CONFIG_SYS_VENDOR		"\0"
#endif
#ifdef CONFIG_SYS_SOC
	"soc="		CONFIG_SYS_SOC			"\0"
#endif
#endif
#ifdef	CONFIG_EXTRA_ENV_SETTINGS
	CONFIG_EXTRA_ENV_SETTINGS
#endif
	"\0"
#ifdef DEFAULT_ENV_INSTANCE_EMBEDDED
	}
#endif
};
