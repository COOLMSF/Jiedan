#!/bin/bash

clear

echo "enter filename:"
read fname
echo "enter content for file"
read var

until [ $var = 'end!' ]
do
	echo $var >> $fname
	read -p "enter content for file, end! to quit" var
done
