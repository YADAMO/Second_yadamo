#pragma once

#include "ev3api.h"
#include <cstdint>

class Sonic{

public:
	Sonic(sensor_port_t port);
	int16_t getDistance();

private:
	sensor_port_t port;
	sensor_type_t type;
};