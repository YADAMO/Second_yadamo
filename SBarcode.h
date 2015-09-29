#pragma once

#include "ScenarioController.h"
#include "Drive.h"
#include "LineTracer.h"
#include "Observer.h"
#include "Logger.h"

class SBarcode : public ScenarioController{
public:
	SBarcode(LineTracer *lt, Observer *ob, Drive *dr, Logger *lg);
    virtual bool run();

private:
	LineTracer *lineTracer;
	Observer *observer;
	Drive *drive;
	Logger *logger;
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
