/*
 * NXTrikeβ2～3(ETR100b2/b3) firmware
 *
 * NXTrikeSample.c for TOPPERS/ATK(OSEK)
 * 2013.11.27 TANAHASHI, Jiro
 */

#include "LineTracer.h"
#include "SectionController.h"
#include "Driver.h"
#include "PositionEstimater.h"
#include "ColorDetector.h"
#include "Pid.h"
#include "ReturnLine.h"
#include "Figure.h"
#include "OffsetHolder.h"

#include "Motor.h"
#include "Port.h" //difined enum of port
#include "Clock.h"
#include "GyroSensor.h"
#include "LightSensor.h"
#include "TouchSensor.h"
#include "Nxt.h"
#include "BtConnection.h"
#include "GamePad.h"
#include "Bluetooth.h"
#include "Lcd.h"
#include "Daq.h"
#include "Speaker.h"

#include "Distance.h"
#include "TouchJudgement.h"
#include "UI.h"
#include "StepDetector.h"
#include "Mogul.h"
#include "Stepper.h"
#include "Jumper.h"
#include "GridRunner.h"
#include "Basic.h"
#include "ParkingL.h"
#include "ParkingP.h"
#include "IN.h"
#include "OUT.h"
#include "SpeedMeter.h"
#include "SpeedPid.h"

using namespace ecrobot;

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define BLACK 591
#define WHITE 542

#define DRIVING_POWER		 70

#define STEER	PORT_C
#define DRIVE_L	PORT_A
#define DRIVE_R	PORT_B
#define LIGHT	PORT_3
#define TOUCH	PORT_2
#define GYRO	PORT_1
extern "C"{
DeclareCounter(SysTimerCnt);
DeclareTask(run_alarm);
}
Bluetooth bt;
static const CHAR* PASSKEY = "YADAMO";

TouchSensor touch(TOUCH);
Nxt nxt;
Clock clk;

OffsetHolder oHolder;
SectionController sectionController;
Speaker speaker;
GyroSensor gyroSensor(GYRO);
Motor motorL(DRIVE_L,true);
Motor motorR(DRIVE_R,true);
Motor motorS(STEER,true);
Driver driver(&motorL, &motorR, &motorS);
Distance distance(&motorR, &motorL);
Distance distance2(&motorR, &motorL);
SpeedMeter speedMeter(&distance2, &motorR, &motorL);
LightSensor light(LIGHT);
Pid pid(&light);
SpeedPid speedPid(&speedMeter);
LineTracer lineTracer(&driver, &pid, &oHolder, &speedPid);
TouchJudgement touchJudgement(&touch);
ColorDetector colorDetector(&light, &oHolder);
UI ui(&light, &touchJudgement, &lineTracer, &clk, &speaker, &oHolder);
ReturnLine returnLine(&driver, &light, &colorDetector);
StepDetector stepDetector(&motorR, &motorL, &speaker);
Stepper stepper(&stepDetector, &lineTracer, &driver, &pid, &distance);
Figure figure(&lineTracer, &colorDetector, &driver, &stepper, &oHolder, &distance);
Mogul mogul(&driver, &lineTracer, &stepDetector, &stepper, &distance, &pid, &colorDetector);
Jumper jumper(&driver, &lineTracer, &stepper, &distance, &stepDetector, &speedPid, &colorDetector);
GridRunner gridRunner(&lineTracer, &driver, &stepper, &colorDetector, &distance, &stepDetector);
Basic basic(&lineTracer, &pid, &speaker, &distance, &motorR, &motorL, &oHolder, &speedPid, &driver);
ParkingL parkingL(&lineTracer, &driver, &stepDetector, &distance);
ParkingP parkingP(&lineTracer, &driver, &colorDetector, &distance);
IN in(&basic, &mogul, &figure, &parkingL);
OUT out(&basic, &jumper, &gridRunner, &parkingP);



// LineTracer _line;
// SectionController section;  
// Driver _driver;
// PositionEstimater _position;
// GrayDetector _gray;
// Pid _pid;

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{

}

void ecrobot_device_terminate()
{

// Motor motorL(DRIVE_L,true);
// Motor motorR(DRIVE_R,true);
// Motor motorS(STEER,true);
// LightSensor light(LIGHT);
// TouchSensor touch(TOUCH);
// 	~nxt;
// 	~clk;

// 	~_line;
// 	~section;  
// 	~_driver;
// 	~_position;
// 	~_gray;
// 	~_pid;

}


/* nxtOSEK hook to be invoked from an ISR in category 2 */
extern "C" void user_1ms_isr_type2(void)
{ /* do nothing */ 
	SignalCounter(SysTimerCnt);
}

Lcd lcd;
bool btConnected = false;

VectorT<S8> command;

Daq daq(bt);

int phase = 0;

extern "C" TASK(OSEK_Task_Background)
{
	
	BTConnection btConnection(bt, lcd, nxt);
	
	if (btConnection.connect(PASSKEY) == 1)
		btConnected = true;
		
	speaker.playTone(442, 100, 10);
	
	motorL.setCount(0);
	motorR.setCount(0);
	

	ui.calibration();
	clk.wait(500); /* 500msec wait */
	
	SetRelAlarm(run_alarm, 1, 3);
	TerminateTask();
}

extern "C" TASK(RUN_TASK)
{	
	S8 logToDataC[2];
	logToDataC[0] = motorR.result;//data1
	logToDataC[1] = motorL.result;//data2
	
	U16 logToBatteryC = light.getBrightness();//data3

	S16 logToAdcC[4];
	logToAdcC[0] = gyroSensor.getAnglerVelocity();//data7
	logToAdcC[1] = (S16)(speedMeter.getSpeed()*100);//data8
	logToAdcC[2] = 6;//data9
	logToAdcC[3] = 7;

	S32 logToMotorrevC[4];
	logToMotorrevC[0] = (S32)distance.getDistance();//data4
	logToMotorrevC[1] = (S32)speedPid.result;//data5
	logToMotorrevC[2] = (S32)pid.result;//data6
	logToMotorrevC[3] = 11;	

	motorR.setDiff();
	motorL.setDiff();


	switch(phase){
		case 0:
			// if(in.run()){
			if(out.run()){
				phase++;
				driver.straightInit();
			}

			break;
		case 1:
			driver.straight(0);
			break;
	}

	lcd.clear(); // clear data buffer at row 1
	if (btConnected){
		daq.send(logToDataC, logToBatteryC, logToAdcC, logToMotorrevC);
		lcd.putf("dd", 0, 0, 0, 5);
	}else{
		lcd.putf("dd", (int)distance.getDistance(), 0, oHolder.getWhite(), 4);
		lcd.clear(); // clear data buffer at row 1
	}
	lcd.disp();

	TerminateTask();
}
