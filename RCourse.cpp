#include "RCourse.h"

<<<<<<< Updated upstream
//フル実装版
// RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob, SFigureL *sf, SLoopLine *sl, SParkingP *sp){

<<<<<<< HEAD
RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob, BlackDetecter *bd, Drive *dr){
=======

RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob, BlackDetecter *bd, Drive *dr, SFigureL *st, SLoopLine *sl, SParking *sp){
>>>>>>> Stashed changes
	lineTracer = lt;
	curve = cv;
	observer = ob;
	blackdetecter = bd;
	drive = dr;
	phase = 9;
	//figureL = sf;
	//loopline = sl;
	//parking = sp;
	//distance = 0;
=======
RCourse::RCourse(LineTracer *lt, Curve *cv, Observer *ob, SLoopLine *sl){
	lineTracer = lt;
	curve = cv;
	observer = ob;
	// figureL = sf;
	loopLine = sl;
	// parking = sp;
	distance = 0;
>>>>>>> master
}

bool RCourse::run(){
	switch(phase){
		//最初の直線
		case 0:
			lineTracer->changeGain(0.4, 0.0, 0.02);
            lineTracer->trace(15, LEFT, 0);
			if(observer->getDistance() - distance > RST1){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		//１番目カーブ前の減速
		case 1:
			// lineTracer->changeGain(0.8, 0.045, 0.08);
            lineTracer->trace(15, LEFT, 0);
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
				distance = observer->getDistance();
			}
		break;

		//１番目カーブ後の直線
		case 4:
			lineTracer->trace(15, LEFT, 0);
			if(observer->getDistance() - distance > RST2){
				changeScenario();
				distance = observer->getDistance();
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
			lineTracer->trace(10, RIGHT, 0);
			if(observer->getDistance() - distance > RAC2){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		//２番目カーブ後の直線
		case 8:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > RST3){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		//３番目カーブ
		case 8:
			if(curve->runPid(9, -365, RC2B, R)){
				changeScenario();
				lineTracer->changeGain(0.8, 0, 0.01);
				distance = observer->getDistance();
			}
		break;

		//３番目カーブ後のライン復帰
		case 7:
			lineTracer->trace(13, RIGHT, 0);
			if(observer->getDistance() - distance > RAC2){
				changeScenario();
				lineTracer->changeGain(0.48, 0.0, 0.023);
				distance = observer->getDistance();
			}
		break;

		//LFigure
		case 7:
			lineTracer->trace(13, RIGHT, 0);
			if(observer->getDistance() - distance > RAC2){
				changeScenario();
				lineTracer->changeGain(0.48, 0.0, 0.023);
				distance = observer->getDistance();
			}
		break;

		//LoopLine
		case 7:
			lineTracer->trace(13, RIGHT, 0);
			if(observer->getDistance() - distance > RAC2){
				changeScenario();
				lineTracer->changeGain(0.48, 0.0, 0.023);
				distance = observer->getDistance();
			}
		break;

		//黒検知+ライントレース
		case 9:
			lineTracer->changeGain(0.48, 0.0, 0.02); //お試し用
			lineTracer->trace(9, RIGHT, 0);
			if(blackdetecter->onBlack()){
				changeScenario();
				ev3_speaker_play_tone(NOTE_C4, 100);
				distance = observer->getDistance();
			}
		break;

		//黒地帯脱出直進
		case 10:
			drive->_drive(1, 8);
			if(observer->getDistance() - distance > RBESC){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		//黒検知後の直線
		case 11:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > RST4){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		//帰り道カーブ前の減速
		case 12:

			lineTracer->trace(17, RIGHT, 0);
			if(observer->getDistance() - distance > RBC4){
				changeScenario();
				distance = observer->getDistance();
				lineTracer->changeGain(0.2, 0, 0.0);
			}
		break;

		//帰り道カーブ
		case 13:
			if(curve->runPid(9, -423, RC4, R)){
				changeScenario();
				lineTracer->changeGain(0.8, 0, 0.01);
				distance = observer->getDistance();
			}
		break;

		//帰り道カーブ後のライン復帰
		case 14:
			lineTracer->trace(13, RIGHT, 0);
			if(observer->getDistance() - distance > RAC4){
				changeScenario();
				lineTracer->changeGain(0.6, 0.0, 0.023);
				distance = observer->getDistance();
			}
		break;

		//帰り道カーブ後の直線
		case 15:
			lineTracer->trace(20, RIGHT, 0);
			if(observer->getDistance() - distance > RST5){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		//縦列駐車位置までバック
		case 16:
			drive->_drive(0, -15);
			if(distance - observer->getDistance() > RBACK){
				changeScenario();
				distance = observer->getDistance();
			}
		break;

		//縦列駐車
		case 17:
			changeScenario();
		break;

		case 18:
			return true;
		break;
	}

	return false;
}
