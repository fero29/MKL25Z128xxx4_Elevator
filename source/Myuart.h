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

#define DEMO_LPSCI UART0
#define DEMO_LPSCI_CLKSRC kCLOCK_CoreSysClk
#define DEMO_LPSCI_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define DEMO_LPSCI_IRQn UART0_IRQn
#define DEMO_LPSCI_IRQHandler UART0_IRQHandler
#define BAUD 9600
#define RING_BUF_SIZE 128




class My_uart {


public:
	static My_uart* get_instance();
	virtual ~My_uart();






private:
	My_uart();
	static My_uart* instance;

	lpsci_config_t config;

	volatile bool readed_data;
	volatile uint8_t idle;

	uint8_t rxBufferData[RING_BUF_SIZE];
	uint8_t txBufferData[RING_BUF_SIZE];

	RingBufferWrapper ringBuffRx;
	RingBufferWrapper ringBuffTx;






};

#endif /* MYUART_H_ */