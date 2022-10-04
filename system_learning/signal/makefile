src = $(wildcard ./*.cpp) #获取当前路径下所有的.cpp文件
obj = $(patsubst %.cpp, %, $(src))#确定要生成的文件名

CC = c++
CFLAGS = -std=c++11 -Wall -g

all:$(obj)

$(obj):%:%.cpp
	$(CC) $< -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf $(obj)


