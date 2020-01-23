/*
 * Mytimer.h
 *
 *  Created on: 23. 1. 2020
 *      Author: ferom
 */

#ifndef MYTIMER_H_
#define MYTIMER_H_

#include "fsl_pit.h"
#include "stdint.h"
#include "stdio.h"

#define PIT_IRQ_ID PIT_IRQn
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

class Mytimer {
public:
	Mytimer(uint32_t us);
	virtual ~Mytimer();
	volatile bool pitIsrFlag;
	void timer_handler();
	//void PIT_IRQ_HANDLER(void);

private:
	pit_config_t pitConfig;
};

#endif /* MYTIMER_H_ */
