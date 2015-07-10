#include "GridRunner.h"

#define EXITLINE 2

RunPattern GridRunner::runPatterns[] = {
	RunPattern(TURN, LEFTEDGE, 350),
	RunPattern(GOSTRAIGHT, -20, 40),
	RunPattern(TURN, RIGHTEDGE, 360),
	RunPattern(LINETRACE, RIGHTEDGE, 40),
	RunPattern(LINETRACE, RIGHTEDGE, 40),
	RunPattern(LINETRACE, RIGHTEDGE, 40),
	// RunPattern(GOSTRAIGHT, -8, 40),
	// RunPattern(TURN, LEFTEDGE, 175),
	// RunPattern(GOSTRAIGHT, -35, 40),
	// RunPattern(TURN, RIGHTEDGE, 185),
	// RunPattern(LINETRACE, RIGHTEDGE, 35),
	// RunPattern(LINETRACE, RIGHTEDGE, 40),
	// RunPattern(LINETRACE, RIGHTEDGE, 40),
	// RunPattern(GOSTRAIGHT, -110, 40),
	// RunPattern(TURN, RIGHTEDGE, 190),
	// RunPattern(GOSTRAIGHT, -60, 40),
	// RunPattern(TURN, RIGHTEDGE, 190),
	RunPattern(GOSTRAIGHT, -30, 40),
	RunPattern(0, 0, 0)
};

GridRunner::GridRunner(LineTracer *lt, Driver *dr, Stepper *sp, ColorDetector *cd, Distance *dis, StepDetector *sd){
	lineTracer = lt;
	driver = dr;
	stepper = sp;
	colorDetector = cd;
	distance = dis;
	stepDetector = sd;
	patIndex = 0;
	curPattern = runPatterns[0];
	detected = false;
	diffflag = false;
	closePhase = 0;
	phase = 0;
	turnflag = false;
	runtime = 0;
	disOffset = 0;
}

GridRunner::~GridRunner(){

}

void GridRunner::changePhase(){
	phase++;
	distance->init();
	driver->straightInit();
	runtime = 0;
}

void GridRunner::changePattern(){
	patIndex++;
	distance->init();
	driver->straightInit();
	runtime = 0;
}

void GridRunner::backTurn(){
	if(distance->getDiff() > 3 && !diffflag){
		driver->backDrive(30 * -curPattern.param, 0);
		runtime = 0;
	}else if(runtime < 1000){
		driver->turn(20 * curPattern.param);
		diffflag = true;
	}else if(runtime < 1200){
		driver->straight(-30);
	}else{
		driver->straightInit();
		distance->init();
		detected = false;
		runtime = 0;
		diffflag = false;
	}
}

void GridRunner::back(){
	if(distance->getDistance() - disOffset < 18){
		driver->drive(20, -40);
	}else{
		driver->straightInit();
		detected = false;
		runtime = 0;
	}
}

void GridRunner::lineTrace(){
	if((colorDetector->blackLineDetect() && runtime > 1000 && distance->getDistance() < -22) || distance->getDistance() < -30){
		detected = false;
		changePattern();
	}else{
		if((stepDetector->detect() && runtime > 1000) || detected){
			detected = true;
			lineTracer->lineTrace(100, curPattern.param);
		}else{
			lineTracer->lineTrace(curPattern.param2, curPattern.param);
		}
	}
}

void GridRunner::goStraight(){
	if(stepDetector->detect() && runtime > 3000){
		detected = true;
		disOffset = distance->getDistance();
	}

	if(detected){
		back();
	}else if(distance->getDistance() > curPattern.param){
		driver->straight(curPattern.param2);
	}else{
		changePattern();
	}
}

void GridRunner::turn(){
	if(distance->getDiff() < curPattern.param2 && !turnflag){
		if(runtime < 1000 && !detected){
			driver->turn(60 * -curPattern.param);
		}else if(detected){
			backTurn();
		}else{
			if((stepDetector->detect() && runtime > 1500)){
				detected = true;
			}else{
				driver->drive(60 * -curPattern.param, 0);
			}
		}
	}else{
		if(turnflag){
			if(runtime < 1000){
				driver->turn(20 * curPattern.param);
			}else{
				changePattern();
				detected = false;
				turnflag = false;
			}
		}else{
			turnflag = true;
			runtime = 0;
		}
	}
}

