#pragma once

#include "StepDetector.h"
#include "LineTracer.h"
#include "Driver.h"
#include "Distance.h"

class Stepper{
private:
	StepDetector *stepDetector;
	LineTracer *lineTracer;
	Driver *driver;
	Pid *pid;
	Distance *distance;
	int phase;
	int runtime;
	int stepSpeed;
	bool sflag;
public:
	Stepper(StepDetector *sd, LineTracer *lt, Driver *dr,Pid *pd, Distance *dis);
	~Stepper();
	bool gridStep(int edge);
	bool run(int edge);
};
