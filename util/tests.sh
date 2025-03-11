#!/bin/sh

# Set of compilers and profiles for testing
compilers="gcc clang"
profiles="Debug Release Asan"

# Build and run tests
build_and_run() {
    compiler=$1
    mode=$2

    # Reconfigure project
    rm -rf build
    cmake -S . -B build -DCMAKE_BUILD_TYPE=${mode} -DCMAKE_C_COMPILER=${compiler}
    if [ $? -ne 0 ]; then
        return 1
    fi

    # Build
    cmake --build build
    if [ $? -ne 0 ]; then
        return 1
    fi

    # Test
    ctest -T test --test-dir build
    if [ $? -ne 0 ]; then
        return 1
    fi

    return 0
}

# For each compiler and profile - run test
for compiler in $compilers; do
    for profile in $profiles; do
        if ! build_and_run $compiler $profile; then
            echo "Tests failed for $compiler $profile"
            exit 1
        fi
    done
done
