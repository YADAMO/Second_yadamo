#include "Calibration.h"

Calibration::Calibration(Color *col, TouchJudge *tj, LineTracer *lt){
  color = col;
  touchJudge = tj;
  lineTracer = lt;

  touchCount = 0;
  tc = 0;
  judge = false;
  white = 0;
  black = 0;
  green = 0;
  gray = 0;
  target = 0;
}

/**
 * キャリブレーションする
 */
bool Calibration::doCalibration() {
  int cali_time = 0;
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

    //追加キャリブレーション
    //それっぽいスタート位置に走行体をセットしたらうるさくなる
    if(touchCount == 4 && color->getReflect() >= target && color->getReflect() < target + 7){
      if(cali_time % 200 == 0){
        ev3_speaker_play_tone(NOTE_C4, 100);
        cali_time = 0;
      }
      cali_time++;
    }

    if(judge){
      switch(touchCount){
        case 0:
          white = color->getReflect();
          lineTracer->white = white;
          ev3_speaker_play_tone(NOTE_C4, 100);
          touchCount++;
        break;

        case 1:
          black = color->getReflect();
          lineTracer->black = black;
          target = (white + black)/2;
          lineTracer->target = target;
          lineTracer->target2 = target;
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

        case 4:
          touchCount++;
        break;

        case 5:
          touchCount++;
        break;
      }

    }
    drawLCD();
    if(touchCount == 6){
      return true;
      break;
    }
    
  }

  return false;

}

void Calibration::drawLCD(){
  ev3_lcd_set_font(EV3_FONT_SMALL);
    char w[64] = "";
    char b[64] = "";
    char gra[64] = "";
    char gre[64] = "";
    char tar[64] = "";
    char bat[64] = "";
    
    sprintf(w, "white = %d", white);
    sprintf(b, "black = %d", black);
    sprintf(gra, "gray = %d", gray);
    sprintf(gre, "green = %d", green);
    sprintf(tar, "target = %d", target);
    sprintf(bat, "battery = %d %%", (int)((double)ev3_battery_voltage_mV() / 9400.0 * 100.0));

    ev3_lcd_draw_string(w, 0, 0);
    ev3_lcd_draw_string(b, 0, 8);
    ev3_lcd_draw_string(gra, 0, 16);
    ev3_lcd_draw_string(gre, 0, 24);
    ev3_lcd_draw_string(tar, 0, 32);
    ev3_lcd_draw_string(bat, 0, 40);
}


void Calibration::setWhite(uint8_t value) {
  white = value;
}
void Calibration::setBlack(uint8_t value) {
  black = value;
}
void Calibration::setGreen(uint8_t value) {
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
