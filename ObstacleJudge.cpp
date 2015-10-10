
#include "ObstacleJudge.h"

ObstacleJudge::ObstacleJudge(Sonic *son){
	this->sonic = son;
	interval = 1;
	obstacledistance = 30; //障害物判定閾値[cm]
}

bool ObstacleJudge::judge(){
	if(sonic->getDistance() <= obstacledistance){
		return true;
	}else{
		return false;
	}
}

void ObstacleJudge::setDistance(int distance){
	obstacledistance = distance;
}
