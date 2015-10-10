#include "RCourse.h"

RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob, BlackDetecter *bd, Drive *dr, SFigureL *fl, SLoopLine *ll, SParkingP *pp, LineReturn *lr){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	blackdetecter = bd;
	drive = dr;
	phase = -1;
	lineReturn = lr;
	figureL = fl;
	loopLine = ll;
	parkingP = pp;
	distance = 0;
}

//curve.curve(5, 40, 50, -1, 10)

void RCourse::changeScenario(){
	phase++;
	ev3_speaker_play_tone(NOTE_C4, 100);
	runtime = observer->getRuntime();
	distance = observer->getDistance();
}

bool RCourse::run(){
	switch(phase){
		case -1:
			lineTracer->changeGain(0.85, 0.0, 0.02);
            changeScenario();
		break;

		//最初の直線
		case 0:
            lineTracer->trace(25, LEFT, 0);
			if(observer->getDistance() - distance > RST1){
				lineTracer->changeGain(1.2, 0.0, 0.015);
				changeScenario();
			}
		break;

		//１番目カーブ前の減速
		case 1:
			// lineTracer->changeGain(0.8, 0.045, 0.08);
            lineTracer->trace(16, LEFT, 0);
            if(observer->getDistance() - distance > RBC1){
            	curve->changeGain(1.5, 0.0, 0.0);
				changeScenario();
			}
		break;

		//１番目カーブ
		case 2:
			if(curve->curve(4, 40, RC1, L, 10, L)){
				lineTracer->changeGain(1.5, 0, 0.02);
				changeScenario();
			}
		break;

		//１番目カーブ後のライン復帰
		case 3:
			// if(lineReturn->run(-1)){
			// 	lineTracer->changeGain(1.5, 0.0, 0.0);
				changeScenario();
			// }
		break;

		//１番目カーブ後の直線
		case 4:
			lineTracer->changeGain(0.7, 0.0, 0.02);
			lineTracer->trace(12, LEFT, 0);
			if(observer->getDistance() - distance > RST2){
            	lineTracer->changeGain(1.5, 0.0, 0.0);
				changeScenario();
			}
		break;

		//２番目カーブの前半 左カーブ
		case 5:
			if(curve->runPid(4, 410, RC2A, L, 14)){
				lineTracer->changeGain(1.5, 0, 0.02);
				changeScenario();
			}
		break;

		//２番目カーブの後半 右カーブ
		case 6:
			if(curve->runPid(5, -420, RC2B, R, 14)){
				lineTracer->changeGain(1.5, 0, 0.02);
				changeScenario();
			}
		break;

		//２番目カーブ後のライン復帰
		case 7:
			if(lineReturn->run(-1)){
				changeScenario();
			}
		break;

		//エッジ切り替え前の減速
		case 8:
			lineTracer->trace(10, LEFT, 0);
			if(observer->getDistance() - distance > RBCE){
				changeScenario();
			}
		break;

		//エッジ切り替え
		case 9:
			drive->_drive(2, 8);
			if(observer->getDistance() - distance > RBESC){
				changeScenario();
			}
		break;

		//エッジ切り替え後の直進
		case 10:
			lineTracer->trace(15, LEFT, 0);
			if(observer->getDistance() - distance > RACE){
				changeScenario();
			}
		break;

		//３番目カーブ後の減速
		case 11:
			lineTracer->trace(10, RBC3, 0);
			if(observer->getDistance() - distance > RAC2){
				lineTracer->changeGain(0.48, 0.0, 0.023);
				changeScenario();
			}
		break;

		//３番目カーブ
		case 12:
			if(curve->runPid(4, -410, RC3, R, 10)){
				lineTracer->changeGain(0.8, 0, 0.01);
				changeScenario();
			}
		break;

		//３番目カーブ後のライン復帰
		case 13:
			if(lineReturn->run(1)){
				changeScenario();
			}
		break;

		//LFigure
		case 14:
			if(figureL->run()){
				changeScenario();
				distance = observer->getDistance();
				ev3_speaker_play_tone(NOTE_C4, 100);
			}
		break;

		//LoopLine
		case 15:
			if(loopLine->run()){
				changeScenario();
			}
		break;

		//黒検知+ライントレース
		case 16:
			lineTracer->changeGain(0.48, 0.0, 0.02); //お試し用
			lineTracer->trace(9, RIGHT, 0);
			blackdetecter->update();
			if(blackdetecter->onBlack()){
				changeScenario();
			}
		break;

		//黒地帯脱出直進
		case 17:
			drive->_drive(1, 8);
			if(observer->getDistance() - distance > RBESC){
				changeScenario();
			}
		break;

		//黒検知後の直線
		case 18:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > RST4){
				changeScenario();
			}
		break;

		//帰り道カーブ前の減速
		case 19:
			lineTracer->trace(17, RIGHT, 0);
			if(observer->getDistance() - distance > RBC4){
				distance = observer->getDistance();
				changeScenario();
			}
		break;

		//帰り道カーブ
		case 20:
			if(curve->runPid(7, -423, RC4, R, 10)){
				lineTracer->changeGain(0.8, 0.0, 0.01);
				changeScenario();
			}
		break;

		//帰り道カーブ後のライン復帰
		case 21:
			if(lineReturn->run(1)){
				lineTracer->changeGain(0.6, 0.0, 0.023);
				changeScenario();
			}
		break;

		//帰り道カーブ後の直線
		case 22:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > RST5){
				lineTracer->changeGain(0.8, 0.0, 0.01);
				changeScenario();
			}
		break;

		//縦列駐車前の減速
		case 23:
			lineTracer->trace(8, RIGHT, 0);
			if(observer->getDistance() - distance > RBPP){
				changeScenario();
			}
		break;

		//縦列駐車
		case 24:
			if(parkingP->run()){
				changeScenario();
			}
		break;

		//Rコース終了
		case 25:
			return true;
		break;
	}

	return false;
}
