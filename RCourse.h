#pragma once

#include "ScenarioController.h"
#include "SFigureL.h"
#include "SLoopLine.h"
#include "Curve.h"
#include "SParkingP.h"

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