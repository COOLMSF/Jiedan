cmake_minimum_required(VERSION 3.20)
project(Array C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Array
        arraylist.c
        arraylist.h
        bookmanagement.c
        bookmanagement.h
        main.c
        select_sort.c
        select_sort.h)
