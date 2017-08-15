//
// Created by vio on 8/14/17.
//

#include <iostream>
#include "Timer.h"

Timer::Timer()
{
	this->prevTicks = 0;
}

void Timer::Update(uint32_t ticks)
{
	if (ticks - prevTicks > 1000) {
		if(prevTicks > 0) {
			std::cout << "FPS: " << numUpdates << std::endl;
		}
		numUpdates = 0;
		prevTicks = ticks;
	}
	numUpdates++;
}
