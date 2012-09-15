cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include(CTest)

# Flag to indicate a general CMakeLists.txt
set(GLOBAL_PROJECT ON)

# Add submodule
add_subdirectory(libavl)

enable_testing()
