#!/bin/bash


rm -rf build
# Define the build directory name
BUILD_DIR=build

# Check if the build directory exists. If not, create it.
if [ ! -d "$BUILD_DIR" ]; then
    mkdir $BUILD_DIR
fi

# Change to the build directory
cd $BUILD_DIR

# Run CMake to configure the project and generate the makefile
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/g++-11

# Build the project
make

# Optional: Change back to the original directory
cd ..

