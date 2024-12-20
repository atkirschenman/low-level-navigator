/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "high_level_drivers/state_machine_defines.hpp"
#include "utility/logger.h"
#include "hardware_drivers/configuration_1.hpp"



// Priorities of our threads - higher numbers are higher priority
//#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 2UL )
//#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1UL )

TaskHandle_t blink_handler;
TaskHandle_t state_machine_handler;
TaskHandle_t startup_handler;

// Stack sizes of our threads in words (4 bytes)
#define MIN_STACK_SIZE configMINIMAL_STACK_SIZE

void led_task(__unused void *params) {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

    bool flipper = 0;
    for(;;) {
        flipper =true;
        gpio_put(PICO_DEFAULT_LED_PIN, flipper);
        vTaskDelay(500);
        flipper =false;
        gpio_put(PICO_DEFAULT_LED_PIN, flipper);
        vTaskDelay(500);

    }
    
}

void sandbox_task(__unused void *params) {
    Logger logg("sandbox");
    for(;;) {
        
        logg.info("%u\t%u", hardware.get_left_rpm(), hardware.get_right_rpm())
        vTaskDelay(100);

    }
    
}

void start_up_task(__unused void *params) {

    enum class SUBTASKS
    {
        INITIALIZATION,
        ENCODER_TEST,
        SUSPEND
    };

    SUBTASKS test_step = SUBTASKS::INITIALIZATION;

    Logger logger("Startup Task");

    HardwareConfigType_1 hardware;

    for(;;)
    {
        switch (test_step)
        {
        case SUBTASKS::INITIALIZATION:
        {
            logger.info("Initializing hardware");
            uint16_t returnstat = hardware.init_other_gpio();
            returnstat += hardware.left_hardware_start();
            returnstat += hardware.right_hardware_start();

            if (returnstat == 0)
            {
                hardware.set_motors_enabled(true);
                logger.info("Hardware initialization successful");
                test_step = SUBTASKS::ENCODER_TEST;
            }
            else
            {
                logger.error("Hardware initialization errors");
                test_step = SUBTASKS::SUSPEND;
            }

            break;
        }
        case SUBTASKS::ENCODER_TEST:
        {
            logger.info("Starting Motion, stand clear!");
            vTaskDelay(3000);
            hardware.set_left_pwm_output(30000, true, false);
            hardware.set_right_pwm_output(30000, false, true);

            vTaskDelay(1000);
            uint16_t left_rpm = hardware.get_left_rpm();
            uint16_t right_rpm = hardware.get_right_rpm();
            if (left_rpm > 0 && right_rpm > 0)
            {
                logger.info("Encoders working: %u %u", left_rpm, right_rpm);
                hardware.set_left_pwm_output(0, false, false);
                hardware.set_right_pwm_output(0, false, false);
            }
            else
            {
                logger.info("Encoders failed startup test: %u %u", left_rpm, right_rpm);
                hardware.set_left_pwm_output(0, false, false);
                hardware.set_right_pwm_output(0, false, false);
                test_step = SUBTASKS::SUSPEND;
            }
        
            break;
        }
        case SUBTASKS::SUSPEND:
        {
            logger.info("Startup Task Completed");
            state_defines::STATE next_state = state_defines::STATE::SANDBOX_ACTIVE;
            xQueueSend(state_defines::state_change_queue, (void *)&next_state, 0);

            vTaskSuspend(NULL);

            break;
        }
        default:
            break;
        }
    }
}

void state_machine_manager(__unused void *params) 
{
    Logger logger("sm_manager");
    //xQueueSend(state_defines::state_change_queue, (void *)&next_state, 0);
     state_defines::request_queue = xQueueCreate(5, sizeof(state_defines::STATE));
      state_defines::register_queue = xQueueCreate(5, sizeof(TaskHandle_t));
    for (;;) 
    {
        // Wait for the next state to be sent to the queue
        if (xQueueReceive(state_defines::state_change_queue, &next_state, portMAX_DELAY) == pdPASS) 
        {
            // do any logic nessesary
            // Notify all tasks of change

            // wait for acks (with timeout, at which case change state to error)

            
            current_state = next_state;
        }
    }
}


void vLaunch( void) {
    Logger logger("task_launch");
    TaskHandle_t task;
    logger.info("Launching initial tasks");
    //xTaskCreate(led_task, "led_handle", MIN_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &blink_handler);
    xTaskCreate(state_machine_manager, "state_machine_manager", MIN_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2UL, &state_machine_handler);
   
    /* Start the tasks and timer running. */
    vTaskStartScheduler();
}

int main( void )
{
    stdio_init_all();

    vLaunch();

    return 0;
}