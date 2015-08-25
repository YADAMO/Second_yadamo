#pragma once

#include "Drive.h"

Drive::Drive(Motor *rm, Motor *lm, Motor *fm, Observer *obsvr){
	Rmotor = rm;
	Lmotor = lm;
	Fmotor = fm;
	observer = obsvr;
	speedPid = new PID(0.001, 0.29, 0, 0.06);
	anglePid = new PID(0.001, 0.29, 0, 0.06);
	Rrad = Rmotor->getCount();
	Lrad = Lmotor->getCount();

}

void Drive::drive(int angle, double spd){
	int speed = speedPid->calc(spd, observer->getSpeed());

	int Rpwm = speed + calcRear(angle);
	int Lpwm = speed;

	Rmotor->setPWM(Rpwm);
	Lmotor->setPWM(Lpwm);
	Fmotor->setPWM(calcFront(angle));
}


int Drive::calcFront(int angle){
	double result = angle /90.0 * 60.0;

	return (int)result;
}

int Drive::calcRear(int angle){
	double pi = 3.14;
	double w = 12;//車幅(cm)
	double r = 4.1;//後輪の半径(cm)

	int needdiff = (int)(2 * pi * w * (angle / 360));
	int targetrad = (int)((needdiff * 360)/(2 * pi * r));

	int raddiff = (Rmotor->getCount()-Rrad) - (Lmotor->getCount()-Lrad);

	return anglePid->calc(targetrad, raddiff);
}
