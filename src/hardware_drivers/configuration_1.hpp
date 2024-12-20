#pragma once
#include "pico/stdlib.h"
/*
    -This configuration is designed for 2 independent driven wheels
    -2 wheels are fixed and all other contacts to the ground must allow omni-directional movement
    -Allows vehicle to turn on a dime
    -Requires steering engine to manipulate propulsion
    -code duplication required, as hardware does not work well in OOP (despite how easy it is to represent in OOP)
*/


class HardwareConfigType_1
{
    public:

        uint16_t left_hardware_start();
        uint16_t right_hardware_start();
        uint16_t get_left_rpm();
        uint16_t get_right_rpm();
        void set_left_pwm_output(uint16_t duty_cycle, bool forward, bool backward);
        void set_right_pwm_output(uint16_t duty_cycle, bool forward, bool backward);
        uint16_t init_other_gpio();
        bool set_motors_enabled(bool enabled);

    private:
        void static left_encoder_interrupt(uint gpio, uint32_t event_mask);
        void static right_encoder_interrupt(uint gpio, uint32_t event_mask);


};
