#!/bin/bash
CMAKE=$(which cmake)
NINJA=$(which ninja)

mdir -p cmake-build-release
$CMAKE -DCMAKE_BUILD_TYPE=Release -DCMAKE_MAKE_PROGRAM=$NINJA -G Ninja -S . -B cmake-build-release

$CMAKE --build cmake-build-release --target clean -j 4
$cmake --build cmake-build-release --target all -j 4
