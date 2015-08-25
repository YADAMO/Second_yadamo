/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "app.h"

// センサー類
#include "SonarSensor.h"
#include "Motor.h"
#include "ColorSensor.h"
#include "TouchSensor.h"

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
#include "Messenger.h"
#include "LineTracer.h"
#include "Drive.h"



#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

// using宣言
using namespace ev3api;

// Device objects
// オブジェクトを静的に確保する
SonarSensor sonar(PORT_1);
ColorSensor color(PORT_3);
TouchSensor touch(PORT_2);
Motor rightMotor(PORT_B);
Motor leftMotor(PORT_C);
Motor frontMotor(PORT_D);

// オブジェクトの定義
WhiteJudge whiteJudge(&color);
BlackJudge blackJudge(&color);
GreenJudge greenJudge(&color);
TouchJudge touchJudge(&touch);
ObstacleJudge obstacleJudge(&sonar);
DistanceMeter distanceMeter(&rightMotor, &leftMotor);
Observer observer(&whiteJudge, &blackJudge, &greenJudge, &obstacleJudge, &touchJudge, &distanceMeter);
Drive drive(&rightMotor, &leftMotor, &frontMotor, &observer);
LineTracer lineTracer(&drive, &color);



/**
 * EV3システム生成
 */
static void user_system_create() {
    // オブジェクトの作成

    // 初期化完了通知
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
}

/**
 * トレース実行タイミング
 */
void ev3_cyc_tracer(intptr_t exinf) {
    act_tsk(TRACER_TASK);
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理

    // 周期ハンドラ開始
    ev3_sta_cyc(EV3_CYC_TRACER);

    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    ev3_stp_cyc(EV3_CYC_TRACER);

    user_system_destroy();  // 終了処理

    ext_tsk();
}

/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf) {
    // if (ev3_button_is_pressed(BACK_BUTTON)) {
    //     wup_tsk(MAIN_TASK);  // バックボタン押下
    // } else {
           
    // }

    // ext_tsk();
    observer.update();
    lineTracer.trace(20, LEFT);

}
