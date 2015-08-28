
#include "SpeedMeter.h"

SpeedMeter::SpeedMeter(){
	preDistance = 0;
}

double SpeedMeter::calcSpeed(double dst){
	double deltDst = dst - preDistance;
	preDistance = dst;
	return deltDst * 1000;
}
