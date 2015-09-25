#pragma once

#include "stdio.h"
#include "ev3api.h"

class Logger{
public:
	Logger();
	bool send();
	void addData(double data);
	void end();
private:
	double buff[16];
	int ptr;
	char sendData[1024];
	FILE *bt;
};
