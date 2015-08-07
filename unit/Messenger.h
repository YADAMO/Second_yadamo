#pragma once

#include "ev3api.h"
#include "ColorSensor.h"
#include <string.h>

using namespace ev3api;

class Messenger{
public:
	Messenger(ColorSensor *colorSensor);
	void messageColor();
	void messageString(char *text, int line);

private:
	ColorSensor *colorSensor;
};