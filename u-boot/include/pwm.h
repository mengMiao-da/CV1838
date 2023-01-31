/*
 * header file for pwm driver.
 *
 * Copyright 2016 Google Inc.
 * Copyright (c) 2011 samsung electronics
 * Donghwa Lee <dh09.lee@samsung.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _pwm_h_
#define _pwm_h_

/* struct pwm_ops: Operations for the PWM uclass */
struct pwm_ops {
	/**
	 * set_config() - Set the PWM configuration
	 *
	 * @dev:	PWM device to update
	 * @channel:	PWM channel to update
	 * @period_ns:	PWM period in nanoseconds
	 * @duty_ns:	PWM duty period in nanoseconds
	 * @return 0 if OK, -ve on error
	 */
	int (*set_config)(struct udevice *dev, uint channel, uint period_ns,
			  uint duty_ns);

	/**
	 * set_enable() - Enable or disable the PWM
	 *
	 * @dev:	PWM device to update
	 * @channel:	PWM channel to update
	 * @enable:	true to enable, false to disable
	 * @return 0 if OK, -ve on error
	 */
	int (*set_enable)(struct udevice *dev, uint channel, bool enable);
	/**
	 * set_invert() - Set the PWM invert
	 *
	 * @dev:        PWM device to update
	 * @channel:    PWM channel to update
	 * @polarity:   true to invert, false to keep normal polarity
	 * @return 0 if OK, -ve on error
	 */
	int (*set_invert)(struct udevice *dev, uint channel, bool polarity);
};

#define pwm_get_ops(dev)	((struct pwm_ops *)(dev)->driver->ops)

/**
 * pwm_set_config() - Set the PWM configuration
 *
 * @dev:	PWM device to update
 * @channel:	PWM channel to update
 * @period_ns:	PWM period in nanoseconds
 * @duty_ns:	PWM duty period in nanoseconds
 * @return 0 if OK, -ve on error
 */
int pwm_set_config(struct udevice *dev, uint channel, uint period_ns,
		   uint duty_ns);

/**
 * pwm_set_enable() - Enable or disable the PWM
 *
 * @dev:	PWM device to update
 * @channel:	PWM channel to update
 * @enable:	true to enable, false to disable
 * @return 0 if OK, -ve on error
 */
int pwm_set_enable(struct udevice *dev, uint channel, bool enable);

/**
 * pwm_set_invert() - Set pwm default polarity
 *
 * @dev:	PWM device to update
 * @channel:	PWM channel to update
 * @polarity:	true to invert, false to keep normal polarity
 * @return 0 if OK, -ve on error
 */
int pwm_set_invert(struct udevice *dev, uint channel, bool polarity);

/* Legacy interface */
#ifndef CONFIG_DM_PWM
int	pwm_init		(int pwm_id, int div, int invert);
int	pwm_config		(int pwm_id, int duty_ns, int period_ns);
int	pwm_enable		(int pwm_id);
void	pwm_disable		(int pwm_id);
#endif

/* cvitek pwm driver interface */
#ifdef CONFIG_PWM_CVITEK
struct pwm_dev {
	int pwm_id;
	int is_config;/* duty_cycle and period is config or not */
};

/**
 * cv_pwm_config_mode() - Set pwm mode
 *
 * @pwm:		set pwm->pwm_id to operate pwm
 * @pwm_mode:	0:Continuous output mode, 1:Pulse number output mode
 * @pulse_num:	Pulse number(valid when pwm_mode = 1)
 * @return		0 if OK, -1 on error
 */
int cv_pwm_config_mode(struct pwm_dev *pwm, int pwm_mode, int pulse_num);

/**
 * cv_pwm_config_cycle() - Set pwm cycle
 *
 * @pwm:		set pwm->pwm_id to operate pwm
 * @duty_ns:	Pulse high level period
 * @period_ns:	Pulse period
 * @return		0 if OK, -1 on error
 */
int	cv_pwm_config_cycle(struct pwm_dev *pwm, int duty_ns, int period_ns);

int	cv_pwm_enable(struct pwm_dev *pwm);

int	cv_pwm_disable(struct pwm_dev *pwm);

/**
 * cv_pwm_update() - Dynamically update cycles when PWM is enabled
 *
 * @pwm:		set pwm->pwm_id to operate pwm
 * @duty_ns:	Pulse high level period
 * @period_ns:	Pulse period
 * @return		0 if OK, -1 on error
 */
int cv_pwm_update(struct pwm_dev *pwm, int duty_ns, int period_ns);

#endif /* CONFIG_PWM_CVITEK */

#endif /* _pwm_h_ */
