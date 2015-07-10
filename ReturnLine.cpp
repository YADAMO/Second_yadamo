#include "ReturnLine.h"

ReturnLine::ReturnLine(Driver *argDriver, LightSensor *argLightSensor, ColorDetector *argColorDetector)
{
	returnLine_time = 0;
	driver = argDriver;
  	lightSensor = argLightSensor;
  	colorDetector = argColorDetector;
  	black_isleft = false;
}

ReturnLine::~ReturnLine()
{
}

//左エッジで復帰したい場合
//これのtrueを確認したあとに左エッジの低速ライントレース
bool ReturnLine::returnLineLeft()
{
	returnLine_time += 4;
	if(!black_isleft){
		if(returnLine_time < 5000){
			driver->drive(-60, 20);
			if(colorDetector->blackLineDetect()){
				black_isleft = true;
				returnLine_time = 0;
			}
			return false;
		}else if(returnLine_time < 6000){
			driver->drive(-60, 0);
			return false;
		}else if(returnLine_time < 11000){
			driver->drive(-60, -20);
			return false;
		}else if(returnLine_time < 16000){
			driver->drive(0, 0);
			return true;
		}
	}else{
		if(returnLine_time < 2000){
			driver->drive(80, 10);
			return false;
		}else{
			driver->drive(0, 0);
			return true;
		}
	}
	return false;
}

//右エッジで復帰したい場合
//これのtrueを確認したあとに右エッジの低速ライントレース
bool ReturnLine::returnLineRight()
{
	returnLine_time += 4;
	if(!black_isleft){
		if(returnLine_time < 5000){
			driver->drive(60, 20);
			if(colorDetector->blackLineDetect()){
				black_isleft = true;
				returnLine_time = 0;
			}
			return false;
		}else if(returnLine_time < 6000){
			driver->drive(60, 0);
			return false;
		}else if(returnLine_time < 11000){
			driver->drive(60, -20);
			return false;
		}else if(returnLine_time < 16000){
			driver->drive(0, 0);
			return true;
		}
	}else{
		if(returnLine_time < 2000){
			driver->drive(-80, 10);
			return false;
		}else{
			driver->drive(0, 0);
			return true;
		}
	}
	return false;
}
