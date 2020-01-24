/*
 * Control.cpp
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#include <Control.h>


/*
 * @brief constructor of object Control. this object have a main control
 */
Control::Control() {
	//door_open = true;
	//for(int i = 0; i < 5; i++)
	//{
	//	led_cabin_state[i] = false;
	//	led_state[i] = false;
	//}
	moving = false;
	move_to = ADDRESS_LIMIT_SWITCH_0;
	motor_move(-100);
	//speed = 0;


}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

/*
 * @brief function must be called in main loop, it usses for getting messages from control object
 */
void Control::read_message() {
	if(commands.message_to_read)
	{
		uint8_t count = commands.ringBuffCom.NumOfElements();
		uint8_t buf[count];
		commands.ringBuffCom.Read(buf, count);
		evaluate_message(buf, count);
		commands.message_to_read = false;
	}
}


/*
 * @brief function evaluate message and call commands
 */
void Control::evaluate_message(uint8_t *data, size_t size) {
	if(data[0] == START_BYTE_DATA)
	{
		uint8_t addr = data[2];
		switch(addr >> 4)
		{
			case ADDRESS_ELEVATOR_BUTTON_HIGH_4_BITS:
			{
				evaluate_button(addr);
			}break;

			case ADDRESS_ELEVATOR_BUTTON_CABIN_HIGH_4_BITS:
			{
				evaluate_button(addr);
			}break;

			case ADDRESS_DISPLAY_HIGH_4_BITS:
			{
				//no command
			}break;

			case ADDRESS_LED_HIGH_4_BITS:
			{
				//no command
			}break;

			case ADDRESS_LED_CABIN_HIGH_4_BITS:
			{
				//no command
			}break;

			case ADDRESS_LIMIT_SWITCH_HIGH_4_BITS:
			{
				evaluate_position(addr, data[4]);
			}break;

			/*TERMINAL AND DOWN LIMIT SWITCH HAVE THE SAME HIGH 4BITS*/
			case ADDRESS_TERMINAL_HIGH_4_BITS:
			{
				if(addr == ADDRESS_TERMINAL)
				{
					size_t s = data[3];
					uint8_t txt[s];
					memcpy(txt, &data[4], s);
					read_from_terminal(data, s);
				}
				else if(addr == ADDRESS_DOWN_LIMIT_SWITCH)
				{
					evaluate_position(data[2], data[4]);
				}
			}break;

			/*CABIN, MOTOR AND WATCHDOG HAVE THE SAME HIGH 4BITS*/
			case ADDRESS_CABIN_HIGH_4_BITS:
			{
				if(addr == ADDRESS_WATCHDOG_TIMER)
				{
					/*TODO finish it*/
				}
				else if(addr == ADDRESS_MOTOR)
				{
					//no command
				}
				else if(addr == ADDRESS_CABIN)
				{
					//no command
				}
			}break;

			default:{};
		}
	}
	else
	{
		if(data[2] >> 4 == ADDRESS_LIMIT_SWITCH_HIGH_4_BITS || data[4] == ADDRESS_DOWN_LIMIT_SWITCH)
		{
			evaluate_position(data[2], data[4]);
		}
	}
}

void Control::evaluate_position(uint8_t address, uint8_t command) {

}

void Control::evaluate_button(uint8_t address) {
	if(!moving)
	{
		uint8_t addr_led = (ADDRESS_LED_HIGH_4_BITS << 4) |  (address & LOW_4_BITS_MASK);
		uint8_t addr_led_cabin = (ADDRESS_LED_CABIN_HIGH_4_BITS << 4) |  (address & LOW_4_BITS_MASK);
		led(addr_led, LED_ON);
		led(addr_led_cabin, LED_ON);
		motor_move(100);
	}
}

/*
 * @brief function close cabin of elevator and send command to move
 */
void Control::motor_move(int32_t speed)
{
	uint8_t s_d[5];
	s_d[0] = MOTOR_MOVEMENT;
	memcpy(&s_d[1], &speed, sizeof(speed));
	door(CABIN_LOCK);
	emergency_break(EMERGENCY_BREAK_DEACTIVATE);
	commands.send_command(ADDRESS_MOTOR, s_d, sizeof(s_d));
	//moving = true;
}

void Control::motor_stop() {
	commands.send_command(ADDRESS_MOTOR, (uint8_t*)MOTOR_STOP, sizeof(uint8_t));
	door(CABIN_UNLOCK);
}

void Control::door(uint8_t command) {
	commands.send_command(ADDRESS_CABIN, &command, sizeof(uint8_t));
}

void Control::emergency_break(uint8_t command) {
	commands.send_command(ADDRESS_EMERGENCY_BREAK, &command, sizeof(uint8_t));
}

void Control::display(uint8_t command) {
	commands.send_command(ADDRESS_DISPLAY, &command, sizeof(uint8_t));
}

void Control::led(uint8_t address, uint8_t command) {
	commands.send_command(address, &command, sizeof(uint8_t));
}

void Control::send_to_terminal(uint8_t *text, size_t size) {
	commands.send_command(ADDRESS_TERMINAL, text, size);
}

void Control::read_from_terminal(uint8_t *text, size_t size) {
	printf("\n<MESSAGE FROM ELEVATOR>");
	for(uint i = 0; i< size; ++i)
	{
		printf("%c", text[i]);
	}
	printf("\n");
}

void Control::watchdog(uint8_t command) {
	commands.send_command(ADDRESS_WATCHDOG_TIMER, &command, sizeof(uint8_t));
}
