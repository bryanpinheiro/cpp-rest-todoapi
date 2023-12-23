#!/bin/bash

# Remove database directory if it exists
if [ -d "database" ]; then
    rm -rf database
fi

# Create database directory
mkdir database

# Remove build directory if it exists
if [ -d "build" ]; then
    rm -rf build
fi

# Create build directory
mkdir build

# Change to the build directory
cd build || exit

# Run CMake
cmake ..

# Build the project
cmake --build .
