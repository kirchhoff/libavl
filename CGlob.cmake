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
# Set default options
if (NOT DEFINED COVERAGE)
    set(COVERAGE ON)
endif (NOT DEFINED COVERAGE)

if (NOT DEFINED DEBUG)
    set(DEBUG ON)
endif (NOT DEFINED DEBUG)

if (NOT DEFINED LOGLEVEL)
    set(LOGLEVEL 5)
endif (NOT DEFINED LOGLEVEL)

if (NOT DEFINED VERBOSE)
    set(VERBOSE ON)
endif (NOT DEFINED VERBOSE)

# Give a name to sub-project
project(${CURRENT_PROJECT})

# Look for the correct origin
if(${GLOBAL_PROJECT})
    message("Call CMake from main directory")
    set(ROOT_DEPENDENCY ${CMAKE_HOME_DIRECTORY}/)
else(${GLOBAL_PROJECT})
    message("Call CMake for a local test")
    set(ROOT_DEPENDENCY ${CMAKE_HOME_DIRECTORY}/..)
endif(${GLOBAL_PROJECT})

# Interprete options
if (${DEBUG})
    add_definitions(-DLOGLEVEL=${LOGLEVEL}
                    -ggdb3
                    -O0
                    -W
                    -Wall
                    -Wextra
                    -Wunused-value
                    -Waddress
                    -Wmain
                    -Wmissing-braces
                    -Wmissing-noreturn
                    -Wpointer-arith
                    -Wreturn-type
                    -Wshadow
                    -Wsign-conversion
                    -Wstack-protector
                    -Wswitch-default
                    -Wundef
                    -Wuninitialized
                    -Wunused-parameter)
else(${DEBUG})
    add_definitions(-DLOGLEVEL=0
                    -03)
endif(${DEBUG})

if (${COVERAGE})
    add_definitions(-fprofile-arcs -ftest-coverage)
    set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -lgcov")
endif(${COVERAGE})

