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
    "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address,undefined" CACHE STRING
    "Linker flags to be used to create executables for Asan build type." FORCE
)

set(CMAKE_SHARED_LINKER_FLAGS_ASAN
    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address,undefined" CACHE STRING
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
    src/Algo.c
    src/Args.c
    src/Hashmap.c
    src/IO.c
    src/Math.c
    src/Queue.c
)

set(BH_HEADER
    include/BH/Common.h
    include/BH/Algo.h
    include/BH/Args.h
    include/BH/Hashmap.h
    include/BH/IO.h
    include/BH/Math.h
    include/BH/Queue.h
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
        src/win32/File.c
    )
elseif(UNIX)
    message(STATUS "Platform: Unix (Linux/BSD/MacOS X)")

    # Add platform dependent files
    list(APPEND BH_SOURCE
        src/posix/File.c
    )
else()
    message(STATUS "Platform: Unknown")

    # Add platform dependent files
    list(APPEND BH_SOURCE
        src/dummy/File.c
    )
endif()

# Library
add_library(BHLib STATIC ${BH_SOURCE} ${BH_HEADER})
target_include_directories(BHLib PUBLIC ${BH_INCLUDE_DIRS})
target_link_libraries(BHLib PUBLIC m)

# Enable all compiler warnings
if(MSVC)
  target_compile_options(BHLib PRIVATE /W4 /WX)
else()
  target_compile_options(BHLib PRIVATE -Wall -Wextra -Wpedantic -Werror -fstrict-aliasing)
endif()

# Coverage
if(COVERAGE)
    target_compile_options(BHLib PRIVATE -coverage)
    target_link_options(BHLib PRIVATE -coverage)
endif()

# Tests
if(TESTING)
    add_subdirectory(unit)
    add_subdirectory(test)
endif()
