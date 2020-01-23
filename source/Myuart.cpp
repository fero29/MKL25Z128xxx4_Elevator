/*
 * Myuart.cpp
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#include <Myuart.h>

My_uart* My_uart::instance = 0;


void My_uart::uart_write(uint8_t *data, size_t size)
{
	LPSCI_WriteBlocking(DEMO_LPSCI, data, size);
}

void My_uart::ring_get_readed_data(uint8_t *data, size_t size)
{
	ringBuffRx.Read(data, size);
}

void My_uart::ring_write(uint8_t *data, size_t size)
{
	ringBuffRx.Write(data, size);
}

size_t My_uart::ring_get_readed_size()
{
	return ringBuffRx.NumOfElements();
}

My_uart::My_uart() : ringBuffRx(rxBufferData, RING_BUF_SIZE)/*, ringBuffTx(txBufferData, RING_BUF_SIZE)*/ {
	readed_data = false;
	idle = 0;

	CLOCK_SetLpsci0Clock(0x1U);

	/*
	 * config.parityMode = kLPSCI_ParityDisabled;
	 * config.stopBitCount = kLPSCI_OneStopBit;
	 * config.enableTx = false;
	 * config.enableRx = false;
	 */
	LPSCI_GetDefaultConfig(&config);
	config.baudRate_Bps = BAUD;
	config.enableTx = true;
	config.enableRx = true;

	LPSCI_Init(DEMO_LPSCI, &config, DEMO_LPSCI_CLK_FREQ);

	LPSCI_EnableInterrupts(DEMO_LPSCI, kLPSCI_RxDataRegFullInterruptEnable);
	EnableIRQ(DEMO_LPSCI_IRQn);


}

My_uart::~My_uart() {
}



My_uart* My_uart::get_instance()
{
	if(instance == 0)
	{
		instance = new My_uart();
	}
	return instance;
}


extern "C" void DEMO_LPSCI_IRQHandler(void)
{
	My_uart* u = My_uart::get_instance();

	uint32_t status_flags = LPSCI_GetStatusFlags(DEMO_LPSCI);

	DisableIRQ(DEMO_LPSCI_IRQn);

	if(status_flags & kLPSCI_IdleLineFlag && !(kLPSCI_RxDataRegFullFlag & status_flags))
		{
			LPSCI_ClearStatusFlags(UART0, kLPSCI_IdleLineFlag);
			u->idle++;
			if(u->idle > 0)
			{
				if(u->ring_get_readed_size() > COUNT_IDLE_BAUDS)
				{
					u->readed_data = true;
				}
				LPSCI_DisableInterrupts(DEMO_LPSCI, kLPSCI_IdleLineInterruptEnable);
				u->idle = 0;
			}
		}


	if (kLPSCI_RxDataRegFullFlag & status_flags)
	{
		if(DEMO_LPSCI->S1 & UART0_S1_RDRF_MASK)
		{
			//printf("new data\n");
			u->ring_write((uint8_t *)&DEMO_LPSCI->D, sizeof(DEMO_LPSCI->D));
			LPSCI_EnableInterrupts(DEMO_LPSCI, kLPSCI_IdleLineInterruptEnable);
		}
	}



	if(status_flags & kLPSCI_RxOverrunFlag)
	{
		printf("kLPSCI_RxOverrunFlag\n");
		LPSCI_ClearStatusFlags(DEMO_LPSCI, kLPSCI_RxOverrunFlag);
	}


	EnableIRQ(DEMO_LPSCI_IRQn);
}


