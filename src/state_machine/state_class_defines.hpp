#pragma once
#include "pico/stdlib.h"
#include "queue"

namespace state_defines
{
    enum class STATE{
        STARTUP,
        PRECAL_IDLE,
        NAV_IDLE,
        CALIBRATION_ACTIVE,
        NAVIGATION_ACTIVE,
        SANDBOX_ACTIVE
    };

    QueueHandle_t register_queue; 
    QueueHandle_t request_queue; 
}
