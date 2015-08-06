#pragma once

#include "TouchJudge.h"

TouchJudge::TouchJudge(TouchSensor *touchSensor){
	this->touchSensor = touchSensor;
}

bool TouchJudge::judge(){
	if(touchSensor->isPressed() == true){
		return true;
	}else{
		return false;
	}
}
