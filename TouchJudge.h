#pragma once

#include "Judgement.h"
#include "ev3api.h"
#include "Touch.h"

class TouchJudge : public Judgement{
public:
	TouchJudge(Touch *tou);
    virtual bool judge();

private:
	Touch *touch;
};