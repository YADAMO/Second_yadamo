#include "LineTracer.h"

LineTracer::LineTracer(Driver *argDriver, Pid *argPid, OffsetHolder *oh, SpeedPid *sp)
{
  driver = argDriver;
  pid = argPid;
  offsetHolder = oh;
  speedPid = sp;
  target = 600;
  nearblack = 0;
  nearnearblack = 0;
  nearnearwhite = 0;
  nearwhite = 0;
}

LineTracer::~LineTracer()
{

}

//hidari adge == 1 , migi adge == -1
void LineTracer::lineTrace(int speed, int edge){
  driver->drive(edge * pid->calcTurn(target), speed);
}

int LineTracer::lineTrace(float speed, int edge){
  int tmp = speedPid->calcSpeed(speed);
  driver->drive(edge * pid->calcTurn(target), tmp);
  return tmp;
}

void LineTracer::setTarget(float tar){
	target = tar;
}

float LineTracer::getTarget(){
	return target;
}

void LineTracer::changePid(float p, float i, float d){
	pid->changePid(p, i, d);
}

void LineTracer::resetIntegral(float rate){
  pid->resetIntegral(rate);
}

void LineTracer::calcAllTarget(){
	nearnearblack = (offsetHolder->getWhite() * 2 + offsetHolder->getBlack() * 3) / 5;
	nearblack = (offsetHolder->getWhite() + offsetHolder->getBlack() * 3) / 4;
	nearwhite = (offsetHolder->getWhite() * 3 + offsetHolder->getBlack()) / 4;
	nearnearblack = (offsetHolder->getWhite() * 3 + offsetHolder->getBlack() * 2) / 5;
}
