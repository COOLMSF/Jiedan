#!/bin/bash

echo "UNIX ls Command Quick Menu"
echo "1.List current directory"
echo "2.List current directory by timestamp"
echo "3.List all files in current directory"
echo "4.List all files in current directory by size"
echo "5.List all files in the root of the file system directory"

echo "Enter menu option:"
read OPTION

case $OPTION in
    1)
        ls -l
        ;;
    2)
        ls -ltr
        ;;
    3)
        ls -la
        ;;
    4)
        ls -lSr
        ;;
    5)
        ls -l
        ;;
    *)
        echo "Not sure what you want"
esac
