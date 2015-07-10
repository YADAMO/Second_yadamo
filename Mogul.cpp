#include "Mogul.h"

Mogul::Mogul(Driver *dr, LineTracer *lt, StepDetector *sd, Stepper *sp, Distance *ds, Pid *pd, ColorDetector *cd){
	driver = dr;
	lineTracer = lt;
	stepDetector = sd;
	stepper = sp;
	distance = ds;
	pid = pd;
	colorDetector = cd;
	phase = 0;
	runtime = 0;
	hillnum = 0;
	sflag = false;
}

Mogul::~Mogul(){

}

bool Mogul::run(){
	runtime += 3;
	switch(phase){
		case 0://段差に上る
			if(stepper->run(-1)){
				phase++;
				distance->init();
			}
			break;
		case 1://
			pid->changePid(0.15, 0.001, 0.02);
			lineTracer->lineTrace(50, LEFTEDGE);
			if(distance->getDistance() < -60){
				phase++;
				distance->init();
			}
			break;
		case 2:
			driver->drive(-40, 30);
			if(colorDetector->blackLineDetect()){
				phase++;
				distance->init();
			}
			break;
		case 3:
			driver->drive(100, 0);
			if(distance->getDiff() > 110){
				phase++;
				distance->init();
			}
			break;
		case 4:
			
			return true;
			break;

	}
	return false;
}
