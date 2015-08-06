#pragma once

#include "Judgement.h"
#include "ev3api.h"
#include "ColorSensor.h"

using namespace ev3api;

class BlackJudge : public Judgement{
public:
	BlackJudge(ColorSensor *ColorSensor);
    virtual bool judge();

private:
	ColorSensor *colorSensor;
};
