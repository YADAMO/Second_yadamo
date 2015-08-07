#pragma once

#include "ScenarioController.h"
#include "SFigureL.h"
#include "SLoopLine.h"
#include "SParkingP.h"

/*--------------------------
アウトコース内容
フィギュアL 	SFigureL
環状線		SLoopLine
縦列駐車		SParkingP
---------------------------*/

class OUT : public ScenarioController{
public:
	OUT(SFigureL *sFigureL,
		SLoopLine *sLoopLine,
		SParkingP *sParkingP);
    virtual bool run();

private:
	SFigureL *sFigureL;
	SLoopLine *sLoopLine;
	SParkingP *sParkingP;
};
