#pragma once

#include "DistanceMeter.h"

DistanceMeter::DistanceMeter(Motor *rm, Motor *lm){
	Rmotor = rm;
	Lmotor = lm;
	rDistance = 0;
	lDistance = 0;
	init();
}

void DistanceMeter::init(){
	lOffset = Lmotor->getCount();
	rOffset = Rmotor->getCount();
}

double DistanceMeter::getDistance(){
	const double DPOD = 0.06981317F;
	double distance = 0.0;

	rDistance = Rmotor->getCount() - rOffset;
	lDistance = Lmotor->getCount() - lOffset;

	distance = (rDistance + lDistance)/2;
	distance = distance * DPOD;

	return distance;
}
