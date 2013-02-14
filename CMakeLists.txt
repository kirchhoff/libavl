#       DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
#                   Version 2, December 2004 
#
# Copyright (C) 2013 Adrien Oliva <adrien.oliva@yapbreak.fr>
#
# Everyone is permitted to copy and distribute verbatim or modified 
# copies of this license document, and changing it is allowed as long 
# as the name is changed. 
#
#           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
#  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 
#
# 0. You just DO WHAT THE FUCK YOU WANT TO.
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
