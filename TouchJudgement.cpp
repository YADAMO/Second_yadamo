#include "TouchJudgement.h"

TouchJudgement::TouchJudgement(TouchSensor *T){
	touchSensor = T;
	count = 0;
}

TouchJudgement::~TouchJudgement(void){

}

bool TouchJudgement::judge(){
	if(touchSensor->isPressed()){
		count++;
	}else{
		count = 0;
	}
	
	if(count == 10){
		return true;
	}
	return false;
}
