
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
			if(curve->run(25, -400, -50, R, -10)){
				changeScenario();
			}
			break;
		case 1:
			if(curve->run(15, 300, -20, L, -7)){
				changeScenario();
			}
			break;
		case 2:
			if(curve->run(0, -200, 10, R, 7)){
				end = true;
			}
			break;
		default:
			break;
	}
	return end;
}