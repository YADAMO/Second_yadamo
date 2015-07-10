#pragma once
#include "LightSensor.h"

using namespace ecrobot;

#define BRIGHT_PLACE  0
#define DARK_PLACE 1

class OffsetHolder{
private:
	S16 black_bright;
	S16 white_bright;
	S16 black_dark;
	S16 white_dark;
public:
	OffsetHolder();
	~OffsetHolder();
	void setBlack(S16 value,int place);
	S16 getBlack(int place);
	S16 getBlack();
	void setWhite(S16 value,int place);
	S16 getWhite(int place);
	S16 getWhite();
};
