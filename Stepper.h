#pragma once

#include "DistanceMeter.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"

class Stepper{
private:
	DistanceMeter *distanceMeter;
	Drive *drive;
	LineTracer *lineTracer;
	Observer *observer;
	int phase;
	int runtime;
	int stepSpeed;
	bool sflag;
public:
	Stepper(DistanceMeter *dm, Drive *dr, LineTracer *lt, Observer *obs);
	~Stepper();
	bool gridStep(int edge);
	bool run(int edge);
};