#pragma once

#include "ev3api.h"
#include <cstdint>

class Motor{
public:
	Motor(motor_port_t port);
	void setSpeed(int speed);
	ER setRotate(int degree, int speed, bool isBlock);
	int getSpeed();
	int32_t getAngle();

private:
	motor_port_t port;
	motor_type_t type;
};
