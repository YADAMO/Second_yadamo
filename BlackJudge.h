#pragma once

#include "Judgement.h"
#include "Color.h"
#include "ev3api.h"

class BlackJudge : public Judgement{
public:
	BlackJudge(Color *col);
    virtual bool judge();

private:
	Color *color;
};
