# Determine the minimum required version for CMake
# This script was elaborated with CMake 2.8 and nothing
# prove that it is fully functionnal under a lower version.
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Start to give a name to your sub-project (ie, your current
# module). Use the name of the subdirectory where you are now.
#
# Ex:   set(CURRENT_PROJECT "sound")
set(CURRENT_PROJECT "libavl")

# Personalize your project
# Set some variable to activate or deactivate features in project
# The value given here are the default value of each parameters.
#
# COVERAGE:
# To perform a coverage test when running the whole test plan.
# This feature is enable by default.
# Accepted values: ON/OFF
#set(COVERAGE ON)
#
# DEBUG:
# Activate debug information when compiling.
# This feature is enable by default.
# Accepted values: ON/OFF
#set(DEBUG ON)
#
#                               NOTE
# With this feature, the source code is compiled with the following
# options:
#                    -ggdb3
#                    -O0
#                    -W
#                    -Wall
#                    -Wextra
#                    -Wunused-value
#                    -Waddress
#                    -Wmain
#                    -Wmissing-braces
#                    -Wmissing-noreturn
#                    -Wpointer-arith
#                    -Wreturn-type
#                    -Wshadow
#                    -Wsign-conversion
#                    -Wstack-protector
#                    -Wswitch-default
#                    -Wundef
#                    -Wuninitialized
#                    -Wunused-paramete
#
# LOGLEVEL:
# Set level of log in trace you want.
# Accepted values:
#       0: No log is printed
#       1: Error log only
#       2: Warning log
#       3: Information log
#       4: Debug log
#       5: Function log
#set(LOGLEVEL 5)
#
# VERBOSE:
# If set to ON, the CMake system give more information on what he is
# doing.
# Enable by default.
# Accepted values: ON/OFF
#set(VERBOSE ON)
#


# It is the first most important step (the second is automatically
# done if this step runs well). You must include the file
# "CGlob.cmake" at the top level of sources.
#
# This file will set a serie of variable which will be very usefull
# in compiling step.
#
# According to the previous options, it tells to the compiler the
# options it must use, and it define variable ROOT_DEPEDENCY which
# is the path of the root of source.
include(../CGlob.cmake)

# Include general macro for building project.
#
# This file create the macro "build" for Makefile generation.
# This macro need only a list of module name that the current
# module need.
#
# It parses all source file in the current project directory and
# separate it in two classes: the module source file and the module
# test file.
# To be recognized as test, a test file must end with _test##.(c|cpp).
# If module sound contains 4 files:
#       sound.cpp, sound.h, sound_test01.cpp and sound_test02.c, 
# both sound_test01.cpp and sound_test02.c will be considerated as test
# file and compiled separratedly with file sound.cpp and sound.h.
#
# If a dependant list of module is specified, CMake will also compile
# and link the module source file of each dependant module.
#
# Finally, by default, the directory "utils" is automatically added to
# the looking directory.
include(${ROOT_DEPENDENCY}/CMacro.cmake)

# Give dependency of a project
# If your module need "net" module and "lib" module, add here:
#list(APPEND DEPEND "net" "lib")
list(APPEND DEPEND "")

# Build your module
build_module()

# Enable testing
enable_testing()
