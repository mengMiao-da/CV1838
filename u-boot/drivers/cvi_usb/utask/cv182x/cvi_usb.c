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

extern int acm_app(void);

static void cvi_usb_hw_init(void)
{
	uint32_t value;

	value = mmio_read_32(TOP_BASE + REG_TOP_SOFT_RST) & (~BIT_TOP_SOFT_RST_USB);
	mmio_write_32(TOP_BASE + REG_TOP_SOFT_RST, value);
	udelay(50);
	value = mmio_read_32(TOP_BASE + REG_TOP_SOFT_RST) | BIT_TOP_SOFT_RST_USB;
	mmio_write_32(TOP_BASE + REG_TOP_SOFT_RST, value);

	/* Set USB phy configuration */
	value = mmio_read_32(REG_TOP_USB_PHY_CTRL);
	mmio_write_32(REG_TOP_USB_PHY_CTRL, value | BIT_TOP_USB_PHY_CTRL_EXTVBUS
					| USB_PHY_ID_OVERRIDE_ENABLE
					| USB_PHY_ID_VALUE);

	/* Enable ECO RXF */
	mmio_write_32(REG_TOP_USB_ECO, mmio_read_32(REG_TOP_USB_ECO) | BIT_TOP_USB_ECO_RX_FLUSH);

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
	acm_app();
#ifdef DISABLE_DCACHE
	NOTICE("Enable DCACHE after leaving UTASK\n");
	dcache_enable();
#endif

	return 0;
}
