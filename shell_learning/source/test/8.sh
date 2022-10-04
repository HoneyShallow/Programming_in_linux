#! /bin/bash
# 打印本机交换分区的大小，处理结果:Swap:2047M
free -m | sed -n '/Swap/p' | echo "Swap:$(awk '{ print $2}')"
