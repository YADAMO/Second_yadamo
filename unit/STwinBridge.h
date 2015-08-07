#pragma once

#include "SenarioController.h"
#include "ev3api.h"

using namespace ev3api;

class STwinBridge : public SenarioController{
public:
	STwinBridge();
    virtual bool judge();

private:
};
