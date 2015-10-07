#pragma once

#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"
#include "ScenarioController.h"
#include "Stepper.h"
#include "Curve.h"

class SFigureL : public ScenarioController{
public:
	SFigureL(Drive *dr, LineTracer *lt, Observer *ob, Stepper *st, Curve *cv);
    virtual bool run();
    void changeScenario();

private:
	Drive *drive;
	LineTracer *lineTracer;
	Observer *observer;
	Stepper *stepper;
	Curve *curve;

	int runtime;
	double distance;
	int phase;
};
