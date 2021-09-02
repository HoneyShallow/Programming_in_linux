src = $(wildcard ./*.cpp)
#查找当前路径下指定类型的所有文件

targets = $(patsubst %.cpp, %, $(src))
#将src中的所有xxx.cpp文件替换为xxx文件
CC = c++
CFLAGS = -std=c++11 -Wall -g

all:$(targets):%:%.cpp
	$(CC) $< -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf $(targets)
