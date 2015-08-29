#pragma once

#include "PID.h"
#include "Drive.h"
#include "Color.h"

#define RIGHT 1
#define LEFT -1

class LineTracer{
public:
	LineTracer(Drive *dr, Color *col);
	int trace(double speed, int edge);
	void setTarget(int tar);
	int getTarget();

private:
	int target;
	PID *brightPid;
	Drive *drive;
	Color *color;
};