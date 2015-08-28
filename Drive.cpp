
#include "Drive.h"

Drive::Drive(Motor *rm, Motor *lm, Motor *fm){
	Rmotor = rm;
	Lmotor = lm;
	Fmotor = fm;
	Rrad = Rmotor->getAngle();
	Lrad = Lmotor->getAngle();

}

void Drive::drive(int angle, double spd){
	// int speed = speedPid->calc(spd, observer->getSpeed());

	// int Rpwm = speed + calcRear(angle);
	// int Lpwm = speed;

	// Rmotor->setSpeed(Rpwm);
	// Lmotor->setSpeed(Lpwm);
	// Fmotor->setSpeed(calcFront(angle));
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

	int raddiff = (Rmotor->getAngle()-Rrad) - (Lmotor->getAngle()-Lrad);

	return anglePid->calc(targetrad, raddiff);
}
