
#include "LineTracer.h"

LineTracer::LineTracer(Drive *dr, Color *col){
	drive = dr;
	color = col;
	// brightPid = new PID(2.5, 0.03, 0.03); // speed = 40
	brightPid = new PID(3, 0.03, 0.03);

	target = 0;
}

int LineTracer::trace(double speed, int edge){
	uint8_t bright = color->getReflect();
	int angle = brightPid->calc(target, bright);
	if(angle > 90){
		angle = 90;
	}else if(angle < -90){
		angle = -90;
	}
	// drive->drive((int)angle * edge , speed);
	drive->_drive(angle* edge, (int)speed);
	return angle;
}


void LineTracer::setTarget(uint8_t tar){
	target = tar;
}

uint8_t LineTracer::getTarget(){
	return target;
}
