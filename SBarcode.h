#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"
#include "Logger.h"
#include "Stepper.h"

class SBarcode : public ScenarioController{
public:
	SBarcode(LineTracer *lt, Observer *ob, Drive *dr, Logger *lg, Stepper *st);
    virtual bool run();
	void changeScenario();

private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
	Logger *logger;
	Stepper *stepper;
	double distance;
	colorid_t preCol;
	int runtime;
	double whiteStack[4];
	int wp;
	double blackStack[4];
	int bp;
	int bitArray[8];
	bool calcend;
	bool calcBarcode();
	unsigned char getBitArray();
};
