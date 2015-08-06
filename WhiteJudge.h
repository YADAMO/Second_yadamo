#pragma once

#include "Judgement.h"

// IExample具象クラス1
class WhiteJudge : public Judgement
{
public:
	WhiteJudge();
    virtual bool judge();

private:
};
