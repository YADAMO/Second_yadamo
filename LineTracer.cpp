
#include "LineTracer.h"

LineTracer::LineTracer(Drive *dr, Color *col){
	drive = dr;
	color = col;
	brightPid = new PID(2, 0.03, 0.003); // speed = 40
	// brightPid = new PID(4, 0, 0);
	black = 0;
	white = 0;
	target = 0;
}

int LineTracer::trace(double speed, int edge, int target){
	// int bright = calcCorrection();
	int bright = color->getReflect();
	// int angle = brightPid->calc(target, bright);
	int angle = brightPid->calc(this->target, bright);

	drive->_drive(angle* edge, (int)speed);
	return angle;
}

int LineTracer::calcCorrection(){
	double rate = (color->getReflect() - (double)black) / ((double)white - (double)black);

	return (int)rate * 200;
}