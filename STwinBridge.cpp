
#include "STwinBridge.h"

STwinBridge::STwinBridge(LineTracer *lt, Observer *ob, Drive *dr){
	lineTracer = lt;
	observer = ob;
	drive = dr;
	runtime = 0;
}

bool STwinBridge::run(){
	bool end = false;
	switch(phase){
		case 0:
			//チョイリーしたらケース1へ
			break;
		case 1:
			//ある程度ライントレースしたらケース2へ
			break;
		case 2:
			//橋にぶつかるまでバックしたらケース3へ
			break;
		case 3:
			//ライン検知したらケース4へ
			break;
		case 4:
			//終わり
			break;
		default:
			break;
	}
	runtime++;
	return end;
}
