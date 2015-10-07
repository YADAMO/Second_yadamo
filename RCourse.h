#pragma once

#include "ScenarioController.h"
#include "SFigureL.h"
#include "SLoopLine.h"
#include "Curve.h"
#include "SParkingP.h"

#define RSTART 340
#define RBC1 85
#define RC1 63
#define RAC1 200

class RCourse : public ScenarioController{
public:
	RCourse(LineTracer *lt, Curve *cv, Observer *ob);
	//フル実装版
	//LCourse(LineTracer *lt, Curve *cv, Observer *ob, SFigureL *sf, SLoopLine *sl, SParking *sp);

	virtual bool run();

private:
	LineTracer *lineTracer;
	Curve *curve;
	Observer *observer;
	//SFigureL *figureL;
	//SLoopLine *loopline;
	//SParking *parking;
	double distance;
};