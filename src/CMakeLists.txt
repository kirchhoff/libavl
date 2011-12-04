# Create the library libavl with the source file avl.c
file(
    GLOB_RECURSE
    src
    *.c
)

file(
    GLOB_RECURSE
    header
    *.h
)

add_library(
    libavl
    SHARED
    ${src}
    ${header}
)

add_definitions(-DLOGLEVEL=4)
set(CMAKE_C_FLAGS "-W -Wall -Wextra -Werror -O0 -ggdb3")
add_definitions(-fprofile-arcs -ftest-coverage)
target_link_libraries(libavl -lgcov)
