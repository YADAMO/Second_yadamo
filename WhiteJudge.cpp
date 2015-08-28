
#include "WhiteJudge.h"

WhiteJudge::WhiteJudge(Color *col){
	this->color = col;
	this->interval = 1;
}

bool WhiteJudge::judge(){
	if(color->getColor() == COLOR_WHITE){
		return true;
	}else{
		return false;
	}
}
