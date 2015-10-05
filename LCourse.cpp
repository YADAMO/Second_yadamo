#include "LCourse.h"

LCourse::LCourse(LineTracer *lt, Curve *cv, Observer *ob){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	distance = 0;

}

bool LCourse::run(){
	switch(phase){
		case 0:
			lineTracer->traceFfixed(20, RIGHT, 0);
			if(observer->getDistance() > 480){
				changeScenario();
			}
		break;

		case 1:
			if(curve->runPid(10, -465, 77, R)){
				changeScenario();
				lineTracer->changeGain(1.5, 0, 0.02);
			}
		break;

		case 2:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() > 800){
				changeScenario();
			}
		break;

		case 3:
			return true;
		break;
	}

	return false;

}
