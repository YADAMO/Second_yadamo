#pragma once

#include "WhiteJudge.h"
#include "BlackJudge.h"
#include "GreenJudge.h"
#include "ObstacleJudge.h"
#include "TouchJudge.h"
#include "DistanceMeter.h"
#include "SpeedMeter.h"

class Observer{
public:
	Observer(WhiteJudge *wj, BlackJudge *bj,
			GreenJudge *gj, ObstacleJudge *oj,
			TouchJudge *tj, DistanceMeter *dm);

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

private:
	WhiteJudge *whiteJudge;
	BlackJudge *blackJudge;
	GreenJudge *greenJudge;
	ObstacleJudge *obstacleJudge;
	TouchJudge *touchJudge;
	DistanceMeter *distanceMeter;
	SpeedMeter *speedMeter = new SpeedMeter();

	bool is_Step, is_Obstacle, is_Touch, is_Black, is_White, is_Green;
	double distance, speed;
	double buffer[5];
	long runtime;

};
