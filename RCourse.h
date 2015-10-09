#pragma once

#include "ScenarioController.h"
#include "SFigureL.h"
#include "SLoopLine.h"
#include "Curve.h"
#include "SParkingP.h"

#define RSTART 340
#define RBC1 70
#define RC1 85
#define RAC1 100

class RCourse : public ScenarioController{
public:
	RCourse(LineTracer *lt, Curve *cv, Observer *ob, SLoopLine *sl);
	//フル実装版
	//RCourse(LineTracer *lt, Curve *cv, Observer *ob, SFigureL *sf, SLoopLine *sl, SParking *sp);

	virtual bool run();

private:
	LineTracer *lineTracer;
	Curve *curve;
	Observer *observer;
	//SFigureL *figureL;
	SLoopLine *loopLine;
	//SParking *parking;
	double distance;
};