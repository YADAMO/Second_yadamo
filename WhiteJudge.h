#pragma once

#include "Judgement.h"
#include "ev3api.h"
#include "Color.h"

class WhiteJudge : public Judgement{
public:
	WhiteJudge(Color *col);
    virtual bool judge();

private:
	Color *color;
};
