cmake_minimum_required(VERSION 3.10)

# Project and C standard configuration
project(bhlib LANGUAGES C)

# Check for IPO/LTO
include(CheckIPOSupported)
check_ipo_supported(RESULT supported)

if(supported)
    message(STATUS "IPO/LTO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Enable testing
include(CTest)
enable_testing()

# Add subdirectories
set(BH_SOURCES
    src/algo.c
    src/ds.c
    src/thread.c
)

set(BH_HEADERS
    include/bh/algo.h
    include/bh/bh.h
    include/bh/ds.h
    include/bh/thread.h
)

add_library(bh STATIC ${BH_SOURCES} ${BH_HEADERS})
target_include_directories(bh PUBLIC include)
