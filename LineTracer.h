#pragma once

#include "PID.h"
#include "Drive.h"
#include "Color.h"
#include <cstdint>

#define RIGHT 1
#define LEFT -1

class LineTracer{
public:
	LineTracer(Drive *dr, Color *col);
	int trace(double speed, int edge, int target);
	int calcCorrection();
	uint8_t getTarget();
	uint8_t black;
	uint8_t white;
	uint8_t target;

private:
	PID *brightPid;
	Drive *drive;
	Color *color;
};
