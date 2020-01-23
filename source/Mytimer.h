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
#include <fsl_debug_console.h>

#define PIT_IRQ_ID PIT_IRQn
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

class Mytimer {
public:
	static Mytimer* get_instance();
	virtual ~Mytimer();
	volatile bool pitIsrFlag;
	void timer_handler();
	void start(uint32_t ms);
	void pause();

private:
	pit_config_t pitConfig;
	Mytimer();
	static Mytimer* instance;
};

#endif /* MYTIMER_H_ */
