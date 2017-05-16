cmake_minimum_required(VERSION 3.6)
project(Odmocnina)

set(CMAKE_CXX_STANDARD 11)


find_package(PkgConfig)

pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(GTK REQUIRED gtk+-2.0)

link_directories(${CMAKE_BINARY_DIR})
set(SOURCE_FILES main.cpp SquareRoot.h include/genprog.h)

add_executable(Odmocnina ${SOURCE_FILES})

target_link_libraries(Odmocnina framework)
target_include_directories(Odmocnina PUBLIC include)

target_include_directories(Odmocnina SYSTEM PRIVATE ${CAIRO_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS})
target_link_libraries(Odmocnina ${CAIRO_LIBRARIES} ${GTK_LIBRARIES})