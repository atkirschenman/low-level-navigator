# Low Level Navigator

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

## LLN Archetecture 

The LLN is a state machine, meaning that different operations are separated at the core of the software

### Pre-calibration Idle

No commands
zero speed
No valid calibration 

### calibration

Going through calibration process

### idle navigation

valid calibration
No guidance commands

### active guidance

actively receiving and executing guidance commands

### exiting guidance

no guidance commands recieved
Still executing commands
Bring system to 0