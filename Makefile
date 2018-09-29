#ouput file
EXECUTABLE := poker.out
 
CC := g++
CFLAGS := -std=c++11 -Wall -O2
LDFLAGS +=
 
#.cpp
SOURCE := $(wildcard *.cpp)
 
#.o
OBJS := $(patsubst %.cpp, %.o, $(SOURCE))
 
# compile .o
all : $(EXECUTABLE)
$(EXECUTABLE) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)
 
 
.PHONY : clean
 
clean :
	@rm -f $(EXECUTABLE) $(OBJS) *~
