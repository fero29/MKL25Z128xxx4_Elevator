/*
 * Control.h
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include <Commands.h>

class Control{
public:
	Control();
	virtual ~Control();

	volatile bool door_open;
	volatile bool led_cabin_state[5];
	volatile bool led_state[5];
	volatile bool move;
	volatile int32_t speed;
	Commands commands;

	void read_message();
	void evaluate_message(uint8_t* data, size_t size);

};

#endif /* CONTROL_H_ */
