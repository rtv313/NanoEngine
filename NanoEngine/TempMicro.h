#ifndef __TEMP_MICRO_H__
#define  __TEMP_MICRO_H__
#include "SDL/include/SDL.h"

class TempMicro
{
private:
	double startTime;
	bool stopTime;

public:
	 static double  frequency;

	TempMicro():startTime(0.0f),stopTime(false)
	{
	}

	~TempMicro()
	{
	}

	void start()
	{
		startTime = SDL_GetPerformanceCounter();
		stopTime = false;
	}

	double read()
	{
		if (stopTime == true)
			return startTime;

		return  (SDL_GetPerformanceCounter() - startTime) / frequency;
	
	}

	double stop()
	{
		if (stopTime == false) {
			stopTime = true;
			startTime = (SDL_GetPerformanceCounter() - startTime)  / frequency;
		}
		return startTime;
	}
};

double TempMicro::frequency = SDL_GetPerformanceFrequency();

#endif