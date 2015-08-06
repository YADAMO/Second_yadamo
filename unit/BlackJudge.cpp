#pragma once

#include "BlackJudge.h"

BlackJudge::BlackJudge(ColorSensor *colorSensor){
	this->colorSensor = colorSensor;
	this->interval = 1;
}

bool BlackJudge::judge(){
	if(colorSensor->getColorNumber() == 1){
		return true;
	}else{
		return false;
	}
}
