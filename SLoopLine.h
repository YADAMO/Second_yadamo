#pragma once

#include "ScenarioController.h"

class SLoopLine : public ScenarioController{
public:
	SLoopLine(LineTracer *lt, Observer *ob, Drive *dr);
    virtual bool run();

private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
	int runtime;
};