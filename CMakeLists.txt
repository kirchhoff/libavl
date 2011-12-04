# Minimum version of CMake
cmake_minimum_required(VERSION 2.6)

# Variable definition
set(LIBRARY_OUTPUT_PATH lib)
set(EXECUTABLE_OUTPUT_PATH bin)

include_directories(src)

# Name of project
project(libavl)

# Source
file(
    GLOB_RECURSE
    src_file
    src/*
)

file(
    GLOB_RECURSE
    test_file
    test/*
)

# Compilation of shared library
add_library(
    libavl
    SHARED
    ${src_file}
)

# Test execution definition
add_executable(
    test_avl
    ${test_file}
    ${src_file}
)
