#pragma once

#include "LightSensor.h"
#include "OffsetHolder.h"

using namespace ecrobot;

class ColorDetector{
private:
    int threshold;
    S16 buffer[15];
	LightSensor *lightSensor;
    int runtime;
    OffsetHolder *oHolder;
public:
	ColorDetector(LightSensor *argLightSensor, OffsetHolder *oh);
    bool grayDetect();
    bool blackLineDetect();
    bool blackLineDetect(int i);
};

