/*
 * Mytimer.cpp
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#include <Mytimer.h>

Mytimer* Mytimer::instance = 0;


/*
 * @brief constructor of singleton object Mytimer
 */
Mytimer::Mytimer()
{
	pitIsrFlag = false;
	PIT_GetDefaultConfig(&pitConfig);
	PIT_Init(PIT, &pitConfig);

	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
	EnableIRQ(PIT_IRQ_ID);


}

Mytimer::~Mytimer() {
	// TODO Auto-generated destructor stub
}

/*
 * @brief IRQ handler for interupts from timer
 */
void PIT_IRQHandler(void)
{
	Mytimer* tim = Mytimer::get_instance();
    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
    tim->pitIsrFlag = true;
}

/*
 * @brief handling function for call timer
 */
void Mytimer::timer_handler()
{
	if(pitIsrFlag)
	{
		printf("timer\n");
		pitIsrFlag = false;
	}
}


/*
 * @brief function to start timer
 */
void Mytimer::start(uint32_t ms) {
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(ms * 1000, PIT_SOURCE_CLOCK));
	PIT_StartTimer(PIT, kPIT_Chnl_0);
}

/*
 * @brief function to pause timer
 */
void Mytimer::pause() {
	PIT_StopTimer(PIT, kPIT_Chnl_0);
}


/*
 * @brief function return pointer to instance of object Mytimer
 */
Mytimer* Mytimer::get_instance()
{
	if(instance == 0)
	{
		instance = new Mytimer();
	}
	return instance;
}
