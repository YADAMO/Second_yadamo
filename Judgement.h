#pragma once

class Judgement{
public:
	virtual bool judge()=0;
	int getInterval(){return interval;}
private:
protected:
	int interval;
};