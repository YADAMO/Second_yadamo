#pragma once

#include "ObstacleJudge.h"

ObstacleJudge::ObstacleJudge(SonarSensor *sonarSensor){
	this->sonarSensor = sonarSensor;
	interval = 1;
	obstacledistance = 20; //障害物判定閾値[cm]
}

bool ObstacleJudge::judge(){
	if(sonarSensor->getDistance() <= obstacledistance){
		return true;
	}else{
		return false;
	}
}

void ObstacleJudge::setDistance(int distance){
	obstacledistance = distance;
}
