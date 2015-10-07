#pragma once

#include "WhiteJudge.h"
#include "BlackJudge.h"
#include "GreenJudge.h"
#include "ObstacleJudge.h"
#include "TouchJudge.h"
#include "DistanceMeter.h"
#include "SpeedMeter.h"
#include "Motor.h"

class Observer{
public:
	Observer(Color *cl, ObstacleJudge *oj,
			TouchJudge *tj, DistanceMeter *dm,
			Motor *rm, Motor *lm, Motor *fm);

	void update();
	bool isStep();
	bool isBlack();
	bool isWhite();
	bool isGreen();
	bool isTouch();
	bool isObstacle();
	double getDistance();
	double getSpeed();
	int getRuntime();
	colorid_t judgeColor();

	long RangleBuf[5];
	long LangleBuf[5];
	int Fangle;

private:
	Color *color;
	ObstacleJudge *obstacleJudge;
	TouchJudge *touchJudge;
	DistanceMeter *distanceMeter;
	SpeedMeter *speedMeter = new SpeedMeter();
	Motor *Rmotor;
	Motor *Lmotor;
	Motor *Fmotor;

	bool is_Step, is_Obstacle, is_Touch, is_Black, is_White, is_Green;
	double distance, speed;
	double buffer[5];

	long runtime;

};
