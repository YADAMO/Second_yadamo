#pragma once

#include "ScenarioController.h"
#include "LineTracer.h"
#include "Curve.h"
#include "Observer.h"
#include "STwinBridge.h"
#include "SBarcode.h"
#include "SUndetermined.h"
#include "LineReturn.h"
#include "Drive.h"

#define LSTART 300
#define LBC1 176.5
#define LC1 85
#define LAC1 20
#define LACC 10
#define LCC 83


class LCourse : public ScenarioController{
public:
	LCourse(LineTracer *lt, Curve *cv, Observer *ob, STwinBridge *st, LineReturn *lr, SBarcode *bar, SUndetermined *und, Drive *dr);

	virtual bool run();
	void changeScenario();
private:
	LineTracer *lineTracer;
	Curve *curve;
	Observer *observer;
	STwinBridge *bridge;
	SBarcode *barcode;
	SUndetermined *undetermined;
	LineReturn *lineReturn;
	Drive *drive;

	double distance;


};