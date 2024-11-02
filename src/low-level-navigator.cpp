#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"



// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

void vTaskCode(void *pvParameters) {
    while (true) {
        printf("Hello from FreeRTOS Task!\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }
}


int main()
{
    stdio_init_all();

    xTaskCreate(vTaskCode, "Task1", 256, NULL, 1, NULL);
    vTaskStartScheduler(); // Start the scheduler

    while (true) {
        // Should never reach here
    }
}
