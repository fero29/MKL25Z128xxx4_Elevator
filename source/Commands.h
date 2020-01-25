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

#define ADDRESS_ELEVATOR_BUTTON_0 0xC0
#define ADDRESS_ELEVATOR_BUTTON_1 0xC1
#define ADDRESS_ELEVATOR_BUTTON_2 0xC2
#define ADDRESS_ELEVATOR_BUTTON_3 0xC3
#define ADDRESS_ELEVATOR_BUTTON_4 0xC4

#define ADDRESS_ELEVATOR_BUTTON_CABIN_0 0xB0
#define ADDRESS_ELEVATOR_BUTTON_CABIN_1 0xB1
#define ADDRESS_ELEVATOR_BUTTON_CABIN_2 0xB2
#define ADDRESS_ELEVATOR_BUTTON_CABIN_3 0xB3
#define ADDRESS_ELEVATOR_BUTTON_CABIN_4 0xB4

#define ADDRESS_CABIN 0xF0
#define CABIN_UNLOCK 0x00
#define CABIN_LOCK 0x01

#define ADDRESS_DISPLAY 0x30
#define DISPLAY_UP 0x01
#define DISPLAY_DOWN 0x02
#define DISPLAY_CLEAR 0x00

#define ADDRESS_LED_0 0x10
#define ADDRESS_LED_1 0x11
#define ADDRESS_LED_2 0x12
#define ADDRESS_LED_3 0x13
#define ADDRESS_LED_4 0x14
#define ADDRESS_LED_CABIN_0 0x20
#define ADDRESS_LED_CABIN_1 0x21
#define ADDRESS_LED_CABIN_2 0x22
#define ADDRESS_LED_CABIN_3 0x23
#define ADDRESS_LED_CABIN_4 0x24
#define LED_ON	0x01
#define LED_OFF 0x00

#define ADDRESS_LIMIT_SWITCH_0 0xE0
#define ADDRESS_LIMIT_SWITCH_1 0xE1
#define ADDRESS_LIMIT_SWITCH_2 0xE2
#define ADDRESS_LIMIT_SWITCH_3 0xE3
#define ADDRESS_LIMIT_SWITCH_4 0xE4
#define ADDRESS_UP_LIMIT_SWITCH 0xE5
#define ADDRESS_DOWN_LIMIT_SWITCH 0xDF
#define LIMIT_SWITCH_LOW 0x00
#define LIMIT_SWITCH_IN_WIDE 0x01
#define LIMIT_SWITCH_IN_NARROW 0x02

#define ADDRESS_MOTOR 0xF1
#define MOTOR_STOP 0x1
#define MOTOR_MOVEMENT 0x2
#define MOTOR_ENCODER_COUNT 0x03
#define MOTOR_CURRENT_SPEED 0x04

#define ADDRESS_TERMINAL 0xD0

#define ADDRESS_WATCHDOG_TIMER 0xFE
#define WATCHDOG_RESET_AFTER_TIMEING_OUT 0x01
#define WATCHDOG_RESET 0x00

#define ADDRESS_EMERGENCY_BREAK 0xf
#define EMERGENCY_BREAK_DEACTIVATE 0x00
#define EMERGENCY_BREAK_ACTIVATE 0x01




class Commands {
public:
	Commands();
	virtual ~Commands();
	My_uart* u;
	uint8_t get_crc_from_msg(uint8_t* data, size_t size);
	void msg_in_callback();
	void send_command(uint8_t dest_addr, uint8_t* command, size_t size_command);
	void send_ack(uint8_t* readed_data, size_t size);
	RingBufferWrapper ringBuffCom;
	volatile bool message_to_read;

private:
	void send_msg(uint8_t* data, size_t size);
	uint8_t get_crc8(const uint8_t * data, const uint8_t size);
	uint8_t commands_data[RING_BUF_SIZE];

};

#endif /* COMMANDS_H_ */
