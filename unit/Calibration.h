#pragma once

#include "ev3api.h"
#include "ColorSensor.h"
#include "Observer.h"
#include "Clock.h"

class Calibration {
public:
    Calibration(ColorSensor *color, Observer *obs, Clock *clk);
    void doCalibration();

private:
    ColorSensor *colorSensor;
    Observer *observer;
    Clock *clock;
    int touchCount;
    bool judge;
    int white, black, green;

    void setWhite(int white);
    void setBlack(int black);
    void setGreen(int green);
    int getWhite();
    int getBlack();
    int getGreen();
};

