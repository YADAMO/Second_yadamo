
#include "Calibration.h"

Calibration::Calibration(Color *col, TouchJudge *tj){
  color = col;
  touchJudge = tj;

  touchCount = 0;
  tc = 0;
  judge = false;
  white = -1;
  black = -1;
  green = -1;
  gray = -1;
  target = 0;
}

/**
 * キャリブレーションする
 */
void Calibration::doCalibration() {

  while(1){
    if(touchJudge->judge()){
      tc++;
    }else{
      tc = 0;
    }

    if(tc == 5){
      judge = true;
    }else{
      judge = false;
    }

    if(judge){
      switch(touchCount){
        case 0:
          white = color->getReflect();
          ev3_speaker_play_tone(NOTE_C4, 100);
          touchCount++;
        break;

        case 1:
          black = color->getReflect();
          ev3_speaker_play_tone(NOTE_D4, 100);
          touchCount++;
        break;

        case 2:
          gray = color->getReflect();
          ev3_speaker_play_tone(NOTE_F4, 100);
          touchCount++;
        break;

        case 3:
          green = color->getReflect();
          ev3_speaker_play_tone(NOTE_G4, 100);
          touchCount++;
        break;
      }

    }
    drawLCD();
    if(touchCount == 4){
      target = (white + black)/2;
      break;
    }
    
  }

}

void Calibration::drawLCD(){
  ev3_lcd_set_font(EV3_FONT_MEDIUM);
    char w[64] = "";
    char b[64] = "";
    char gra[64] = "";
    char gre[64] = "";
    
    sprintf(w, "white = %d", white);
    sprintf(b, "black = %d", black);
    sprintf(gra, "gray = %d", gray);
    sprintf(gre, "green = %d", green);

    ev3_lcd_draw_string(w, 0, 8);
    ev3_lcd_draw_string(b, 0, 24);
    ev3_lcd_draw_string(gra, 0, 40);
    ev3_lcd_draw_string(gre, 0, 56);
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

int Calibration::getTarget(){
  return target;
}
