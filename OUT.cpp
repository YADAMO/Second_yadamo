#include "OUT.h"

OUT::OUT(Basic *bs, Jumper *jp, GridRunner *gr, ParkingP *pP){
	basic = bs;
	jumper = jp;
	gridRunner = gr;
	parkingP = pP;
	phase = 0;
}

OUT::~OUT(){

}

bool OUT::run(){
	switch(phase){
		case 0:
			if(basic->runOUT()){
				phase++;
			}
			break;
		case 1:
			if(jumper->run()){
				phase++;
			}
			break;
		case 2:
			if(basic->runToGrid()){
				phase++;
			}
			break;
		case 3:
			if(gridRunner->run()){
				phase++;
			}
			break;
		case 4:
			if(basic->runToJump()){
				phase++;
			}
			break;
		case 5:
			if(jumper->run()){
				phase++;
			}
			break;
		case 6:
			if(basic->runToGarage()){
				phase++;
			}
			break;
		case 7:
			if(parkingP->run()){
				phase = 10;
			}
			break;
		case 10:
			phase = 0;
			return true;
			break;
	}
	return false;
}
