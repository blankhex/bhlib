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

# Unit testing and coverage configuration
set(ENABLE_TESTING ON CACHE BOOL "Enable unit-testing")
set(ENABLE_COVERAGE OFF CACHE BOOL "Enable coverage")
set(ENABLE_EXAMPLES ON CACHE BOOL "Enable building examples")
set(ENABLE_LTO ON CACHE BOOL "Enable LTO support")
set(ENABLE_MT ON CACHE BOOL "Enable multithreading support")

# Enable IPO/LTO
if(ENABLE_LTO)
    check_ipo_supported(RESULT LTO_SUPPORTED)
    if(LTO_SUPPORTED)
        message(STATUS "IPO/LTO enabled")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endif()

# Enable testing
if(ENABLE_TESTING)
    include(CTest)
    enable_testing()
endif()

# Set library code
set(BH_SOURCE
    src/Algo.c
    src/Args.c
    src/Hashmap.c
    src/IO.c
    src/Math/Box2f.c
    src/Math/Box3f.c
    src/Math/Line.c
    src/Math/Mat3f.c
    src/Math/Mat4f.c
    src/Math/Misc.c
    src/Math/Plane.c
    src/Math/Quat4f.c
    src/Math/Ray2f.c
    src/Math/Ray3f.c
    src/Math/Vec2f.c
    src/Math/Vec2i.c
    src/Math/Vec3f.c
    src/Math/Vec3i.c
    src/Math/Vec4f.c
    src/Math/Vec4i.c
    src/Queue.c
    src/Util.c
)

set(BH_HEADER
    include/BH/Common.h
    include/BH/Algo.h
    include/BH/Args.h
    include/BH/Hashmap.h
    include/BH/IO.h
    include/BH/Math.h
    include/BH/Queue.h
    include/BH/Util.h
    include/BH/Thread.h
)

set(BH_SOURCE_DUMMY
    src/Platform/Dummy/File.c
)

set(BH_SOURCE_WIN32
    src/Platform/Win32/File.c
)

set(BH_SOURCE_POSIX
    src/Platform/Posix/File.c
)

set(BH_SOURCE_WIN32_MT
    src/Platform/Win32/Condition.c
    src/Platform/Win32/Mutex.c
    src/Platform/Win32/Semaphore.c
    src/Platform/Win32/Thread.c
    src/Platform/Win32/Tss.c
    src/Platform/Spinlock.c
)

set(BH_HEADER_WIN32_MT
    src/Platform/Win32/Thread.h
)

set(BH_SOURCE_POSIX_MT
    src/Platform/Posix/Condition.c
    src/Platform/Posix/Mutex.c
    src/Platform/Posix/Semaphore.c
    src/Platform/Posix/Thread.c
    src/Platform/Posix/Tss.c
    src/Platform/Spinlock.c
)

set(BH_HEADER_POSIX_MT
    src/Platform/Posix/Thread.h
)

set(BH_SOURCE_DUMMY_MT
    src/Platform/Dummy/Condition.c
    src/Platform/Dummy/Mutex.c
    src/Platform/Dummy/Semaphore.c
    src/Platform/Dummy/Thread.c
    src/Platform/Dummy/Tss.c
)

set(BH_HEADER_DUMMY_MT
    src/Platform/Dummy/Thread.h
)

set(BH_INCLUDE_DIRS
    include
    ${PROJECT_BINARY_DIR}/include
)

# Determine platform
if(WIN32)
    message(STATUS "Platform - Win32")

    # Add platform dependent files
    list(APPEND BH_SOURCE ${BH_SOURCE_WIN32})

    # Add platform dependent multithreading support
    if(ENABLE_MT)
        list(APPEND BH_SOURCE ${BH_SOURCE_WIN32_MT})
        list(APPEND BH_HEADER ${BH_HEADER_WIN32_MT})
    else()
        list(APPEND BH_SOURCE ${BH_SOURCE_DUMMY_MT})
        list(APPEND BH_HEADER ${BH_HEADER_DUMMY_MT})
    endif()
elseif(UNIX)
    message(STATUS "Platform: Unix (Linux/BSD/MacOS X)")

    # Add platform dependent files
    list(APPEND BH_SOURCE ${BH_SOURCE_POSIX})

    # Add platform dependent multithreading support
    if(ENABLE_MT)
        list(APPEND BH_SOURCE ${BH_SOURCE_POSIX_MT})
        list(APPEND BH_HEADER ${BH_HEADER_POSIX_MT})
    else()
        list(APPEND BH_SOURCE ${BH_SOURCE_DUMMY_MT})
        list(APPEND BH_HEADER ${BH_HEADER_DUMMY_MT})
    endif()
else()
    message(STATUS "Platform: Unknown")

    # Add platform dependent files
    list(APPEND BH_SOURCE ${BH_SOURCE_DUMMY} ${BH_SOURCE_DUMMY_MT})
    list(APPEND BH_HEADER ${BH_HEADER_DUMMY_MT})
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
if(ENABLE_COVERAGE)
    target_compile_options(BHLib PRIVATE -coverage)
    target_link_options(BHLib PRIVATE -coverage)
endif()

# Tests
if(ENABLE_TESTING)
    add_subdirectory(unit)
    add_subdirectory(test)
endif()

if(ENABLE_EXAMPLES)
    add_subdirectory(doc/Examples)
endif()