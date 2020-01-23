/*
 * Myuart.cpp
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#include <Myuart.h>

My_uart* My_uart::instance = 0;


/*
 * @brief function to write data on UART
 */
void My_uart::uart_write(uint8_t *data, size_t size)
{
	LPSCI_WriteBlocking(DEMO_LPSCI, data, size);
}

/*
 * @brief function get readed data from uart, saved in ring buffer
 */
void My_uart::ring_get_readed_data(uint8_t *data, size_t size)
{
	ringBuffRx.Read(data, size);
}

/*
 * @brief function to save data to ring buffer
 */
void My_uart::ring_write(uint8_t *data, size_t size)
{
	ringBuffRx.Write(data, size);
}

/*
 * @brief function to get readed data in ring buffer
 */
size_t My_uart::ring_get_readed_size()
{
	return ringBuffRx.NumOfElements();
}

/*
 * @brief Constructor of object My_uart which handle UART0
 */
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


/*
 * @brief function return pointer to instance, this object is singleton
 */
My_uart* My_uart::get_instance()
{
	if(instance == 0)
	{
		instance = new My_uart();
	}
	return instance;
}


/*
 * @brief IRQ handler for uart0, it wait for data and when comes idle flag, set flag readed_data
 */
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
			u->ring_write((uint8_t *)&DEMO_LPSCI->D, sizeof(DEMO_LPSCI->D));
			LPSCI_EnableInterrupts(DEMO_LPSCI, kLPSCI_IdleLineInterruptEnable);
		}
	}

	if(status_flags & kLPSCI_RxOverrunFlag)
	{
		//printf("kLPSCI_RxOverrunFlag\n");
		LPSCI_ClearStatusFlags(DEMO_LPSCI, kLPSCI_RxOverrunFlag);
	}

	if(status_flags & kLPSCI_NoiseErrorFlag)
	{
		printf("kLPSCI_NoiseErrorFlag\n");
		LPSCI_ClearStatusFlags(DEMO_LPSCI, kLPSCI_NoiseErrorFlag);
	}

	if(status_flags & kLPSCI_FramingErrorFlag)
	{
		printf("kLPSCI_FramingErrorFlag\n");
		LPSCI_ClearStatusFlags(DEMO_LPSCI, kLPSCI_FramingErrorFlag);
	}

	if(status_flags & kLPSCI_ParityErrorFlag)
	{
		printf("kLPSCI_ParityErrorFlag\n");
		LPSCI_ClearStatusFlags(DEMO_LPSCI, kLPSCI_ParityErrorFlag);
	}

	if(status_flags & kLPSCI_LinBreakFlag)
	{
		printf("kLPSCI_LinBreakFlag\n");
		LPSCI_ClearStatusFlags(DEMO_LPSCI, kLPSCI_LinBreakFlag);
	}

	EnableIRQ(DEMO_LPSCI_IRQn);
}


