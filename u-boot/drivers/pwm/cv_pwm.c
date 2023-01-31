/*
 * Copyright (c) 2016 Google, Inc
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <div64.h>
#include <pwm.h>
#include <asm/io.h>

#define CV_PWM_BASE 0x03060000
#define CV_PWM_HLPERIOD 0X00
#define CV_PWM_PERIOD 0X04
#define CV_PWM_POLARITY 0X40
#define CV_PWM_PWMSTART 0X44
#define CV_PWM_PWMDONE 0x48
#define CV_PWM_PWMUPDATE 0x4c
#define CV_PWM_PCOUNT 0x50
#define CV_PWM_PULSECOUNT 0x60
#define CV_PWM_SHIFTCOUNT 0x80
#define CV_PWM_SHIFTSTART 0x90
#define CV_PWM_PWM_OE 0xd0

#define CV_PWM_CLK_MHZ 100

int cv_pwm_config_mode(struct pwm_dev *pwm, int pwm_mode, int pulse_num)
{
	uint32_t value;
	uint32_t pwm_chip_num;
	uint32_t pwm_num;
	int pwm_id = pwm->pwm_id;

	if (pwm_id < 0 || pwm_id > 15)
		return -1;
	pwm_chip_num = pwm_id / 4;
	pwm_num = pwm_id % 4;

	value = readl(CV_PWM_BASE + 0x1000 * pwm_chip_num +
				CV_PWM_POLARITY);
	value = (pwm_mode == 1) ? value | (0x1 << (pwm_num + 8)) :
				value & ~(0x1 << (pwm_num + 8));
	writel(value, CV_PWM_BASE + 0x1000 * pwm_chip_num +
				CV_PWM_POLARITY);
	if (pwm_mode == 1) {
		writel(pulse_num, CV_PWM_BASE + 0x1000 * pwm_chip_num +
				CV_PWM_PULSECOUNT + 0x4 * pwm_num);
	}
	return 0;
}

int cv_pwm_config_cycle(struct pwm_dev *pwm, int duty_ns, int period_ns)
{
	u32 period_val, hlperiod_val;
	uint32_t pwm_chip_num;
	uint32_t pwm_num;
	int pwm_id = pwm->pwm_id;

	if (pwm_id < 0 || pwm_id > 15)
		return -1;
	if (duty_ns <= 0)
		duty_ns = 1;
	if (duty_ns >= period_ns)
		duty_ns = period_ns - 1;

	pwm_chip_num = pwm_id / 4;
	pwm_num = pwm_id % 4;
	period_val = CV_PWM_CLK_MHZ * period_ns / 1000;
	hlperiod_val = CV_PWM_CLK_MHZ * (period_ns - duty_ns) / 1000;

	/* set duty cycles */
	writel(hlperiod_val, CV_PWM_BASE + 0x1000 * pwm_chip_num +
				CV_PWM_HLPERIOD + 0x8 * pwm_num);
	/* set period cycles */
	writel(period_val, CV_PWM_BASE + 0x1000 * pwm_chip_num +
				CV_PWM_PERIOD + 0x8 * pwm_num);

	pwm->is_config = 1;
	return 0;
}

int cv_pwm_enable(struct pwm_dev *pwm)
{
	uint32_t value;
	uint32_t pwm_chip_num;
	uint32_t pwm_num;
	int pwm_id = pwm->pwm_id;

	if (pwm_id < 0 || pwm_id > 15 || pwm->is_config != 1)
		return -1;
	pwm_chip_num = pwm_id / 4;
	pwm_num = pwm_id % 4;

	value = readl(CV_PWM_BASE + 0x1000 * pwm_chip_num +
				CV_PWM_PWMSTART);
	/* enable pwmstart */
	writel(value & ~(0x1 << pwm_num), CV_PWM_BASE +
				0x1000 * pwm_chip_num + CV_PWM_PWMSTART);
	writel(value | (0x1 << pwm_num), CV_PWM_BASE +
				0x1000 * pwm_chip_num + CV_PWM_PWMSTART);
	writel(value | (0x1 << pwm_num), CV_PWM_BASE +
				0x1000 * pwm_chip_num + CV_PWM_PWM_OE);
	return 0;
}

int cv_pwm_disable(struct pwm_dev *pwm)
{
	uint32_t value;
	uint32_t pwm_chip_num;
	uint32_t pwm_num;
	int pwm_id = pwm->pwm_id;

	if (pwm_id < 0 || pwm_id > 15)
		return -1;
	pwm_chip_num = pwm_id / 4;
	pwm_num = pwm_id % 4;

	value = readl(CV_PWM_BASE + 0x1000 * pwm_chip_num +
				CV_PWM_PWMSTART);
	/* disable pwmstart */
	writel(value & ~(0x1 << pwm_num), CV_PWM_BASE +
				0x1000 * pwm_chip_num + CV_PWM_PWMSTART);
	return 0;
}

int cv_pwm_update(struct pwm_dev *pwm, int duty_ns, int period_ns)
{
	uint32_t value;
	uint32_t pwm_chip_num;
	uint32_t pwm_num;
	int pwm_id = pwm->pwm_id;

	if (pwm_id < 0 || pwm_id > 15)
		return -1;
	pwm_chip_num = pwm_id / 4;
	pwm_num = pwm_id % 4;

	if (cv_pwm_config_cycle(pwm, duty_ns, period_ns))
		return -1;

	value = readl(CV_PWM_BASE + 0x1000 * pwm_chip_num +
				CV_PWM_PWMUPDATE);

	/* update pwm period and duty cycle */
	writel(value | (0x1 << pwm_num), CV_PWM_BASE +
				0x1000 * pwm_chip_num + CV_PWM_PWMUPDATE);
	writel(value & ~(0x1 << pwm_num), CV_PWM_BASE +
				0x1000 * pwm_chip_num + CV_PWM_PWMUPDATE);
	return 0;
}
