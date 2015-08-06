#pragma once

class Judgement{
public:
	virtual bool judge(){}
	int getInterval(){return interval;}
private:
protected:
	int interval;
};