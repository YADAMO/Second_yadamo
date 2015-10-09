#include "RCourse.h"

//フル実装版
// RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob, SFigureL *sf, SLoopLine *sl, SParkingP *sp){

RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob, SLoopLine *sl){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	// figureL = sf;
	loopLine = sl;
	// parking = sp;
	distance = 0;
}

bool RCourse::run(){
	switch(phase){
		case 0:
			lineTracer->changeGain(0.5, 0.04, 0.03);
            lineTracer->fastrace(30, LEFT, 0);
			if(observer->getDistance() - distance > RSTART){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 1:
			// lineTracer->changeGain(0.8, 0.045, 0.08);
            lineTracer->fastrace(15, LEFT, 0);
            if(observer->getDistance() - distance > RBC1){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 2:
			if(curve->runPid(10, 465, RC1, L)){
				changeScenario();
				lineTracer->changeGain(1.5, 0, 0.02);
				distance = observer->getDistance();
			}
		break;

		case 3:
			lineTracer->traceReturn(20, LEFT, 0);
			if(observer->getDistance() > RAC1){
				changeScenario();
			}
		break;

		case 4:
			return true;
		break;
	}

	return false;
}
