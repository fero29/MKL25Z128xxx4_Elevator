/*
 * Copyright 2016-2019 NXP
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

#include <fsl_clock.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_LPSCI UART0
#define DEMO_LPSCI_CLKSRC kCLOCK_CoreSysClk
#define DEMO_LPSCI_CLK_FREQ CLOCK_GetFreq(kCLOCK_CoreSysClk)
#define DEMO_LPSCI_IRQn UART0_IRQn
#define DEMO_LPSCI_IRQHandler UART0_IRQHandler

/**
 * @file    MKL25Z128xxx4_Project.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_lpsci.h"
//#include "RingBuffer.h"
#include "Ringbuffer/RingBufferWrapper.h"
/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

uint8_t g_tipString[] =
		"LPSCI functional API interrupt example\r\nBoard receives characters then sends them out\r\nNow please input:\r\n";

volatile bool ready_to_send = false;
volatile bool readed_data = false;
volatile uint8_t idle = 0;

//buffer_t rxBuffer_handler;
//buffer_t txBuffer_handler;
uint8_t rxBufferData[100];
uint8_t txBufferData[100];

/* Setup RingBuffers */
RingBufferWrapper ringBuffRx(rxBufferData,sizeof(rxBufferData));
RingBufferWrapper ringBuffTx(txBufferData,sizeof(txBufferData));

//LPSCI_EnableInterrupts(DEMO_LPSCI, kLPSCI_IdleLineInterruptEnable);
//LPSCI_DisableInterrupts(DEMO_LPSCI, kLPSCI_IdleLineInterruptEnable);



/*******************************************************************************
 * Code
 ******************************************************************************/


/*
 * https://stackoverflow.com/questions/29214301/ios-how-to-calculate-crc-8-dallas-maxim-of-nsdata
 */

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

uint8_t get_crc8(const uint8_t * data, const uint8_t size)
{
	uint8_t crc = 0;
    for ( uint8_t i = 0; i < size; ++i )
    {
         crc = crc_array[data[i] ^ crc];
    }
    return crc;
}






extern "C" void DEMO_LPSCI_IRQHandler(void)
{

	//uint8_t data;
	uint32_t status_flags = LPSCI_GetStatusFlags(DEMO_LPSCI);

	DisableIRQ(DEMO_LPSCI_IRQn);

	if(status_flags & kLPSCI_IdleLineFlag && !(kLPSCI_RxDataRegFullFlag & status_flags))
		{
			LPSCI_ClearStatusFlags(UART0, kLPSCI_IdleLineFlag);
			idle++;
			if(idle > 0)
			{
				if(ringBuffRx.NumOfElements() > 3)
				{
					readed_data = true;
				}
				LPSCI_DisableInterrupts(DEMO_LPSCI, kLPSCI_IdleLineInterruptEnable);
				idle = 0;
			}
		}


	if (kLPSCI_RxDataRegFullFlag & status_flags)
	{
		if(DEMO_LPSCI->S1 & UART0_S1_RDRF_MASK)
		{
			//printf("new data\n");
			ringBuffRx.Write((uint8_t*)&DEMO_LPSCI->D, sizeof(DEMO_LPSCI->D));
			LPSCI_EnableInterrupts(DEMO_LPSCI, kLPSCI_IdleLineInterruptEnable);
		}
	}







	/*If there are data to send*/
//	if (kLPSCI_TxDataRegEmptyFlag & status_flags) {
//		ringBuffTx.Read(&data, 1);

		//LPSCI_WriteByte(DEMO_LPSCI, data);

		/* Disable TX interrupt If there are NO data to send */
//		if (ringBuffTx.NumOfElements() == 0)
//			LPSCI_DisableInterrupts(DEMO_LPSCI, kLPSCI_TxDataRegEmptyInterruptEnable);
//	}





	if(status_flags & kLPSCI_RxOverrunFlag)
	{
		//printf("kLPSCI_RxOverrunFlag\n");
		LPSCI_ClearStatusFlags(DEMO_LPSCI, kLPSCI_RxOverrunFlag);
	}


	EnableIRQ(DEMO_LPSCI_IRQn);
}

/*
 * @brief   Application entry point.
 */
int main(void) {
	lpsci_config_t config;

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();


	uint8_t d[2] = {0x0, 0xC2};
	uint8_t crc = get_crc8(d, 2);
	printf("crc = %x\n", crc);




	CLOCK_SetLpsci0Clock(0x1U);

	/*
	 * config.parityMode = kLPSCI_ParityDisabled;
	 * config.stopBitCount = kLPSCI_OneStopBit;
	 * config.enableTx = false;
	 * config.enableRx = false;
	 */
	LPSCI_GetDefaultConfig(&config);
	config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	config.enableTx = true;
	config.enableRx = true;

	LPSCI_Init(DEMO_LPSCI, &config, DEMO_LPSCI_CLK_FREQ);

	/* Send g_tipString out. */
	LPSCI_WriteBlocking(DEMO_LPSCI, g_tipString, sizeof(g_tipString));













	/* Enable RX interrupt. */

	LPSCI_EnableInterrupts(DEMO_LPSCI, kLPSCI_RxDataRegFullInterruptEnable);
	EnableIRQ(DEMO_LPSCI_IRQn);

	while (1) {

		// Wait for new line
		//while (!new_line_flag)
		//{};
		//new_line_flag = false; /* Clear new line flag */

		if(readed_data)
		{

			static uint8_t buf[255];
			int8_t count = ringBuffRx.NumOfElements();
			DisableIRQ(DEMO_LPSCI_IRQn);
			ringBuffRx.Read(buf, count);

			//printf("data: ");
			//for(int i = 0; i < count; i++ )
			//{
			//	printf("0x%x ", buf[i]);
			//}
			//printf("\n----\n");


			if(count == 5)
			{
				uint8_t cr [2] = {buf[1], buf[2]};
				if(get_crc8(cr, 2) == buf[4])
				{

				}
			}


			readed_data = false;
			EnableIRQ(DEMO_LPSCI_IRQn);
		}




		/* Copy data  from rxBuffer to txbuffer*/
		//uint16_t count = ringBuffRx.NumOfElements();
		//uint8_t buffer[count];
		//ringBuffRx.Read( buffer, count);


		/* Write new line to txHandler and enable Tx interrupt*/
		//ringBuffTx.Write(buffer, count);
		//LPSCI_EnableInterrupts(DEMO_LPSCI, kLPSCI_TxDataRegEmptyInterruptEnable);
	}
}
