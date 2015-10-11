#pragma once

#include "ev3api.h"
#include "ScenarioController.h"
#include "SFigureL.h"
#include "SLoopLine.h"
#include "Curve.h"
#include "SParkingP.h"
#include "BlackDetecter.h"
#include "Drive.h"
#include "LineReturn.h"

#define RST1 385 	//最初の直線
#define RBC1 30 	//１番目カーブ前の減速
#define RC1 68 		//１番目カーブ
#define RAC1 20 	//１番目カーブ後のライン復帰
#define RST2 80 	//１番目カーブ後の直線

#define RC2A 53 	//２番目カーブの前半 左カーブ
#define CTOC 7		//前半カーブと後半カーブの間
#define RC2B 55 	//２番目カーブの後半 右カーブ
#define RAC2 30 	//２番目カーブ後半のライン復帰


#define RBCE 30 	//エッジ切り替え前の減速
#define RCE 10 		//エッジ切り替え
#define RACE 50 	//エッジ切り替え後の直進

#define RBC3 30		//３番目カーブ前の減速
#define RC3 70		//３番目カーブ
#define RAC3 40		//３番目カーブ後のライン復帰

					//FigureL
					//LoopLine

#define RBESC 10	//黒検知後の黒地帯脱出
#define RST4 115	//黒検知後の直線

#define RBC4 8		//帰り道カーブ前の減速
#define RC4 66		//帰り道カーブ
#define RAC4 30		//帰り道カーブ後のライン復帰
#define RST5 250	//帰り道カーブ後の直線

#define RBPP 30		//縦列駐車前の減速

					//ParkingP

class RCourse : public ScenarioController{
public:
	RCourse(LineTracer *lt, Curve *cv, Observer *ob, BlackDetecter *bd, Drive *dr, SFigureL *fl, SLoopLine *ll, SParkingP *pp, LineReturn *lr);
	void changeScenario();
	virtual bool run();

private:
	LineTracer *lineTracer;
	Curve *curve;
	Observer *observer;
	BlackDetecter *blackdetecter;
	Drive *drive;
	SFigureL *figureL;
	SLoopLine *loopLine;
	SParkingP *parkingP;
	LineReturn *lineReturn;
	int runtime;
	double distance;
};