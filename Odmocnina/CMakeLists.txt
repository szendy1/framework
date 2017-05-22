cmake_minimum_required(VERSION 3.6)
project(Odmocnina)

set(CMAKE_CXX_STANDARD 11)


find_package(PkgConfig)

pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(GTK REQUIRED gtk+-2.0)

find_package(Gnuplot)
find_package(Threads)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include("${wxWidgets_USE_FILE}")

link_directories(${CMAKE_BINARY_DIR})
set(SOURCE_FILES main.cpp SquareRoot.h include/GenProg.h )

add_executable(Odmocnina ${SOURCE_FILES})

#target_link_libraries(Odmocnina framework)
target_include_directories(Odmocnina PUBLIC include)

target_include_directories(Odmocnina SYSTEM PRIVATE ${CAIRO_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS})
target_link_libraries(Odmocnina ${CAIRO_LIBRARIES} ${GTK_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} mgl ${wxWidgets_LIBRARIES})