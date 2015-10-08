
#include "SFigureL.h"

SFigureL::SFigureL(Drive *dr, LineTracer *lt, Observer *ob, Stepper *st, Curve *cv, BlackDetecter *bd){
	drive = dr;
	lineTracer = lt;
	observer = ob;
	stepper = st;
	curve = cv;
	blackDetecter = bd;
	phase = 0;
	runtime = 0;
	distance = 0;
}

bool SFigureL::run(){
	switch(phase) {
		case 0:
			lineTracer->changeGain(1.5, 0, 0.02);
			lineTracer->trace(20, RIGHT, 0);
			if(observer->isStep() && runtime > 800){
				changeScenario();
			}
			
		break;

		case 1:
			if(stepper->run(1)){
				changeScenario();
				lineTracer->changeTarget(5);
			}
		break;

		case 2:
			lineTracer->changeGain(1.5, 0, 0.02);
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > 15){
				changeScenario();
				drive->init(true);
			
			}
		break;

		case 3:
			drive->curve(0, 0);
			if(runtime > 1000){
				changeScenario();
			}
		break;

		case 3:
			lineTracer->changeGain(0.5, 0, 0.02);
			lineTracer->fastrace(7, RIGHT, 0);
			if(observer->getDistance() - distance > 10){
				changeScenario();
				
			}
		break;

		case 4:
			drive->curve(0, 0);
			if(runtime > 1000){
				changeScenario();
			}
		break;

		case 5:
			drive->curve(-1, -1);
			if(blackDetecter->onBlack()){
				changeScenario();
				// drive->init(false);
				lineTracer->backTarget();
			}
		break;

		case 6:
			drive->curve(2, 2);
			if(distance - observer->getDistance() > 4){
				changeScenario();
			}
		break;

		case 7:
			drive->curve(0, 0);
			if(runtime > 1000){
				changeScenario();
			}
		break;

		case 8:
			if(curve->run(-7, -15, -600, 11)){
				changeScenario();
				// drive->init(true);
			}
			
		break;

		case 9:
			drive->curve(8,8);
			if(observer->isStep() && runtime > 1000){
				changeScenario();
			}
		break;

		case 10:
			return true;
		break;
	}
	runtime++;
	return false;
}

void SFigureL::changeScenario(){
	phase++;
	runtime = 0;
	distance = observer->getDistance();

}
