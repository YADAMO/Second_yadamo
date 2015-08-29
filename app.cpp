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
Observer observer(&whiteJudge, &blackJudge, &greenJudge, &obstacleJudge, &touchJudge, &distanceMeter);
// Drive drive(&rightMotor, &leftMotor, &frontMotor, &observer);
// Drive drive(&rightMotor, &leftMotor, &frontMotor);
Calibration calibration(&color, &touchJudge);
// LineTracer lineTracer(&drive, &color, &calibration);



void loggging_cyc(intptr_t exinf){
    // logger.addData(1.00);
    // logger.addData(2.00);
    // logger.addData(3.00);
    // logger.addData(4.00);
    // logger.addData(5.00);
    // logger.addData(6.00);
    // logger.addData(7.00);
    // logger.addData(8.00);
    // logger.addData(9.00);
    // logger.addData(10.00);
    // logger.addData(11.00);
    // logger.addData(12.00);
    // logger.addData(13.00);
    // logger.addData(14.00);
    // logger.addData(15.00);
    // logger.addData(16.00);

    // logger.send();
    char bright[64] = "";
    char ambient[64] = "";

    sprintf(bright, "bright = %d", color.getReflect());
    sprintf(ambient, "ambient = %d", color.getAmbient());
    ev3_lcd_draw_string(bright, 0, 72);
    ev3_lcd_draw_string(ambient, 0, 88);

    // logger.addData((double)color.getReflect());
    // logger.send();
    // lineTracer.trace(10, RIGHT);
    // drive.drive(15,30);     
}

void main_task(intptr_t unused) {
    calibration.doCalibration();  
    
    ev3_sta_cyc(LOGGING_CYC);

}
