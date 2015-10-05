#pragma once

#include "ScenarioController.h"
#include "LineTracer.h"
#include "Curve.h"
#include "Observer.h"
#include "STwinBridge.h"

class LCourse : public ScenarioController{
public:
	LCourse(LineTracer *lt, Curve *cv, Observer *ob, STwinBridge *st);
	virtual bool run();

private:
	LineTracer *lineTracer;
	Curve *curve;
	Observer *observer;
	STwinBridge *bridge;
	double distance;


};