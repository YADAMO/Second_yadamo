
#include "LineTracer.h"

LineTracer::LineTracer(Drive *dr, Color *col){
	drive = dr;
	color = col;
	brightPid = new PID(0.001, 0.05, 0.05, 0.05);
	target = 0;
}

int LineTracer::trace(double speed, int edge){
	int bright = color->getReflect();
	// int angle = brightPid->calc(target, bright);
	int angle = 0;

	if(bright > target){
		angle = 60;
	}else if(bright < target){
		angle = -60;
	}
	if(angle > 90){
		angle = 90;
	}else if(angle < -90){
		angle = -90;
	}

	return drive->drive(angle * edge , speed);
	// return angle;
}


void LineTracer::setTarget(int tar){
	target = tar;
}

int LineTracer::getTarget(){
	return target;
}
