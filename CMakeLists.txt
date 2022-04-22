cmake_minimum_required(VERSION 3.21)
project(yukon C)

set(CMAKE_C_STANDARD 99)

add_executable(yukon main.c GameLogic.h GamrLogic2.h)
