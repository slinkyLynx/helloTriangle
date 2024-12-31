#!/bin/bash

cd code/build_release
make -j$(nproc)
cd ../..
