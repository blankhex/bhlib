#!/bin/bash

rm -rf build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -DCOVERAGE=1
cmake --build build
pushd build
ctest -T test
ctest -T coverage
popd
