#! /bin/sh

# 函数的声明和定义
foo(){

	echo "Function foo is called"
}

echo "-=start=-"
foo
echo "-=end=-"


is_directory()
{
	DIR_NAME=$1
	if [ ! -d DIR_NAME ]; then
		return 1
	else
		return 0
	fi
}

for DIR in "$@"; do
	if is_directory "$DIR"
       	then :
#		continue	
	else
		echo "$DIR doesn't exist. Creating it now..."
		mkdir $DIR > /dev/null 2>&1
		if [ $? -ne 0 ]; then
			echo "Cannot create directory $DIR"
			exit 1
		fi
	fi
done
