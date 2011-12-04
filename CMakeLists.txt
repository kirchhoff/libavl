# Minimum version of CMake
cmake_minimum_required(VERSION 2.6)

# Name of project
project(libavl)

include(CTest)

# Add subdirectory
add_subdirectory(src)
add_subdirectory(test)

enable_testing()

add_definitions(-DLOGLEVEL=4)
