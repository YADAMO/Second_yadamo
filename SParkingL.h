#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"

class SParkingL : public ScenarioController{
public:
	SParkingL(LineTracer *lt, Observer *ob, Drive *dr);
    virtual bool run();

private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
	int runtime;
	int phase;
	double distance;
	void changeFhase();
};
