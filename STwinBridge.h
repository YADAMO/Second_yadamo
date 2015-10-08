#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"
#include "Choilie.h"

class STwinBridge : public ScenarioController{
public:
	STwinBridge(LineTracer *lt, Observer *ob, Drive *dr, Choilie *ch);
    virtual bool run();

private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
	Choilie *choilie;
	int runtime;
	double distance;
};
