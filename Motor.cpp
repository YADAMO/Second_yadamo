
#include "Motor.h"

Motor::Motor(motor_port_t port){
	this->port = port;
	type = MEDIUM_MOTOR;
	ev3_motor_config(port, type);
	ev3_motor_reset_counts(port);

}

void Motor::setSpeed(int speed){
	ev3_motor_set_power	(port, -speed);
}

int Motor::getSpeed(){
	return -ev3_motor_get_power(port);
}

int32_t Motor::getAngle(){
	return -ev3_motor_get_counts(port);

}
