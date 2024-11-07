#include <iostream>
#include "high_level_drivers/propulsion_engine.hpp"
#include "hardware_configurations/configuration_1.hpp"





int main() {
    stdio_init_all();

    //gpio_set_function(16, GPIO_FUNC_UART); //TX
    //gpio_set_function(17, GPIO_FUNC_UART); //RX
//hardware test
log_info("Hardware test starting");

    //Run motors forward

        //test encoders match direction 

        //test accelleration matches

    //stop motors

        //test encoders match 0 speed

        //test acceleration matches


    //repeat for backwards


    //repeat for rotate ccw + cw

//pre-cal idle




//calibration



//navigation idle



//live navigation



//debug override

    //set left/right rpm from debug console

    //command an acceleration vector from mcu?
    info()
    HardwareConfigType_1 hardware;
    std::cout << "Hardware Initialized\n";
    uint16_t current_rpm=0;
    //struct repeating_timer timer;
    //add_repeating_timer_ms(-50, repeating_timer_callback, NULL, &timer);
    PropulsionEngineClass prop_engine(32.0,0.0,0.0);
    std::cout << "Propulsion Initialized\n";
    uint16_t returnstat = hardware.left_hardware_start();
    std::cout << "left hardware started\n";
    std::cout << "Speed Set\n";
    while (1)
    {   
        
        uint32_t command_pwm = prop_engine.control_loop(current_rpm);
        current_rpm = hardware.get_left_rpm();
        hardware.set_left_pwm_output(command_pwm);
        std::cout << "RPM: " << current_rpm;
        std::cout << " Command: " << command_pwm << "\n";
        sleep_ms(100);
    }

    return 0;
}