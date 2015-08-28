#pragma once

#include "DistanceMeter.h"

class SpeedMeter{
public:
	SpeedMeter();
	double calcSpeed(double dst);
private:
	double preDistance;

};
