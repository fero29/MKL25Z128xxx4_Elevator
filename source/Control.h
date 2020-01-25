/*
 * Control.h
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#ifndef CONTROL_H_
#define CONTROL_H_

#include <Commands.h>
#include <stdio.h>
#include <wchar.h>

#define ADDRESS_ELEVATOR_BUTTON_HIGH_4_BITS 0xC
#define ADDRESS_ELEVATOR_BUTTON_CABIN_HIGH_4_BITS 0xB
#define ADDRESS_DISPLAY_HIGH_4_BITS 0x3
#define ADDRESS_LED_HIGH_4_BITS 0x1
#define ADDRESS_LED_CABIN_HIGH_4_BITS 0x2
#define ADDRESS_LIMIT_SWITCH_HIGH_4_BITS 0xE

#define ADDRESS_DOWN_LIMIT_SWITCH_HIGH_4_BITS 0xD
#define ADDRESS_TERMINAL_HIGH_4_BITS 0xD

#define ADDRESS_CABIN_HIGH_4_BITS 0xF
#define ADDRESS_MOTOR_HIGH_4_BITS 0xF
#define ADDRESS_WATCHDOG_HIGH_4_BITS 0xF

#define HIGH_4_BITS_MASK 0b11110000
#define LOW_4_BITS_MASK 0b00001111

#define FLOOR_LED_COUNT 5



class Control{
public:
	Control();
	virtual ~Control();
	volatile int32_t moving_speed;
	volatile uint8_t move_to, position;
	Commands commands;

	void read_message();

private:
		void evaluate_message(uint8_t* data, size_t size);

		void evaluate_position(uint8_t address, uint8_t command);
		void evaluate_button(uint8_t address);

		void motor_move(int32_t speed);
		void motor_stop();
		void door(uint8_t command);
		void emergency_break(uint8_t command);
		void display(uint8_t command);
		void led(uint8_t address, uint8_t command);
		void all_floor_led(uint8_t command);
		void send_to_terminal(uint8_t* text, size_t size);
		void read_from_terminal(uint8_t* text, size_t size);
		void watchdog(uint8_t command);


};

#endif /* CONTROL_H_ */
