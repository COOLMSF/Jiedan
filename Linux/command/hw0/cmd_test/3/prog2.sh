#!/bin/bash

echo "enter a number (>100 to quit):"

read var
while [ $var -lt 100 ]
do
	echo $var square
	expr $var \* $var
	echo "enter a number (>100 to quit):"
	read var
done
