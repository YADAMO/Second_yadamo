#include "ColorDetector.h"

ColorDetector::ColorDetector(LightSensor *argLightSensor, OffsetHolder *oH){
    // threshold = 0;
    // buffer = 0;
    lightSensor = argLightSensor;
    oHolder = oH;

    runtime = 0;
}

bool ColorDetector::grayDetect(){
    // bool isGray;
    
    // return isGray;
    return true;
}

bool ColorDetector::blackLineDetect(){
    if(runtime < 56){
        runtime += 4;
    }else{
        runtime = 0;
    }
    buffer[runtime/4] = lightSensor->getBrightness();

    int sum = 0;
    for(int i = 0; i < 15; i++){
        sum += (int)buffer[i];
    }

    if(lightSensor->getBrightness() < oHolder->getBlack() + 25){
        return true;
    }else{
        return false;
    }
}

bool ColorDetector::blackLineDetect(int i){
    if(runtime < 56){
    	runtime += 4;
    }else{
    	runtime = 0;
    }
   	buffer[runtime/4] = lightSensor->getBrightness();

    int sum = 0;
    for(int i = 0; i < 15; i++){
    	sum += (int)buffer[i];
    }

    if(i == 1){
        if(lightSensor->getBrightness() < oHolder->getBlack(DARK_PLACE) + 25){
        	return true;
        }else{
        	return false;
        }
    }else{
        if(lightSensor->getBrightness() < oHolder->getBlack() + 25){
            return true;
        }else{
            return false;
        }
    }
}
