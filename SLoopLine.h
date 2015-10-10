#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"
#include "Stepper.h"
#include "Curve.h"

class SLoopLine : public ScenarioController{
public:
	SLoopLine(LineTracer *lt, Observer *ob, Drive *dr, Stepper *st, Curve *cv);
	void changeScenario();
    virtual bool run();

private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
	Stepper *stepper;
	Curve *curve;
	double distance;
};