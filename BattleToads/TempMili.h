#include "SDL/include/SDL.h" 

class TempMili {

private:
	float  startTime;

public:

	TempMili() :startTime(0.0f)
	{}

	void start()
	{

		startTime = SDL_GetTicks();
	}

	float stop()
	{
		startTime = SDL_GetTicks();
		return startTime;
	}

	float read()
	{
		return SDL_GetTicks() - startTime;
	}

};
