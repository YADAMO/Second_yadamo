#pragma once

#include "LineTracer.h"
#include "Driver.h"
#include "Stepper.h"
#include "ColorDetector.h"
#include "Distance.h"
#include "StepDetector.h"
#include "RunPattern.h"

class GridRunner{
private:
	LineTracer *lineTracer;
	Driver *driver;
	Stepper *stepper;
	ColorDetector *colorDetector;
	Distance *distance;
	StepDetector *stepDetector;
	int runtime;
	bool turnflag;
	RunPattern curPattern;
	int patIndex;
	bool detected;
	bool diffflag;
	int phase;
	int closePhase;
	F32 disOffset;
	int exitline;
	void back();
	void changePattern();
	void changePhase();
	void lineTrace();
	void goStraight();
	void turn();
	void backTurn();
public:
	GridRunner(LineTracer *lt, Driver *dr, Stepper *sp, ColorDetector *cd, Distance *dis, StepDetector *sd);
	~GridRunner();
	static RunPattern runPatterns[];
	bool run();
};

//RunPattern(pattern, param: distance or direction, param2: speed or angle)
//マス移動の距離 -20
//斜め移動の距離 -35
//90度旋回 382
//45度旋回 175
// RunPattern GridRunner::runPatterns[] = {
// 	RunPattern(TURN, LEFTEDGE, 350),
// 	RunPattern(GOSTRAIGHT, -20, 40),
// 	RunPattern(TURN, RIGHTEDGE, 360),
// 	RunPattern(LINETRACE, RIGHTEDGE, 40),
// 	RunPattern(LINETRACE, RIGHTEDGE, 40),
// 	RunPattern(LINETRACE, RIGHTEDGE, 40),
// 	// RunPattern(GOSTRAIGHT, -8, 40),
// 	// RunPattern(TURN, LEFTEDGE, 175),
// 	// RunPattern(GOSTRAIGHT, -35, 40),
// 	// RunPattern(TURN, RIGHTEDGE, 185),
// 	// RunPattern(LINETRACE, RIGHTEDGE, 35),
// 	// RunPattern(LINETRACE, RIGHTEDGE, 40),
// 	// RunPattern(LINETRACE, RIGHTEDGE, 40),
// 	// RunPattern(GOSTRAIGHT, -110, 40),
// 	// RunPattern(TURN, RIGHTEDGE, 190),
// 	// RunPattern(GOSTRAIGHT, -60, 40),
// 	// RunPattern(TURN, RIGHTEDGE, 190),
// 	RunPattern(GOSTRAIGHT, -30, 40),
// 	RunPattern(0, 0, 0)
// };
