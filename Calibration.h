#pragma once

#include "ev3api.h"
#include "Color.h"
#include "TouchJudge.h"
#include "LineTracer.h"

class Calibration {
public:
    Calibration(Color *col, TouchJudge *tj, LineTracer *lt);
    bool doCalibration();
    int getTarget();
private:
    Color *color;
    TouchJudge *touchJudge;
    LineTracer *lineTracer;

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

