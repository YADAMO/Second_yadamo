#pragma once

#include "Motor.h"
#include "PID.h"

class Drive{
public:
	Drive(Motor *rm, Motor *lm, Motor *fm);
	void drive(int angle, double spd);
private:
	int calcFront(int angle);
	int calcRear(int angle);

	Motor *Rmotor;
	Motor *Lmotor;
	Motor *Fmotor;
	PID *speedPid = new PID(0.001, 0.29, 0, 0.06);
	PID *anglePid = new PID(0.001, 0.29, 0, 0.06);
	int32_t Rrad, Lrad;
};