
#include "Sonic.h"

Sonic::Sonic(sensor_port_t port){
	this->port = port;
	type = ULTRASONIC_SENSOR;
	ev3_sensor_config(port, type);
}

int16_t Sonic::getDistance(){
	return ev3_ultrasonic_sensor_get_distance(port);
}
