#! /bin/bash

for filename in $(ls *.sh~~~)
do
	# %表示截断，相当于在原文件名的基础上截断了有效的文件名
	mv  $filename ${filename%~~~}
done
