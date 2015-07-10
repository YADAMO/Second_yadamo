#pragma once

#include "Driver.h"
#include "LineTracer.h"
#include "StepDetector.h"
#include "Stepper.h"
#include "Distance.h"
#include "Motor.h"
#include "ColorDetector.h"

class Mogul{
private:
	Driver *driver;
	LineTracer *lineTracer;
	StepDetector *stepDetector;
	Stepper *stepper;
	Distance *distance;
	Pid *pid;
	ColorDetector *colorDetector;
	int phase;
	int runtime;
	int hillnum;
	bool sflag;
public:
	Mogul(Driver *dr, LineTracer *lt, StepDetector *sd, Stepper *stepper, Distance *ds, Pid *pd, ColorDetector *cd);
	~Mogul();
	bool run();
};
