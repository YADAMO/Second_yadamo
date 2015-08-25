#pragma once

#include "Motor.h"
#include "PID.h"
#include "Observer.h"

using namespace ev3api;

class Drive{
public:
	Drive(Motor *rm, Motor *lm, Motor *fm, Observer *obsvr);
	void drive(int angle, double spd);
private:
	int calcFront(int angle);
	int calcRear(int angle);

	Motor *Rmotor;
	Motor *Lmotor;
	Motor *Fmotor;
	Observer *observer;
	PID *speedPid;
	PID *anglePid;
	int32_t Rrad, Lrad;
};