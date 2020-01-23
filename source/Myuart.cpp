/*
 * Myuart.cpp
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#include <Myuart.h>


My_uart::My_uart() : ringBuffRx(rxBufferData, RING_BUF_SIZE), ringBuffTx(txBufferData, RING_BUF_SIZE) {
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
	if(instance == nullptr)
	{

		instance = new My_uart();
	}
	return instance;
}

/*
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

*/	/*If there are data to send*/
//	if (kLPSCI_TxDataRegEmptyFlag & status_flags) {
//		ringBuffTx.Read(&data, 1);

		//LPSCI_WriteByte(DEMO_LPSCI, data);

		/* Disable TX interrupt If there are NO data to send */
//		if (ringBuffTx.NumOfElements() == 0)
//			LPSCI_DisableInterrupts(DEMO_LPSCI, kLPSCI_TxDataRegEmptyInterruptEnable);
//	}/


/*


	if(status_flags & kLPSCI_RxOverrunFlag)
	{
		//printf("kLPSCI_RxOverrunFlag\n");
		LPSCI_ClearStatusFlags(DEMO_LPSCI, kLPSCI_RxOverrunFlag);
	}


	EnableIRQ(DEMO_LPSCI_IRQn);
}*/
