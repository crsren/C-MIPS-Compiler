#!/bin/bash

rm -rf bin build
mkdir -p build bin && cd build
cmake .. -DCMAKE_CXX_FLAGS=-std=c++11
make
cd ..
cp build/src/compiler bin/compiler