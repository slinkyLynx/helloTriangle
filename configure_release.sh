#!/bin/bash

cd code
mkdir -p build_release
cd build_release
cmake ..
cmake -DCMAKE_BUILD_TYPE=Release .
cd ../..
