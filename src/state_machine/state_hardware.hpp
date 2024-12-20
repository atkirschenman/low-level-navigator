#pragma once

#include "state_class.hpp"
#include <cstdio> // For printf

class HardwareState : public StateMachineBase {
public:
    HardwareState();

private:
    // State methods
    void stateIdle();
    void stateProcessing();
    void stateError();
};

