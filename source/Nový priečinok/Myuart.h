/*
 * Myuart.h
 *
 *  Created on: 18. 1. 2020
 *      Author: ferom
 */

#ifndef MYUART_H_
#define MYUART_H_


#include "fsl_lpsci_freertos.h"
#include <cstdio>
#include <stdlib.h>


#define LPSCI0_BAUD_RATE 					115200
#define LPSCI_BACKGROUND_BUFFER_SIZE		512


class My_uart {
public:
	My_uart();
	virtual ~My_uart();
	void uart_send(const uint8_t *buffer, uint32_t length);
	size_t uart_receive(uint8_t *buffer, uint32_t length);
	void reset_rx_events();
	void reset_tx_events();


private:
	lpsci_rtos_handle_t handle;
	lpsci_handle_t t_handle;
	lpsci_rtos_config_t cfg;
};

#endif /* MYUART_H_ */
