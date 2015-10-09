#pragma once

#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"
#include "ScenarioController.h"
#include "Stepper.h"
#include "Curve.h"
#include "BlackDetecter.h"

class SFigureL : public ScenarioController{
public:
	SFigureL(Drive *dr, LineTracer *lt, Observer *ob, Stepper *st, Curve *cv, BlackDetecter *bd);
    virtual bool run();
    void changeScenario();

private:
	Drive *drive;
	LineTracer *lineTracer;
	Observer *observer;
	Stepper *stepper;
	Curve *curve;
	BlackDetecter *blackDetecter;

	int runtime;
	double distance;
	int phase;
};
