#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"

class LineReturn : public ScenarioController{
public:
	LineReturn(LineTracer *lt, Observer *ob, Drive *dr);
    virtual bool run();
    bool run2(int dir);
    bool run(int dir);


private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
	int runtime;
	double reDis;
	int distance;
	int phase2;
	colorid_t color;
};
