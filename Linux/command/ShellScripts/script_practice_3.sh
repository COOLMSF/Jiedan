#!/bin/bash

# print the name of the script
echo $0

# check argument number 
if [ $# -eq 0 ];then
    echo "You must provide one parameter"
    exit -1
elif [ $# -gt 1 ]; then
    echo "You must provide only one parameter"
    exit -1
fi

# test if the argument is a directory
test -d $1

# test return status
if [ "$?" = "0" ]; then
    echo "Already exist"
else
    mkdir $1
fi
