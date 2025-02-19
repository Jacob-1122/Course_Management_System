#!/bin/bash

# Compile the C++ files
clang++ -o quadrant_analysis main.cpp Point.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Running the program..."
    ./quadrant_analysis
else
    echo "Compilation failed!"
fi