#pragma once

#include <cstdint>

class PID{
public:
	PID(double p, double i, double d);
	void changeGain(float p, float i, float d);
	int calc(double target, double current);
	int calc(int target, int current);
    int calc(uint8_t target, uint8_t current);
private:
    double delta;
    double kp;
    double ki;
    double kd;
    double diff[2];
    double integral;

};
