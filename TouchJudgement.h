#pragma once

#include "TouchSensor.h"

using namespace ecrobot;

class TouchJudgement{
private:
	TouchSensor *touchSensor;
	S8 count;
public:
	TouchJudgement(TouchSensor *T);
	~TouchJudgement(void);
	bool judge(void);

};
