
#include "SLoopLine.h"

SLoopLine::SLoopLine(LineTracer *lt, Observer *ob, Drive *dr){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	runtime = 0;
}

bool SLoopLine::run(){
	bool end = false;
	switch(phase){
		case 0:
			//超音波が反応したらケース1へ
			break;
		case 1:
			//段差のぼったらケース2へ
			break;
		case 2:
			//ある程度ライントレースしたらケース3へ
			break;
		case 3:
			//超音波が反応したらケース4へ
			break;
		case 4:
			//ある程度ライントレースする
			break;
		default:
			break;
	}
	runtime++;
	return end;
}
