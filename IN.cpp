#include "IN.h"

IN::IN(Basic *bs, Mogul *mg, Figure *fg, ParkingL *pL){
	basic = bs;
	mogul = mg;
	figure = fg;
	parkingL = pL;
	phase = 0;
}

IN::~IN(){

}

bool IN::run(){
	switch(phase){
		case 0:
			if(basic->runIN(1)){
				phase++;
			}
			break;
		case 1:
			if(mogul->run()){
				phase++;
			}
			break;
		case 2:
			if(basic->runToFigure()){
				phase++;
			}
			break;
		case 3:
			if(parkingL->run()){
				phase++;
			}
			break;
		case 4:
			if(figure->run()){
				phase++;
			}
			break;
		case 5:
			return true;
			break;
	}
	return false;
}
