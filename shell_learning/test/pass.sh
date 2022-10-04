#! /bin/bash

echo "Enter password: "
COUNT=0
read TRY
while [ "$TRY" != "secret" ]
do	
	COUNT=$[$COUNT+1]
	if [ "$COUNT" = 5 ]
	then
		echo "Sorry, you have no chance!"
		break
	fi
	echo "Sorry, try again"
	read TRY
done
