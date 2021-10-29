#!/bin/bash

# go to the root directory
cd ..

# Build the test project
cmake -S "test" -B "build/test" -DGIT_INFO_CMAKE_INFO=ON
cmake --build "build/test" --config Release

# run the application
./build/test/test_app