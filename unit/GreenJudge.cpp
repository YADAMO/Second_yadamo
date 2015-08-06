#pragma once

#include "GreenJudge.h"

GreenJudge::GreenJudge(ColorSensor *colorSensor){
	this->colorSensor = colorSensor;
}

bool GreenJudge::judge(){
	if(colorSensor->getColorNumber() == 3){
		return true;
	}else{
		return false;
	}
}