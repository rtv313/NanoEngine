#include "TempMicro.h"

TempMicro::TempMicro() :startTime(0.0f), stopTime(false)
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
	if (stopTime == true)
		return startTime;

	return  (SDL_GetPerformanceCounter() - startTime) / frequency;

}

double TempMicro::stop()
{
	if (stopTime == false) {
		stopTime = true;
		startTime = (SDL_GetPerformanceCounter() - startTime) / frequency;
	}
	return startTime;
}

double TempMicro::frequency = SDL_GetPerformanceFrequency();