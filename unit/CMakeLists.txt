cmake_minimum_required(VERSION 3.10)

# Project and C standard configuration
project(bhunit LANGUAGES C)
set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Disable extensions
set(CMAKE_C_EXTENSIONS OFF)

# Library code
set(BHUNIT_SOURCE
    src/unit.c
)

set(BHUNIT_HEADER
    include/bh/unit.h
)

# Library
add_library(bhunit STATIC ${BHUNIT_SOURCE} ${BHUNIT_HEADER})
target_include_directories(bhunit PUBLIC include)

# Enable all compiler warnings
if(MSVC)
  target_compile_options(bhunit PRIVATE /W4 /WX)
else()
  target_compile_options(bhunit PRIVATE -Wall -Wextra -Wpedantic -Werror -fstrict-aliasing)
endif()