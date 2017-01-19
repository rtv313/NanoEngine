#pragma once
class TempMicro
{
private:
	double startTime;
	bool stopTime;

public:
	TempMicro();
	~TempMicro();

	void start();
	double read();
	double stop();

};

