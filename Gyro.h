#pragma once

#include "ev3api.h"
#include <cstdint>

class Gyro{

public:
	Gyro(sensor_port_t port);
	int16_t getAngle();

private:
	sensor_port_t port;
	sensor_type_t type;
};