#pragma once

#include "Motor.h"
#include "PID.h"
#include "Observer.h"

#define MAX_FRONT_RANGLE 500
#define MAX_FRONT_LANGLE -500

class Drive{
public:
	Drive(Motor *rm, Motor *lm, Motor *fm, Observer *ob);
	int drive(int angle, double spd);
	int calcFront(int angle);
	int calcRear(int angle);
private:

	Motor *Rmotor;
	Motor *Lmotor;
	Motor *Fmotor;
	Observer *observer;
	PID *speedPid = new PID(0.001, 0.29, 0, 0.06);
	PID *anglePid = new PID(0.001, 0.5, 0.5, 0.5);
};