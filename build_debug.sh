#!/bin/bash

cd code/build_debug
make -j$(nproc)
cd ../..
