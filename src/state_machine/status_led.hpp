#pragma once

#include "StateMachineBase.hpp"
#include <cstdio> // For printf

class StatusLed : public StateMachineBase {
public:
    MyStateMachine();

private:
    // State methods
    void stateIdle();
    void stateProcessing();
    void stateError();
};

