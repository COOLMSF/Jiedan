#!/bin/bash

# display message on the screen
echo "Enter file name. To end type q:"

# save data into variable from user input
read variable

# while loop, variable != "q" is condition
while [ $variable != "q" ]; do
    # create file named by variable (user input)
    touch $variable
    # display message on screen
    echo "Enter file name. To end type q:"
    # save data into variable from user input, again
    read variable
done
