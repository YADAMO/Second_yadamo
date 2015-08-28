#pragma once

class ScenarioController{
public:
	ScenarioController();
	virtual bool run()=0;
private:
	void changeScenario();
	int phase;
};