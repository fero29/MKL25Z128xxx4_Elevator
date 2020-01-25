/*
 * Hardwareresources.h
 *
 *  Created on: 25. 1. 2020
 *      Author: ferom
 */

#ifndef HARDWARERESOURCES_H_
#define HARDWARERESOURCES_H_

#include <Myuart.h>
#include "Mytimer.h"
#include <My_led.h>

class My_uart;

class Hardware_resources {
public:
	Hardware_resources();
	virtual ~Hardware_resources();
	My_uart* uart;
	//Mytimer* timer;
	//My_led* led;
	void dealy(uint32_t time);
};

#endif /* HARDWARERESOURCES_H_ */
