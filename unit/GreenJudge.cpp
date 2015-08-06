#pragma once

#include "GreenJudge.h"

GreenJudge::GreenJudge(ColorSensor *colorSensor){
	this->colorSensor = colorSensor;
	this->interval = 1;
}

bool GreenJudge::judge(){
	if(colorSensor->getColorNumber() == 3){
		return true;
	}else{
		return false;
	}
}