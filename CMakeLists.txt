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
add_subdirectory(core)
