
#include "Touch.h"

Touch::Touch(sensor_port_t port){
	this->port = port;
	type = TOUCH_SENSOR;
	ev3_sensor_config(port, type);
}

bool Touch::isPush(){
	return ev3_touch_sensor_is_pressed(port);
}
