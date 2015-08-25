#pragma once

#include "PID.h"
#include "Drive.h"
#include "ColorSensor.h"

#define RIGHT 1
#define LEFT -1

using namespace ev3api;

class LineTracer{
public:
	LineTracer(Drive *dr, ColorSensor *col);
	void trace(double speed, int edge);
	void setTarget(int tar);
	int getTarget();

private:
	int target;
	PID *brightPid;
	Drive *drive;
	ColorSensor *colorSensor;
};