#pragma once

class PID{
public:
	PID(double del, double p, double i, double d);
	void changeGain(float p, float i, float d);
	int calc(double target, double current);
	int calc(int target, int current);

private:
    double delta;
    double kp;
    double ki;
    double kd;
    double diff[2];
    double integral;

};
