#pragma once
//read neccessary header file
#include "Motor.h"

#define MAX_STEERING_ANGLE  270
#define TURN_BASE_SPEED 70

using namespace ecrobot;

class Driver {
private:
  Motor *motorL;
  Motor *motorR;
  Motor *motorS;
  S32 rightOffset, leftOffset;
  int calcSteerAngle(S8 right, S8 left);

public:
  Driver(Motor *L, Motor *R, Motor *S);
  ~Driver();   
  void drive(int turn, int speed);
  void backDrive(int turn, int speed); 
  void turn(int angle);
  void straightInit();
  void straight(int speed);
  int steerAngle;
  void operate(int leftA, int rightA);
};
