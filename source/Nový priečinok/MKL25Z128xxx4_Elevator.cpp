/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL25Z128xxx4_Elevator.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#include <Myuart.h>
#include "event_groups.h"
#include <task.h>
#include <RingBufferWrapper.h>


/* TODO: insert other definitions and declarations here. */
/*
const char *to_send = "FreeRTOS LPSCI driver example!\r\n";
const char *send_ring_overrun = "\r\nRing buffer overrun!\r\n";
const char *send_hardware_overrun = "\r\nHardware buffer overrun!\r\n";
*/

static void lpsci_send_task(void *pvParameters);
static void lpsci_read_task(void *pvParameters);

const char *to_send = "FreeRTOS LPSCI driver example!\r\n";
const char *send_ring_overrun = "\r\nRing buffer overrun!\r\n";
const char *send_hardware_overrun = "\r\nHardware buffer overrun!\r\n";

#define CRC8POLY 0x31
#define CRC8INIT 0x00


/*
 * https://stackoverflow.com/questions/29214301/ios-how-to-calculate-crc-8-dallas-maxim-of-nsdata
 */
uint8_t crc8(uint8_t *data, uint16_t size)
{
    uint8_t crc, i;
    crc = CRC8INIT;

    while (size--)
    {
        crc ^= *data++;

        for (i = 0; i < 8; i++)
        {
            if (crc & 0x80) crc = (crc << 1) ^ CRC8POLY;
            else crc <<= 1;
        }
    }

    return crc;
}




/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void lpsci_read_task(void *pvParameters)
{
	My_uart * uart = (My_uart *)pvParameters;

	static uint8_t header[4];
	static uint8_t data[255];
	static uint8_t crc[1];
	static uint8_t send_data[5];


	//100110001

	for( ;; )
	{
		//printf("lpsci_read_task\n");


 		int s = uart->uart_receive(header, sizeof(header));
 		printf("rec header: %d\n", s);
		//if(s > 0)
		//{
		//	uart->uart_send(buf, s);
		//}
 		s = uart->uart_receive(data, header[3]);
 		printf("rec data: %d\n", s);

 		s = uart->uart_receive(crc, sizeof(crc));
		printf("rec data: %d\n", s);

		send_data[0] = 0xA1;
		send_data[1] = header[2];
		send_data[2] = header[1];
		send_data[3] = 0;


		//uart->uart_send(send_data, sizeof(send_data));


 	}




	vTaskSuspend(NULL);
}




/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
static void lpsci_send_task(void *pvParameters)
{
	My_uart uart = My_uart();

	uint8_t d[2] = {0x0, 0xC4};
	uint8_t crc = crc8(d, 2);
	printf("crc = %d", crc);

	for( ;; )
	{
		//uart.uart_send((uint8_t *)"other task\n", 11);
		//printf("other task\n");

	}

	vTaskSuspend(NULL);
}

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();


    printf("Hello World\n");

    //LPSCI_EnableInterrupts(UART0, kLPSCI_RxDataRegFullInterruptEnable);
	//EnableIRQ(UART0_IRQn);


    My_uart uart = My_uart();


    //xTaskCreate(lpsci_send_task, "Uart_task", configMINIMAL_STACK_SIZE, (void*)&uart, tskIDLE_PRIORITY, NULL);
    xTaskCreate(lpsci_read_task, "Uart_read_task", configMINIMAL_STACK_SIZE, (void*)&uart, configMAX_PRIORITIES, NULL);

    vTaskStartScheduler();
    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
