#! /bin/bash
# 打印root可以使用的可执行文件数，处理结果为：root's bins:2306
SEARCH_PATH=./ # 路径变量不能使用内置变量
echo "root's bins:$(find $SEARCH_PATH -type f | ls -l | sed "/^-..x/p" -r -n | wc -l)"
# echo "root's bins:$(find ./ -type f | ls -l | sed "/^-..x/p" -r -n | wc -l)"

