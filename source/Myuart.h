/*
 * Myuart.h
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#ifndef MYUART_H_
#define MYUART_H_


#include "Ringbuffer/RingBufferWrapper.h"
#include "fsl_lpsci.h"
#include <fsl_debug_console.h>
#include <stdio.h>
#include <Mytimer.h>

#define DEMO_LPSCI UART0
#define DEMO_LPSCI_CLKSRC kCLOCK_CoreSysClk
#define DEMO_LPSCI_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define DEMO_LPSCI_IRQn UART0_IRQn
#define DEMO_LPSCI_IRQHandler UART0_IRQHandler
#define BAUD 115200
#define RING_BUF_SIZE 128
#define COUNT_IDLE_BAUDS 3


class My_uart {


public:
	static My_uart* get_instance();
	virtual ~My_uart();
	void uart_write(uint8_t* data, size_t size);
	void ring_write(uint8_t* data, size_t size);
	void ring_get_readed_data(uint8_t* data, size_t size);
	size_t ring_get_readed_size();

	volatile bool readed_data;
	volatile uint8_t idle;


private:

	My_uart();
	static My_uart* instance;
	lpsci_config_t config;
	uint8_t rxBufferData[RING_BUF_SIZE];
	RingBufferWrapper ringBuffRx;




};

#endif /* MYUART_H_ */
