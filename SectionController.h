#pragma once
#include "ColorDetector.h"
#include "PositionEstimater.h"
#include "LineTracer.h"


class SectionController
{
public:
	SectionController();
	~SectionController();
	void changeSection(int setting_position);
	int getCurSection();
private:
	int current_section;
};
