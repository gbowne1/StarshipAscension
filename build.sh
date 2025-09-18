#!/bin/bash

BUILD_TYPE=$1

if [ -z "$BUILD_TYPE" ]; then
  BUILD_TYPE="release"
fi

mkdir -p build
cd build

if [ "$BUILD_TYPE" = "debug" ]; then
  cmake .. -DCMAKE_BUILD_TYPE=Debug
else
  cmake .. -DCMAKE_BUILD_TYPE=Release
fi

make
