cmake_minimum_required(VERSION 3.20)
project(pro C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(pro
        Jack_client.c
        kernel_list.h
        list.h
        server.c common.h server.h)
