src = $(wildcard *.cpp)
targets = $(patsubst %.cpp, %, $(src))

CC = g++
CFLAGS = -std=c++11 -g -Wall -lpthread 

all:$(targets)

$(targets):%:%.cpp
	$(CC) $< -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf $(targets) 

