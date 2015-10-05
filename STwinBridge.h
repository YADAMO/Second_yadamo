#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"
#include "Tyoiri.h"

class STwinBridge : public ScenarioController{
public:
	STwinBridge(LineTracer *lt, Observer *ob, Drive *dr, Tyoiri *ty);
    virtual bool run();

private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
	Tyoiri *tyoiri;
	int runtime;
	double distance;
};
