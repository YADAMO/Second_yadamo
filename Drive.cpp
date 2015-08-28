
#include "Drive.h"

Drive::Drive(Motor *rm, Motor *lm, Motor *fm){
	Rmotor = rm;
	Lmotor = lm;
	Fmotor = fm;
	Rrad = Rmotor->getAngle();
	Lrad = Lmotor->getAngle();

}

int Drive::calcSteerAngle(int right, int left){
	int angle = right - left;
	if(angle >= 127)  angle = 127;
	if(angle <= -128) angle = -128;

	return angle*4;
}

void Drive::drive(int angle, double spd){
	// int speed = speedPid->calc(spd, observer->getSpeed());
	int speed = (int)spd;
	// int Rpwm = speed + calcRear(angle);
	int Rpwm = speed;
	int Lpwm = speed;

	Rmotor->setSpeed(Rpwm);
	Lmotor->setSpeed(Lpwm);
	Fmotor->setSpeed(calcFront(angle));
}

void Drive::drive(int turn, int speed){
  int count = Fmotor->getAngle();
  steerAngle = 0;
  int right, left;
  
  right = -turn + speed;
  left = turn + speed;
  if(right >= 127)	right = 127;
  if(right <= -128)	right = -128;
  if(left >= 127)	left = 127;
  if(left <= -128)	left = -128;
  
  Lmotor->setSpeed(left);
  Rmotor->setSpeed(right);

  steerAngle = calcSteerAngle(right, left);

  if(turn > 0){//左旋回  steerAngle負
    if(count > steerAngle){
	  if(-turn - TURN_BASE_SPEED <= -128)	Fmotor->setSpeed(-128);
	  else Fmotor->setSpeed(-turn - TURN_BASE_SPEED);
    }else{
      Fmotor->setSpeed(0);
    }
  }else if(turn < 0){//右旋回 steerAngle正
    if(count < steerAngle){
	  if(-turn + TURN_BASE_SPEED >= 127)	Fmotor->setSpeed(127);
	  else Fmotor->setSpeed(-turn + TURN_BASE_SPEED);
    }else{
      Fmotor->setSpeed(0);
    }
  }else{
    if(count > 0){
	  if(-turn - TURN_BASE_SPEED <= -128)	Fmotor->setSpeed(-128);
	  else Fmotor->setSpeed(-turn - TURN_BASE_SPEED);
    }else if(count < 0){
	  if(-turn + TURN_BASE_SPEED >= 127)	Fmotor->setSpeed(127);
	  else Fmotor->setSpeed(-turn + TURN_BASE_SPEED);
    }else{
      Fmotor->setSpeed(0);
    }
  }
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
