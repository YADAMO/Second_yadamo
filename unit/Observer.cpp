#pragma once

#include "Observer.h"

Observer::Observer(WhiteJudge &whiteJudge, BlackJudge &blackJudge, GreenJudge &greenJudge, ObstacleJudge &obstacleJudge, TouchJudge &touchJudge, DistanceMeter &distanceMeter, SpeedMeter &speedMeter){
	this->whiteJudge = &whiteJudge;
	this->blackJudge = &blackJudge;
	this->greenJudge = &greenJudge;
	this->obstacleJudge = &obstacleJudge;
	this->touchJudge = &touchJudge;
	this->distanceMeter = &distanceMeter;
	this->speedMeter = &speedMeter;

	this->is_Step = false;
	this->is_Black = false;
	this->is_White = false;
	this->is_Green = false;
	this->is_Touch = false;
	this->is_Obstacle = false;

	this->distance = 0;
	this->speed = 0;

	int i = 0;
	for(i = 0; i < 5; i++){
		buffer.push_back(0);
	}

	runtime = 0;

}
void Observer::update(){
	runtime++;
	if(runtime % whiteJudge->getInterval() == 0){
		is_White = whiteJudge->judge();
	}

	if(runtime % blackJudge->getInterval() == 0){
		is_Black = blackJudge->judge();
	}

	if(runtime % greenJudge->getInterval() == 0){
		is_Green = greenJudge->judge();
	}

	if(runtime % obstacleJudge->getInterval() == 0){
		is_Obstacle = obstacleJudge->judge();
	}

	if(runtime % touchJudge->getInterval() == 0){
		is_Touch = touchJudge->judge();
	}

	if(runtime % obstacleJudge->getInterval() == 0){
		is_Obstacle = obstacleJudge->judge();
	}

	if(runtime % 1 == 0){
		distance = distanceMeter->getDistance();
		speed = speedMeter->calcSpeed(distance);

		buffer.push_back(distance);
		buffer.pop_front();

		is_Step = (buffer.front() == distance);
	}


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
