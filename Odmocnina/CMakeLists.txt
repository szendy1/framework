cmake_minimum_required(VERSION 3.6)
project(Odmocnina)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

link_directories(${CMAKE_BINARY_DIR})
set(SOURCE_FILES main.cpp SquareRoot.h include_GenProg/GenProgLib.h)

add_executable(Odmocnina ${SOURCE_FILES})

target_include_directories(Odmocnina PUBLIC include)

target_link_libraries(Odmocnina ${CMAKE_THREAD_LIBS_INIT} mgl)