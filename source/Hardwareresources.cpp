/*
 * Hardwareresources.cpp
 *
 *  Created on: 25. 1. 2020
 *      Author: ferom
 */

#include <Hardwareresources.h>

Hardware_resources::Hardware_resources() {
	this->uart = My_uart::get_instance();
}

Hardware_resources::~Hardware_resources() {
	delete(uart);
}

void Hardware_resources::dealy(uint32_t time) {
	volatile uint32_t i = 0;
	for (i = 0; i < time; ++i)
	{
		__asm("NOP"); /* delay */
	}
}

