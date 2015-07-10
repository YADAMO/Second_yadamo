#pragma once

#define GOSTRAIGHT 1
#define TURN 2
#define LINETRACE 3

class RunPattern{
private:
public:
	RunPattern(){
		pattern = 0;
		param = 0;
		param2 = 0;
	}
	RunPattern(int pat, int prm, int ang){
		pattern = pat;
		param = prm;
		param2 = ang;
	}
	~RunPattern(){
	}
	int pattern;
	int param;
	int param2;
};
