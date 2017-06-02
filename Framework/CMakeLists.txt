cmake_minimum_required(VERSION 3.6)
project(framework)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)


set(SOURCE_FILES main.cpp src/Node.h src/Log.h src/GenProg.h src/Func.h )
add_library(framework SHARED ${SOURCE_FILES})
