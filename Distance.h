#pragma once
#include "Motor.h"

using namespace ecrobot;
class Distance{
private:
	Motor *motorR;
	Motor *motorL;
	S32 leftOffset, rightOffset;
	S32 distanceL, distanceR;
	F32 distance;
public:
	Distance(Motor *rm, Motor *lm);
	~Distance(void);
	void init(void);
	void init(S32 mR, S32 mL);
	F32 getDistance(void);
	int getDiff(void);
};
