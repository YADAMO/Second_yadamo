
#include "LineTracer.h"

LineTracer::LineTracer(Drive *dr, Color *col){
	drive = dr;
	color = col;
	brightPid = new PID(1.8, 0.03, 0.0025); // speed = 40
	// brightPid = new PID(4, 0, 0);
	black = 0;
	white = 0;
	target = 0;
	bright = 0;
}

int LineTracer::trace(double speed, int edge, int target){
	// int bright = calcCorrection();
	bright = color->getReflect();
	// int angle = brightPid->calc(target, bright);
	int angle = brightPid->calc(this->target, bright);

	drive->_drive(angle* edge, (int)speed);
	return angle;
}

int LineTracer::traceReturn(double speed, int edge, int target){
	// int bright = calcCorrection();
	bright = color->getReflect();
	// int angle = brightPid->calc(target, bright);
	int angle = brightPid->calc(this->target, bright);
	if(angle > 15)	angle = 15;
	else if(angle < -30)	angle = -30;

	drive->_drive(angle* edge, (int)speed);
	return angle;
}

int LineTracer::traceFfixed(double speed, int edge, int target){
	// int bright = calcCorrection();
	bright = color->getReflect();
	// int angle = brightPid->calc(target, bright);
	int angle = brightPid->calc(this->target, bright);

	drive->driveFfixed(angle* edge, (int)speed);
	return angle;
}

int LineTracer::calcCorrection(){
	double rate = (color->getReflect() - (double)black) / ((double)white - (double)black);

	return (int)rate * 200;
}

int LineTracer::getBright(){
	return bright;
}

void LineTracer::changeGain(float p, float i, float d){
	brightPid->changeGain(p, i, d);
}
