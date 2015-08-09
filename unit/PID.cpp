#pragma once

#include "PID.h"


PID::PID(double del, double p, double i, double d){
	delta = del;
	kp = p;
	ki = i;
	kd = d;
}

void PID::changeGain(float p, float i, float d){
	kp = p;
	ki = i;
	kd = d;
}

int PID::calc(double target, double current){
	double p, i, d;
	diff[0] = diff[1];
	diff[1] = current - target;

    integral += (diff[1] + diff[0]) / 2.0 * delta;

	p = kp * diff[1];
	i = ki * integral;
	d = kd * (diff[1] - diff[0]) / delta;

	return (int)(p + i + d);
}

int PID::calc(int target, int current){
	double p, i, d;
	diff[0] = diff[1];
	diff[1] = current - target;

    integral += (diff[1] + diff[0]) / 2.0 * delta;

	p = kp * diff[1];
	i = ki * integral;
	d = kd * (diff[1] - diff[0]) / delta;

	return (int)(p + i + d);
}
