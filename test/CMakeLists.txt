set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Enable testing
include(CTest)
enable_testing()

# Search files
file(GLOB TEST_FILES "src/*.c")

foreach(TEST_FILENAME ${TEST_FILES})
    # Add test
    get_filename_component(TEST_NAME ${TEST_FILENAME} NAME_WE)
    add_executable("${TEST_NAME}" ${TEST_FILENAME})
    target_link_libraries("${TEST_NAME}" BHLib BHUnit)
    add_test(NAME "${TEST_NAME}" COMMAND "${TEST_NAME}")

    # Enable all compiler warnings
    if(MSVC)
        target_compile_options("${TEST_NAME}" PRIVATE /W4 /WX)
    else()
        target_compile_options("${TEST_NAME}" PRIVATE -Wall -Wextra -Wpedantic -Werror -fstrict-aliasing)
    endif()

    # Enable coverage
    if(COVERAGE)
        target_compile_options("${TEST_NAME}" PRIVATE -coverage)
        target_link_options("${TEST_NAME}" PRIVATE -coverage)
    endif()
endforeach()
