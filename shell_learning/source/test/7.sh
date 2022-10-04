#! /bin/bash
# 计算创建和删除目录所需要的时间
time (
    for i in {1..2000}
    do 
        #mkdir /tmp/nnn$i
	rm /tmp/nnn$i -r
    done
)
