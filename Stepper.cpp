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
			lineTracer->changeGain(1.0, 0, 0.02);
			lineTracer->trace(10, edge, 0);

			if(observer->isStep() && runtime > 800){
				drive->init();
				changeFhase();
			}
			runtime++;
		break;

		case 1:
			drive->curve(10, 10);

			if(distance - observer->getDistance() > 5){
				changeFhase();
			}
		break;

		case 2:
			drive->curve(-25, -25);
			if(observer->getDistance() - distance > 23){
				changeFhase();
			}
		break;

		case 3:
			return true;
		break;
	}
	return false;
}

void Stepper::changeFhase(){
	phase++;
	runtime = 0;
	distance = observer->getDistance();
}
