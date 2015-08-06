mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += balancer.o balancer_param.o

APPL_CXXOBJS += \
	BalancingWalker.o \
	LineMonitor.o \
	BalancerCpp.o \
	LineTracer.o \
	WhiteJudge.o \
	BlackJudge.o \
	GreenJudge.o \
	TouchJudge.o \
<<<<<<< HEAD
	ObstacleJudge.o \
	DistanceMeter.o
=======
	DistanceMeter.o \
	SpeedMeter.o
>>>>>>> 9a0ee573befb695c0ad060ec60366b02c8157fba


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