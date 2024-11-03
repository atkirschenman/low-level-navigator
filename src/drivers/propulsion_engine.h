#pragma once
#include "pico/stdlib.h"

class PropulsionEngineClass {
  public:
    PropulsionEngineClass(float kp_init, float ki_init, float kd_init);
    ~PropulsionEngineClass();

    uint8_t setSpeed(uint16_t new_rpm);

  private:
    uint16_t controlLoop();

    uint16_t target_rpm;
    uint16_t current_rpm;
    float error_rpm;
    float prior_error;

    float integral_rpm;

    float kp;
    float ki;
    float kd;
};