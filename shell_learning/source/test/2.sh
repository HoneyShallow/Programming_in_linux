#! /bin/bash
# 计算1-100的和
count=1
ret=0
while [ $count -le 100 ]
do
	ret=$[$ret+$count]
	count=$[$count+1]
done
echo "1-100的和为: $ret"
