#pragma once

#include "WhiteJudge.h"

WhiteJudge::WhiteJudge(ColorSensor *colorSensor){
	this->colorSensor = colorSensor;
}

bool WhiteJudge::judge(){
	if(colorSensor->getColorNumber() == 6){
		return true;
	}else{
		return false;
	}
}
