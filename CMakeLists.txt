cmake_minimum_required(VERSION 3.20)
project(libphonecode)

set(CMAKE_C_STANDARD 99)

add_subdirectory(tests)

add_library(libphonecode phonecode.c phonecode.h)
