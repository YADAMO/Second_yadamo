
#include "SFigureL.h"

SFigureL::SFigureL(DistanceMeter *dm, Drive *dr, LineTracer *lt, Observer *ob){
	phase = 1;
}

bool SFigureL::run(){
	// switch(phase) {
	// 	case 1: // 段差を登るlog
	// 	case 2: // 右エッジでライントレースする
	// 	case 3: // 黒色を検知する
	// 	case 4: // 右に90度旋回する
	// 	case 5: // 右エッジでライントレースする
	// 	case 6: // 段差を登る
	// }
	return false;
}
