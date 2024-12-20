#include "StateMachineBase.hpp"
#include <cstdio>

// Constructor
StateMachineBase::StateMachineBase(size_t queueLength)
    : currentState(0), taskHandle(nullptr) {
    stateQueue = xQueueCreate(queueLength, sizeof(int));
    if (stateQueue == nullptr) {
        // Handle queue creation failure
        configASSERT(false);
    }
}

// Destructor
StateMachineBase::~StateMachineBase() {
    if (stateQueue) {
        vQueueDelete(stateQueue);
    }
    if (taskHandle) {
        vTaskDelete(taskHandle);
    }
}

// Add a state to the state map
void StateMachineBase::add_state(state_defines::STATE stateId, StateFunction stateFunc) {
    stateMap[stateId] = stateFunc;
}

// Set the initial state
void StateMachineBase::set_initial_state(state_defines::STATE stateId) {
    currentState = stateId;
}

// Transition to a new state
void StateMachineBase::transisition_to_state(state_defines::STATE newState) {
    xQueueSend(request_queue, &newState, portMAX_DELAY);
}

void StateMachineBase::register_with_state_manager(TaskHandle_t task) {
    xQueueSend(register_queue, &newState, portMAX_DELAY);
}

// Start the state machine task
void StateMachineBase::start(const char *taskName, uint16_t stackDepth, UBaseType_t priority) {
    xTaskCreate(taskFunction, taskName, stackDepth, this, priority, &taskHandle);
}

// Task function for the state machine
void StateMachineBase::task_function(void *param) {
    StateMachineBase *self = static_cast<StateMachineBase *>(param);
    state_defines::STATE nextState;

    while (true) {
        // Wait for a state transition
        if (xQueueReceive(self->stateQueue, &nextState, portMAX_DELAY) == pdPASS) {
            self->currentState = nextState;
            auto it = self->stateMap.find(nextState);
            if (it != self->stateMap.end()) {
                // Execute the state function
                it->second();
            }
        }
    }
}
