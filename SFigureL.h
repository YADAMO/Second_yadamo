#pragma once


#include "DistanceMeter.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"
#include "ScenarioController.h"
#include "Stepper.h"

class SFigureL : public ScenarioController{
public:
	SFigureL(DistanceMeter *dm, Drive *dr, LineTracer *lt, Observer *ob);
    virtual bool run() = 0;

private:
	
	DistanceMeter *distanceMeter;
	Drive *drive;
	LineTracer *lineTracer;
	Observer *observer;
	Stepper *stepper;

	int phase;
};
