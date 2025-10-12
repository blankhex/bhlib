# Project and C standard configuration
project(bhunit LANGUAGES C)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Disable extensions
set(CMAKE_C_EXTENSIONS OFF)

# Library code
set(BHBENCH_SOURCE
    src/Bench.c
)

set(BHBENCH_HEADER
    include/BH/Bench.h
)

# Library
add_library(BHBench STATIC ${BHBENCH_SOURCE} ${BHBENCH_HEADER})
target_include_directories(BHBench PUBLIC include)
target_link_libraries(BHBench BHLib)

# Enable testing
include(CTest)
enable_testing()

# Search files
file(GLOB TEST_FILES "tests/*.c")

foreach(TEST_FILENAME ${TEST_FILES})
    # Add test
    get_filename_component(TEST_NAME ${TEST_FILENAME} NAME_WE)
    add_executable("${TEST_NAME}" ${TEST_FILENAME})
    target_link_libraries("${TEST_NAME}" BHLib BHBench)
    add_test(NAME "${TEST_NAME}" COMMAND "${TEST_NAME}")

    # Enable coverage
    if(ENABLE_COVERAGE)
        target_compile_options("${TEST_NAME}" PRIVATE -coverage)
        target_link_options("${TEST_NAME}" PRIVATE -coverage)
    endif()
endforeach()
