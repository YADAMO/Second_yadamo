#pragma once

#include "ScenarioController.h"
#include "STwinBridge.h"
#include "SBarcode.h"
#include "SUndetermined.h"
#include "SParkingL.h"

/*--------------------------
インコース内容
二本橋 	STwinBridge
バーコード	SBarcode
仕様未確定	SUndetermined
直角駐車	SParkingL
---------------------------*/

class IN : public ScenarioController{
public:
	IN(STwinBridge *sTwinBridge,
		SBarcode *sBarcode,
		SUndetermined *sUndetermined,
		SParkingL *sParkingL);
    virtual bool run();

private:
	STwinBridge *sTwinBridge;
	SBarcode *sBarcode;
	SUndetermined *sUndetermined;
	SParkingL *sParkingL;
};
