#include "RCourse.h"

//フル実装版
//LCourse::LCourse(LineTracer *lt, Curve *cv, Observer *ob, SFigureL *st, SLoopLine *sl, SParking *sp){

RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	//figureL = sf;
	//loopline = sl;
	//parking = sp;
	//distance = 0;
}

bool RCourse::run(){
	switch(phase){
		//最初の直線
		case 0:
			lineTracer->changeGain(0.75, 0.0, 0.0);
            lineTracer->fastrace(15, LEFT, 0);
			if(observer->getDistance() - distance > RST1){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		//１番目カーブ前の減速
		case 1:
			// lineTracer->changeGain(0.8, 0.045, 0.08);
            lineTracer->fastrace(15, LEFT, 0);
            if(observer->getDistance() - distance > RBC1){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		//１番目カーブ
		case 2:
			if(curve->runPid(11, 380, RC1, L)){
				changeScenario();
				lineTracer->changeGain(1.5, 0, 0.02);
				distance = observer->getDistance();
			}
		break;

		//１番目カーブ後のライン復帰
		case 3:
			lineTracer->trace(10, LEFT, 0);
			if(observer->getDistance() - distance > RAC1){
				changeScenario();
			}
		break;

		//１番目カーブ後の直線
		case 4:
			lineTracer->fastrace(15, LEFT, 0);
			if(observer->getDistance() - distance > RST2){
				changeScenario();
			}
		break;

		//２番目カーブの前半 左カーブ
		case 5:
			if(curve->runPid(7, 330, RC2A, L)){
				changeScenario();
				lineTracer->changeGain(1.5, 0, 0.02);
				distance = observer->getDistance();
			}
		break;

		//２番目カーブの後半 右カーブ
		case 6:
			if(curve->runPid(9, -365, RC2B, R)){
				changeScenario();
				lineTracer->changeGain(1.5, 0, 0.02);
				distance = observer->getDistance();
			}
		break;

		//２番目カーブ後のライン復帰
		case 7:
			lineTracer->trace(20, LEFT, 0);
			if(observer->getDistance() - distance > RAC2){
				changeScenario();
			}
		break;

		//２番目カーブ後の直線
		case 8:
			lineTracer->fastrace(15, LEFT, 0);
			if(observer->getDistance() - distance > RST3){
				changeScenario();
			}
		break;

		case 9:
			return true;
		break;
	}

	return false;
}
