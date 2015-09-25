#pragma once

class ScenarioController{
public:
	ScenarioController();
	virtual bool run()=0;
	void changeScenario();
	int phase;
private:
};