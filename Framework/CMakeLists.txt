cmake_minimum_required(VERSION 3.6)
project(framework)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)




set(SOURCE_FILES main.cpp src/Node.cpp src/Node.h src/Log.cpp src/Log.h src/Generation.cpp src/Generation.h src/GenProg.cpp src/GenProg.h src/Func.cpp src/Func.h)
#add_executable(framework ${SOURCE_FILES})
add_library(framework SHARED ${SOURCE_FILES})

