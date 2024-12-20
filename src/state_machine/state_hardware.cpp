#include "state_hardware.hpp"

// Constructor
HardwareState::HardwareState() : StateMachineBase(5) {
    // Add states to the state map
    addState(0, [this]() { stateIdle(); });
    addState(1, [this]() { stateProcessing(); });
    addState(2, [this]() { stateError(); });

    // Set the initial state
    setInitialState(0);

    // Start the state machine task
    start("MyStateMachineTask", 1024, 1);
}

// State: Idle
void StatusLed::stateIdle() {
    printf("State: Idle\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    // Transition to the next state
    transitionToState(1);
}

// State: Processing
void StatusLed::stateProcessing() {
    printf("State: Processing\n");
    vTaskDelay(pdMS_TO_TICKS(2000));
    // Transition to the next state
    transitionToState(2);
}

// State: Error
void StatusLed::stateError() {
    printf("State: Error\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
    // Transition back to idle
    transitionToState(0);
}
