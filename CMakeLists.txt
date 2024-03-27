cmake_minimum_required(VERSION 3.10) # Specify the minimum version of CMake required

# Project Name, Version, and Description
project(MDTraj VERSION 1.0 DESCRIPTION "Molecular Dynamics Analysis Tool")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create a library target for the core functionality
add_library(core
  src/XYZReader.cpp
  src/RDFCalculator.cpp
)

# Include directories
# Assuming all relevant headers are in the 'src' directory or specifically in an 'include' directory
include_directories(src)
include_directories(include) # Only if you have this directory and it's necessary

# Main executable
add_executable(MDTraj src/main.cpp)
target_link_libraries(MDTraj core)

# Enable testing with CTest
enable_testing()

# Include Google Test as a dependency
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.10.0.zip
)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(runUnitTests
  tests/test_xyz_reader.cpp
  tests/test_rdf_calculator.cpp
)
target_link_libraries(runUnitTests core gtest gtest_main pthread)

# Include Google Test's utilities for better integration and reporting
include(GoogleTest)
gtest_discover_tests(runUnitTests)

# Compiler options to handle specific warnings or requirements
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # Suppressing maybe-uninitialized warning caused by Google Test in GCC
  target_compile_options(gtest PRIVATE -Wno-maybe-uninitialized)
endif()

