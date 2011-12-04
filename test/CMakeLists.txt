# Make sure the compiler can find include files from avl library.
include_directories(${libavl_SOURCE_DIR}/src)

# Make sure the linker can find the libavl once it is built.
link_directories(${libavl_BINARY_DIR}/src)

# Add executable called test1.
add_executable(
    test1
    test1.c
)

# Link executable with library.
target_link_libraries(test1 libavl)

# Test section
enable_testing()

add_test(test1 ${libavl_BINARY_DIR}/test/test1 100)

set(CMAKE_C_FLAGS "-W -Wall -Wextra -Werror -O0 -ggdb3")
add_definitions(-fprofile-arcs -ftest-coverage)
target_link_libraries(test1 -lgcov)
