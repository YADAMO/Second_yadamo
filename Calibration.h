#pragma once

#include "ev3api.h"
#include "Color.h"
#include "TouchJudge.h"
#include "LineTracer.h"
#include <cstdint>

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
    uint8_t white, black, green, gray;
    uint8_t target;

    void setWhite(uint8_t white);
    void setBlack(uint8_t black);
    void setGreen(uint8_t green);
    int getWhite();
    int getBlack();
    int getGreen();
    void drawLCD();

};

