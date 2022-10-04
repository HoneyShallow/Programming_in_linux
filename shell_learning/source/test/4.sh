#! /bin/bash
# 编译当前目录下的所有.c文件

for FILE in "*.c"
do
	gcc -c $FILE 
done
