#pragma once

#include "ScenarioController.h"
#include "LineTracer.h"
#include "Curve.h"
#include "Observer.h"
#include "STwinBridge.h"
#include "LineReturn.h"

#define LSTART 300
#define LBC1 172
#define LC1 72
#define LAC1 100


class LCourse : public ScenarioController{
public:
	LCourse(LineTracer *lt, Curve *cv, Observer *ob, STwinBridge *st, LineReturn *lr);
	virtual bool run();

private:
	LineTracer *lineTracer;
	Curve *curve;
	Observer *observer;
	STwinBridge *bridge;
	LineReturn *lineReturn;

	double distance;


};