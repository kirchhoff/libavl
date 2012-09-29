# Include test definition
include(CTest)

# Macro for building the current module
macro(build_module)
    # Path used in macro
    if (${VERBOSE})
        message("Source directory: ${${CURRENT_PROJECT}_SOURCE_DIR}")
        message("Root directory..: ${ROOT_DEPENDENCY}")
    endif(${VERBOSE})

    # Get all source file in current module directory
    file(GLOB ${CURRENT_PROJECT}_sources
         RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
         *.c *.cpp *.h
         )

    # Separate test and source file
    foreach(source ${${CURRENT_PROJECT}_sources})
        if (${source} MATCHES "^.*_test[0-9][0-9]*.(c|cpp)$")
            # Current file is a test file
            list(APPEND ${CURRENT_PROJECT}_source_test ${source})
        else (${source} MATCHES "^.*_test[0-9][0-9]*.(c|cpp)$")
            # Current file is a module source file
            list(APPEND ${CURRENT_PROJECT}_source_module ${source})
        endif (${source} MATCHES "^.*_test[0-9][0-9]*.(c|cpp)$")
    endforeach(source ${${CURRENT_PROJECT}_sources})

    if (${VERBOSE})
        message("Source files....:")
        foreach(source ${${CURRENT_PROJECT}_source_module})
            message("                  ${source}")
        endforeach(source ${${CURRENT_PROJECT}_source_module})
        message("Test files......:")
        foreach(source ${${CURRENT_PROJECT}_source_test})
            message("                  ${source}")
        endforeach(source ${${CURRENT_PROJECT}_source_test})
    endif(${VERBOSE})

    # Compile into a static library to do some tests
    add_library(${CURRENT_PROJECT}_static
                STATIC
                ${${CURRENT_PROJECT}_source_module})

    # Add compilation rules for unit tests
    foreach(test ${${CURRENT_PROJECT}_source_test})
        string(REGEX REPLACE ".*/(.*).(c|cpp)$" "\\1" output_test ${test})
        add_executable(${output_test}
                       ${test})
        add_dependencies(${output_test}
                         ${CURRENT_PROJECT}_static)
        target_link_libraries(${output_test} ${CURRENT_PROJECT}_static)
        target_link_libraries(${output_test} --static)

        # Add Test definition
        if (${GLOBAL_PROJECT})
            add_test(${output_test}
                     ${CMAKE_BINARY_DIR}/${CURRENT_PROJECT}/${output_test})
        else (${GLOBAL_PROJECT})
            add_test(${output_test}
                     ${CMAKE_BINARY_DIR}/${output_test})
        endif (${GLOBAL_PROJECT})
    endforeach(test ${${CURRENT_PROJECT}_source_test})
endmacro(build_module)

