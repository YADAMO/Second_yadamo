#pragma once

#include "WhiteJudge.h"
#include "BlackJudge.h"
#include "GreenJudge.h"
#include "ObstacleJudge.h"
#include "TouchJudge.h"
#include "DistanceMeter.h"
#include "SpeedMeter.h"

#include <list>

class Observer{
public:
	Observer(WhiteJudge *whiteJudge, BlackJudge *blackJudge, GreenJudge *greenJudge, ObstacleJudge *obstacleJudge, TouchJudge *touchJudge, DistanceMeter *distanceMeter);

	void update();
	bool isStep();
	bool isBlack();
	bool isWhite();
	bool isGreen();
	bool isTouch();
	bool isObstacle();
	double getDistance();
	double getSpeed();

private:
	WhiteJudge *whiteJudge;
	BlackJudge *blackJudge;
	GreenJudge *greenJudge;
	ObstacleJudge *obstacleJudge;
	TouchJudge *touchJudge;
	DistanceMeter *distanceMeter;
	SpeedMeter *speedMeter;

	bool is_Step, is_Obstacle, is_Touch, is_Black, is_White, is_Green;
	double distance, speed;
	std::list<double> buffer;
	long runtime;

};