#pragma once
//read neccessary header file
//#include header file of Motor class

class PositionEstimater {
private:
  int coordinate[2];
  int angle;
  int distance;
public:
  PositionEstimater();
  ~PositionEstimater();   
  void estimate();
};
