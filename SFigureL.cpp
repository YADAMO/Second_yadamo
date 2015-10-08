
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
			if(stepper->run(1)){
				changeScenario();
				lineTracer->changeTarget(5);
			}
		break;

		case 1:
			lineTracer->changeGain(1.2, 0, 0.02);
			lineTracer->trace(15, RIGHT, 0);
			if(observer->getDistance() - distance > 15){
				changeScenario();
				drive->init(true);
			
			}
		break;

		// case 2:
		// 	drive->curve(0, 0);
		// 	if(runtime > 1000){
		// 		changeScenario();
		// 	}
		// break;

		case 2:
			lineTracer->changeGain(0.5, 0, 0.02);
			lineTracer->fastrace(6, RIGHT, 0);
			if(observer->getDistance() - distance > 14){
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

		case 4:
			if(runtime % 3 == 0){
				drive->curve(-1, -1);	
			}else{
				drive->curve(0, 0);
			}
			if(blackDetecter->onBlack()){
				changeScenario();
				// drive->init(false);
				lineTracer->backTarget();
			}
		break;

		case 5:
			drive->curve(2, 2);
			if(distance - observer->getDistance() > 4){
				changeScenario();
			}
		break;

		case 6:
			drive->curve(0, 0);
			if(runtime > 1000){
				changeScenario();
			}
		break;

		case 7:
			if(curve->run(-7, -15, -625, 17)){
				changeScenario();
				drive->init(true);
			}
			
		break;

		case 8:
			drive->curve(0, 0);
			if(runtime > 1000){
				changeScenario();
			}
		break;

		case 9:
			lineTracer->changeGain(1.2, 0, 0.02);
			lineTracer->trace(15, RIGHT, 0);
			if(observer->getDistance() - distance > 15){
				changeScenario();
				drive->init(true);
			}

		break;

		case 10:
			drive->curve(6,6);
			if(observer->isStep() && runtime > 1000){
				changeScenario();
			}
		break;

		case 11:
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
