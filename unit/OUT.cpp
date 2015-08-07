#pragma once

#include "OUT.h"

OUT::OUT(SFigureL *sFigureL,
		SLoopLine *sLoopLine,
		SParkingP *sParkingP)
{
	this->sFigureL 	= sFigureL;
	this->sLoopLine = sLoopLine;
	this->sParkingP = sParkingP;
}

bool OUT::run(){
	return false;
}
