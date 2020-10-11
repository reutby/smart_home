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
TARGET =unboundedqueue_test

# All .c files in this directory are my sources
SOURCES = unboundedqueue_test.cpp ../../src/experis/mutex.cpp ../../src/experis/thread.cpp ../../src/experis/conditionvarible.cpp ../src/producer.cpp ../src/consumer.cpp

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

Halgrind:	$(TARGET)
	  valgrind --tool=helgrind --log-file=loghelgrind01.txt ./$(TARGET) -v

