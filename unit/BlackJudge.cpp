#pragma once

#include "BlackJudge.h"

BlackJudge::BlackJudge(ColorSensor *colorSensor){
	this->colorSensor = colorSensor;
}

bool BlackJudge::judge(){
	if(colorSensor->getColorNumber() == 1){
		return true;
	}else{
		return false;
	}
}
