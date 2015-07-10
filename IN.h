#pragma once
#include "Basic.h"
#include "Mogul.h"
#include "Figure.h"
#include "ParkingL.h"


class IN{
private:
    Basic *basic;
    Mogul *mogul;
    Figure *figure;
    ParkingL *parkingL;
    int phase;
public:
	IN(Basic *bs, Mogul *mg, Figure *fg, ParkingL *pL);
    ~IN();
    bool run();
};
