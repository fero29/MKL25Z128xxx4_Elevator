/*
 * Commands.cpp
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#include <Commands.h>

/*
 * @brief constructor of object Commands, this object care of sending and reading commands
 */
Commands::Commands():ringBuffCom(commands_data, RING_BUF_SIZE) {
	//this->u = My_uart::get_instance();
	message_to_read = false;
}

/*
 * @brief destructor of object Commands
 */
Commands::~Commands() {
}

/*
 * @brief callback function for incoming messages
 */
void Commands::msg_in_callback() {
	if(hardvare.uart->readed_data)
	{
		int8_t count = (uint)hardvare.uart->ring_get_readed_size();
		uint8_t buf[count];
		DisableIRQ(DEMO_LPSCI_IRQn);
		hardvare.uart->ring_get_readed_data(buf, count);
		EnableIRQ(DEMO_LPSCI_IRQn);



		if(get_crc_from_msg(buf, count) == buf[count - 1])
		{

			if(count >= HEADER_MSG_SIZE && buf[0] == START_BYTE_DATA)
			{
				send_ack(buf, count);
			}


			while(message_to_read)
			{}
			ringBuffCom.Write(buf, count);
			message_to_read = true;
		}
		else
		{
			//printf("bad crc\n");
		}

		hardvare.uart->readed_data = false;
	}
}


/*
 * @ generate data for send command and calculate crc
 */
void Commands::send_command(uint8_t dest_addr, uint8_t *command,
		size_t size_command)
{
	uint8_t crc_array[size_command + 2];
	uint8_t send_data[size_command + HEADER_MSG_SIZE];
	send_data[0] = START_BYTE_DATA;
	send_data[1] = dest_addr;
	send_data[2] = 0x00;
	send_data[3] = (uint8_t)size_command;

	crc_array[0] = send_data[1];
	crc_array[1] = send_data[2];

	if(size_command > 0)
	{
		memcpy(&send_data[4], command, size_command);
		memcpy(&crc_array[2], command, size_command);
	}

	send_data[4 + size_command] = get_crc8(crc_array, sizeof(crc_array));
	send_msg(send_data, sizeof(send_data));
}

/*
 * @brief generate ack from message and send it
 */
void Commands::send_ack(uint8_t *readed_data, size_t size)
{
	uint8_t send[size];
	uint8_t crc_array[2];
	send[0] = START_BYTE_ACK;
	send[1] = readed_data[2];
	send[2] = readed_data[1];
	send[3] = 0x00;
	crc_array[0] = send[1];
	crc_array[1] = send[2];
	send[4] = get_crc8(crc_array, sizeof(crc_array));
	send_msg(send, sizeof(send));
	//printf("sended ack\n");
}


/*
 * @brief diable irq from uart0 and send data
 */
void Commands::send_msg(uint8_t *data, size_t size)
{
	DisableIRQ(DEMO_LPSCI_IRQn);
	hardvare.uart->uart_write(data, size);
	EnableIRQ(DEMO_LPSCI_IRQn);
}




uint8_t crc_array[256] =
{
    0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83,
    0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
    0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e,
    0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
    0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0,
    0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
    0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d,
    0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
    0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5,
    0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
    0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58,
    0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
    0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6,
    0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
    0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b,
    0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
    0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f,
    0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
    0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92,
    0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
    0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c,
    0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
    0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1,
    0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
    0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49,
    0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
    0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4,
    0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
    0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a,
    0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
    0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7,
    0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
};

/*
 * @brief return crc_8 from message  to confirm
 */
uint8_t Commands::get_crc_from_msg(uint8_t *data, size_t size)
{
	uint8_t crc_array[size - 3];
	crc_array[0] = data[1];
	crc_array[1] = data[2];
	if(size - HEADER_MSG_SIZE > 0)
	{
		memcpy(&crc_array[2], &data[4], size - HEADER_MSG_SIZE);
	}

	return get_crc8(crc_array, sizeof(crc_array));
}

/*
 * @brief return crc_8
 * source : https://stackoverflow.com/questions/29214301/ios-how-to-calculate-crc-8-dallas-maxim-of-nsdata
 */
uint8_t Commands::get_crc8(const uint8_t * data, const uint8_t size)
{
	uint8_t crc = 0;
    for ( uint8_t i = 0; i < size; ++i )
    {
         crc = crc_array[data[i] ^ crc];
    }
    return crc;
}


