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


	int ret_val = LPSCI_RTOS_Init(&this->handle, &this->t_handle, &this->cfg);
	if(ret_val != 0)
	{
		printf("ERROR: init uart\n");
		vTaskSuspend(NULL);
	}
}

My_uart::~My_uart() {
	LPSCI_RTOS_Deinit(&handle);
}

void My_uart::uart_send(const uint8_t *buffer, uint32_t length) {
	int error = LPSCI_RTOS_Send(&this->handle, buffer, length);
	if(kStatus_Success != error)
	{
		printf("Error: uart send\n");
		reset_tx_events();
		//vTaskSuspend(NULL);
	}
}

size_t My_uart::uart_receive(uint8_t *buffer, uint32_t length) {
	size_t read_count;
	int error;
	error = LPSCI_RTOS_Receive(&this->handle, buffer, length, &read_count);
	if (error == kStatus_LPSCI_RxHardwareOverrun)
	{
		// Notify about hardware buffer overrun
		printf("Error: uart hardware buffer overrun\n");
		read_count = -1;
		//reset_rx_events();
		//vTaskSuspend(NULL);
	}
	if (error == kStatus_LPSCI_RxRingBufferOverrun)
	{
		// Notify about ring buffer overrun
		printf("Error: uart ring buffer overrun\n");
		read_count = -1;
		//reset_rx_events();
		//vTaskSuspend(NULL);
	}

	return read_count;
}

void My_uart::reset_rx_events() {
	xEventGroupSetBits(this->handle.rxEvent, RTOS_LPSCI_COMPLETE);
	xEventGroupClearBits(this->handle.rxEvent, RTOS_LPSCI_RING_BUFFER_OVERRUN);
	xEventGroupClearBits(this->handle.rxEvent, RTOS_LPSCI_HARDWARE_BUFFER_OVERRUN);
}

void My_uart::reset_tx_events() {
	xEventGroupSetBits(this->handle.txEvent, RTOS_LPSCI_COMPLETE);
	xEventGroupClearBits(this->handle.txEvent, RTOS_LPSCI_RING_BUFFER_OVERRUN);
	xEventGroupClearBits(this->handle.txEvent, RTOS_LPSCI_HARDWARE_BUFFER_OVERRUN);
}
