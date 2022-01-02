#!/bin/sh

sudo insmod charDev.ko
sudo mknod /dev/charDev c 249 0
sudo chmod 777 /dev/charDev
