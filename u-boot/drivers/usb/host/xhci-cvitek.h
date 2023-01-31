#ifndef __REG_USBDRD_ADDR_MAP_H__
#define __REG_USBDRD_ADDR_MAP_H__

#include "xhci-plat-macro.h"
#include <common.h>

#if defined(CONFIG_TARGET_CVITEK_CV1835)
#include <../../../board/cvitek/cv1835/cv1835_reg.h>
#elif defined(CONFIG_TARGET_CVITEK_CV1822)
#include <../../../board/cvitek/cv1822/cv1822_reg.h>
#else
#error "use bm_utask at wrong platform"
#endif

#define OTG_HW_VERSION		0x100

#define DAMR_REG_USB_REMAP_ADDR_39_32_OFFSET	16
#define DAMR_REG_USB_REMAP_ADDR_39_32_MSK	(0xff)

#define UCR_MODE_STRAP_OFFSET	0
#define UCR_MODE_STRAP_NON		0x0
#define UCR_MODE_STRAP_HOST		0x2
#define UCR_MODE_STRAP_DEVICE	0x4
#define UCR_MODE_STRAP_MSK		(0x7)
#define UCR_PORT_OVER_CURRENT_ACTIVE_OFFSET		10
#define UCR_PORT_OVER_CURRENT_ACTIVE_MSK		1

#define UPCR_EXTERNAL_VBUS_VALID_OFFSET		0

enum cvi_role {
	CVI_ROLE_HOST = 0,
	CVI_ROLE_GADGET,
	CVI_ROLE_OTG,
	CVI_ROLE_END,
};

struct usbdrd_register_block_type {
	volatile uint32_t OTGCMD;                       /*        0x0 - 0x4        */
	volatile uint32_t OTGSTS;                       /*        0x4 - 0x8        */
	volatile uint32_t OTGSTATE;                     /*        0x8 - 0xc        */
	volatile uint32_t OTGREFCLK;                    /*        0xc - 0x10       */
	volatile uint32_t OTGIEN;                       /*       0x10 - 0x14       */
	volatile uint32_t OTGIVECT;                     /*       0x14 - 0x18       */
	volatile char pad__0[0x8];                      /*       0x18 - 0x20       */
	volatile uint32_t PAD2_18;                     /*       0x20 - 0x24       */
	volatile uint32_t OTGTMR;                       /*       0x24 - 0x28       */
	volatile char pad__1[0x8];                      /*       0x28 - 0x30       */
	volatile uint32_t OTGVERSION;                   /*       0x30 - 0x34       */
	volatile uint32_t OTGCAPABILITY;                /*       0x34 - 0x38       */
	volatile char pad__2[0x8];                      /*       0x38 - 0x40       */
	volatile uint32_t OTGSIMULATE;                  /*       0x40 - 0x44       */
	volatile char pad__3[0xc];                      /*       0x44 - 0x50       */
	volatile uint32_t PAD2_26;                    /*       0x50 - 0x54       */
	volatile uint32_t PAD2_27;                /*       0x54 - 0x58       */
	volatile uint32_t OTGCTRL1;                     /*       0x58 - 0x5c       */
	volatile uint32_t PAD2_29;                     /*       0x5c - 0x60       */
};

struct USBDRD_addr_map {
	struct usbdrd_register_block_type usbdrd_register_block;
	/*        0x0 - 0x60       */
};

struct cvi_xhci {
	struct usbdrd_register_block_type *regs;
	struct xhci_hccr *hcd;
	u32 current_mode;
	u16 otg_version;
	u16 ss_disable;		/* Disable super speed. */
	u32 ext_hub;		/* On board hub exists. */
};

#endif /* __REG_USBDRD_ADDR_MAP_H__ */
