
#include "STwinBridge.h"

STwinBridge::STwinBridge(LineTracer *lt, Observer *ob, Drive *dr, Choilie *ch){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	choilie = ch;
	runtime = 0;
	distance = 0;
}

bool STwinBridge::run(){
	switch(phase){
		case 0:
			lineTracer->changeTarget(-10);
			changeScenario();
		break;

		case 1:
			//ぶつかるまで前へ
			lineTracer->changeGain(1.5, 0, 0.02);
			lineTracer->trace(16, RIGHT, 0);
			if(observer->isStep() && runtime > 800){
				changeScenario();
				drive->init(true);
			}
			break;
		
		// case 2:
		// 	drive->curve(2, 2);
		// 	if(distance - observer->getDistance() > 5){
		// 		changeScenario();
		// 		drive->curve(0, 0);
		// 	}
		// break;

		case 2:
			// チョイリーする
			if(choilie->run()){
				changeScenario();
				drive->curve(0, 0);
			}
			break;

		case 3:
			// 待つ
			if(runtime > 500){
				changeScenario();
			}
			break;

		case 4:
			drive->curve(-15, -15);
			if(observer->isStep() && runtime > 500){
				changeScenario();
			}
		break;

		case 5:
			drive->curve(3, 3);
			if(distance - observer->getDistance() > 10){
				changeScenario();
			}
		break;

		case 6:
			//後輪を乗せる
			drive->curve(-100, -100);
			if(observer->getDistance() - distance > 16){
				drive->curve(0, 0);
				changeScenario();
			}
			break;
		case 7:
			// 待つ
			if(runtime > 1000){
				changeScenario();
			}
			break;

		case 8:
			drive->_drive(-5, 8);
			if(observer->getDistance() - distance > 3){
				changeScenario();
			}

			if(runtime > 2000 && observer->isStep()){
				phase -= 2;
				runtime = 0;
				distance = observer->getDistance();
			}
		break;

		case 9:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > 11){
				changeScenario();
				drive->init();
			}

		break;

		case 10:
			drive->curve(-80, -80);
			if(observer->getDistance() - distance > 15){
				changeScenario();

			}
			break;

		case 11:
			drive->curve(20, 20);
			if(observer->isStep()){
				changeScenario();
			}
		break;

		case 12:
			drive->curve(-5, -5);
			if(observer->getDistance() - distance > 20){
				changeScenario();
			}
		break;

		case 13:
			drive->curve(10, 10);
			if(runtime > 1000 && observer->isStep()){
				changeScenario();
			}
		break;

		case 14:
		break;
		default:
			break;
	}
	runtime++;
	
	return false;
}

void STwinBridge::changeScenario(){
	phase++;
	runtime = 0;
	distance = observer->getDistance();
}
