#pragma once

#include "ScenarioController.h"

ScenarioController::ScenarioController(){
	phase = 0;
}

void ScenarioController::changeScenario(){
	phase++;
}