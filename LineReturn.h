#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"

class LineReturn : public ScenarioController{
public:
	LineReturn(LineTracer *lt, Observer *ob, Drive *dr);
    virtual bool run();

private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
};
