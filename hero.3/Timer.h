//
// Created by vio on 8/14/17.
//

#ifndef HERO_TIMER_H
#define HERO_TIMER_H


#include <SDL2/SDL.h>

class Timer {
public:
	Timer();
	void Update(uint32_t ticks);

private:
	uint32_t prevTicks;
	uint32_t numUpdates;
};


#endif //HERO_TIMER_H
