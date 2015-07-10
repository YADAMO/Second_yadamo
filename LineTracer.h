#pragma once
//read neccessary header file
//#include header file of PID class
#include "Driver.h"
#include "Pid.h"
#include "OffsetHolder.h"
#include "SpeedPid.h"

#define RIGHTEDGE 1
#define LEFTEDGE -1

class Driver;
class LineTracer {
private:
//not define on UML
  Driver *driver;
  Pid *pid;
  OffsetHolder *offsetHolder;
  SpeedPid *speedPid;
  float target;
public:
	LineTracer(Driver *argDriver, Pid *argPid, OffsetHolder *oh, SpeedPid *sp);
	~LineTracer();
	void lineTrace(int speed, int edge);
	int lineTrace(float speed, int edge);
	void setTarget(float target);
	float getTarget();
	void changePid(float p, float i, float d);
	void resetIntegral(float rate);
	void calcAllTarget();
	float nearblack;
	float nearnearblack;
	float nearnearwhite;
	float nearwhite;
};
