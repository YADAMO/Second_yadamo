
#include "SParkingL.h"

SParkingL::SParkingL(LineTracer *lt, Observer *ob, Drive *dr){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	runtime = 0;
}

bool SParkingL::run(){
	bool end = false;
	switch(phase){
		case 0:
			drive->opeFRL(0, 0, 0);
			if(runtime > 500){
				changeScenario();
			}
			break;
		case 1:
			lineTracer->changeGain(1.4, 0, 0.03);
			lineTracer->trace(10, RIGHT, 0);
			if(distance - observer->getDistance() > 6){
				changeScenario();
				drive->init();
				drive->stop(false);
			}
			break;
		case 2:
			if(drive->turn(90, RIGHT, -15)){
				changeScenario();
				drive->init();
				drive->stop(false);
			}
			break;
		case 3:
			drive->curve(4, 4);
			if(distance - observer->getDistance() > 20){
				changeScenario();
				drive->init();
				drive->stop(false);
			}
			break;
		case 4:
			if(runtime > 4000){
				changeScenario();
				end = true;
			}
			break;
		case 5:
			drive->curve(0, 0);
			break;
		default:
			break;
	}
	runtime++;
	return end;
}

void SBarcode::changeScenario(){
	phase++;
	runtime = 0;
	distance = observer->getDistance();
}
