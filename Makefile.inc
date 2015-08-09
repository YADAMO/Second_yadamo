mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
	WhiteJudge.o \
	BlackJudge.o \
	GreenJudge.o \
	TouchJudge.o \
	ObstacleJudge.o \
	DistanceMeter.o \
	SpeedMeter.o \
	Messenger.o \
	Observer.o \
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
	LineTracer.o


SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION

# Include libraries
include $(WORKSPACE_LIB_DIR)/libcpp-ev3/Makefile

endif

srcpath = $(mkfile_path)app $(mkfile_path)unit

ifdef app
  APPL_DIR += $(srcpath)
endif

ifdef mod
  SRCDIRS += $(srcpath)
endif

INCLUDES += \
	-I$(mkfile_path)app \
	-I$(mkfile_path)unit

COPTS += -fno-use-cxa-atexit
