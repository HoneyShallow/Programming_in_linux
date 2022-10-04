#! /bin/sh
# 共7列

# sort 将文本行排序，uniq则是记录和忽略重复行
cat /etc/passwd | awk -F: '{if ($7!="") print $7}' | sort | uniq -c

# cat /etc/passwd|awk -F: '{if ($7!="") print $7}'| sort | uniq -c | awk '{print $2,$1}'
