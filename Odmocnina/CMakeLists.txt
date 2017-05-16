cmake_minimum_required(VERSION 3.6)
project(Odmocnina)

set(CMAKE_CXX_STANDARD 11)

link_directories(${CMAKE_BINARY_DIR})
set(SOURCE_FILES main.cpp myGenProg.h include/genprog.h)

add_executable(Odmocnina ${SOURCE_FILES})

target_link_libraries(Odmocnina framework)
target_include_directories(Odmocnina PUBLIC include)