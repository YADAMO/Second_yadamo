
#include "LineReturn.h"

LineReturn::LineReturn(LineTracer *lt, Observer *ob, Drive *dr){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	runtime = 0;
}

bool LineReturn::run(){
	bool end = false;
	switch(phase){
		case 0:
			//色検出もーどで色検知
			//左に旋回する
				//もしラインがあったならケース1へ
				//ラインがなかったならケース2へ
			break;
		case 1:
			//ある程度右へ旋回する　その後ケース4へ
			break;
		case 2:
			//色検出モードで色検知
			//右旋回する
				//ラインがあったならケース3へ
			break;
		case 3:
			//ある程度←へ旋回する　その後ケース4へ
			break;
		case 4:
			//ライントレースする
			break;
		default:
			break;
	}
	runtime++;
	return end;
}
