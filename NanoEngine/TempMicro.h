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
	 TempMicro();
	 ~TempMicro();
	 void start();
	 double stop();
	 double read();
};
#endif