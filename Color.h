#pragma once

#include "ev3api.h"
#include <cstdint>

class Color{

public:
	Color(sensor_port_t port);
	uint8_t getAmbient();
	uint8_t getReflect();
	colorid_t getColor();


private:
	sensor_port_t port;
	sensor_type_t type;
};
