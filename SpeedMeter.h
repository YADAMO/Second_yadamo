#pragma once
#include "Distance.h"
#include "Motor.h"

class SpeedMeter{
private:
	Distance *distance;
	Motor *motorR;
	Motor *motorL;
public:
	SpeedMeter(Distance *ds, Motor *mR, Motor *mL);
	~SpeedMeter();
	float getSpeed(void);
};
