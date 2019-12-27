#---------------------------------------------------------------------------
#CMake minimum required version
cmake_minimum_required (VERSION 2.8)
#---------------------------------------------------------------------------
#look up dir's file, and add to var
aux_source_directory(. DIR_TESTS)
#---------------------------------------------------------------------------
#generate test
set (TEST_files ../src/value.cc ../src/set_value.cc ../src/string_value.cc
    ../src/hash_value.cc ../src/list_value.cc ../src/zset_value.cc ../src/object_ptr.cc)

set(TEST_string test_string)
add_executable(${TEST_string} ${TEST_files} test_string.cc)

set(TEST_hash test_hash)
add_executable(${TEST_hash} ${TEST_files} test_hash.cc)

set(TEST_list test_list)
add_executable(${TEST_list} ${TEST_files} test_list.cc)

set(TEST_set test_set)
add_executable(${TEST_set} ${TEST_files} test_set.cc)

set(TEST_zset test_zset)
add_executable(${TEST_zset} ${TEST_files} test_zset.cc)

set(TEST_object test_object)
add_executable(${TEST_object} ${TEST_files} test_object.cc)

set(TEST_ldb test_ldb)
add_executable(${TEST_ldb} ${TEST_files} ../src/dump.cc ../src/undump.cc
    ../src/server.cc test_ldb.cc)
#---------------------------------------------------------------------------
#add link lib
find_library(LIBBASE base HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../thirdpart/base/lib)
if(NOT LIBBASE)
    message(FATAL_ERROR "base library not found, please copy from base project")
endif()
target_link_libraries(${TEST_string} ${LIBBASE} pthread )
target_link_libraries(${TEST_hash} ${LIBBASE} pthread )
target_link_libraries(${TEST_list} ${LIBBASE} pthread )
target_link_libraries(${TEST_set} ${LIBBASE} pthread )
target_link_libraries(${TEST_zset} ${LIBBASE} pthread )
target_link_libraries(${TEST_object} ${LIBBASE} pthread )
target_link_libraries(${TEST_ldb} ${LIBBASE} pthread )
#---------------------------------------------------------------------------
#add test
add_test(${TEST_string} ${EXECUTABLE_OUTPUT_PATH}/${TEST_string})
add_test(${TEST_hash} ${EXECUTABLE_OUTPUT_PATH}/${TEST_hash})
add_test(${TEST_list} ${EXECUTABLE_OUTPUT_PATH}/${TEST_list})
add_test(${TEST_set} ${EXECUTABLE_OUTPUT_PATH}/${TEST_set})
add_test(${TEST_zset} ${EXECUTABLE_OUTPUT_PATH}/${TEST_zset})
add_test(${TEST_object} ${EXECUTABLE_OUTPUT_PATH}/${TEST_object})
add_test(${TEST_ldb} ${EXECUTABLE_OUTPUT_PATH}/${TEST_ldb})
#---------------------------------------------------------------------------
