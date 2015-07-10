#pragma once
#include "LineTracer.h"
#include "ColorDetector.h"
#include "Driver.h"
#include "Stepper.h"
#include "OffsetHolder.h"
#include "Distance.h"

using namespace ecrobot;

class Figure{
private:
	LineTracer *lineTracer;
	ColorDetector *colorDetector;
	Driver *driver;
	Stepper *stepper;
	OffsetHolder *offsetHolder;
	Distance *distance;
	int phase;
	int runtime;
	bool st;
	bool detected;
	float tmptarget;
	void changePhase();
public:
	Figure(LineTracer *argLineTracer, ColorDetector *argColorDetector, Driver *argDriver, Stepper *sp, OffsetHolder *of, Distance *dis);
	~Figure();
	bool run();
};
