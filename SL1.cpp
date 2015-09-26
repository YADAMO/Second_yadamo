#include "SL1.h"

SL1::SL1(Drive *dr, Observer *ob, Motor *fm){
	drive = dr;
	observer = ob;
	Fmotor = fm;
	disOffset = 0;
	right = 0;
	left = 0;
	front = 0;
	distance = 0;
	phase = 0;
}

bool SL1::run(int ri, int lf, int32_t fr, int32_t dis){
	switch(phase){
		case 0:
			disOffset = observer->getDistance();
			Fmotor->setRotate((-observer->Fangle + fr), 100, false);
			phase++;
		break;
		case 1:
			drive->curve(ri, lf);
			if((observer->getDistance() - disOffset) > dis){
				phase++;
			}
		break;
		case 2:
			Fmotor->setRotate(observer->Fangle, 100, false);
			return true;
		break;
	}
	return false;
}
