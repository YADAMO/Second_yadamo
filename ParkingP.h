#pragma once
#include "LineTracer.h"
#include "Driver.h"
#include "ColorDetector.h"
#include "Distance.h"

class ParkingP{
private:
	LineTracer *lineTracer;
	Driver *driver;
	ColorDetector *colorDetector;
	Distance *distance;
	int runtime;
	int phase;
	void changePhase();
public:
	ParkingP(LineTracer *argLineTracer, Driver *argDriver, ColorDetector *cd, Distance *dis);
	~ParkingP();
	bool run();
};
