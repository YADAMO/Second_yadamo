#include "Jumper.h"

Jumper::Jumper(Driver *argDriver, LineTracer *argLineTracer, Stepper *argStepper, Distance *argDistance, StepDetector *sd, SpeedPid *sp, ColorDetector *cd)
{
	phase = 0;
	runtime = 0;
	dbuf = 0.0;
	stepper = argStepper;
	lineTracer = argLineTracer;
	driver = argDriver;
	distance = argDistance;
	stepDetector = sd;
	speedPid = sp;
	colorDetector = cd;
}

Jumper::~Jumper()
{
}

//左エッジで復帰したい場合
//これのtrueを確認したあとに左エッジの低速ライントレース
bool Jumper::run()
{
	switch(phase){
		case 0://段差に上る
			if(stepper->run(RIGHTEDGE)){
				phase++;
				driver->straightInit();
				distance->init();
			}
			break;
		case 1:
			driver->straight(speedPid->calcSpeed(32));
			if(distance->getDistance() < -35){
				phase++;
				speedPid->resetIntegral(0);
			}
			break;
		case 2:
			driver->straight(speedPid->calcSpeed(10));
			if(distance->getDistance() < -45){
				phase++;
				distance->init();
				driver->straightInit();
			}
			break;

		case 3:
			driver->straight(speedPid->calcSpeed(-10));
			if(distance->getDistance() > 5){
				distance->init();
				driver->straightInit();
				if(colorDetector->blackLineDetect()){
					phase = 7;
				}else{
					phase = 4;
				}
			}
			break;
		case 4:
			driver->straight(speedPid->calcSpeed(15));
			if(distance->getDistance() < -18){
				phase++;
			}
			if(colorDetector->blackLineDetect()){
				dbuf = distance->getDistance();
				phase = 6;
			}
			break;

		case 5:
			driver->drive(20, 50);
			if(colorDetector->blackLineDetect(1)){
				phase = 6;
				dbuf = distance->getDistance();
				distance->init();
			}
			break;
		case 6:
			driver->drive(-100, 0);
			if(distance->getDiff() > 110){
				phase++;
			}
			break;
		case 7:
			lineTracer->changePid(0.18, 0.001, 0.055);
			lineTracer->lineTrace((float)20, RIGHTEDGE);
			if((distance->getDistance() + dbuf) < -50){
				phase++;
			}
			break;
		case 8:
			distance->init();
			phase = 0;
			return true;
			break;
	}
	runtime += 3;
	return false;
}
