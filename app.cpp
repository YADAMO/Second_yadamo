/**
 * This sample program balances a two-wheeled Segway type robot such as Gyroboy in EV3 core set.
 *
 * References:
 * http://www.hitechnic.com/blog/gyro-sensor/htway/
 * http://www.cs.bgu.ac.il/~ami/teaching/Lejos-2013/classes/src/lejos/robotics/navigation/Segoway.java
 */

#include "ev3api.h"
#include "app.h"

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#include "libcpp-test.h"

//センサ周り
#include "Motor.h"
#include "Gyro.h"
#include "Color.h"
#include "Touch.h"
#include "Sonic.h"
#include "Battery.h"

// 判断クラス系
#include "Observer.h"
#include "WhiteJudge.h"
#include "BlackJudge.h"
#include "GreenJudge.h"
#include "TouchJudge.h"
#include "ObstacleJudge.h"
#include "BlackDetecter.h"

// 計測器系
#include "DistanceMeter.h"
#include "SpeedMeter.h"

// シナリオ系
#include "LCourse.h"
#include "RCourse.h"
#include "SBarcode.h"
#include "SFigureL.h"
#include "SLoopLine.h"
#include "SParkingL.h"
#include "SParkingP.h"
#include "STwinBridge.h"
#include "SUndetermined.h" 
#include "LineReturn.h"

#include "Curve.h"
#include "LCourse.h"
#include "Choilie.h"
#include "Stepper.h"
#include "LineReturn.h"

// その他
#include "LineTracer.h"
#include "Drive.h"
#include "Logger.h"
#include "Calibration.h"
#include "Observer.h"



#include <stdlib.h>
#include <string>
#include <sstream>

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

using namespace std;

void destroy();
void logging();
void display();

bool calibration_flag = false;
int phase = 0;

// オブジェクトの定義
Motor rightMotor(EV3_PORT_B);
Motor leftMotor(EV3_PORT_C);
Motor frontMotor(EV3_PORT_D);
Gyro gyro(EV3_PORT_4);
Color color(EV3_PORT_3);
Touch touch(EV3_PORT_1);
Sonic sonic(EV3_PORT_2);

WhiteJudge whiteJudge(&color);
BlackJudge blackJudge(&color);
GreenJudge greenJudge(&color);
TouchJudge touchJudge(&touch);
ObstacleJudge obstacleJudge(&sonic);
DistanceMeter distanceMeter(&rightMotor, &leftMotor);
Logger logger;

Observer observer(&color, &obstacleJudge, &touchJudge, &distanceMeter, &rightMotor, &leftMotor, &frontMotor);
Drive drive(&rightMotor, &leftMotor, &frontMotor, &observer);
LineTracer lineTracer(&drive, &color);
Calibration calibration(&color, &touchJudge, &lineTracer);
Curve curve(&drive, &observer, &frontMotor, &rightMotor, &leftMotor, &color, &lineTracer);
Choilie choilie(&drive, &observer);
STwinBridge bridge(&lineTracer, &observer, &drive, &choilie);
Stepper stepper(&drive, &lineTracer, &observer);
BlackDetecter blackDetecter(&color);
SBarcode barcode(&lineTracer, &observer, &drive, &logger, &stepper);
LineReturn lineReturn(&lineTracer, &observer, &drive);
SFigureL sfigureL(&drive, &lineTracer, &observer, &stepper, &curve, &blackDetecter);
SUndetermined undetermined(&barcode, &drive, &observer, &lineReturn, &lineTracer, &stepper);
SLoopLine loopLine(&lineTracer, &observer, &drive, &stepper, &curve);
SParkingP parkingP(&observer, &drive, &curve);
SParkingL parkingL(&lineTracer, &observer, &drive);

LCourse lcorse(&lineTracer, &curve, &observer, &bridge, &lineReturn, &barcode, &undetermined, &drive);
RCourse rcourse(&lineTracer, &curve, &observer, &blackDetecter, &drive, &sfigureL, &loopLine, &parkingP, &lineReturn);

void yadamo_task(intptr_t exinf){
  observer.update();
    if (ev3_button_is_pressed(BACK_BUTTON)) {
        wup_tsk(MAIN_TASK);  // メインタスクを起こす
    }else{
        if(!calibration_flag){
            calibration_flag = calibration.doCalibration();
        }else{
           // logging();
           if(lcorse.run()){
            // if(choilie.run()){
            // if(curve.curve(5, 40, 50, L, 10, L)){
                wup_tsk(MAIN_TASK);
                // drive.init(true);
           }
        }
    }
    ext_tsk();
}

void miri_cyc(intptr_t exinf){
    act_tsk(YADAMO_TASK);
}

void main_task(intptr_t unused) {
    ev3_sta_cyc(MIRI_CYC);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    ev3_stp_cyc(MIRI_CYC);

    destroy();

    ext_tsk();
}

void logging(){
    logger.addData((double)observer.getRuntime());
    logger.addData((double)rightMotor.getAngle());
    logger.addData((double)leftMotor.getAngle());
    logger.addData((double)observer.Fangle);
    logger.addData((double)color.getReflect());
    logger.send();
}

void destroy(){
    ev3_speaker_play_tone(NOTE_G4, 1000);
    logger.end();
    bool back = false;
    frontMotor.setRotate(observer.Fangle, 100, true);
    rightMotor.setSpeed(0);
    leftMotor.setSpeed(0);
    int count = 0;

    while(1){
        if(count > 100000){
            break;
        }
        count++;
    }

    if(back){
        rightMotor.setRotate(rightMotor.getAngle(), 35, false);
        leftMotor.setRotate(leftMotor.getAngle(), 35, false);
    }else{
        rightMotor.setSpeed(0);
        leftMotor.setSpeed(0);
    }
}

void display(){
    char br[64] = "";
    char tr[64] = "";
    char ar[64] = "";

    sprintf(br, "%d", (int)rightMotor.getAngle());
    sprintf(tr, "%d", (int)leftMotor.getAngle());
    sprintf(ar, "%d", (int)frontMotor.getAngle());

    ev3_lcd_draw_string("            ", 0, 40);
    ev3_lcd_draw_string("            ", 0, 48); 
    ev3_lcd_draw_string(br, 0, 40);
    ev3_lcd_draw_string(tr, 0, 48);            
    ev3_lcd_draw_string(ar, 0, 56); 
}
