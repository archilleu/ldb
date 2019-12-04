#---------------------------------------------------------------------------
#CMake minimum required version
cmake_minimum_required (VERSION 2.8)
#---------------------------------------------------------------------------
#look up dir's file, and add to var
aux_source_directory(. DIR_TESTS)
#---------------------------------------------------------------------------
#generate test
set(TEST_string test_string)
add_executable(${TEST_string} ../src/value.cc ../src/string_value.cc test_string.cc)
#---------------------------------------------------------------------------
#add link lib
find_library(LIBBASE base HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../thirdpart/base/lib)
if(NOT LIBBASE)
    message(FATAL_ERROR "base library not found, please copy from base project")
endif()
target_link_libraries(${TEST_string} ${LIBBASE})
#---------------------------------------------------------------------------
#add test
add_test(${TEST_string} ${EXECUTABLE_OUTPUT_PATH}/${TEST_string})
#---------------------------------------------------------------------------
