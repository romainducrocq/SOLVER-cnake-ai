#!/bin/sh

BUILD_T="Debug"

if [ "$1" = "-R" ]; then
    BUILD_T="Release"
fi

cmake -G "Unix Makefiles" -S ../build/ -B ../build/out/ -DCMAKE_BUILD_TYPE=${BUILD_T}
