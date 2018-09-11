TARGET= logtest

# ARM_CROOS_TOOL_PATH := /opt/hisi-linux/x86-arm/aarch64-himix100-linux/bin/
# ARM_CROSS := $(ARM_CROOS_TOOL_PATH)aarch64-himix100-linux-
# CXX = ${ARM_CROSS}g++
CXX = g++

all:	$(TARGET)

# LOGEX_INCLUDE  := -I./
# LOGEX_LIB      := -L./ -llogex

LOGEX_INCLUDE  := -I../LogEx
LOGEX_LIB      := -L../LogEx -lCWLog.1.5

INCLUDES := ${LOGEX_INCLUDE}
LIBS     := ${LOGEX_LIB} -lpthread -ldl

CXXFLAGS = $(INCLUDES) -g -Wall -std=c++11

SRCS += $(wildcard *.cpp)

OBJS := $(addsuffix .o,$(basename ${SRCS}))

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
	    
.cpp.o:
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o *~
	rm -f $(TARGET)

