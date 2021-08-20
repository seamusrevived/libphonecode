cmake_minimum_required(VERSION 3.20)
project(libphonecode)

set(CMAKE_C_STANDARD 99)

add_subdirectory(tests)

add_library(libphonecode phonecode.c phonecode.h phone_encodings.c phone_encodings.h)
target_link_libraries(libphonecode)


add_executable(example main.c)
target_link_libraries(example libphonecode)
