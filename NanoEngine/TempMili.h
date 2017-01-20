#ifndef __TEMP_MILI_H__
#define __TEMP_MILI_H__
#include "SDL/include/SDL.h" 


class TempMili {

private:
	double  startTime;
	bool stopTime;
public:

	TempMili() :startTime(0.0f),stopTime(false)
	{
	}

	~TempMili() 
	{
	}

	void start()
	{
		startTime = SDL_GetTicks();
		stopTime = false;
	}

	double read()
	{
		if (stopTime == true)
			return startTime;

		return SDL_GetTicks() - startTime;
	}

	double stop()
	{
		if (stopTime == false) {
			stopTime = true;
			startTime = SDL_GetTicks() - startTime;
		}
		return startTime;
	}

};
#endif