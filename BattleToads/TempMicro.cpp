#include "TempMicro.h"
#include "SDL/include/SDL.h"



TempMicro::TempMicro()
{
}


TempMicro::~TempMicro()
{
}
void TempMicro::start()
{
	startTime = SDL_GetPerformanceCounter();
	stopTime = false;
}
double TempMicro::read()
{
	if (stopTime) {
		return startTime;
	}
	return startTime - SDL_GetPerformanceCounter();
}
double TempMicro::stop()
{
	stopTime = true;
	startTime = startTime - SDL_GetPerformanceCounter();
	return startTime;
}