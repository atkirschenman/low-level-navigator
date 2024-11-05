#include "propulsion_engine.h"
#include <algorithm>

        PropulsionEngineClass::PropulsionEngineClass(float kp_init, float ki_init, float kd_init):
        kp(kp_init), ki(ki_init), kd(kd_init)
        {

        }

        PropulsionEngineClass::~PropulsionEngineClass()
        {

        }

        uint8_t PropulsionEngineClass::setSpeed(uint16_t new_rpm)
        {
            if (new_rpm < 200)
            {
                target_rpm = new_rpm;
            }
        }

        uint16_t PropulsionEngineClass::controlLoop()
        {

            error_rpm = target_rpm - current_rpm;

            integral_rpm += error_rpm;
            float derivative = error_rpm - prior_error;
            uint16_t output = static_cast<unsigned int>(std::floor(kp * error_rpm + ki * integral_rpm + kd * derivative));

            output = std::max(0, std::min(output, 255));;
                    
            prior_error = error_rpm;
            return output;

        }