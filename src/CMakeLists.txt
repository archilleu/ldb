#---------------------------------------------------------------------------
#CMake minimum required version
cmake_minimum_required (VERSION 2.8)
#---------------------------------------------------------------------------
#look up dir's file, and add to var
aux_source_directory(. DIR_SRC)
#---------------------------------------------------------------------------
#generate test
set(EXENAME ldb)
add_executable(${EXENAME} ${DIR_SRC})
#---------------------------------------------------------------------------
#add include path
include_directories(../../thirdpart)
#---------------------------------------------------------------------------
#add lib
find_library(LIBBASE base HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../thirdpart/base/lib)
find_library(LIBNET net HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../thirdpart/net/lib)
if(NOT LIBBASE)
    message(FATAL_ERROR "base library not found, please copy from base project")
endif()
if(NOT LIBNET)
    message(FATAL_ERROR "net library not found, please copy from net project")
endif()
#---------------------------------------------------------------------------
#add link lib
target_link_libraries(${EXENAME} ${LIBNET} ${LIBBASE} pthread rt)
#---------------------------------------------------------------------------
#install target 
#install(TARGETS ldb_test DESTINATION ${EXECUTABLE_OUTPUT_PATH})
#---------------------------------------------------------------------------
#add test
#add_test(test_run ${EXECUTABLE_OUTPUT_PATH}/${TESTNAME})
#---------------------------------------------------------------------------
