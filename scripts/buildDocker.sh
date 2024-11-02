#! /bin/bash

docker build -t pico-freertos-dev .

echo $PWD

docker run -it --rm \
    -v $PWD:/low-level-navigator \
    pico-freertos-dev