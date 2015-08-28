#pragma once

#include "Motor.h"

class DistanceMeter{
public:
	DistanceMeter(Motor *rm, Motor *lm);
	void init();
	double getDistance();

private:
	Motor *Rmotor;
	Motor *Lmotor;
	int32_t lOffset, rOffset;
	double rDistance, lDistance;


};
