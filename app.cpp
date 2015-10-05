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

// 計測器系
#include "DistanceMeter.h"
#include "SpeedMeter.h"

// シナリオ系
#include "IN.h"
#include "OUT.h"
#include "SBarcode.h"
#include "SFigureL.h"
#include "SLoopLine.h"
#include "SParkingL.h"
#include "SParkingP.h"
#include "STwinBridge.h"
#include "SUndetermined.h" 
#include "Curve.h"
#include "LCourse.h"

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
SBarcode barcode(&lineTracer, &observer, &drive, &logger);
Curve curve(&drive, &observer, &frontMotor, &rightMotor, &leftMotor, &color, &lineTracer);
LCourse lcorse(&lineTracer, &curve, &observer);

void miri_cyc(intptr_t exinf){
    act_tsk(YADAMO_TASK);
}

void yadamo_task(intptr_t exinf){
  observer.update();
    if (ev3_button_is_pressed(BACK_BUTTON)) {
    // if(observer.getDistance() > 200){
        wup_tsk(MAIN_TASK);  // メインタスクを起こす
    }else{
        if(!calibration_flag){

            calibration_flag = calibration.doCalibration();
        }else{

           logging();

           if(lcorse.run()){
                wup_tsk(MAIN_TASK);
           }

        // switch(phase){
        // case 0:
        //     // curve.run();
        //     // lineTracer.traceFfixed(20, RIGHT, 0);
        //     // if(observer.getDistance() > 490){
        //         // phase++;
        //     // }
        //     // if(drive.turn(45, 1, 8)){
        //     // if(curve.run(-15, -20, -450, 5000)){
        //     if(curve.runPid(10, -450, 65, R)){
        //         phase++;
        //     }
        // break;
        // case 1:
        //     wup_tsk(MAIN_TASK);
        //     // if(curve.run(-15, -50, -400, 70))    phase++;
        // break;
        // case 2:
        //     //lineTracer.traceFfixed(20, RIGHT, 0);
        // break;
        //     }
        }
    }


    ext_tsk();
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


    logger.addData((double)color.getReflect());
    // logger.addData((double)curve.runPid(35, -470, 70, R));
    logger.addData((double)observer.getSpeed());
    
    // logger.addData((double)lineTracer.trace(5, LEFT));
    // logger.addData((double)sonic.getDistance());
    logger.send();
}


void destroy(){
    logger.end();
    bool back = false;
    frontMotor.setRotate(observer.Fangle, 100, true);
    if(back){
        rightMotor.setRotate(rightMotor.getAngle(), 25, false);
        leftMotor.setRotate(leftMotor.getAngle(), 25, false);
    }else{
        rightMotor.setSpeed(0);
        leftMotor.setSpeed(0);
    }       

    while(1){
        if(ev3_button_is_pressed(BACK_BUTTON)){
            break;
        }

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
