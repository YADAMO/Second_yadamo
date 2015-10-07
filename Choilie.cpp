#include "Choilie.h"

Choilie::Choilie(Drive *dr, Observer *ob){
	drive = dr;
	observer = ob;
	distance = 0;
}

bool Choilie::run(){
	switch(phase){
		case 0:
			distance = observer->getDistance();
			drive->init();
			changeScenario();
		break;

		case 1:
			drive->curve(100, 100);
			if(distance - observer->getDistance() > 18){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 2:
			drive->curve(-100, -100);
			if(observer->getDistance() - distance > 18){
				changeScenario();
			}
		break;

		case 3:
			return true;
		break;
	}

	return false;
}
