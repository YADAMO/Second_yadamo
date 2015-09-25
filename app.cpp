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

bool calibration_flag = false;


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
Observer observer(&whiteJudge, &blackJudge, &greenJudge, &obstacleJudge, &touchJudge, &distanceMeter, &rightMotor, &leftMotor, &frontMotor);
Drive drive(&rightMotor, &leftMotor, &frontMotor, &observer);
LineTracer lineTracer(&drive, &color);
Calibration calibration(&color, &touchJudge, &lineTracer);

void miri_cyc(intptr_t exinf){
    act_tsk(YADAMO_TASK);
}

void yadamo_task(intptr_t exinf){
    observer.update();
    

    // if (ev3_button_is_pressed(BACK_BUTTON)) {
    if(observer.getDistance() > 300){
        wup_tsk(MAIN_TASK);  // バックボタン押下
    }else{
        if(!calibration_flag){

            calibration_flag = calibration.doCalibration();
            drive.init();
        }else{
            // drive.straight(10);
            drive._drive(10, 20);
           logging();
            // int a = lineTracer.trace(20, RIGHT, 0);
   
            char br[64] = "";
            char tr[64] = "";
            char ar[64] = "";

            sprintf(br, "%d", rightMotor.getAngle());
            sprintf(tr, "%d", leftMotor.getAngle());
            sprintf(ar, "%d", frontMotor.getAngle());

            // ev3_lcd_draw_string("            ", 0, 40);
            // ev3_lcd_draw_string("            ", 0, 48); 
            ev3_lcd_draw_string(br, 0, 40);
            ev3_lcd_draw_string(tr, 0, 48);            
            ev3_lcd_draw_string(ar, 0, 56);            
            // drive._drive(0, 10);
            // lineTracer.trace(20, RIGHT, 0);
            // drive.straight(20);
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
    // logger.addData((double)lineTracer.trace(20, RIGHT, 0));
    logger.addData((double)gyro.getAngle());
    
    // logger.addData((double)lineTracer.trace(5, LEFT));
    // logger.addData((double)sonic.getDistance());
    logger.send();
}


void destroy(){

        
        // rightMotor.setSpeed(0);
        // leftMotor.setSpeed(0);
        logger.end();
        frontMotor.setRotate(observer.Fangle, 100, true);
        rightMotor.setRotate(rightMotor.getAngle(), 15, false);
        leftMotor.setRotate(leftMotor.getAngle(), 15, false);

    while(1){
        if(ev3_button_is_pressed(BACK_BUTTON)){
            break;
        }

    }
    // delete rightMotor;
    // delete leftMotor;
    // delete frontMotor;
    // delete gyro;
    // delete color;
    // delete touch;
    // delete sonic;
    // delete whiteJudge;
    // delete blackJudge;
    // delete greenJudge;
    // delete touchJudge;
    // delete obstacleJudge;
    // delete distanceMeter;
    // delete logger;
    // delete observer;
    // delete drive;
    // delete lineTracer;
    // delete calibration;

}
