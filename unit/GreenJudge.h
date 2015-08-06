#pragma once

#include "Judgement.h"
#include "ev3api.h"
#include "ColorSensor.h"

using namespace ev3api;

class GreenJudge : public Judgement{
public:
	GreenJudge(ColorSensor *ColorSensor);
    virtual bool judge();

private:
	ColorSensor *colorSensor;
};