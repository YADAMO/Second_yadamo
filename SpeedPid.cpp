#include "SpeedPid.h"

SpeedPid::SpeedPid(SpeedMeter *sm){
    delta = 0.003; //処理周期：現在1msec

    kp = 5; //ストレート
    ki = 20;//ストレート
    // kd = 0.05;//ストレート
    kd = 0.0;
    diff[0] = 0;
	diff[1] = 0;
    integral = 0;
	speedMeter = sm;
    speedbuf = 50;
    result = 0;
}

void SpeedPid::changePid(float p, float i, float d){
	if((p < 0) || (i < 0) || (d < 0)){
		return;
	}
	
	kp = p;
	ki = i;
	kd = d;
}

int SpeedPid::calcSpeed(float target){
    float sp = speedMeter->getSpeed();
    float p, i, d;
    int speed;
    diff[0] = diff[1];
    diff[1] = target - sp;
    
    integral += (diff[1] + diff[0]) / 2.0 * delta;
    
    p = kp * diff[1];
    i = ki * integral;
    d = kd * (diff[1] - diff[0]) / delta;
	
	speed = (int)(p + i + d);
	
    if(speed < -100){
        speed = -100;
    }else if(speed > 100){
        speed = 100;
    }

    // if((speed - speedbuf) < -70){
    //     speed = speedbuf - 5;
    // }
    speedbuf = speed;
    result = speed;
    return  speed;
}
void SpeedPid::resetIntegral(float rate){
    integral = integral * rate;
}
