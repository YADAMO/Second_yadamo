#include "LCourse.h"

LCourse::LCourse(LineTracer *lt, Curve *cv, Observer *ob, STwinBridge *st){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	bridge = st;
	distance = 0;
}

bool LCourse::run(){
	switch(phase){
		case 0:
			// lineTracer->traceFfixed(20, RIGHT, 0);
			lineTracer->changeGain(0.5, 0.05, 0.03);
            lineTracer->fastrace(25, RIGHT, 0);
			if(observer->getDistance() - distance > LSTART){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 1:
			lineTracer->changeGain(0.5, 0.05, 0.03);
            lineTracer->fastrace(25, RIGHT, 0);
            if(observer->getDistance() - distance > LBC1){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 2:
			if(curve->runPid(10, -465, LC1, R)){
				changeScenario();
				lineTracer->changeGain(1.5, 0, 0.02);
				distance = observer->getDistance();
			}
		break;

		case 3:
			lineTracer->traceReturn(20, RIGHT, 0);
			if(observer->getDistance() > LAC1){
				changeScenario();
			}
		break;

		case 4:
			if(bridge->run()){
				changeScenario();
			}
		break;

		case 5:
		return true;
		break;
	}

	return false;

}
