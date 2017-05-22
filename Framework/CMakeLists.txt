cmake_minimum_required(VERSION 3.6)
project(framework)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

find_package(PkgConfig)

pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(GTK REQUIRED gtk+-2.0)


set(SOURCE_FILES main.cpp src/Node.h src/Log.h src/GenProg.h src/Func.h include/gnuplot_i.hpp src/Graphics.h)
#add_executable(framework ${SOURCE_FILES})
add_library(framework SHARED ${SOURCE_FILES})

target_include_directories(framework SYSTEM PRIVATE ${CAIRO_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS})
target_link_libraries(framework ${CAIRO_LIBRARIES} ${GTK_LIBRARIES})