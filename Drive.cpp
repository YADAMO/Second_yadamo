
#include "Drive.h"

Drive::Drive(Motor *rm, Motor *lm, Motor *fm, Observer *ob){
	Rmotor = rm;
	Lmotor = lm;
	Fmotor = fm;
	observer = ob;

}

int Drive::drive(int angle, double spd){
	// int speed = speedPid->calc(spd, observer->getSpeed());
	int Rpwm = spd + calcRear(angle);
	int Lpwm = spd;
	int Fpwm = calcFront(angle);

	Rmotor->setSpeed(Rpwm);
	Lmotor->setSpeed(Lpwm);
	Fmotor->setSpeed(Fpwm);
	return Fpwm;
}


int Drive::calcFront(int angle){
	int targetDegrees = 0;
	if(angle > 0){
		targetDegrees = MAX_FRONT_RANGLE * ((double)angle/90.0);
	}else if(angle < 0){
		targetDegrees = MAX_FRONT_LANGLE * ((double)angle/90.0);
	}else if(angle == 0){
		targetDegrees = 0;
	}

	if(observer->Fangle > MAX_FRONT_RANGLE){
		return -30;
	}else if(observer->Fangle < MAX_FRONT_LANGLE){
		return 30;
	}
	return 	(targetDegrees - observer->Fangle) /10;
}

int Drive::calcRear(int angle){
	double pi = 3.14;
	double w = 12.0;//車幅(cm)
	double r = 4.1;//後輪の半径(cm)

	double needdiff = (2 * pi * w * ((double)angle / 360.0));
	double targetrad = ((needdiff * 360.0)/(2.0 * pi * r));

	int raddiff = (observer->RangleBuf[4] - observer->RangleBuf[0]) - (observer->LangleBuf[4] - observer->LangleBuf[0]);

	return anglePid->calc(targetrad, (double)raddiff);
	
}
