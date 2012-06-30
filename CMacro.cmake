# Include test definition
include(CTest)


# Macro for module building
macro(build_module)

    # Path used in macro
    if(${VERBOSE})
        message("Project source directory.......................: ${${CURRENT_PROJECT}_SOURCE_DIR}")
        message("Root directory.................................: ${ROOT_DEPENDENCY}")
    endif(${VERBOSE})

    file(GLOB ${CURRENT_PROJECT}_sources
        RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
        *.c *.h *.cpp
    )

    # Separate test and source file
    foreach(source ${${CURRENT_PROJECT}_sources})
        if(${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
            list(APPEND ${CURRENT_PROJECT}_source_test ${source})
        else(${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
            list(APPEND ${CURRENT_PROJECT}_source_module ${source})
        endif(${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
    endforeach(source ${${CURRENT_PROJECT}_sources})

    if(${VERBOSE})
        message("Found these source files..............: ${${CURRENT_PROJECT}_source_module}")
        message("Found these test files................: ${${CURRENT_PROJECT}_source_test}")
    endif(${VERBOSE})

    # Add compilation rules
    include_directories(${ROOT_DEPENDENCY}/utils)
    foreach(test ${${CURRENT_PROJECT}_source_test})
        string(REGEX REPLACE ".*/(.*).(c|cpp)$" "\\1" output_test ${test})
        add_executable(${output_test} ${test} ${${CURRENT_PROJECT}_source_module} )
        if(${COVERAGE})
            target_link_libraries(${output_test} -lgcov)
        endif(${COVERAGE})

        if(${GLOBAL_PROJECT})
            add_test(${output_test} ${CMAKE_BINARY_DIR}/${CURRENT_PROJECT}/${output_test})
        else(${GLOBAL_PROJECT})
            add_test(${output_test} ${CMAKE_BINARY_DIR}/${output_test})
        endif(${GLOBAL_PROJECT})
    endforeach(test ${${CURRENT_PROJECT}_source_test})
endmacro(build_module)

# Macro for module building
macro(build depend_list)

    # Path used in macro
    if(${VERBOSE})
        message("Project source directory.......................: ${${CURRENT_PROJECT}_SOURCE_DIR}")
        message("Root directory.................................: ${ROOT_DEPENDENCY}")
    endif(${VERBOSE})

    file(GLOB ${CURRENT_PROJECT}_sources
        RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
        *.c *.h *.cpp
    )

    # Separate test and source file
    foreach(source ${${CURRENT_PROJECT}_sources})
        if(${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
            list(APPEND ${CURRENT_PROJECT}_source_test ${source})
        else(${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
            list(APPEND ${CURRENT_PROJECT}_source_module ${source})
        endif(${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
    endforeach(source ${${CURRENT_PROJECT}_sources})

    if(${VERBOSE})
        message("Found these source files..............: ${${CURRENT_PROJECT}_source_module}")
        message("Found these test files................: ${${CURRENT_PROJECT}_source_test}")
    endif(${VERBOSE})

    # Locate dependency source files
    foreach(depend_module ${DEPEND})
        file(GLOB
            ${depend_module}_sources
            RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
            ${ROOT_DEPENDENCY}/${depend_module}/*.[ch] ${ROOT_DEPENDENCY}/${depend_module}/*.cpp
        )
        if(${VERBOSE})
            message("(${depend_module}) Found these source file.........: ${${depend_module}_sources}")
        endif(${VERBOSE})

        # Get source file for dependency
        foreach(source ${${depend_module}_sources})
            if(NOT ${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
                list(APPEND depend_source_module ${source})
            endif(NOT ${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
        endforeach(source ${${depend_module}_sources})

        # Add include directory directive
        include_directories(${ROOT_DEPENDENCY}/${depend_module})
    endforeach(depend_module ${DEPEND})

    if(${VERBOSE})
        message("Found these dependant files...........: ${depend_source_module}")
    endif(${VERBOSE})

    # Add compilation rules
    include_directories(${ROOT_DEPENDENCY}/utils)
    foreach(test ${${CURRENT_PROJECT}_source_test})
        string(REGEX REPLACE ".*/(.*).(c|cpp)$" "\\1" output_test ${test})
        add_executable(${output_test} ${test} ${${CURRENT_PROJECT}_source_module} ${depend_source_module})
        if(${COVERAGE})
            target_link_libraries(${output_test} -lgcov)
        endif(${COVERAGE})

        if(${GLOBAL_PROJECT})
            add_test(${output_test} ${CMAKE_BINARY_DIR}/${CURRENT_PROJECT}/${output_test})
        else(${GLOBAL_PROJECT})
            add_test(${output_test} ${CMAKE_BINARY_DIR}/${output_test})
        endif(${GLOBAL_PROJECT})
    endforeach(test ${${CURRENT_PROJECT}_source_test})
endmacro(build depend_list)

# Macro for main program building
macro(build_main output depend_list)

    # Path used in macro
    if(${VERBOSE})
        message("Project source directory.......................: ${${CURRENT_PROJECT}_SOURCE_DIR}")
        message("Root directory.................................: ${ROOT_DEPENDENCY}")
    endif(${VERBOSE})

    file(GLOB ${CURRENT_PROJECT}_sources
        RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
        *.c *.h *.cpp
    )

    # Separate test and source file
    if(${VERBOSE})
        message("Found these source files..............: ${${CURRENT_PROJECT}_sources}")
    endif(${VERBOSE})

    # Locate dependency source files
    foreach(depend_module ${DEPEND})
        file(GLOB
            ${depend_module}_sources
            RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
            ${ROOT_DEPENDENCY}/${depend_module}/*.[ch] ${ROOT_DEPENDENCY}/${depend_module}/*.cpp
        )
        if(${VERBOSE})
            message("(${depend_module}) Found these source file.........: ${${depend_module}_sources}")
        endif(${VERBOSE})

        # Get source file for dependency
        foreach(source ${${depend_module}_sources})
            if(NOT ${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
                list(APPEND depend_source_module ${source})
            endif(NOT ${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
        endforeach(source ${${depend_module}_sources})

        # Add include directory directive
        include_directories(${ROOT_DEPENDENCY}/${depend_module})
    endforeach(depend_module ${DEPEND})

    if(${VERBOSE})
        message("Found these dependant files...........: ${depend_source_module}")
    endif(${VERBOSE})

    # Add compilation rules
    include_directories(${ROOT_DEPENDENCY}/utils)
    add_executable(${output} ${${CURRENT_PROJECT}_sources} ${depend_source_module})
    if(${COVERAGE})
        target_link_libraries(${output} -lgcov)
    endif(${COVERAGE})
endmacro(build_main output depend_list)

