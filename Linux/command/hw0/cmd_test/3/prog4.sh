#!/bin/bash

if [ $# -eq 0 ]
then
	echo "no number"
	exit 1
fi

export total=0
until [ $# -eq 0 ]
do
	total=$[ total + $1 ]
	shift
done

echo $total
