
#include "Drive.h"

Drive::Drive(Motor *rm, Motor *lm, Motor *fm, Observer *ob){
	Rmotor = rm;
	Lmotor = lm;
	Fmotor = fm;
	observer = ob;
	rightOffset = 0;
	leftOffset = 0;

}

int Drive::calcSteerAngle(int8_t right, int8_t left){
  int angle = right - left;
  if(angle >= 100)  angle = 100;
  if(angle <= -100) angle = -100;

  return angle*4;
}

int Drive::drive(int angle, double spd){
	// int speed = speedPid->calc(spd, observer->getSpeed());
	int diff = calcRear(angle);
	int Rpwm = spd + diff;
	int Lpwm = spd - diff;
	int Fpwm = calcFront(angle);

	Rmotor->setSpeed(Rpwm);
	Lmotor->setSpeed(Lpwm);
	Fmotor->setSpeed(Fpwm);
	return Fpwm;
}

void Drive::_drive(int turn, int speed){
  int32_t count = observer->Fangle;
  steerAngle = 0;
  int right, left;
  
  right = -speed - turn;
  left = -speed + turn;
  if(right >= 100)	right = 100;
  if(right <= -100)	right = -100;
  if(left >= 100)	left = 100;
  if(left <= -100)	left = -100;
  
  Lmotor->setSpeed(left);
  Rmotor->setSpeed(right);
 
  // Fmotor->setSpeed(calcFront(turn));
  steerAngle = calcSteerAngle(right, left);
  if(turn > 0){//左旋回  steerAngle負
    if(count > steerAngle){
	  if(-turn - TURN_BASE_SPEED <= -100)	Fmotor->setSpeed(-100);
	  else Fmotor->setSpeed(-turn - TURN_BASE_SPEED);
    }else{
      Fmotor->setSpeed(0);
    }
  }else if(turn < 0){//右旋回 steerAngle正
    if(count < steerAngle){
	  if(-turn + TURN_BASE_SPEED >= 100)	Fmotor->setSpeed(100);
	  else Fmotor->setSpeed(-turn + TURN_BASE_SPEED);
    }else{
      Fmotor->setSpeed(0);
    }
  }else{
    if(count > 0){
	  if(-turn - TURN_BASE_SPEED <= -100)	Fmotor->setSpeed(-100);
	  else Fmotor->setSpeed(-turn - TURN_BASE_SPEED);
    }else if(count < 0){
	  if(turn + TURN_BASE_SPEED >= 100)	Fmotor->setSpeed(100);
	  else Fmotor->setSpeed(turn + TURN_BASE_SPEED);
    }else{
      Fmotor->setSpeed(0);
    }
  }
}


int Drive::calcFront(int angle){
	int targetDegrees = 0;
	if(angle > 0){
		targetDegrees = 500 * ((double)angle/90.0);
	}else if(angle < 0){
		targetDegrees = -500 * ((double)angle/90.0);
	}else if(angle == 0){
		targetDegrees = 0;
	}

	if(observer->Fangle > MAX_FRONT_RANGLE){
		return -30;
	}else if(observer->Fangle < MAX_FRONT_LANGLE){
		return 30;
	}
	return ((targetDegrees - observer->Fangle) /20);
}

int Drive::calcRear(int angle){
	double pi = 3.14;
	double w = 12.0;//車幅(cm)
	double r = 4.1;//後輪の半径(cm)

	double needdiff = (2 * pi * w * ((double)angle / 360.0));
	double targetrad = ((needdiff * 360.0)/(2.0 * pi * r))/3;//最後の/3は1:3

	int raddiff = (observer->RangleBuf[4] - observer->RangleBuf[0]) - (observer->LangleBuf[4] - observer->LangleBuf[0]);

	return anglePid->calc(targetrad, (double)raddiff);
	
}

void Drive::init(){
	rightOffset = Rmotor->getAngle();
	leftOffset = Lmotor->getAngle();

}

void Drive::straight(int speed){
	int turn = (Rmotor->getAngle() - rightOffset) - (Lmotor->getAngle() - leftOffset);
	
	int right = -turn/2 - speed;
	int left = turn/2 - speed;
	if(right >= 100)	right = 100;
	if(right <= -100)	right = -100;
	if(left >= 100)	left = 100;
	if(left <= -100)	left = -100;

	int handle = Fmotor->getAngle();
	if(handle >= 100)	handle = 126;
	if(handle <= -100)	handle = -100;
  
	Lmotor->setSpeed(left);
	Rmotor->setSpeed(right);
  	// Fmotor->setSpeed(-handle);
  	Fmotor->setRotate(turn*8, 100, false);
}
