cmake_minimum_required(VERSION 2.6)
project(yeep)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(SFML REQUIRED)
find_package(BOX2D REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(${SFML_INCLUDE_DIR})

set(mainLibs ${SFML_LIBRARY} ${BOX2D_LIBRARY})
add_subdirectory(src)
