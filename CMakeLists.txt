# Name of project
project(libavl)

# Test execution definition
add_executable(
    bin/test_avl
    src/test_avl.c
    src/avl.h
    src/avl.c
    src/syslog.h
)
