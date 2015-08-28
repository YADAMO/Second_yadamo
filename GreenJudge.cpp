
#include "GreenJudge.h"

GreenJudge::GreenJudge(Color *col){
	this->color = col;
	this->interval = 1;
}

bool GreenJudge::judge(){
	if(color->getColor() == COLOR_GREEN){
		return true;
	}else{
		return false;
	}
}