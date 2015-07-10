#include "Distance.h"

Distance::Distance(Motor *rm, Motor *lm){
	motorR = rm;
	motorL = lm;
	rightOffset = 0;
	leftOffset = 0;
}

// Distance::Distance(S32 L, S32 R){
// 	rightOffset = R;
// 	leftOffset = L;
// }

Distance::~Distance(){

}

void Distance::init(void){
	leftOffset = motorL->getCount();
	rightOffset = motorR->getCount();
}

void Distance::init(S32 mR, S32 mL){
	leftOffset = mL;
	rightOffset = mR;
}

F32 Distance::getDistance(void){
	static const F32 DPOD = 0.06981317F;
	
	distanceL = motorL->getCount() - leftOffset;
	distanceR = motorR->getCount() - rightOffset;
	
	distance = F32(distanceL + distanceR) / 2.0;
	distance = distance * DPOD;
	
	return distance;
}

int Distance::getDiff(void){
	distanceL = motorL->getCount() - leftOffset;
	distanceR = motorR->getCount() - rightOffset;
	
	// distance = distanceL - distanceR;
	if(distanceL - distanceR >= 0){
		distance = distanceL - distanceR;
	}else{
		distance = distanceR - distanceL;
	}

	return distance;
}
