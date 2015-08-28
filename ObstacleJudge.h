#pragma once

#include "Judgement.h"
#include "ev3api.h"
#include "Sonic.h"

class ObstacleJudge : public Judgement{
public:
	ObstacleJudge(Sonic *son);
    virtual bool judge();
    void setDistance(int distance);

private:
	int obstacledistance;
	Sonic *sonic;
};