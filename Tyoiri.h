#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "Observer.h"

class Tyoiri : public ScenarioController{
public:
	Tyoiri(Drive *dr, Observer *ob);
	virtual bool run();

private:
	Drive *drive;
	Observer *observer;
	double distance;
};