/**********************************************************************
 * main.c
 *
 * USB Core Driver
 * main component function
 ***********************************************************************/
#include "include/debug.h"
#include "include/cvi_usb.h"
#include "include/platform_def.h"
#include <common.h>
#include <asm/arch-armv8/mmio.h>

extern int AcmApp(void);

static void cvi_usb_hw_init(void)
{
	uint32_t value;

#if defined(CONFIG_TARGET_CVITEK_CV1835_FPGA)
	mmio_write_32(USB_BASE, (SS_PERIPH_DISABLED_SET | HOST_BUS_DROP | DEV_BUS_REQ));
	value = mmio_read_32(REG_TOP_USB_PHY_CTRL) | BIT_TOP_USB_PHY_CTRL_EXTVBUS;
	mmio_write_32(REG_TOP_USB_PHY_CTRL, value);
#elif defined(CONFIG_TARGET_CVITEK_CV1822_FPGA)
	mmio_write_32(USB_BASE, (SS_PERIPH_DISABLED_SET | HOST_BUS_DROP | DEV_BUS_REQ));
	value = mmio_read_32(REG_TOP_USB_PHY_CTRL) | BIT_TOP_USB_PHY_CTRL_EXTVBUS;
	mmio_write_32(REG_TOP_USB_PHY_CTRL, value);
#else

	value = mmio_read_32(TOP_BASE + REG_TOP_SOFT_RST) & (~BIT_TOP_SOFT_RST_USB);
	mmio_write_32(TOP_BASE + REG_TOP_SOFT_RST, value);
	udelay(50);
	value = mmio_read_32(TOP_BASE + REG_TOP_SOFT_RST) | BIT_TOP_SOFT_RST_USB;
	mmio_write_32(TOP_BASE + REG_TOP_SOFT_RST, value);
#endif
	NOTICE("cvi_usb_hw_init done\n");
}

/* program starts here */
int cvi_usb_polling(void)
{
	cvi_usb_hw_init();
#ifdef DISABLE_DCACHE
	NOTICE("Disable DCACHE before entering UTASK\n");
	dcache_disable();
#endif
	AcmApp();
#ifdef DISABLE_DCACHE
	NOTICE("Enable DCACHE after leaving UTASK\n");
	dcache_enable();
#endif

	return 0;
}
