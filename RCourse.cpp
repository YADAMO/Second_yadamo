#include "RCourse.h"

RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob, BlackDetecter *bd, Drive *dr, SFigureL *fl, SLoopLine *ll, SParkingP *pp, LineReturn *lr){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	blackdetecter = bd;
	drive = dr;
	phase = 9;
	lineReturn = lr;
	figureL = fl;
	loopLine = ll;
	parkingP = pp;
	distance = 0;
}

void RCourse::changeScenario(){
	phase++;
	distance = observer->getDistance();
}

bool RCourse::run(){
	switch(phase){
		//最初の直線
		case 0:
			lineTracer->changeGain(0.4, 0.0, 0.02);
            lineTracer->trace(15, LEFT, 0);
			if(observer->getDistance() - distance > RST1){
				changeScenario();
			}
		break;

		//１番目カーブ前の減速
		case 1:
			// lineTracer->changeGain(0.8, 0.045, 0.08);
            lineTracer->trace(15, LEFT, 0);
            if(observer->getDistance() - distance > RBC1){
				changeScenario();
			}
		break;

		//１番目カーブ
		case 2:
			if(curve->runPid(11, 380, RC1, L)){
				lineTracer->changeGain(1.5, 0, 0.02);
				changeScenario();
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
			lineTracer->trace(15, LEFT, 0);
			if(observer->getDistance() - distance > RST2){
				changeScenario();
			}
		break;

		//２番目カーブの前半 左カーブ
		case 5:
			if(curve->runPid(7, 330, RC2A, L)){
				lineTracer->changeGain(1.5, 0, 0.02);
				changeScenario();
			}
		break;

		//２番目カーブの後半 右カーブ
		case 6:
			if(curve->runPid(9, -365, RC2B, R)){
				lineTracer->changeGain(1.5, 0, 0.02);
				changeScenario();
			}
		break;

		//２番目カーブ後のライン復帰
		case 7:
			lineTracer->trace(10, RIGHT, 0);
			if(observer->getDistance() - distance > RAC2){
				changeScenario();
			}
		break;

		//２番目カーブ後の直線
		case 8:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > RST3){
				changeScenario();
			}
		break;

		//３番目カーブ
		case 9:
			if(curve->runPid(9, -365, RC2B, R)){
				lineTracer->changeGain(0.8, 0, 0.01);
				changeScenario();
			}
		break;

		//３番目カーブ後のライン復帰
		case 10:
			lineTracer->trace(13, RIGHT, 0);
			if(observer->getDistance() - distance > RAC2){
				lineTracer->changeGain(0.48, 0.0, 0.023);
				changeScenario();
			}
		break;

		//LFigure
		case 11:
			if(figureL->run()){
				changeScenario();
			}
		break;

		//LoopLine
		case 12:
			if(loopLine->run()){
				changeScenario();
			}
		break;

		//黒検知+ライントレース
		case 13:
			lineTracer->changeGain(0.48, 0.0, 0.02); //お試し用
			lineTracer->trace(9, RIGHT, 0);
			if(blackdetecter->onBlack()){
				ev3_speaker_play_tone(NOTE_C4, 100);
				changeScenario();
			}
		break;

		//黒地帯脱出直進
		case 14:
			drive->_drive(1, 8);
			if(observer->getDistance() - distance > RBESC){
				changeScenario();
			}
		break;

		//黒検知後の直線
		case 15:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > RST4){
				changeScenario();
			}
		break;

		//帰り道カーブ前の減速
		case 16:
			lineTracer->trace(17, RIGHT, 0);
			if(observer->getDistance() - distance > RBC4){
				distance = observer->getDistance();
				changeScenario();
			}
		break;

		//帰り道カーブ
		case 17:
			if(curve->runPid(9, -423, RC4, R)){
				lineTracer->changeGain(0.8, 0, 0.01);
				changeScenario();
			}
		break;

		//帰り道カーブ後のライン復帰
		case 18:
			lineTracer->trace(13, RIGHT, 0);
			if(observer->getDistance() - distance > RAC4){
				lineTracer->changeGain(0.6, 0.0, 0.023);
				changeScenario();
			}
		break;

		//帰り道カーブ後の直線
		case 19:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > RST5){
				changeScenario();
			}
		break;

		//縦列駐車位置までバック
		case 20:
			drive->_drive(0, -15);
			if(distance - observer->getDistance() > RBACK){
				changeScenario();
			}
		break;

		//縦列駐車
		case 21:
			if(parkingP->run()){
				changeScenario();
			}
		break;

		case 22:
			return true;
		break;
	}

	return false;
}
