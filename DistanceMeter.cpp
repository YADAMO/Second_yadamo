
#include "DistanceMeter.h"

DistanceMeter::DistanceMeter(Motor *rm, Motor *lm){
	Rmotor = rm;
	Lmotor = lm;
	rDistance = 0;
	lDistance = 0;
	init();
}

void DistanceMeter::init(){
	lOffset = Lmotor->getAngle();
	rOffset = Rmotor->getAngle();
}

double DistanceMeter::getDistance(){
	const double DPOD = 0.06981317F;
	double distance = 0.0;

	rDistance = Rmotor->getAngle() - rOffset;
	lDistance = Lmotor->getAngle() - lOffset;

	distance = (rDistance + lDistance)/2;
	distance = distance * DPOD * 3;

	return distance;
}
