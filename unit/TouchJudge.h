#pragma once

#include "Judgement.h"
#include "ev3api.h"
#include "TouchSensor.h"

using namespace ev3api;

class TouchJudge : public Judgement{
public:
	TouchJudge(TouchSensor *TouchSensor);
    virtual bool judge();

private:
	TouchSensor *touchSensor;
};