
#include "Choilie.h"

Choilie::Choilie(LineTracer *lt, Observer *ob, Drive *dr){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	runtime = 0;
}

bool Choilie::run(){
	bool end = false;
	switch(phase){
		case 0:
			//段差まで低速ライントレースしたらケース1へ
			break;
		case 1:
			//少しバックしたらケース2へ
			break;
		case 2:
			//段差昇るまで高速前進したらケース3へ
			break;
		case 3:
			//終わり
			break;
		default:
			break;
	}
	runtime++;
	return end;
}
