#pragma once

#include "Calibration.h"

Calibration::Calibration(ColorSensor *color, Observer *obs, Clock *clk){
  this->colorSensor = color;
  this->observer = obs;
  this->clock = clk;
  touchCount = 0;
  judge = false;
  white = 0;
  black = 0;
  green = 0;
}

/**
 * キャリブレーションする
 */
void Calibration::doCalibration() {
    while(true){
    judge = observer->isTouch();
    if(judge){
      touchCount++;
      if(touchCount == 1){
        white = colorSensor->getBrightness();
        setWhite(white);
        ev3_speaker_play_tone(NOTE_C4, 100);
        judge = false;
      }else if(touchCount == 2){
        black = colorSensor->getBrightness();
        setBlack(black);
        ev3_speaker_play_tone(NOTE_D4, 100);
        judge = false;
      }else if(touchCount == 3){
        green = colorSensor->getBrightness();
        setGreen(green);
        ev3_speaker_play_tone(NOTE_F4, 100);
        judge = false;
      }else if(touchCount == 4){
        // lineTracer->setTarget(((float)white + (float)black) / 2);
        // lineTracer->calcAllTarget();
        ev3_speaker_play_tone(NOTE_G4, 100);
        judge = false;
        break;
      }
    }
    clock->wait(10);
  }
}


void Calibration::setWhite(int value) {
  white = value;
}
void Calibration::setBlack(int value) {
  black = value;
}
void Calibration::setGreen(int value) {
  green = value;
}

int Calibration::getWhite(){
  return white;
}
int Calibration::getBlack(){
  return black;
}
int Calibration::getGreen(){
  return green;
}
