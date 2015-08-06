#pragma once

#include "Judgement.h"

// IExample具象クラス1
class WhiteJudge : public Judgement
{
public:
    virtual bool judge();

private:
};
