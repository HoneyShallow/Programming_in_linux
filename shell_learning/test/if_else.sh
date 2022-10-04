#! /bin/sh

echo "Is it morning? Please answer yes or no: "
read RET
if [ "$RET" = "yes" ]; then
	echo "Gooding morning!\n"
elif [ "$RET" = "no" ]; then 
	echo "Gooding afternoon!\n"
else
	echo "Sorry, $RET not recognized. Enter yes or no."
	exit 1
fi
exit 0
