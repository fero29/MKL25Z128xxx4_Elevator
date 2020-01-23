/*
 * Commands.h
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_


#include <Myuart.h>

#define START_BYTE_DATA 0xA0
#define START_BYTE_ACK 0xA1

#define HEADER_MSG_SIZE 5

#define MY_ADDRESS 0x00

#define ADDRESS_ELEVATOR_BUTTON_P 0xC0
#define ADDRESS_ELEVATOR_BUTTON_1 0xC1
#define ADDRESS_ELEVATOR_BUTTON_2 0xC2
#define ADDRESS_ELEVATOR_BUTTON_3 0xC3
#define ADDRESS_ELEVATOR_BUTTON_4 0xC4

#define ADDRESS_ELEVATOR_BUTTON_CABIN_P 0xB0
#define ADDRESS_ELEVATOR_BUTTON_CABIN_1 0xB1
#define ADDRESS_ELEVATOR_BUTTON_CABIN_2 0xB2
#define ADDRESS_ELEVATOR_BUTTON_CABIN_3 0xB3
#define ADDRESS_ELEVATOR_BUTTON_CABIN_4 0xB4

#define ADDRESS_CABIN 0xF0
#define CABIN_UNLOCK 0x00
#define CABIN_LOCK 0x01


class Commands {
public:
	Commands();
	virtual ~Commands();
	My_uart* u;
	uint8_t get_crc8(const uint8_t * data, const uint8_t size);
	void msg_in_callback();
	void send_command(uint8_t dest_addr, uint8_t* command, size_t size_command);
	void send_ack(uint8_t* readed_data, size_t size);

private:
	void send_msg(uint8_t* data, size_t size);
};

#endif /* COMMANDS_H_ */
