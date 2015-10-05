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
	int traceFfixed(double speed, int edge, int target);
	int traceReturn(double speed, int edge, int target);
	void changeGain(float p, float i, float d);
	int calcCorrection();
	uint8_t getTarget();
	uint8_t black;
	uint8_t white;
	uint8_t target;
	int bright;
	int getBright();

private:
	PID *brightPid;
	Drive *drive;
	Color *color;
};
