/*
 * Mytimer.cpp
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#include <Mytimer.h>

Mytimer::Mytimer(uint32_t ms)
{
	pitIsrFlag = false;
	PIT_GetDefaultConfig(&pitConfig);
	PIT_Init(PIT, &pitConfig);
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(ms * 1000, PIT_SOURCE_CLOCK));
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT_IRQ_ID);
	PIT_StartTimer(PIT, kPIT_Chnl_0);

}

Mytimer::~Mytimer() {
	// TODO Auto-generated destructor stub
}

void PIT_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
    //pitIsrFlag = true;
}

void Mytimer::timer_handler()
{
	if(pitIsrFlag)
	{
		//call function
		printf("timer\n");
		pitIsrFlag = false;
	}
}
