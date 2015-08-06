#pragma once

#include "SpeedMeter.h"

SpeedMeter::SpeedMeter(){
	preDistance = 0;
}

double SpeedMeter::calcSpeed(double dst){
	double deltDst = dst - preDistance;
	return deltDst * 1000;
}
