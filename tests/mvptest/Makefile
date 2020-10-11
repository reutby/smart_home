CC = g++ 

CCX = g++
# The compiler flags will be... ("CFLAGS" is MAKE variable)
CFLAGS = -ansi -pedantic -Werror -Wall
CFLAGS+=-g
CXXFLAGS = $(CFLAGS) -std=c++03
#for pre-procees compiletime
CPPFLAGS += -I$(INC_DIR_EXPERIS) -I$(INC_DIR_ADVCPP) -I$(INC_DIR_PIKACHU) -I$(INC_TEST)
#linkerflags
LDFLAGS= -g -pthread


# this is my target
TARGET =mvp_test

# All .c files in this directory are my sources
SOURCES = mvp_test.cpp ../../src/experis/mutex.cpp ../../src/experis/thread.cpp ../../src/experis/conditionvarible.cpp ../../src/pikachu/event_base.cpp ../../src/pikachu/event_queue.cpp ../../src/pikachu/time_stamp.cpp ../../src/pikachu/ireciver.cpp ../../src/pikachu/mvp_reciver.cpp ../../src/pikachu/location.cpp ../../src/pikachu/motion_detector_event.cpp ../../src/pikachu/motion_detector_sensor.cpp ../../src/pikachu/isensor.cpp ../../src/pikachu/icontroller.cpp ../../src/pikachu/monitor_detector_controller.cpp ../../src/pikachu/isubscriber_container.cpp ../../src/pikachu/isubscriber_selector.cpp ../../src/pikachu/isubscriber_manager.cpp ../../src/pikachu/subscriber_container.cpp ../../src/pikachu/isender.cpp ../../src/pikachu/sender_mvp.cpp ../../src/pikachu/event_distributor.cpp ../../src/pikachu/ievent_queue.cpp ../../src/pikachu/ienqueue.cpp ../../src/pikachu/idequeue.cpp ../../src/pikachu/smart_home_system.cpp ../../src/pikachu/agent_container.cpp ../../src/pikachu/mvp_factory.cpp ../../src/pikachu/ifactory.cpp ../../src/pikachu/idevice_agent.cpp ../../src/pikachu/device_agent.cpp ../../src/pikachu/idistribute_policy.cpp ../../src/pikachu/hard_distribute_policy.cpp ../../src/pikachu/easy_distribute_policy.cpp

# Include directory
INC_DIR_EXPERIS = ../../inc/experis
INC_DIR_ADVCPP = ../../inc/advcpp
INC_DIR_PIKACHU = ../../inc/pikachu
INC_TEST = ../inc
# General compilation flags

# The compiler will be gcc("CC" is MAKE variable)


#  my objects are the .o of my sources
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all
all: $(TARGET)

# The default command, compile all the sources
#$(CC) $(LDFLAGS) $(^) -o $(@)

$(TARGET): $(OBJECTS)  

#built-in c compiler rule is $(CC) $(CFLAGS) $(CPPFLAGS) -c  -o $(@) $(<)

#vector.o: Vector.c Vector.h ADTDefs.h
include depends
depends:
	$(CC) -MM $(CPPFLAGS) $(SOURCES) > $(@)

#spacial targets
.PHONY:clean
clean:
	rm -f $(TARGET) *.o depends *.log
	rm -f $(TARGET) ../../src/experis/*.o
	rm -f $(TARGET) ../src/*.o
	rm -f $(TARGET) ../../src/advcpp/*.o
	rm -f $(TARGET) ../../src/pikachu/*.o

.PHONY:test
test:  $(TARGET)
	 ./$(TARGET) -v

check: test

hell:	$(TARGET)
	  valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET) -v

