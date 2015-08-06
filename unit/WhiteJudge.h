#pragma once

#include "Judgement.h"
#include "ev3api.h"
#include "ColorSensor.h"

using namespace ev3api;

class WhiteJudge : public Judgement{
public:
	WhiteJudge(ColorSensor *ColorSensor);
    virtual bool judge();

private:
	ColorSensor *colorSensor;
};
