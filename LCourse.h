#pragma once

#include "ScenarioController.h"
#include "LineTracer.h"
#include "Curve.h"
#include "Observer.h"
#include "STwinBridge.h"

#define LSTART 300
#define LBC1 180
#define LC1 77
#define LAC1 100


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