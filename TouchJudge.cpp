
#include "TouchJudge.h"

TouchJudge::TouchJudge(Touch *tou){
	this->touch = tou;
	interval = 1;
}

bool TouchJudge::judge(){
	if(touch->isPush() == true){
		return true;
	}else{
		return false;
	}
}
