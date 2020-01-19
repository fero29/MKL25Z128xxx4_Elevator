/*
 * Myuart.cpp
 *
 *  Created on: 18. 1. 2020
 *      Author: ferom
 */

#include <Myuart.h>

uint8_t lpsci_background_buffer[LPSCI_BACKGROUND_BUFFER_SIZE];


My_uart::My_uart() {
	this->cfg.base = UART0;
	this->cfg.baudrate = LPSCI0_BAUD_RATE;
	this->cfg.srcclk = CLOCK_GetFreq(kCLOCK_CoreSysClk);
	this->cfg.parity = kLPSCI_ParityDisabled;
	this->cfg.stopbits = kLPSCI_OneStopBit;
	this->cfg.buffer = lpsci_background_buffer;
	this->cfg.buffer_size = sizeof(lpsci_background_buffer);

	lpsci_recv_buffer = new uint8_t[LPSCI_RECV_BUFFER_SIZE];

	int ret_val = LPSCI_RTOS_Init(&this->handle, &this->t_handle, &this->cfg);
	if(ret_val != 0)
	{
		printf("ERROR: init uart\n");
		vTaskSuspend(NULL);
	}
}

My_uart::~My_uart() {
	free(lpsci_recv_buffer);
	LPSCI_RTOS_Deinit(&handle);
}

int My_uart::uart_send(const uint8_t *buffer, uint32_t length) {
	return LPSCI_RTOS_Send(&this->handle, buffer, length);
}

int My_uart::uart_receive(uint8_t *buffer, uint32_t length, size_t *received) {
	return LPSCI_RTOS_Receive(&this->handle, buffer, length, received);
}
