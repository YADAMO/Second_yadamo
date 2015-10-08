#pragma once

#include "Motor.h"
#include "PID.h"
#include "Observer.h"

#define MAX_FRONT_RANGLE 500
#define MAX_FRONT_LANGLE -500
#define TURN_BASE_SPEED 70

class Drive{
public:
	Drive(Motor *rm, Motor *lm, Motor *fm, Observer *ob);
	int drive(int angle, double spd);
	void _drive(int turn, int speed);
	void driveFfixed(int turn, int speed);
	int calcFront(int angle);
	int calcRear(int angle);
	void straight(int speed);
	void init();
	int calcSteerAngle(int turn);
	int calcSteerAngleFfixed(int8_t right, int8_t left);
	void curve(int right, int left);
	bool turn(double angle, char d, int speed);
	void turnReset();
	void opeF(int angle);
	void init(bool lock);
private:

	Motor *Rmotor;
	Motor *Lmotor;
	Motor *Fmotor;
	Observer *observer;
	PID *speedPid = new PID(0.29, 0, 0.06);
	PID *anglePid = new PID(0.05, 0.005, 0.005);
	int steerAngle;
	int32_t rightOffset, leftOffset;
	char turnPhase;
	int turnRuntime;
	int32_t turnrightOffset;
	int32_t turnleftOffset;
};