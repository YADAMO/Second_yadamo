
#include "STwinBridge.h"

STwinBridge::STwinBridge(LineTracer *lt, Observer *ob, Drive *dr, Tyoiri *ty){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	tyoiri = ty;
	runtime = 0;
	distance = 0;
}

bool STwinBridge::run(){
	switch(phase){
		case 0:
			//ぶつかるまで前へ
			lineTracer->changeGain(1.5, 0, 0.02);
			lineTracer->trace(20, RIGHT, 0);
			if(observer->isStep() && runtime > 800){
				changeScenario();
				runtime = 0;
			}
			runtime++;
			break;
		
		case 1:
			// チョイリーする
			if(tyoiri->run()){
				changeScenario();
				distance = observer->getDistance();
				drive->curve(0, 0);
			}
			break;

		case 2:
			// 待つ
			if(runtime > 500){
				changeScenario();
				distance = observer->getDistance();
				runtime = 0;
			}
			runtime++;
			break;

		case 3:
			drive->curve(-15, -15);
			if(observer->isStep()){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 4:
			drive->curve(10, 10);
			if(distance - observer->getDistance() > 5.5){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		case 5:
			//後輪を乗せる
			drive->curve(-100, -100);
			if(observer->getDistance() - distance > 15){
				drive->curve(0, 0);
				distance = observer->getDistance();
				changeScenario();
			}
			break;
		case 6:
			// 待つ
			if(runtime > 2000){
				changeScenario();
				distance = observer->getDistance();
			}
			runtime++;
			break;
		case 7:
			// ライントレース
			lineTracer->trace(70, RIGHT, 0);
			if(observer->getDistance() - distance > 30){
				changeScenario();

			}
			break;

		case 8:
			return true;
		break;
		default:
			break;
	}
	
	return false;
}
