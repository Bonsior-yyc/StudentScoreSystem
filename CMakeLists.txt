cmake_minimum_required(VERSION 3.15)
project(StudentScoreSystem C)

set(CMAKE_C_STANDARD 99)

add_executable(StudentScoreSystem main.c structs.h functions.h FileRelated.h config.h)