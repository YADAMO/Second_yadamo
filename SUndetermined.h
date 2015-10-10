#pragma once
#include <stdlib.h>
//#include <vector>

#include "SBarcode.h"
#include "Observer.h"
#include "Drive.h"
#include "DistanceMeter.h"
#include "ScenarioController.h"
#include "LineReturn.h"
#include "LineTracer.h"
#include "Stepper.h"

class SUndetermined : public ScenarioController{
public:

    SBarcode *barCode;
    Drive *drive;
    Observer *observer;
    LineReturn *lineReturn;
    LineTracer *lineTracer;
    Stepper *stepper;

	SUndetermined(SBarcode *bc, Drive *dri, Observer *obs, LineReturn *lr, LineTracer *lt, Stepper *st);
   // int getRunPattern(std::vector<int> bit_array);
    virtual bool run();

private:
    int phase;
    int run_on_board_pattern;
    int start_position;
    int tmp_distance;
    int runtime;
	double distance;
    
    int calcManhattanDistance(int pos_1, int pos_2);
    int getRunPattern(unsigned char c);
    int checkRoutePattern(int p1, int p2);
	void changeScenario();
    //Point2 decideStartPosition(std::vector<Point2> p_vec);
    // std::vector<Point2> bitary2BottlesPos(std::vector<int> bit_array);
    // std::vector<int> uchar2bitary(unsigned char c);

};
