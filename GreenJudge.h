#pragma once

#include "Judgement.h"
#include "ev3api.h"
#include "Color.h"

class GreenJudge : public Judgement{
public:
	GreenJudge(Color *col);
    virtual bool judge();

private:
	Color *color;
};