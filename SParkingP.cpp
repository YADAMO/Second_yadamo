
#include "SParkingP.h"

SParkingP::SParkingP(Observer *ob, Drive *dr, Curve *cv){
	observer = ob;
	drive = dr;
	curve = cv;
	distance = 0;
}

void SParkingP::changeScenario(){
	phase++;
	distance = observer->getDistance();
}

bool SParkingP::run(){
	bool end = false;
	switch(phase){
		case 0:
			if(curve->run(6, -530, -40, R, -10)){
				changeScenario();
			}
			break;
		case 1:
			if(curve->run(0, 0, -3, R, -10)){
				changeScenario();
			}
			break;
		case 2:
			if(curve->run(3, 500, -13, L, -5)){
				changeScenario();
			}
			break;
		case 3:
			if(curve->run(4, -400, 5, R, 7)){
				changeScenario();
			}
			break;
		case 4:
			if(curve->run(0, 0, 0, R, 0)){
				end = true;
			}
		break;
		default:
			break;
	}
	return end;
}
