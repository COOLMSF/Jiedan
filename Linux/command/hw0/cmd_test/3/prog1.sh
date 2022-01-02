#!/bin/bash

for num in 10 20 30 40 50 60
do
	echo $num square
	expr $num \* $num
done

