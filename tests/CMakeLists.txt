project(libphonecode_tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} ../)


link_directories(..)

add_executable(libphonecode_tests_run phonecode_test.cpp testutils.h testutils.cpp)
target_link_libraries(libphonecode_tests_run gtest gtest_main libphonecode)
