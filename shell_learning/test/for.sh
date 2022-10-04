#! /bin/bash

for FRUIT in apple banana pear
do
	echo "I like $FRUIT"
done

#for FILENAME in `ls | grep test?.sh`
#do
#	mv $FILENAME $FILENAME~
#done

for MYFILE in $(ls)
do
	printf "$MYFILE "

	if [ -d "$MYFILE" ]; then
		echo "It's a dir!"
	elif [ -f "$MYFILE" ]; then
		echo "IT's a file"
	else
		echo "other."
	fi
done
