/*
COLOR_NONE 	無色
COLOR_BLACK 黒
COLOR_BLUE 	青
COLOR_GREEN 緑
COLOR_YELLOW 黄
COLOR_RED 	赤
COLOR_WHITE 白
COLOR_BROWN 茶
TNUM_COLOR 	識別できるカラーの数
*/

#include "Observer.h"

Observer::Observer(Color *cl,
	ObstacleJudge *oj, TouchJudge *tj, DistanceMeter *dm,
	Motor *rm, Motor *lm, Motor *fm){
	color = cl;
	obstacleJudge = oj;
	touchJudge = tj;
	distanceMeter = dm;
	Rmotor = rm;
	Lmotor = lm;
	Fmotor = fm;

	is_Step = false;
	is_Black = false;
	is_White = false;
	is_Green = false;
	is_Touch = false;
	is_Obstacle = false;

	distance = 0;
	speed = 0;

	for(int i = 0; i < 5; i++){
		buffer[i] = i;
		RangleBuf[i] = 0;
		LangleBuf[i] = 0;
	}

	runtime = 0;
	Fangle = Fmotor->getAngle();;

}

void Observer::update(){
	runtime += 1;

	if(runtime % obstacleJudge->getInterval() == 0){
		is_Obstacle = obstacleJudge->judge();
	}

	if(runtime % touchJudge->getInterval() == 0){
		is_Touch = touchJudge->judge();
	}

	// 毎回値入れる系
	distance = -distanceMeter->getDistance();
	speed = speedMeter->calcSpeed(distance);

	Fangle = Fmotor->getAngle();



	if(runtime % 100 == 0){
		for(int i = 0; i < 4; i++){
		buffer[i] = buffer[i+1];
		RangleBuf[i] = RangleBuf[i+1];
		LangleBuf[i] = LangleBuf[i+1];
		}
		buffer[4] = distance;
		RangleBuf[4] = Rmotor->getAngle();
		LangleBuf[4] = Lmotor->getAngle();
		// 段差判定
		is_Step = (buffer[0] == buffer[4]);

	}


}

colorid_t Observer::judgeColor(){
	return color->getColor();
}

bool Observer::isStep(){
	return is_Step;
}
bool Observer::isBlack(){
	return is_Black;
}
bool Observer::isWhite(){
	return is_White;
}
bool Observer::isGreen(){
	return is_Green;
}
bool Observer::isTouch(){
	return is_Touch;
}
bool Observer::isObstacle(){
	return is_Obstacle;
}
double Observer::getDistance(){
	return distance;
}
double Observer::getSpeed(){
	return speed;
}

int Observer::getRuntime(){
	return runtime;
}
