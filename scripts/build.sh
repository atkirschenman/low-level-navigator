#! /bin/bash

if [ -d "build" ]; then
    # Directory exists
    echo "build already exists"
else
    # Directory does not exist
    mkdir build
fi
cd build
cmake ..
make