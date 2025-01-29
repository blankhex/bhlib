cmake_minimum_required(VERSION 3.10)

# Project and C standard configuration
project(bhlib LANGUAGES C)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Asan profile
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(isMultiConfig)
    if(NOT "Asan" IN_LIST CMAKE_CONFIGURATION_TYPES)
        list(APPEND CMAKE_CONFIGURATION_TYPES Asan)
    endif()
else()
    set(allowedBuildTypes Asan Debug Release RelWithDebInfo MinSizeRel)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${allowedBuildTypes}")

    if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes)
        message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
    endif()
endif()

set(CMAKE_C_FLAGS_ASAN
    "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address,undefined -fno-omit-frame-pointer" CACHE STRING
    "Flags used by the C compiler for Asan build type or configuration." FORCE
)

set(CMAKE_CXX_FLAGS_ASAN
    "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -fno-omit-frame-pointer" CACHE STRING
    "Flags used by the C++ compiler for Asan build type or configuration." FORCE
)

set(CMAKE_EXE_LINKER_FLAGS_ASAN
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address,undefined -static-libasan" CACHE STRING
    "Linker flags to be used to create executables for Asan build type." FORCE
)

set(CMAKE_SHARED_LINKER_FLAGS_ASAN
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address,undefined -static-libasan" CACHE STRING
    "Linker lags to be used to create shared libraries for Asan build type." FORCE
)

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
  target_compile_options(bhlib PRIVATE -Wall -Wextra -Wpedantic -Werror -fstrict-aliasing)
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
