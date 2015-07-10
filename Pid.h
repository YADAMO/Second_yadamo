#pragma once
#include "LightSensor.h"

using namespace ecrobot;

class Pid{
private:
    float delta;
    float kp;
    float ki;
    float kd;
    float diff[2];
    float integral;
	LightSensor *lightSensor;

public:
	Pid(LightSensor *light);
	void changePid(float p, float i, float d);
	int calcTurn(float target);
    void resetIntegral(float rate);
    int result;
};
