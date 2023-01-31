#include <common.h>
#include <command.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <asm/io.h>

#ifdef CONFIG_TARGET_CVITEK_CV1822
#include "../board/cvitek/cv1822/cv1822_reg.h"
#include "../board/cvitek/cv1822/cv1822_pinlist_swconfig.h"
#include "../board/cvitek/cv1822/cv1822_reg_fmux_gpio.h"
#else
#include "../include/cvitek/cv183x_reg.h"
#include "../board/cvitek/cv1835/cv1835_pinlist_swconfig.h"
#include "../board/cvitek/cv1835/cv1835_reg_fmux_gpio.h"
#endif

#define SARADC_BASE 0x030F0000
#define RTCSYS_SARADC_BASE 0x0502C000
#define SARADC_INTR_EN 0x20
#define SARADC_CTRL 0x4
#define SARADC_STATUS 0x8
#define SARADC_CH1_RESULT 0x14
#define SARADC_SEL_SHIFT 0x4

#define ADC1_IO_ADDR_CV182X	0x03001810
#define ADC2_IO_ADDR_CV182X	0x0300180C
#define ADC3_IO_ADDR_CV182X	0x03001808
#define PWR_ADC2_IO_ADDR_CV182X	0x05027030
#define ADC1_IO_ADDR_CV183X	0x03001950
#define ADC2_IO_ADDR_CV183X	0x0300194C
#define ADC3_IO_ADDR_CV183X	0x03001944

#define EFUSE_DEBUG 1

#define CVI_U8 unsigned char
#define CVI_U32 unsigned int
#define CVI_S8 signed char
#define CVI_S32 int

#define CVI_SUCCESS 0
#define CVI_FAILURE (-1)

#define _cc_trace(fmt, ...) __trace("", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)
#define _cc_error(fmt, ...) __trace("ERROR:", __FILE__, __func__, __LINE__, fmt, ##__VA_ARGS__)

#if EFUSE_DEBUG
static int __trace(const char *prefix, const char *path, const char *func, int lineno, const char *fmt, ...)
{
	va_list ap;
	int ret;

	printf("[%s%s:%s:%d] ", prefix, path, func, lineno);
	if (!fmt || fmt[0] == '\0') {
		ret = printf("\n");
	} else {
		va_start(ap, fmt);
		ret = vprintf(fmt, ap);
		va_end(ap);
	}

	return ret;
}
#else
static int __trace(const char *prefix, const char *path, const char *func, int lineno, const char *fmt, ...)
{
	return 0;
}
#endif

#define PINMUX_CONFIG(PIN_NAME, FUNC_NAME) \
		mmio_clrsetbits_32(PINMUX_BASE + fmux_gpio_funcsel_##PIN_NAME, \
			fmux_gpio_funcsel_##PIN_NAME##_MASK << fmux_gpio_funcsel_##PIN_NAME##_OFFSET, \
			PIN_NAME##__##FUNC_NAME)

enum ADCChannel {
	ADC1 = 1,
	ADC2,
	ADC3,
	PWR_ADC
};

#ifdef CONFIG_TARGET_CVITEK_CV1822
static void cv182x_io_config(uint32_t channel)
{
	switch (channel) {
	case ADC1:
		PINMUX_CONFIG(ADC1, XGPIOB_3);
		writel(0x0, ADC1_IO_ADDR_CV182X);
		break;
	case ADC2:
		PINMUX_CONFIG(ADC2, XGPIOB_2);
		writel(0x0, ADC2_IO_ADDR_CV182X);
		break;
	case ADC3:
		PINMUX_CONFIG(ADC3, XGPIOB_1);
		writel(0x0, ADC3_IO_ADDR_CV182X);
		break;
	case PWR_ADC:
		PINMUX_CONFIG(PWR_GPIO1, PWR_GPIO_1);
		writel(0x0, PWR_ADC2_IO_ADDR_CV182X);
		break;
	default:
		printf("io_config: invalid saradc channel %d\n", channel);
		break;
	}
}
#else
static void cv183x_io_config(uint32_t channel)
{
	switch (channel) {
	case ADC1:
		PINMUX_CONFIG(ADC1, XGPIOB_24);
		writel(0x0, ADC1_IO_ADDR_CV183X);
		break;
	case ADC2:
		PINMUX_CONFIG(UART2_CTS, XGPIOB_19);
		writel(0x0, ADC2_IO_ADDR_CV183X);
		break;
	case ADC3:
		PINMUX_CONFIG(UART1_CTS, XGPIOB_20);
		writel(0x0, ADC3_IO_ADDR_CV183X);
		break;
	default:
		printf("io_config: invalid saradc channel %d\n", channel);
		break;
	}
}
#endif

static int get_ic_version(void)
{
	return readl(0x03000000) & 0x1;
}

CVI_U32 CVI_SARADC_read(CVI_U32 ch)
{
	CVI_U32 BASE_ADDR;
	CVI_U32 value;
	CVI_U32 adc_value;

	_cc_trace("channel: %d\n", ch);

#ifdef CONFIG_TARGET_CVITEK_CV1822
	if (ch < ADC1 ||
	    ch > PWR_ADC ||
	    (!get_ic_version() && ch == PWR_ADC)) {
#else
	if (ch < ADC1 || ch > ADC3) {
#endif
		return CMD_RET_USAGE;
	}

	// Set pinmux and pd register
#ifdef CONFIG_TARGET_CVITEK_CV1822
	cv182x_io_config(ch);
#else
	cv183x_io_config(ch);
#endif

	if (ch == PWR_ADC) {
		BASE_ADDR = RTCSYS_SARADC_BASE;//PWR_GPIO1属于RTCSYS_SARADC
		ch = 2;//PWR_GPIO1属于channel2
	} else {
		BASE_ADDR = SARADC_BASE;
	}

	// Disable saradc interrupt
	writel(0x0, BASE_ADDR + SARADC_INTR_EN);

	// Set channel
	writel(1 << (SARADC_SEL_SHIFT + ch), BASE_ADDR + SARADC_CTRL);

	// Trigger measurement
	value = readl(BASE_ADDR + SARADC_CTRL) | 1;
	writel(value, BASE_ADDR + SARADC_CTRL);
	_cc_trace("SARADC_CTRL = %#X\n", value);

	// Check busy status
	while (readl(BASE_ADDR + SARADC_STATUS) & 0x1)
		;

	adc_value = readl((void *)(BASE_ADDR + SARADC_CH1_RESULT) + (ch - 1) * 4) & 0xFFF;
	_cc_trace("adc_value = %d\n", adc_value);

	return adc_value;
}

static int do_adc_read(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	uint32_t ch;

	if (argc != 2)
		return CMD_RET_USAGE;

	ch = simple_strtol(argv[1], NULL, 10);
#ifdef CONFIG_TARGET_CVITEK_CV1822
	if (ch < ADC1 ||
	    ch > PWR_ADC ||
	    (!get_ic_version() && ch == PWR_ADC)) {
#else
	if (ch < ADC1 || ch > ADC3) {
#endif
		return CMD_RET_USAGE;
	}

	CVI_SARADC_read(ch);
	return 0;
}

U_BOOT_CMD(adc_read, 2, 1, do_adc_read, "read saradc value",
	   "[args..]\n"
	   "    - args ...");
