#pragma once

#include "Motor.h"

class DistanceMeter{
public:
	DistanceMeter();
	double calcDistance();

private:
	Motor *Rmotor;
	Motor *Lmotor;
	int32_t lOffset, rOffset;
	
}