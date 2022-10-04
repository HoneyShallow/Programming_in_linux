#! /bin/bash

echo "The program $0 is now running"

echo "The first parameter is $1"
echo "The second parameter is $2"
echo "The parameter list is $@"
echo "The parameter number are $#"

shift
echo "The first parameter is $1"
echo "The second parameter is $2"
echo "The parameter list is $@"
echo "The parameter number are $#"
