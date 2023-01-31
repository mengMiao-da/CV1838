/*
 * Copyright (C) 2013 Altera Corporation <www.altera.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <watchdog.h>
#include <asm/io.h>
#include <asm/utils.h>
#include <cvitek/cv183x_reg.h>

#define DW_WDT_CR	0x00
#define DW_WDT_TORR	0x04
#define DW_WDT_CRR	0x0C

#define DW_WDT_CR_EN_OFFSET	0x00
#define DW_WDT_CR_RMOD_OFFSET	0x01
#define DW_WDT_CR_RMOD_VAL	0x00
#define DW_WDT_CRR_RESTART_VAL	0x76

/*
 * Set the watchdog time interval.
 * Counter is 32 bit.
 */
static int designware_wdt_settimeout(unsigned int timeout)
{
	signed int i;

	/* calculate the timeout range value */
	i = (log_2_n_round_up(timeout * CONFIG_DW_WDT_CLOCK_KHZ)) - 16;
	if (i > 15)
		i = 15;
	if (i < 0)
		i = 0;

	writel((i | (i << 4)), (CONFIG_DW_WDT_BASE + DW_WDT_TORR));
	return 0;
}

static void designware_wdt_enable(void)
{
	writel(((DW_WDT_CR_RMOD_VAL << DW_WDT_CR_RMOD_OFFSET) |
	      (0x1 << DW_WDT_CR_EN_OFFSET)),
	      (CONFIG_DW_WDT_BASE + DW_WDT_CR));
}

static void designware_wdt_disable(void)
{
	printf("wdt_disable\n");

	writel(0xfffeffff, CV183X_SOFT_RST_REG1);
	writel(0xffffffff, CV183X_SOFT_RST_REG1);
}

static unsigned int designware_wdt_is_enabled(void)
{
	unsigned long val;

	val = readl((CONFIG_DW_WDT_BASE + DW_WDT_CR));
	return val & 0x1;
}

static void cv183x_wdt_init(void)
{
	unsigned long val;

	val = readl((CV183X_TOP + CV183X_TOP_WDT_OFFSET)) | CV183X_TOP_WDT_VAL;
	writel(val, CV183X_TOP + CV183X_TOP_WDT_OFFSET);
}

#if defined(CONFIG_HW_WATCHDOG)
void hw_watchdog_reset(void)
{
	if (designware_wdt_is_enabled())
		/* restart the watchdog counter */
		writel(DW_WDT_CRR_RESTART_VAL,
		       (CONFIG_DW_WDT_BASE + DW_WDT_CRR));
}

void hw_watchdog_init(void)
{
	cv183x_wdt_init();
	/* reset to disable the watchdog */
	hw_watchdog_reset();
	/* set timer in miliseconds */
	designware_wdt_settimeout(CONFIG_WATCHDOG_TIMEOUT_MSECS);
	/* enable the watchdog */
	designware_wdt_enable();
	/* reset the watchdog */
	hw_watchdog_reset();
}

void hw_watchdog_disable(void)
{
	if (designware_wdt_is_enabled())
		designware_wdt_disable();
}
#endif
