cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include(CTest)

# Flag to indicate a general CMakeLists.txt
set(GLOBAL_PROJECT ON)

# Add submodule
add_subdirectory(libavl)
add_subdirectory(example)

enable_testing()


# Add doxygen generator
add_custom_target(doc doxygen ${CMAKE_HOME_DIRECTORY}/Doxyfile)

# Add library build
#add_library(avl SHARED    ${CMAKE_HOME_DIRECTORY}/libavl/avl.c
#                          ${CMAKE_HOME_DIRECTORY}/libavl/avl.h
#                          ${CMAKE_HOME_DIRECTORY}/utils/syslog.h)
#add_library(stavl STATIC  ${CMAKE_HOME_DIRECTORY}/libavl/avl.c
#                          ${CMAKE_HOME_DIRECTORY}/libavl/avl.h
#                          ${CMAKE_HOME_DIRECTORY}/utils/syslog.h)
