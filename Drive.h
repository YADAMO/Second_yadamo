#pragma once

#include "Motor.h"
#include "PID.h"
#include "SpeedMeter.h"

#define MAX_STEERING_ANGLE  270
#define TURN_BASE_SPEED 70

class Drive{
public:
	Drive(Motor *rm, Motor *lm, Motor *fm, SpeedMeter *sp);
	void drive(int angle, double spd);
	void drive(int turn, int speed);
	int calcSteerAngle(int right, int left);
private:
	int calcFront(int angle);
	int calcRear(int angle);

	Motor *Rmotor;
	Motor *Lmotor;
	Motor *Fmotor;
	SpeedMeter *speedMeter;
	PID *speedPid = new PID(0.001, 0.29, 0, 0.06);
	PID *anglePid = new PID(0.001, 0.29, 0, 0.06);
	int steerAngle;
	int32_t Rrad, Lrad;
};