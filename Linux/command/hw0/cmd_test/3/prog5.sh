#!/bin/bash

echo "inter a number:"
if [ $# -ne 1 ]
then
	echo "enter number:"
	exit
fi

total=0
var=$1

while true
do
	total=$[ total + var ]
	var=$[ var - 1 ]

	if [ $var -eq 0 ]
	then
		break
	fi
done
echo $total
