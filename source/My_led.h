/*
 * Led.h
 *
 *  Created on: 25. 1. 2020
 *      Author: ferom
 */

#ifndef MY_LED_H_
#define MY_LED_H_

#include "fsl_gpio.h"
#include "board.h"

class Led {
public:
	Led();
	virtual ~Led();
private:
	gpio_pin_config_t led_config;
};

#endif /* MY_LED_H_ */
