#pragma once

#include "TouchJudge.h"

TouchJudge::TouchJudge(TouchSensor *touchSensor){
	this->touchSensor = touchSensor;
	interval = 1;
}

bool TouchJudge::judge(){
	if(touchSensor->isPressed() == true){
		return true;
	}else{
		return false;
	}
}
