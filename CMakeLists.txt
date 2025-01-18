cmake_minimum_required(VERSION 3.10)

# Project and C standard configuration
project(bhlib LANGUAGES C)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Project includes
include(CheckIPOSupported)
include(CheckIncludeFile)
include(CheckSymbolExists)

# Check for IPO/LTO
check_ipo_supported(RESULT supported)
 
# Unit testing and coverage configuration
set(TESTING ON CACHE BOOL "Enable unit-testing")
set(COVERAGE OFF CACHE BOOL "Enable coverage")

if(supported)
    message(STATUS "IPO/LTO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

if(TESTING)
    # Enable testing
    include(CTest)
    enable_testing()
endif(TESTING)

# Set library code
set(BH_SOURCE
    src/algo.c
    src/hashmap.c
    src/io.c
    src/math.c
    src/queue.c
)

set(BH_HEADER
    include/bh/common.h
    include/bh/algo.h
    include/bh/hashmap.h
    include/bh/io.h
    include/bh/math.h
    include/bh/queue.h
)

set(BH_INCLUDE_DIRS
    include
    ${PROJECT_BINARY_DIR}/include
)

# Determine platform
if(WIN32)
    message(STATUS "Platform - Win32")

    # Add platform dependent files
    list(APPEND BH_SOURCE
        src/win32/file.c
    )
elseif(UNIX)
    message(STATUS "Platform: Unix (Linux/BSD/MacOS X)")

    # Add platform dependent files
    list(APPEND BH_SOURCE
        src/posix/file.c
    )
else()
    message(STATUS "Platform: Unknown")

    # Add platform dependent files
    list(APPEND BH_SOURCE
        src/dummy/file.c
    )
endif()

# Library
add_library(bhlib STATIC ${BH_SOURCE} ${BH_HEADER})
target_include_directories(bhlib PUBLIC ${BH_INCLUDE_DIRS})
target_link_libraries(bhlib PUBLIC m)

# Enable all compiler warnings
if(MSVC)
  target_compile_options(bhlib PRIVATE /W4 /WX)
else()
  target_compile_options(bhlib PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Coverage
if(COVERAGE)
    target_compile_options(bhlib PRIVATE -coverage)
    target_link_options(bhlib PRIVATE -coverage)
endif()

# Tests
if(TESTING)
    add_subdirectory(unit)
    add_subdirectory(test)
endif()
