
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
	blackDetecter->update();
	switch(phase) {
		case 0:
			if(stepper->run(1)){
				changeScenario();
				lineTracer->changeTarget(5);
			}
		break;

		case 1:
			lineTracer->changeGain(1.2, 0, 0.02);
			lineTracer->trace(12, RIGHT, 0);
			if(observer->getDistance() - distance > 12){
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
			lineTracer->changeGain(0.125, 0.025, 0.15);
			lineTracer->trace(10, RIGHT, 0);
			// lineTracer->changeGain(0.5, 0, 0.02);
			// lineTracer->fastrace(6, RIGHT, 0);
			if(observer->getDistance() - distance > 18){
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
			if(runtime % 900 == 0){
				drive->stop(false);
			}else{
				drive->curve(-2, -2);	

			}
			if(blackDetecter->onBlack()){
				changeScenario();
				drive->stop(false);
				lineTracer->backTarget();
			}
		break;

		case 5:
			drive->curve(2, 2);
			if(distance - observer->getDistance() > 4.5){
				changeScenario();
			}
		break;

		case 6:
			drive->curve(0, 0);
			if(runtime > 1000){
				changeScenario();
				drive->init(true);
				drive->Frotate(-700);

			}
		break;

		case 7:
			drive->curve(0, -5);
			if(observer->getDistance() - distance > 4.5){
				changeScenario();
				drive->init(true);
			}
		break;

		case 8:
			drive->curve(-1, -1);
			if(blackDetecter->onBlack()){
				drive->stop(false);
				changeScenario();
				drive->Frotate(-700);
			}
		break;

		case 9:
			drive->curve(0, -5);
			if(observer->getDistance() - distance > 4){
				changeScenario();
				drive->stop(false);
				drive->init(true);
			}
		break;

		case 10:

			drive->curve(-1, -1);
			if(observer->getDistance() - distance > 5){
				drive->stop(false);
				changeScenario();
				drive->Frotate(-700);
			}
		break;

		case 11:
			drive->curve(0, -4);
			if(blackDetecter->onBlack()){
				changeScenario();
				drive->stop(false);
			}
		break;

		case 12:
			drive->curve(0, -4);
			if(observer->getDistance() - distance > 4){
				changeScenario();
				drive->stop(false);
				drive->init(true);
			}
		break;

		case 13:
			lineTracer->changeGain(1.2, 0, 0.02);
			lineTracer->trace(12, RIGHT, 0);
			if(observer->getDistance() - distance > 15){
				changeScenario();
				drive->init(true);
			}
		break;

		case 14:
			drive->curve(6,6);
			if(observer->isStep() && runtime > 1000){
				changeScenario();
			}
		break;

		case 15:
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
