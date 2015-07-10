#include "SpeedMeter.h"

SpeedMeter::SpeedMeter(Distance *ds, Motor *mR, Motor *mL){
	distance = ds;
	motorR = mR;
	motorL = mL;
}

SpeedMeter::~SpeedMeter(){

}

float SpeedMeter::getSpeed(void){
	distance->init(motorR->getDiff().front(), motorL->getDiff().front());
	F32 dis = distance->getDistance();
	return -(dis * 66.67);
}
