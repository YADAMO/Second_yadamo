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
<<<<<<< Updated upstream
=======
#include "Curve.h"
#include "LCourse.h"
#include "Choilie.h"
#include "Stepper.h"
>>>>>>> Stashed changes

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
Choilie choilie(&drive, &observer);
STwinBridge bridge(&lineTracer, &observer, &drive, &choilie);
Stepper stepper(&drive, &lineTracer, &observer);
SFigureL sfigureL(&drive, &lineTracer, &observer, &stepper, &curve);

LCourse lcorse(&lineTracer, &curve, &observer, &bridge);


void miri_cyc(intptr_t exinf){
    act_tsk(YADAMO_TASK);
}

void yadamo_task(intptr_t exinf){
  observer.update();
    if (ev3_button_is_pressed(BACK_BUTTON)) {
        wup_tsk(MAIN_TASK);  // メインタスクを起こす
    }else{
        if(!calibration_flag){
            calibration_flag = calibration.doCalibration();
        }else{
           logging();
           // if(lcorse.run()){
           if(sfigureL.run()){
                wup_tsk(MAIN_TASK);
           }
        }
    }
    ext_tsk();
}



void main_task(intptr_t unused) {

    
    // 周期ハンドラ停止
    ev3_stp_cyc(MIRI_CYC);

    destroy();

    ext_tsk();
}

void destroy(){
    logger.end();
    bool back = true;
    frontMotor.setRotate(observer.Fangle, 100, true);
    if(back){
        rightMotor.setRotate(rightMotor.getAngle(), 35, false);
        leftMotor.setRotate(leftMotor.getAngle(), 35, false);
    }else{
        rightMotor.setSpeed(0);
        leftMotor.setSpeed(0);
    }
}
