#! /bin/bash

display()
{
	echo "enter a filename or dir name:"
	if [ $# -ne 1 ]
	then
		echo "only one name allowed"
		exit
	fi

	if [ -d $1 ]
	then
		dir $1
	elif [ -f $1 ]
	then
		cat $1
	else true
		echo "not found"
	fi
}

display $1
