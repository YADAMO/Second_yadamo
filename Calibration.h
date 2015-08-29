#pragma once

#include "ev3api.h"
#include "Color.h"
#include "TouchJudge.h"

class Calibration {
public:
    Calibration(Color *col, TouchJudge *tj);
    void doCalibration();
    int getTarget();
private:
    Color *color;
    TouchJudge *touchJudge;

    int touchCount, tc;
    bool judge;
    int white, black, green, gray;
    int target;

    void setWhite(int white);
    void setBlack(int black);
    void setGreen(int green);
    int getWhite();
    int getBlack();
    int getGreen();
    void drawLCD();

};

