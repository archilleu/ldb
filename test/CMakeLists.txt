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

set(TEST_hash test_hash)
add_executable(${TEST_hash} ../src/value.cc ../src/hash_value.cc
    ../src/string_value.cc ../src/set_value.cc ../src/object_ptr.cc test_hash.cc)

set(TEST_list test_list)
add_executable(${TEST_list} ../src/value.cc ../src/list_value.cc
    ../src/string_value.cc ../src/hash_value.cc ../src/set_value.cc ../src/object_ptr.cc test_list.cc)

set(TEST_set test_set)
add_executable(${TEST_set} ../src/value.cc ../src/set_value.cc
    ../src/string_value.cc ../src/hash_value.cc ../src/object_ptr.cc test_set.cc)
#---------------------------------------------------------------------------
#add link lib
find_library(LIBBASE base HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../thirdpart/base/lib)
if(NOT LIBBASE)
    message(FATAL_ERROR "base library not found, please copy from base project")
endif()
target_link_libraries(${TEST_string} ${LIBBASE})
target_link_libraries(${TEST_hash} ${LIBBASE})
target_link_libraries(${TEST_list} ${LIBBASE})
target_link_libraries(${TEST_set} ${LIBBASE})
#---------------------------------------------------------------------------
#add test
add_test(${TEST_string} ${EXECUTABLE_OUTPUT_PATH}/${TEST_string})
add_test(${TEST_hash} ${EXECUTABLE_OUTPUT_PATH}/${TEST_hash})
add_test(${TEST_list} ${EXECUTABLE_OUTPUT_PATH}/${TEST_list})
add_test(${TEST_set} ${EXECUTABLE_OUTPUT_PATH}/${TEST_set})
#---------------------------------------------------------------------------
