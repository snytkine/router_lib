cmake_minimum_required(VERSION 3.6)
project(router)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp strlib.h strlib.cpp RouterNode.cpp RouterNode.h PathParamNode.cpp PathParamNode.h node_result.cpp node_result.h measure.h factory.h FuncParamNode.cpp FuncParamNode.h constants.h constants.cpp)
add_executable(router ${SOURCE_FILES})