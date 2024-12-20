#ifndef STATE_MACHINE_BASE_HPP
#define STATE_MACHINE_BASE_HPP

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <functional>
#include <map>

#include "state_machine_defines.hpp"

class StateMachineBase {
protected:
    using StateFunction = std::function<void()>;

    // Queue to handle state transitions
    QueueHandle_t stateQueue;

    // Map to store state functions
    std::map<state_defines::STATE, StateFunction> stateMap;

    // Current state
    state_defines::STATE currentState;

    // Task handle for the state machine task
    TaskHandle_t taskHandle;

public:
    StateMachineBase(size_t queueLength = 10);
    virtual ~StateMachineBase();

    // Add a state to the state map
    void add_state(state_defines::STATE stateId, StateFunction stateFunc);

    // Set the initial state
    void set_initial_state(state_defines::STATE stateId);

    // Transition to a new state
    void transisition_to_state(state_defines::STATE newState);

protected:
    // Start the state machine task
    void start(const char *taskName, uint16_t stackDepth, UBaseType_t priority);

private:
    // Task function for the state machine
    static void task_function(void *param);
};

#endif // STATE_MACHINE_BASE_HPP
