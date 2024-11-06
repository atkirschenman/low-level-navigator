# Low Level Navigator

![build workflow](https://github.com/atkirschenman/low-level-navigator/actions/workflows/build.yml/badge.svg)

## To Build:

### Clone:

` git clone git@github.com:atkirschenman/low-level-navigator.git --recurse-submodule `

### Install Required packages (Ubuntu 22.04 or greater):

```
sudo apt install \
    cmake \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    build-essential \
    pkg-config \
    libusb-1.0-0-dev \
```

### Compile:

```
./scripts/build.sh
```

## LLN Architecture 

The LLN is a state machine, meaning that different operations are separated at the core of the software

### Pre-Calibration Idle

No commands
Zero speed
No valid calibration 

### Calibration

Going through calibration process

### Idle Navigation

valid calibration
No guidance commands

### Active Guidance

Actively receiving and executing guidance commands

### Exiting Guidance

No guidance commands recieved
Still executing commands
Bring system to 0
