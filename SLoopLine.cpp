
#include "SLoopLine.h"

SLoopLine::SLoopLine(LineTracer *lt, Observer *ob, Drive *dr, Stepper *st, Curve *cv){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	stepper = st;
	curve = cv;
	distance = 0;
}

void SLoopLine::changeScenario(){
	phase++;
	distance = observer->getDistance();
}

bool SLoopLine::run(){
	bool end = false;
	switch(phase){
		case 0:
			//フィギュアLの段差を降り、後輪を段差にぶつけた状態からスタート
			//環状線に近づくために、ある程度ライントレースしたらケース1へ
			lineTracer->trace(10, RIGHT, 0);
			if(observer->getDistance() > 10){
				drive->curve(0, 0);
				drive->init(true);
				changeScenario();
			}
		case 1:
			//超音波が反応するまで、一定周期で少しづつライントレースをし、反応したらケース2へ
			if(observer->isObstacle()){
				changeScenario();
			}
			break;
		case 2:
			//段差のぼったらケース3へ
			if(stepper->run(1)){
				changeScenario();
				// lineTracer->changeTarget(5);
			}
			break;
		case 3:
			//ある程度ライントレースしたらケース4へ
			lineTracer->trace(10, RIGHT, 0);
			if(observer->getDistance() - distance > 30){
				drive->curve(0, 0);
				drive->init(true);
				changeScenario();
			}
			break;
		case 4:
			//超音波が反応したらケース5へ
			if(observer->isObstacle()){
				changeScenario();
			}
			break;
		case 5:
			//ある程度左に曲がったらケース6へ
			if(curve->runPid(10, 300, 55, R)){
				changeScenario();
			}
			break;
		case 6:
			//ある程度右に曲がったらケース7へ
			if(curve->runPid(-10, -350, 30, L)){
				changeScenario();
			}
			break;
		case 7:
			//ライン上に乗るよう、少し戻って終了
			drive->curve(9,9);
			if(distance - observer->getDistance() > 25){
				end = true;
			}
			break;
		default:
			break;
	}
	return end;
}
