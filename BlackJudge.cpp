
#include "BlackJudge.h"

BlackJudge::BlackJudge(Color *col){
	this->color = col;
	this->interval = 1;
}

bool BlackJudge::judge(){
	if(color->getColor() == COLOR_BLACK){
		return true;
	}else{
		return false;
	}
}
