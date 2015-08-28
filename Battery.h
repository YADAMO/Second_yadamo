#pragma once

#include "ev3api.h"

int getBatteryCurrent(){
	return ev3_battery_current_mA();
}

int getBatteryVoltage(){
	return ev3_battery_voltage_mV();
}
