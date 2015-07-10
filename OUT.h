#pragma once
#include "Basic.h"
#include "Jumper.h"
#include "GridRunner.h"
#include "ParkingP.h"


class OUT{
private:
    Basic *basic;
    Jumper *jumper;
    GridRunner *gridRunner;
    ParkingP *parkingP;
    int phase;
public:
	OUT(Basic *bs, Jumper *jp, GridRunner *gr, ParkingP *pP);
    ~OUT();
    bool run();
};
