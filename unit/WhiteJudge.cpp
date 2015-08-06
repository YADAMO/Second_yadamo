#pragma once

#include "WhiteJudge.h"

WhiteJudge::WhiteJudge(ColorSensor *colorSensor){
	this->colorSensor = colorSensor;
	this->interval = 1;
}

bool WhiteJudge::judge(){
	if(colorSensor->getColorNumber() == 6){
		return true;
	}else{
		return false;
	}
}
