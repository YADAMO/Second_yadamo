
#include "Motor.h"

Motor::Motor(motor_port_t port){
	this->port = port;
	type = LARGE_MOTOR;
	ev3_motor_config(port, type);
	ev3_motor_reset_counts(port);

}

void Motor::setRotate(int degree, int speed, bool block){
	ev3_motor_rotate(port, -degree, speed, block);	
}

void Motor::setSpeed(int speed){
	int sp=0;
	if(speed > 100){
		sp = 100;
	}else if(speed < -100){
		sp = -100;
	}else{
		sp = speed;
	}
	ev3_motor_set_power	(port, -sp);
}

int Motor::getSpeed(){
	return -ev3_motor_get_power(port);
}

int32_t Motor::getAngle(){
	return -ev3_motor_get_counts(port);

}
