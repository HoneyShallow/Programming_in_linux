#! /bin/bash
# 将以目录下所有文件的扩展名改为.bak
for FILENAME in *.*
do
	mv $FILENAME ${FILENAME%.*}.bak
done
