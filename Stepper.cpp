#include "Stepper.h"


Stepper::Stepper(Drive *dr, LineTracer *lt, Observer *obs){
	drive = dr;
	lineTracer = lt;
	observer = obs;
	
	phase = 0;
	runtime = 0;
	distance = 0;
}

bool Stepper::run(int edge){
	switch(phase){
		case 0:
			lineTracer->changeGain(0.9, 0, 0.02);
			lineTracer->trace(14, edge, 0);
			if(observer->isStep() && runtime > 800){
				drive->init();
				changeFhase();
			}
		break;

		case 1:
			drive->curve(10, 10);
			if(distance - observer->getDistance() > 6){
				changeFhase();
			}
		break;

		case 2:
			drive->curve(-23, -23);
			if(observer->getDistance() - distance > 20){
				changeFhase();
			}
		break;

		case 3:
			drive->curve(0, 0);
			if(runtime > 1000){
				changeFhase();
			}
		break;

		case 4:
			phase = 0;
			runtime = 0;
			return true;
			

		break;
	}
	runtime++;
	return false;
}

bool Stepper::gRun(int edge){
	switch(phase){
		case 0:
			lineTracer->changeGain(0.9, 0, 0.02);
			lineTracer->trace(14, edge, 0);
			if(observer->isStep() && runtime > 800){
				drive->init();
				changeFhase();
			}
		break;

		case 1:
			drive->curve(10, 10);
			if(distance - observer->getDistance() > 7){
				changeFhase();
			}
		break;

		case 2:
			drive->curve(-25, -25);
			if(observer->getDistance() - distance > 9){
				changeFhase();
			}
		break;

		case 3:
			lineTracer->changeGain(0.9, 0, 0.02);
			lineTracer->trace(12, edge, 0);
			if(observer->isStep() && runtime > 1500){
				drive->init();
				changeFhase();
			}
		break;

		case 4:
			drive->curve(10, 10);
			if(distance - observer->getDistance() > 7){
				changeFhase();
			}
		break;

		case 5:
			drive->curve(-25, -25);
			if(observer->getDistance() - distance > 9.5){
				changeFhase();
			}
		break;

		case 6:
			drive->curve(0, 0);
			if(runtime > 1000){
				changeFhase();
			}
		break;

		case 7:
			phase = 0;
			runtime = 0;
			return true;
			

		break;
	}
	runtime++;
	return false;
}

bool Stepper::sRun(){
	switch(phase){
		case 0:
			drive->opeFRL(0, -4, -4);
			if(observer->isStep() && runtime > 800){
				drive->init();
				changeFhase();
			}
		break;

		case 1:
			drive->curve(10, 10);
			if(distance - observer->getDistance() > 7){
				changeFhase();
			}
		break;

		case 2:
			drive->curve(-25, -25);
			if(observer->getDistance() - distance > 9){
				changeFhase();
			}
		break;

		case 3:
			drive->curve(-4, -4);
			if(observer->isStep() && runtime > 1500){
				drive->init();
				changeFhase();
			}
		break;

		case 4:
			drive->curve(10, 10);
			if(distance - observer->getDistance() > 7){
				changeFhase();
			}
		break;

		case 5:
			drive->curve(-25, -25);
			if(observer->getDistance() - distance > 9.5){
				changeFhase();
			}
		break;

		case 6:
			drive->curve(0, 0);
			if(runtime > 1000){
				changeFhase();
			}
		break;

		case 7:
			phase = 0;
			runtime = 0;
			return true;
			

		break;
	}
	runtime++;
	return false;
}

void Stepper::changeFhase(){
	phase++;
	runtime = 0;
	distance = observer->getDistance();
}
