#include "configuration_1.hpp"
#include "hardware/pwm.h"
#include "configuration_defines.hpp"
#include "utility/logger.h"
#include <queue>
#include <cstring>



Logger logger("config_1.cpp");
static std::queue<uint32_t> left_irq_queue;
static std::queue<uint32_t> right_irq_queue;


uint16_t HardwareConfigType_1::left_hardware_start()
{
    logger.info("Initializing Left Encoder at pin: %d", config_defines::config_1::left_encoder_pin);
    gpio_init(config_defines::config_1::left_encoder_pin);
    gpio_set_dir(config_defines::config_1::left_encoder_pin, GPIO_IN);
    gpio_pull_up(config_defines::config_1::left_encoder_pin);
    gpio_set_irq_enabled_with_callback(config_defines::config_1::left_encoder_pin, GPIO_IRQ_EDGE_FALL, true, HardwareConfigType_1::left_encoder_interrupt);

    gpio_init(config_defines::config_1::left_forward_pin);
    gpio_set_dir(config_defines::config_1::left_forward_pin, GPIO_OUT);
    gpio_init(config_defines::config_1::left_backward_pin);
    gpio_set_dir(config_defines::config_1::left_backward_pin, GPIO_OUT);
    
    logger.info("Initializing Left PWM at pin: %d", config_defines::config_1::left_pwm_pin);
    gpio_set_function(config_defines::config_1::left_pwm_pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(config_defines::config_1::left_pwm_pin);
    pwm_set_clkdiv(slice_num, 125.f);  // Set the clock divider
    pwm_set_wrap(slice_num, 65535);    // Set the PWM period to maximum value (16-bit resolution)
    pwm_set_gpio_level(config_defines::config_1::left_pwm_pin, 0); // Set initial duty cycle
    pwm_set_enabled(slice_num, true);
    pwm_set_clkdiv(slice_num, 125.f * (float)1000 / config_defines::config_1::pwm_frequency);
    logger.info("Left Hardware Started", config_defines::config_1::left_pwm_pin);
    return 0;
}
uint16_t HardwareConfigType_1::right_hardware_start()
{
    logger.info("Initializing Right Encoder at pin: %d", config_defines::config_1::right_encoder_pin);
    gpio_init(config_defines::config_1::right_encoder_pin);
    gpio_set_dir(config_defines::config_1::right_encoder_pin, GPIO_IN);
    gpio_pull_up(config_defines::config_1::right_encoder_pin);
    gpio_set_irq_enabled_with_callback(config_defines::config_1::right_encoder_pin, GPIO_IRQ_EDGE_FALL, true, HardwareConfigType_1::right_encoder_interrupt);
    
    gpio_init(config_defines::config_1::right_forward_pin);
    gpio_set_dir(config_defines::config_1::right_forward_pin, GPIO_OUT);
    gpio_init(config_defines::config_1::right_backward_pin);
    gpio_set_dir(config_defines::config_1::right_backward_pin, GPIO_OUT);

    logger.info("Initializing Right PWM at pin: %d", config_defines::config_1::right_pwm_pin);
    gpio_set_function(config_defines::config_1::right_pwm_pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(config_defines::config_1::right_pwm_pin);
    pwm_set_clkdiv(slice_num, 125.f);  // Set the clock divider
    pwm_set_wrap(slice_num, 65535);    // Set the PWM period to maximum value (16-bit resolution)
    pwm_set_gpio_level(config_defines::config_1::right_pwm_pin, 0); // Set initial duty cycle
    pwm_set_enabled(slice_num, true);
    pwm_set_clkdiv(slice_num, 125.f * (float)1000 / config_defines::config_1::pwm_frequency);
    logger.info("Right Hardware Started", config_defines::config_1::right_pwm_pin);
    return 0;
}

uint16_t HardwareConfigType_1::init_other_gpio()
{
    gpio_init(config_defines::config_1::driver_enable_pin);
    gpio_set_dir(config_defines::config_1::driver_enable_pin, GPIO_OUT);
    return 0;
}

bool HardwareConfigType_1::set_motors_enabled(bool enabled)
{
    gpio_put(config_defines::config_1::driver_enable_pin, enabled);
}

uint16_t HardwareConfigType_1::get_left_rpm()
{
    int static index = 0;
    float readings[15];
    float time_recorded[15];
    uint32_t current_timing = time_us_32();

    //moves time measurements from queue -> vector
    while (!left_irq_queue.empty()) {
        std::memcpy(&readings[1], &readings[0], (13) * sizeof(float));
        readings[0] = left_irq_queue.front()/60000000.0;

        std::memcpy(&time_recorded[1], &time_recorded[0], (13) * sizeof(uint32_t));
        time_recorded[0] = current_timing;
        
        left_irq_queue.pop(); 
    }

    float times_summed = 0;
    uint8_t iter = 0;

    //averages time between 2 tick marks, up to 14 ticks, or 300ms, whichever comes first
    while(time_recorded[iter] + 300000 > current_timing  && iter <= 14)
    {
        times_summed += readings[iter];
        iter++;
    }
    
    if (iter == 0)
    {
        return 0;
    }

    float rpm = (static_cast<float>(iter)/config_defines::config_1::encoder_ticks) / (times_summed);

    return static_cast<unsigned int>(rpm);
}

uint16_t HardwareConfigType_1::get_right_rpm()
{
    int static index = 0;
    float readings[15];
    float time_recorded[15];
    uint32_t current_timing = time_us_32();

    //moves time measurements from queue -> vector
    while (!right_irq_queue.empty()) {
        std::memcpy(&readings[1], &readings[0], (13) * sizeof(float));
        readings[0] = right_irq_queue.front()/60000000.0;

        std::memcpy(&time_recorded[1], &time_recorded[0], (13) * sizeof(uint32_t));
        time_recorded[0] = current_timing;
        
        right_irq_queue.pop(); 
    }

    float times_summed = 0;
    uint8_t iter = 0;

    //averages time between 2 tick marks, up to 14 ticks, or 300ms, whichever comes first
    while(time_recorded[iter] + 300000 > current_timing  && iter <= 14)
    {
        times_summed += readings[iter];
        iter++;
    }
    
    if (iter == 0)
    {
        return 0;
    }

    float rpm = (static_cast<float>(iter)/config_defines::config_1::encoder_ticks) / (times_summed);

    return static_cast<unsigned int>(rpm);
}
void HardwareConfigType_1::set_left_pwm_output(uint16_t duty_cycle, bool forward, bool backward)
{
    pwm_set_gpio_level(config_defines::config_1::left_pwm_pin, duty_cycle);
    gpio_put(config_defines::config_1::left_forward_pin, forward);
    gpio_put(config_defines::config_1::left_backward_pin, backward);
}
void HardwareConfigType_1::set_right_pwm_output(uint16_t duty_cycle, bool forward, bool backward)
{
    pwm_set_gpio_level(config_defines::config_1::right_pwm_pin, duty_cycle);
        gpio_put(config_defines::config_1::right_forward_pin, forward);
    gpio_put(config_defines::config_1::right_backward_pin, backward);
}
void HardwareConfigType_1::left_encoder_interrupt(uint gpio, uint32_t event_mask)
{
    static uint32_t last_reading = 0;
    uint32_t current_reading = 0;
    current_reading = time_us_32();
    left_irq_queue.push(current_reading - last_reading);
    last_reading = current_reading;
}
void HardwareConfigType_1::right_encoder_interrupt(uint gpio, uint32_t event_mask)
{
    static uint32_t last_reading = 0;
    uint32_t current_reading = 0;
    current_reading = time_us_32();
    right_irq_queue.push(current_reading - last_reading);
    last_reading = current_reading;
}

