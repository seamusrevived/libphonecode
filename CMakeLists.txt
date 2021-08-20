cmake_minimum_required(VERSION 3.13)
project(libphonecode C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(tests)

add_library(libphonecode phonecode.c phonecode.h string_coll.c string_coll.h util.c util.h)
target_link_libraries(libphonecode)


add_executable(example main.c)
target_link_libraries(example libphonecode)
