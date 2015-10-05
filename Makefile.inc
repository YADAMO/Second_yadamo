APPL_COBJS += 

APPL_CXXOBJS += \
	Motor.o \
	Gyro.o \
	Color.o \
	Touch.o \
	Sonic.o \
	WhiteJudge.o \
	BlackJudge.o \
	GreenJudge.o \
	TouchJudge.o \
	ObstacleJudge.o \
	DistanceMeter.o \
	SpeedMeter.o \
	ScenarioController.o \
	STwinBridge.o \
	SBarcode.o \
	SUndetermined.o \
	SFigureL.o \
	SLoopLine.o \
	SParkingP.o \
	SParkingL.o \
	IN.o \
	OUT.o \
	Calibration.o \
	Drive.o \
	PID.o\
	LineTracer.o \
	Battery.o \
	Logger.o \
	Observer.o \
	Stepper.o \
	LineReturn.o \
	Curve.o \
	LCourse.o

SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(WORKSPACE_LIB_DIR)/libcpp-test/Makefile
include $(WORKSPACE_LIB_DIR)/lib2/Makefile

endif
