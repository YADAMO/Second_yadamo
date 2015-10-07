#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "Observer.h"

class Choilie : public ScenarioController{
public:
	Choilie(Drive *dr, Observer *ob);
	virtual bool run();

private:
	Drive *drive;
	Observer *observer;
	double distance;
};