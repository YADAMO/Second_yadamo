#pragma once

#include "ev3api.h"
#include "ColorSensor.h"
#include <string.h>

using namespace ev3api;

class Messenger{
public:
	Messenger(ColorSensor *colorSensor);
	void message();

private:
	ColorSensor *colorSensor;
};