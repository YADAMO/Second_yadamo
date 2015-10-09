#pragma once

#include "Color.h"

#define BUFFSIZE 50

class BlackDetecter{
public:
	BlackDetecter(Color *co);
	void update();
	bool onBlack();
private:
	Color *color;
	bool buff[BUFFSIZE];

};