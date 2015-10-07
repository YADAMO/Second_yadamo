#include "RCourse.h"

//フル実装版
//LCourse::LCourse(LineTracer *lt, Curve *cv, Observer *ob, SFigureL *st, SLoopLine *sl, SParking *sp){

RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	//figureL = sf;
	//loopline = sl;
	//parking = sp;
	//distance = 0;
}

bool RCourse::run(){
	switch(phase){
		case 0:
			lineTracer->traceFfixed(20, RIGHT, 0);
			if(observer->getDistance() > 485){
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
			lineTracer->traceReturn(20, RIGHT, 0);
			if(observer->getDistance() > 700){
				changeScenario();
			}
		break;

		case 3:
		break;

		case 4:
		return true;
		break;
	}

	return false;

}
