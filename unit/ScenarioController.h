#pragma once

class ScenarioController{
public:
	ScenarioController();
	virtual bool run(){}
private:
	void changeScenario();
	int phase;
};