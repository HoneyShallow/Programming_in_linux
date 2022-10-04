#! /bin/sh

echo "Is it morning? Please answer yes or no: "
read RET

case "$RET" in
yes|y|Yes|YES)
	echo "Gooding morning!\n";;
[nN]*)
	echo "Gooding afternoon!\n";;
*)
	echo "Sorry, $RET not recognized. Enter yes or no."
	exit 1;;
	# 使用return会报错,只有函数或者sourced script脚本需要return
	# 所以此处还是应该使用exit， 不过exit会退出当前进程，如果在交互shell中调用该shell脚本
	# 会直接退出正在运行的终端
esac
exit 0
