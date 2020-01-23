/*
 * Commands.h
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <stdio.h>


class Commands {
public:
	Commands();
	virtual ~Commands();
	uint8_t get_crc8(const uint8_t * data, const uint8_t size);
};

#endif /* COMMANDS_H_ */
