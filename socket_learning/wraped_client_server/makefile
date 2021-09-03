src = $(wildcard ./*.cpp)
#查找当前路径下指定类型.cpp的所有文件

obj = $(patsubst %.cpp, %.o, $(src))
#将src中所有的.cpp文件替换为.o文件并添加且不删除.cpp文件

#targets = $(patsubst %.cpp, %, $(src))
#将src中的所有xxx.cpp文件替换为xxx文件

#主命令
all:server client
#从命令1
server:server.o wrap.o
	c++ server.o wrap.o -o server
#从命令2
client:client.o wrap.o
	c++ client.o wrap.o -o client

%.o:%.cpp
	c++ -c $< -std=c++11 -Wall
#CC = c++
#CFLAGS = -std=c++11 -Wall -g

#all:$(targets):%:%.cpp
#	$(CC) $< -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf server client $(obj)
