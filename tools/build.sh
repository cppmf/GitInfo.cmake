#!/bin/bash

# go to the root directory
cd ..

# Build the test project
cmake -S "test" -B "build/test" -DGIT_INFO_CMAKE_INFO=ON
cmake --build "build/test"
cmake --build "build/test" --target test