#pragma once

#include "Judgement.h"
#include "ev3api.h"
#include "SonarSensor.h"

using namespace ev3api;

class ObstacleJudge : public Judgement{
public:
	ObstacleJudge(SonarSensor *SonarSensor);
    virtual bool judge();
    void setDistance(int distance);

private:
	int obstacledistance;
	SonarSensor *sonarSensor;
};