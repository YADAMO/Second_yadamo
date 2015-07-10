#include "SectionController.h"

SectionController::SectionController()
{
	current_section = 0;
}

SectionController::~SectionController()
{
}

void SectionController::changeSection(int next_section)
{
	current_section = next_section;
}


int SectionController::getCurSection()
{
	return current_section;
}
