#pragma once

#include "Motor.h"
#include "Speaker.h"

using namespace ecrobot;

class StepDetector{
private:
	Motor *Rmotor;
	Motor *Lmotor;
	Speaker *speaker;
public:
	StepDetector(Motor *rmotor, Motor *lmotor, Speaker *sp);
	~StepDetector();
	bool detect();
};
