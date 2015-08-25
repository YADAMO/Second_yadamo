#pragma once

#include "LineTracer.h"

LineTracer::LineTracer(Drive *dr, ColorSensor *col){
	drive = dr;
	colorSensor = col;
	brightPid = new PID(0.001, 0.29, 0, 0.06);
	target = 0;
}

void LineTracer::trace(double speed, int edge){
	int bright = colorSensor->getBrightness();
	int turn = brightPid->calc(target, bright);

	drive->drive(turn, speed);
}


void LineTracer::setTarget(int tar){
	target = tar;
}

int LineTracer::getTarget(){
	return target;
}
