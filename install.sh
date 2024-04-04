#!/bin/bash


rm -rf build bin

cmake -S . -B build  -DCMAKE_CXX_COMPILER=/usr/bin/g++-11
cmake --build build

cd build
#ctest

# Optional: Change back to the original directory
cd ..

