#pragma once

#include "Drive.h"
#include "Observer.h"
#include "Motor.h"
#include <cstdint>

class SL1{
public:
	SL1(Drive *dr, Observer *ob, Motor *fm);
	bool run(int ri, int lf, int32_t fr, int32_t dis);

private:
	Drive *drive;
	Observer *observer;
	Motor *Fmotor;
	int32_t disOffset, distance;
	int right, left ,front;
	int phase;
};
