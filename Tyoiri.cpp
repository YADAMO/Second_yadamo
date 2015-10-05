#include "Tyoiri.h"

Tyoiri::Tyoiri(Drive *dr, Observer *ob){
	drive = dr;
	observer = ob;
	distance = 0;
}

bool Tyoiri::run(){
	switch(phase){
		case 0:
			distance = observer->getDistance();
			drive->init();
			changeScenario();
		break;

		case 1:
			drive->curve(100, 100);
			if(distance - observer->getDistance() > 17){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 2:
			drive->curve(-100, -100);
			if(observer->getDistance() - distance > 17){
				changeScenario();
			}
		break;

		case 3:
			return true;
		break;
	}

	return false;
}
