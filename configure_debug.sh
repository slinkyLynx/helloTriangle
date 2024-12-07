#!/bin/bash

cd code
mkdir -p build_debug
cd build_debug
cmake ..
cmake -DCMAKE_BUILD_TYPE=Debug .
cd ../..
