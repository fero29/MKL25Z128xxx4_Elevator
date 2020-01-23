/*
 * Control.cpp
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#include <Control.h>

Control::Control() {
	door_open = true;
	for(int i = 0; i < 5; i++)
	{
		led_cabin_state[i] = false;
		led_state[i] = false;
	}
	moving = false;
	speed = 0;


}

Control::~Control() {
	// TODO Auto-generated destructor stub
}

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

void Control::evaluate_message(uint8_t *data, size_t size) {
	if(data[0] == START_BYTE_DATA)
	{
		switch(data[2])
		{
			case ADDRESS_ELEVATOR_BUTTON_0:
			{
				commands.send_command(ADDRESS_LED_0, (uint8_t*)LED_ON, sizeof(LED_ON));
				move(-100);
			}break;

			case ADDRESS_ELEVATOR_BUTTON_1:
			{
				commands.send_command(ADDRESS_LED_1, (uint8_t*)LED_ON, sizeof(LED_ON));
			}break;

			case ADDRESS_ELEVATOR_BUTTON_2:
			{
				commands.send_command(ADDRESS_LED_2, (uint8_t*)LED_ON, sizeof(LED_ON));
			}break;

			case ADDRESS_ELEVATOR_BUTTON_3:
			{
				commands.send_command(ADDRESS_LED_3, (uint8_t*)LED_ON, sizeof(LED_ON));
			}break;

			case ADDRESS_ELEVATOR_BUTTON_4:
			{
				commands.send_command(ADDRESS_LED_4, (uint8_t*)LED_ON, sizeof(LED_ON));
				move(100);
			}break;

/*-----------------------------------------------------------------------------------------------*/
			case ADDRESS_ELEVATOR_BUTTON_CABIN_0:
			{
				commands.send_command(ADDRESS_LED_CABIN_0, (uint8_t*)LED_ON, sizeof(LED_ON));
			}break;

			case ADDRESS_ELEVATOR_BUTTON_CABIN_1:
			{
				commands.send_command(ADDRESS_LED_CABIN_1, (uint8_t*)LED_ON, sizeof(LED_ON));
			}break;

			case ADDRESS_ELEVATOR_BUTTON_CABIN_2:
			{
				commands.send_command(ADDRESS_LED_CABIN_2, (uint8_t*)LED_ON, sizeof(LED_ON));
			}break;

			case ADDRESS_ELEVATOR_BUTTON_CABIN_3:
			{
				commands.send_command(ADDRESS_LED_CABIN_3, (uint8_t*)LED_ON, sizeof(LED_ON));
			}break;

			case ADDRESS_ELEVATOR_BUTTON_CABIN_4:
			{
				commands.send_command(ADDRESS_LED_CABIN_4, (uint8_t*)LED_ON, sizeof(LED_ON));
			}break;






		}
	}
	else
	{

	}
}



void Control::move(int32_t speed)
{
	uint8_t s_d[5];
	s_d[0] = MOTOR_MOVEMENT;
	memcpy(&s_d[1], &speed, sizeof(speed));
	commands.send_command(ADDRESS_CABIN, (uint8_t*)CABIN_LOCK, sizeof(CABIN_LOCK));

	commands.send_command(ADDRESS_MOTOR, s_d, sizeof(s_d));
}

void Control::get_position()
{

}
