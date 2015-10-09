#pragma once

#include "ScenarioController.h"
#include "SFigureL.h"
#include "SLoopLine.h"
#include "Curve.h"
#include "SParkingP.h"
#include "BlackDetecter"

#define RST1 390 	//最初の直線
#define RBC1 40 	//１番目カーブ前の減速
#define RC1 70 		//１番目カーブ
#define RAC1 50 	//１番目カーブ後のライン復帰
#define RST2 80 	//１番目カーブ後の直線
#define RC2A 60 	//２番目カーブの前半 左カーブ
#define RC2B 45 	//２番目カーブの後半 右カーブ
#define RAC2 30 	//２番目カーブ後半のライン復帰
#define RST3 100 	//２番目カーブ後の直線


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