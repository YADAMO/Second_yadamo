#include "Figure.h"

Figure::Figure(LineTracer *argLineTracer, ColorDetector *argColorDetector, Driver *argDriver, Stepper *sp, OffsetHolder *of, Distance *dis){
	lineTracer = argLineTracer;
	colorDetector = argColorDetector;
	driver = argDriver;
	stepper = sp;
	offsetHolder = of;
	distance = dis;
	phase = 1;
	runtime = 0;
	detected = false;
	st = false;
	tmptarget = 0;
}

Figure::~Figure(){
}

void Figure::changePhase(){
	phase++;
	runtime = 0;
	distance->init();
	driver->straightInit();
}

bool Figure::run(){
	st = false;

	switch(phase){
		case 1:
		if(stepper->run(RIGHTEDGE)){
			lineTracer->setTarget((tmptarget + offsetHolder->getBlack() * 3) / 4);
			changePhase();
		}else{
			tmptarget = lineTracer->getTarget();
		}
		break;

		case 2:
		if(distance->getDistance() < -15){
			lineTracer->setTarget(tmptarget);
			lineTracer->changePid(0.15, 0.001, 0.02);
			changePhase();
		}
		lineTracer->lineTrace(30, RIGHTEDGE);
		break;

		case 3:
		if(distance->getDistance() < -10){
			changePhase();
		}
		colorDetector->blackLineDetect();
		lineTracer->lineTrace(30, LEFTEDGE);
		break;

		case 4:
		if(colorDetector->blackLineDetect()){
			driver->straight(0);
			changePhase();
		}else{
			lineTracer->lineTrace(30, LEFTEDGE);
		}
		break;

		case 5:
		if(runtime > 1000){
			changePhase();
		}
		driver->turn(80);
		break;

		case 6:
		if(distance->getDiff() > 245){
			changePhase();
		}
		driver->drive(35, 40);
		break;

		case 7:
		if(distance->getDistance() < -40){
			changePhase();
		}
		lineTracer->lineTrace(30, LEFTEDGE);
		break;

		case 8:
		if(distance->getDiff() > 650){
			changePhase();
		}
		driver->drive(35, 40);
		break;

		case 9:
		if(distance->getDistance() < - 40){
			changePhase();
		}
		driver->straight(35);
		break;

		case 10:
		driver->straight(0);
		st = true;
		break;
	}
	runtime += 3;
	return st;
}
