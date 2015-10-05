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
			if(curve->runPid(10, -465, 76, R)){
				changeScenario();
			}
		break;

		case 2:
			lineTracer->traceFfixed(20, RIGHT, 0);
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