bool GridRunner::run(){
	RunPattern runPatterns1[] = {
		RunPattern(LINETRACE, RIGHTEDGE, 40),
		RunPattern(LINETRACE, RIGHTEDGE, 40),
		RunPattern(TURN, LEFTEDGE, 190),
		RunPattern(GOSTRAIGHT, -29, 40),
		RunPattern(TURN, RIGHTEDGE, 180),
		// RunPattern(GOSTRAIGHT, -8, 40),
		// RunPattern(TURN, LEFTEDGE, 175),
		// RunPattern(GOSTRAIGHT, -35, 40),
		// RunPattern(TURN, RIGHTEDGE, 185),
		// RunPattern(LINETRACE, RIGHTEDGE, 35),
		// RunPattern(LINETRACE, RIGHTEDGE, 40),
		// RunPattern(LINETRACE, RIGHTEDGE, 40),
		// RunPattern(GOSTRAIGHT, -110, 40),
		// RunPattern(TURN, RIGHTEDGE, 190),
		// RunPattern(GOSTRAIGHT, -60, 40),
		// RunPattern(TURN, RIGHTEDGE, 190),
		RunPattern(GOSTRAIGHT, -40, 40),
		RunPattern(0, 0, 0)
	};

	curPattern = runPatterns1[patIndex];
	bool st = false;
	switch(phase){
		case 0:
		if(stepper->gridStep(RIGHTEDGE)){
			changePhase();
		}
		break;

		// case 1:
		// if(distance->getDistance() > 5){
		// 	lineTracer->lineTrace(RIGHTEDGE, 15);
		// }else{
		// 	changePhase();
		// }
		// break;

		case 1:
		switch(curPattern.pattern){
			case GOSTRAIGHT:
				goStraight();
				break;
			case TURN:
				turn();
				break;
			case LINETRACE:
				lineTrace();
				break;
			default:
				driver->straight(0);
				changePhase();
				break;
		}
		break;

		case 2:
		switch(closePhase){
			case 0:
				if(EXITLINE > 3){
					closePhase = 4;
				}else{
					closePhase = 1;
				}
				break;
			case 1:
				if(distance->getDiff() < 260 && !turnflag){
					if(runtime < 1000){
						driver->turn(-60);
					}else{
						driver->drive(-60, 0);
					}
				}else{
					if(turnflag){
						if(runtime < 1000){
							driver->turn(0);
						}else{
							closePhase = 10;
							distance->init();
							driver->straightInit();
							runtime = 0;
							turnflag = false;
						}
					}else{
						turnflag = true;
						runtime = 0;
					}
				}
				break;
			case 3:
				if(distance->getDistance() < 5){
					driver->straight(-40);
				}else{
					closePhase = 10;
					distance->init();
					driver->straightInit();
					runtime = 0;
				}
				break;
			case 10:
				if(colorDetector->blackLineDetect() && runtime > 10){
					closePhase = 4;	
					distance->init();
					driver->straightInit();
					runtime = 0;
				}else{
					driver->straight(40);
				}
				break;
			case 4:
				if(distance->getDistance() > -8){
					driver->straight(40);
				}else{
					closePhase = 5;	
					distance->init();
					driver->straightInit();
					runtime = 0;
				}
				break;
			case 5:
				if(runtime < 1000){
					driver->turn(60);
				}else if(!colorDetector->blackLineDetect()){
					driver->drive(60, 0);
				}else{
					closePhase = 2;
					distance->init();
					driver->straightInit();
					runtime = 0;
				}
				break;
			case 2:
				if(distance->getDiff() < 50 && !turnflag){
					if(runtime < 1000){
						driver->turn(-60);
					}else{
						driver->drive(-60, 0);
					}
				}else{
					if(turnflag){
						if(runtime < 500){
							driver->turn(10);
						}else{
							closePhase = 6;
							distance->init();
							driver->straightInit();
							runtime = 0;
							turnflag = false;
						}
					}else{
						turnflag = true;
						runtime = 0;
					}
				}
				break;
			case 6:
				lineTracer->changePid(0.15, 0.001, 0.055);
				lineTracer->lineTrace(60, RIGHTEDGE);
				if(distance->getDistance() < -25){
					closePhase = 7;
					driver->straight(0);	
					changePhase();
				}
				break;
			case 7:
				break;
		}
		break;

		case 3:
		st = true;
		driver->straightInit();
		driver->straight(0);
		break;
	}
	runtime += 3;
	return st;
}
