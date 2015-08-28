#pragma once

#include "ev3api.h"
#include <cstdint>

class Touch{

public:
	Touch(sensor_port_t port);
	bool isPush();

private:
	sensor_port_t port;
	sensor_type_t type;
};