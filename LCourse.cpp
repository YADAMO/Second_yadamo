#include "LCourse.h"

LCourse::LCourse(LineTracer *lt, Curve *cv, Observer *ob, STwinBridge *st, LineReturn *lr){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	bridge = st;
	lineReturn = lr;
	distance = 0;
	phase = 0;
}

bool LCourse::run(){
	switch(phase){
		case 0:
			// lineTracer->changeGain(0.2, 0.01, 0.25);
            // lineTracer->fastrace(95, RIGHT, 0);
	

			// lineTracer->changeGain(0.14, 0.032, 0.4);
            // lineTracer->fastrace(40, RIGHT, 0);

   			// lineTracer->changeGain(0.125, 0.025, 0.5);
            // lineTracer->changeGain(0.28, 0.032, 0.4);
            // lineTracer->fastrace(25, RIGHT, 0);

			lineTracer->changeGain(0.9, 0, 0.02);
			lineTracer->trace(25, RIGHT, 0);


			if(observer->getDistance() - distance > LSTART){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 1:
			lineTracer->changeGain(0.9, 0, 0.02);
			lineTracer->trace(25, RIGHT, 0);
			// lineTracer->changeGain(0.125, 0.025, 0.5);
            // lineTracer->changeGain(0.28, 0.032, 0.4);
            // lineTracer->fastrace(25, RIGHT, 0);
            if(observer->getDistance() - distance > LBC1){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 2:
		// return true;
		curve->changeGain(1.5, 0, 0);
			if(curve->runPid(3, -495, LC1, R, 10)){
				changeScenario();
				lineTracer->changeGain(1.5, 0, 0.02);
				distance = observer->getDistance();
			}
		break;

		case 3:
		// return true;
			// lineTracer->traceReturn(15, RIGHT, 0);
			if(lineReturn->run(1)){
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
