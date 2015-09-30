#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"

class Choilie : public ScenarioController{
public:
	Choilie(LineTracer *lt, Observer *ob, Drive *dr);
    virtual bool run();

private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
	int runtime;
};