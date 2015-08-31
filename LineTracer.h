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
	int trace(double speed, int edge);
	void setTarget(uint8_t tar);
	uint8_t getTarget();

private:
	uint8_t target;
	PID *brightPid;
	Drive *drive;
	Color *color;
};
