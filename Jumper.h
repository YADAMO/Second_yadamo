#pragma once
#include "LineTracer.h"
#include "Stepper.h"
#include "Driver.h"
#include "Distance.h"
#include "StepDetector.h"
#include "SpeedPid.h"
#include "ColorDetector.h"

class Jumper
{
public:
	Jumper(Driver *argDriver, LineTracer *argLineTracer, Stepper *argStepper, Distance *argDistance, StepDetector *sd, SpeedPid *sp, ColorDetector *cd);
	~Jumper();
	bool run();
private:
	int runtime;
	int phase;
	float dbuf;
	Stepper *stepper;
	Driver *driver;
	LineTracer *lineTracer;
	Distance *distance;
	StepDetector *stepDetector;
	SpeedPid *speedPid;
	ColorDetector *colorDetector;
};
