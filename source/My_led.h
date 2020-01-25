/*
 * My_led.h
 *
 *  Created on: 25. 1. 2020
 *      Author: ferom
 */

#ifndef MY_LED_H_
#define MY_LED_H_

#include "fsl_gpio.h"
#include "board.h"

class My_led {
public:
	My_led();
	virtual ~My_led();
	void green_on();
	void red_on();
	void blue_on();
	void white_on();

	void green_off();
	void red_off();
	void blue_off();
	void white_off();

	void green_togle();
	void red_togle();
	void blue_togle();
	void white_togle();



private:
	gpio_pin_config_t led_config;

};

#endif /* MY_LED_H_ */
