project(DelayedStream)
cmake_minimum_required(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "-std=c++0x")
#aux_source_directory(. SRC_LIST)
set(SRC_LIST 
    ${SRC_LIST}
    "likelisp.h"
    "util.h"
    "cons.h"
    "interface.h"
    "main.cpp"
    )
    
add_executable(${PROJECT_NAME} ${SRC_LIST})

