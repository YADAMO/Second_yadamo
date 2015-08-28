
#include "IN.h"

IN::IN(STwinBridge *sTwinBridge,
		SBarcode *sBarcode,
		SUndetermined *sUndetermined,
		SParkingL *sParkingL)
{
	this->sTwinBridge 	= sTwinBridge;
	this->sBarcode    	= sBarcode;
	this->sUndetermined = sUndetermined;
	this->sParkingL 	= sParkingL;
}

bool IN::run(){
	return false;
}
