# /***************************************************************************
# *                                                                          *
# * INSERT COPYRIGHT HERE!                                                   *
# *                                                                          *
# ****************************************************************************
# PURPOSE: Makefile for common utilities
# */

BUILD_HOME=..
include $(BUILD_HOME)/Options

SRCS = zcl_main.c

all: $(ZCL_LIB) $(ZCL_LIB_ED)

$(ZCL_LIB) : $(OBJS)
	$(MAKE_LIB)

$(ZCL_LIB_ED) : $(OBJS_ED)
	$(MAKE_LIB)
