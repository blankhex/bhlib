cmake_minimum_required(VERSION 3.10)

# Project and C standard configuration
project(bhunit LANGUAGES C)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Disable extensions
set(CMAKE_C_EXTENSIONS OFF)

# Library code
set(BHUNIT_SOURCE
    src/Unit.c
)

set(BHUNIT_HEADER
    include/BH/Unit.h
)

# Library
add_library(BHUnit STATIC ${BHUNIT_SOURCE} ${BHUNIT_HEADER})
target_include_directories(BHUnit PUBLIC include)

# Enable all compiler warnings
if(MSVC)
    target_compile_options(BHUnit PRIVATE /W4 /WX)
else()
    target_compile_options(BHUnit PRIVATE -Wall -Wextra -Wpedantic -Werror -fstrict-aliasing)
endif()
