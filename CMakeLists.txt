# --- General CMake configuration ---
cmake_minimum_required(VERSION 3.10)

# Project and C standard configuration
project(bhlib LANGUAGES C)

# Include CMake modules
include(CheckIPOSupported)
include(CheckIncludeFile)
include(CheckSymbolExists)

# Check for IPO/LTO
check_ipo_supported(RESULT BH_IPO)
if(BH_IPO)
    message(STATUS "IPO/LTO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Enable testing
include(CTest)
enable_testing()

# --- Project configuration ---
# Sources
set(BH_SOURCES
    src/algo.c
    src/ds.c
    src/tpool.c
)

set(BH_HEADERS
    include/bh/algo.h
    include/bh/bh.h
    include/bh/ds.h
    include/bh/thread.h
    ${PROJECT_BINARY_DIR}/include/bh/config.h
)

set(BH_INCLUDE_DIRS
    include
    ${PROJECT_BINARY_DIR}/include
)

# Determine platform
if(WIN32)
    message(STATUS "Platform - Win32")
    
    list(APPEND BH_INCLUDE_DIRS
        platform/win32/include
    )

    # Check multithreading support
    check_symbol_exists(_beginthread process.h BH_USE_THREADS)
    if (BH_USE_THREADS)
        message(STATUS "Multithreading enabled")
        list(APPEND BH_SOURCES
            platform/win32/src/thread.c
        )
        list(APPEND BH_HEADERS
            platform/win32/include/bh/thread_base.h
        )
    else()
        list(APPEND BH_SOURCES
            src/thread.c
        )
    endif()
    list(APPEND BH_SOURCES
    )
    list(APPEND BH_HEADERS
    )
elseif(UNIX)
    message(STATUS "Platform: Unix (Linux/BSD/MacOS X)")

    list(APPEND BH_INCLUDE_DIRS
        platform/unix/include
    )

    # Check multithreading support
    check_include_file(pthread.h BH_USE_THREADS)
    if (BH_USE_THREADS)
        message(STATUS "Multithreading enabled")
        list(APPEND BH_SOURCES
            platform/unix/src/thread.c
        )
        list(APPEND BH_HEADERS
            platform/unix/include/bh/thread_base.h
        )
    else()
        list(APPEND BH_SOURCES
            src/thread.c
        )
    endif()
    list(APPEND BH_HEADERS
    )
    list(APPEND BH_SOURCES
    )
else()
    message(STATUS "Platform: Unknown")
    list(APPEND BH_SOURCES
        src/thread.c
    )
endif()

# Configure library
configure_file(include/bh/config.in include/bh/config.h)

add_library(bh STATIC ${BH_SOURCES} ${BH_HEADERS})
target_include_directories(bh PUBLIC ${BH_INCLUDE_DIRS})
