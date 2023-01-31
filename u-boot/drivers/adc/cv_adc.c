/*
 * Copyright (C) 2015 Samsung Electronics
 * Przemyslaw Marczak <p.marczak@samsung.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <errno.h>
#include <dm.h>
#include <adc.h>
#include <asm/io.h>
#include <malloc.h>
#include <linux/errno.h>
#ifdef CONFIG_TARGET_CVITEK_CV1822
#include "../../board/cvitek/cv1822/cv1822_reg.h"
#include "../../board/cvitek/cv1822/cv1822_pinlist_swconfig.h"
#include "../../board/cvitek/cv1822/cv1822_reg_fmux_gpio.h"
#else
#include "../../include/cvitek/cv183x_reg.h"
#include "../../board/cvitek/cv1835/cv1835_pinlist_swconfig.h"
#include "../../board/cvitek/cv1835/cv1835_reg_fmux_gpio.h"
#endif

#define CVITEK_ADC_BASE_ADDR 0x030F0000
#define CVITEK_RTCSYS_ADC_BASE_ADDR 0x0502C000
#define CVITEK_ADC_CTRL 0x04
#define CVITEK_ADC_STATE 0x08
#define CVITEK_ADC_CHx_RESULT 0x14
#define CVITEK_ADC_INTR_EN 0x20

#define ADC1_IO_ADDR_CV182X	0x03001810
#define ADC2_IO_ADDR_CV182X	0x0300180C
#define ADC3_IO_ADDR_CV182X	0x03001808
#define PWR_ADC2_IO_ADDR_CV182X	0x05027030
#define ADC1_IO_ADDR_CV183X	0x03001950
#define ADC2_IO_ADDR_CV183X	0x0300194C
#define ADC3_IO_ADDR_CV183X	0x03001944

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

static int cvitek_adc_channel_data(struct cvitek_adc_dev *adc)
{
	unsigned int BASE_ADDR;
	unsigned int value;
	unsigned int adc_value;
	int channel;

	channel = adc->channel;
	BASE_ADDR = adc->BASE_ADDR;

#ifdef CONFIG_TARGET_CVITEK_CV1822
	cv182x_io_config(channel);
#else
	cv183x_io_config(channel);
#endif

	// Trigger measurement
	value = readl(BASE_ADDR + CVITEK_ADC_CTRL);
	writel(value | 0x1, BASE_ADDR + CVITEK_ADC_CTRL);

	// Check busy status
	while (readl(BASE_ADDR + CVITEK_ADC_STATE) & 0x1)
		;

	adc->value = readl(BASE_ADDR +
			   CVITEK_ADC_CHx_RESULT +
			   (channel - 1) * 0x4)
		     & 0xFFF;

	return 0;
}

static int cvitek_adc_channel_config(struct cvitek_adc_dev *adc)
{
	unsigned int BASE_ADDR;
	unsigned int value;
	int channel;

	channel = adc->channel;
	BASE_ADDR = adc->BASE_ADDR;

	// Disable saradc interrupt
	writel(0x0, BASE_ADDR + CVITEK_ADC_INTR_EN);

	// Set channel
	value = readl(BASE_ADDR + CVITEK_ADC_CTRL);
	writel(value | (1 << (0x4 + channel)),
	       BASE_ADDR + CVITEK_ADC_CTRL);

	return 0;
}

static int get_ic_version(void)
{
	return readl(0x03000000) & 0x1;
}

unsigned int cvitek_adc_read(int channel)
{
	struct cvitek_adc_dev adc;

#ifdef CONFIG_TARGET_CVITEK_CV1822
	if (channel < ADC1 ||
	    channel > PWR_ADC ||
	    (!get_ic_version() && channel == PWR_ADC)) {
#else
	if (channel < ADC1 || channel > ADC3) {
#endif
		return -1;
	}

	if (channel == PWR_ADC) {
		adc.BASE_ADDR = CVITEK_RTCSYS_ADC_BASE_ADDR;//PWR_GPIO1属于RTCSYS_SARADC
		channel = 2;//PWR_GPIO1属于channel2
	} else {
		adc.BASE_ADDR = CVITEK_ADC_BASE_ADDR;
	}

	adc.channel = channel;
	cvitek_adc_channel_config(&adc);//Initialize the adc
	cvitek_adc_channel_data(&adc);//Get the sample value

	return adc.value;
}
