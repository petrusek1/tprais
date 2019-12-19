/*
 * Timer.h
 *
 *  Created on: 9. 12. 2019
 *      Author: Daniel
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_


#include "fsl_pit.h"

class Timer {
public:
	Timer();
	~Timer();

	bool starTimer();
	bool setTime(uint64_t us);

private:
	pit_config_t m_config;
};



#endif /* TIMER_TIMER_H_ */
