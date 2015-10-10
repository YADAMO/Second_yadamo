#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "Observer.h"
#include "Curve.h"

class SParkingP : public ScenarioController{
public:
	SParkingP(Observer *ob, Drive *dr, Curve *cv);
	void changeScenario();
    virtual bool run();

private:
	Observer *observer;
	Drive *drive;
	Curve *curve;
	double distance;
};