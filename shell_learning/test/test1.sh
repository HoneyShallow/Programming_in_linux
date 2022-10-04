#! /bin/bash

if [ -f /bin/bash ]
then
	echo "/bin/bash is a file"
else
	echo "/bin/bash is NOT file"
fi
if :; then echo "always true"; fi 
