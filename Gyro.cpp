
#include "Gyro.h"

Gyro::Gyro(sensor_port_t port){
	this->port = port;
	type = GYRO_SENSOR;
	ev3_sensor_config(port, type);
}

int16_t Gyro::getAngle(){
	return ev3_gyro_sensor_get_angle(port);	
}
