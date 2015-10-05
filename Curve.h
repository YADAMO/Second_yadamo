#pragma once

#include "Drive.h"
#include "Observer.h"
#include "Motor.h"
#include <cstdint>
#include "Color.h"
#include "PID.h"
#include "LineTracer.h"

#define R 1
#define L -1

class Curve{
public:
	Curve(Drive *dr, Observer *ob, Motor *fm, Motor *rm, Motor *lm , Color *cl, LineTracer *ln);
	bool run(int ri, int lf, int32_t fr, int32_t dis);
	bool runPid(int dif, int32_t fr, int32_t dis, int dir);

private:
	Drive *drive;
	Observer *observer;
	Motor *Fmotor;
	Motor *Rmotor;
	Motor *Lmotor;
	Color *color;
	PID *pid;
	LineTracer *lineTracer;

	int32_t disOffset, distance;
	int right, left ,front;
	int phase;
	int bright, turn;
	int curveSP;
};
