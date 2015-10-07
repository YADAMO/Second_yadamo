
#include "SFigureL.h"

SFigureL::SFigureL(Drive *dr, LineTracer *lt, Observer *ob, Stepper *st, Curve *cv){
	drive = dr;
	lineTracer = lt;
	observer = ob;
	stepper = st;
	curve = cv;
	phase = 0;
	runtime = 0;
	distance = 0;
}

bool SFigureL::run(){
	switch(phase) {
		case 0:
			lineTracer->changeGain(1.5, 0, 0.02);
			lineTracer->trace(20, LEFT, 0);
			if(observer->isStep() && runtime > 800){
				changeScenario();
				runtime = 0;
			}
			runtime++;
		break;

		case 1:
			if(stepper->run(-1)){
				changeScenario();
			}
		break;

		case 2:
			lineTracer->trace(20, LEFT, 0);
			if(observer->getDistance() - distance > 25){
				changeScenario();
			}
		break;

		case 3:
			if(curve->runPid(10, -490, 30, R)){
				changeScenario();
			}
			
		break;

		case 4:
			lineTracer->trace(20, LEFT, 0);
			if(observer->getDistance() - distance > 30){
				changeScenario();
			}
		break;

		case 5:
			return true;
		break;
	}
	return false;
}

void SFigureL::changeScenario(){
	phase++;
	runtime = 0;
	distance = observer->getDistance();

}
