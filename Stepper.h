#pragma once

#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"

class Stepper{
private:
	Drive *drive;
	LineTracer *lineTracer;
	Observer *observer;
	int phase;
	int runtime;
	double distance;

	void changeFhase();
public:
	Stepper(Drive *dr, LineTracer *lt, Observer *obs);
	bool run(int edge);

};
