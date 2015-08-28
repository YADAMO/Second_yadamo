
#include "Color.h"

Color::Color(sensor_port_t port){
	this->port = port;
	type = COLOR_SENSOR;
	ev3_sensor_config(port, type);
}

uint8_t Color::getAmbient(){
	return ev3_color_sensor_get_ambient(port);
}

uint8_t Color::getReflect(){
	return ev3_color_sensor_get_reflect(port);
}

colorid_t Color::getColor(){
	return ev3_color_sensor_get_color(port);
}
