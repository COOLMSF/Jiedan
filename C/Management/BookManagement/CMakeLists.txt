cmake_minimum_required(VERSION 3.20)
project(BookManagement C)

set(CMAKE_C_STANDARD 11)

include_directories(LinkedList)
include_directories(LinkedList/backup)
include_directories(Tree)

add_executable(BookManagement
        LinkedList/backup/main.c
        LinkedList/backup/slist.c
        LinkedList/backup/slist.h
        LinkedList/backup/slist_test.c
        LinkedList/main.c
        LinkedList/slist.c
        LinkedList/slist.h
        LinkedList/slist_test.c
        Tree/main.c Tree/BinaryTree.c Tree/BinaryTree.h)
