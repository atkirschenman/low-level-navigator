#! /bin/bash


if [ ! -d build ]; then
  mkdir build;
fi

cd build

cmake -DPICO_BOARD=pico2  ..

make