# Macro for building the current module with dependency
macro(build depend_list)
    # Path used in macro
    if (${VERBOSE})
        message("Source directory: ${${CURRENT_PROJECT}_SOURCE_DIR}")
        message("Root directory..: ${ROOT_DEPENDENCY}")
    endif(${VERBOSE})

    # Get all source file in current module directory
    file(GLOB ${CURRENT_PROJECT}_sources
         RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
         *.c *.cpp *.h
         )

    # Separate test and source file
    foreach(source ${${CURRENT_PROJECT}_sources})
        if (${source} MATCHES "^.*_test[0-9][0-9]*.(c|cpp)$")
            # Current file is a test file
            list(APPEND ${CURRENT_PROJECT}_source_test ${source})
        else (${source} MATCHES "^.*_test[0-9][0-9]*.(c|cpp)$")
            # Current file is a module source file
            list(APPEND ${CURRENT_PROJECT}_source_module ${source})
        endif (${source} MATCHES "^.*_test[0-9][0-9]*.(c|cpp)$")
    endforeach(source ${${CURRENT_PROJECT}_sources})

    if (${VERBOSE})
        message("Source files....:")
        foreach(source ${${CURRENT_PROJECT}_source_module})
            message("                  ${source}")
        endforeach(source ${${CURRENT_PROJECT}_source_module})
        message("Test files......:")
        foreach(source ${${CURRENT_PROJECT}_source_test})
            message("                  ${source}")
        endforeach(source ${${CURRENT_PROJECT}_source_test})
    endif(${VERBOSE})

    # Get dependency module information
    foreach (depend_module ${depend_list})
        file(GLOB
             ${depend_module}_all_sources
             RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
             ${ROOT_DEPENDENCY}/${depend_module}/*.[ch]
             ${ROOT_DEPENDENCY}/${depend_module}/*.cpp)
        # Discard test source file
        foreach(source ${${depend_module}_all_sources})
            if(NOT ${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
                list(APPEND ${depend_module}_source ${source})
            endif(NOT ${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
        endforeach(source ${${depend_module}_all_sources})

        if (${VERBOSE})
            message("[${depend_module}]")
            message("Source files....:")
            foreach(source ${${depend_module}_source})
                message("                  ${source}")
            endforeach(source ${${depend_module}_source})
        endif(${VERBOSE})

        # Create static library and add it to dependency list
        add_library(${CURRENT_PROJECT}_${depend_module}_static
                    STATIC
                    ${${depend_module}_source})
        list(APPEND lib_depend ${CURRENT_PROJECT}_${depend_module}_static)

        # Add include directory directive
        include_directories(${ROOT_DEPENDENCY}/${depend_module})
    endforeach (depend_module ${depend_list})

    # Compile into a static library to do some tests
    add_library(${CURRENT_PROJECT}_static
                STATIC
                ${${CURRENT_PROJECT}_source_module})

    # Add compilation rules for unit tests
    foreach(test ${${CURRENT_PROJECT}_source_test})
        string(REGEX REPLACE ".*/(.*).(c|cpp)$" "\\1" output_test ${test})
        add_executable(${output_test}
                       ${test})
        add_dependencies(${output_test}
                         ${CURRENT_PROJECT}_static
                         ${lib_depend})
                     message("${CURRENT_PROJECT}_static ${lib_depend}")
        target_link_libraries(${output_test} ${CURRENT_PROJECT}_static)
        foreach(static ${lib_depend})
            target_link_libraries(${output_test} ${static})
        endforeach(static ${lib_depend})
        target_link_libraries(${output_test} --static)

        # Add Test definition
        if (${GLOBAL_PROJECT})
            add_test(${output_test}
                     ${CMAKE_BINARY_DIR}/${CURRENT_PROJECT}/${output_test})
        else (${GLOBAL_PROJECT})
            add_test(${output_test}
                     ${CMAKE_BINARY_DIR}/${output_test})
        endif (${GLOBAL_PROJECT})
    endforeach(test ${${CURRENT_PROJECT}_source_test})
endmacro(build depend_list)

# Macro for building the main module with dependency
macro(build_main output main_src depend_list)
    # Path used in macro
    if (${VERBOSE})
        message("Source directory: ${${CURRENT_PROJECT}_SOURCE_DIR}")
        message("Root directory..: ${ROOT_DEPENDENCY}")
    endif(${VERBOSE})

    # Get all source file in current module directory
    file(GLOB ${CURRENT_PROJECT}_sources
         RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
         *.c *.cpp *.h
         )

    # Separate test and source file
    foreach(source ${${CURRENT_PROJECT}_sources})
        if (${source} MATCHES "^.*_test[0-9][0-9]*.(c|cpp)$")
            # Current file is a test file
            list(APPEND ${CURRENT_PROJECT}_source_test ${source})
        else (${source} MATCHES "^.*_test[0-9][0-9]*.(c|cpp)$")
            if (NOT ${source} MATCHES "${main_src}")
                # Current file is a module source file
                list(APPEND ${CURRENT_PROJECT}_source_module ${source})
            endif (NOT ${source} MATCHES "${main_src}")
        endif (${source} MATCHES "^.*_test[0-9][0-9]*.(c|cpp)$")
    endforeach(source ${${CURRENT_PROJECT}_sources})

    if (${VERBOSE})
        message("Source files....:")
        foreach(source ${${CURRENT_PROJECT}_source_module})
            message("                  ${source}")
        endforeach(source ${${CURRENT_PROJECT}_source_module})
        message("Test files......:")
        foreach(source ${${CURRENT_PROJECT}_source_test})
            message("                  ${source}")
        endforeach(source ${${CURRENT_PROJECT}_source_test})
        message("Main src file...:")
        message("                 ${main_src}")
    endif(${VERBOSE})

    # Get dependency module information
    foreach (depend_module ${depend_list})
        file(GLOB
             ${depend_module}_all_sources
             RELATIVE ${${CURRENT_PROJECT}_SOURCE_DIR}
             ${ROOT_DEPENDENCY}/${depend_module}/*.[ch]
             ${ROOT_DEPENDENCY}/${depend_module}/*.cpp)
        # Discard test source file
        foreach(source ${${depend_module}_all_sources})
            if(NOT ${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
                list(APPEND ${depend_module}_source ${source})
            endif(NOT ${source} MATCHES "^.*_test[0-9][0-9].(c|cpp)$")
        endforeach(source ${${depend_module}_all_sources})

        if (${VERBOSE})
            message("[${depend_module}]")
            message("Source files....:")
            foreach(source ${${depend_module}_source})
                message("                  ${source}")
            endforeach(source ${${depend_module}_source})
        endif(${VERBOSE})

        # Create static library and add it to dependency list
        add_library(${CURRENT_PROJECT}_${depend_module}_static
                    STATIC
                    ${${depend_module}_source})
        list(APPEND lib_depend ${CURRENT_PROJECT}_${depend_module}_static)

        # Add include directory directive
        include_directories(${ROOT_DEPENDENCY}/${depend_module})
    endforeach (depend_module ${depend_list})

    # Compile into a static library to do some tests
    if ("${${CURRENT_PROJECT}_source_module}")
        add_library(${CURRENT_PROJECT}
                    STATIC
                    ${${CURRENT_PROJECT}_source_module})
    endif("${${CURRENT_PROJECT}_source_module}")

    # Add compilation rules for unit tests
    foreach(test ${${CURRENT_PROJECT}_source_test})
        string(REGEX REPLACE ".*/(.*).(c|cpp)$" "\\1" output_test ${test})
        add_executable(${output_test}
                       ${test})
        if ("${${CURRENT_PROJECT}_source_module}")
            add_dependencies(${output_test}
                             ${CURRENT_PROJECT})
            target_link_libraries(${output_test} ${CURRENT_PROJECT})
        endif("${${CURRENT_PROJECT}_source_module}")
        if ("${lib_depend}")
            add_dependencies(${output_test}
                             ${lib_depend})
            foreach(static ${lib_depend})
                target_link_libraries(${output_test} ${static})
            endforeach(static ${lib_depend})
        endif ("${lib_depend}")
        target_link_libraries(${output_test} --static)

        # Add Test definition
        if (${GLOBAL_PROJECT})
            add_test(${output_test}
                     ${CMAKE_BINARY_DIR}/${CURRENT_PROJECT}/${output_test})
        else (${GLOBAL_PROJECT})
            add_test(${output_test}
                     ${CMAKE_BINARY_DIR}/${output_test})
        endif (${GLOBAL_PROJECT})
    endforeach(test ${${CURRENT_PROJECT}_source_test})

    # Add compilation of main program
    add_executable(${output}
                   ${main_src})
    if ("${${CURRENT_PROJECT}_source_module}")
        add_dependencies(${output}
                         ${CURRENT_PROJECT})
        target_link_libraries(${output} ${CURRENT_PROJECT})
    endif("${${CURRENT_PROJECT}_source_module}")
    if (lib_depend)
        message("Add dependency: ${lib_depend}")
        add_dependencies(${output} ${lib_depend})
        foreach(static ${lib_depend})
            target_link_libraries(${output} ${static})
        endforeach(static ${lib_depend})
    endif (lib_depend)
    target_link_libraries(${output} --static)
endmacro(build_main output main_src depend_list)
