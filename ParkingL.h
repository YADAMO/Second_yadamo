#pragma once
#include "LineTracer.h"
#include "Driver.h"
#include "StepDetector.h"
#include "Distance.h"

class ParkingL{
private:
	LineTracer *lineTracer;
	Driver *driver;
	StepDetector *stepDetector;
	Distance *distance;
	int runtime;
	int phase;
	void changePhase();
public:
	ParkingL(LineTracer *argLineTracer, Driver *argDriver, StepDetector *sd, Distance *dis);
	~ParkingL();
	bool run();
};
