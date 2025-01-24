#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define UART_TX_PIN 0  
#define UART_RX_PIN 1 

// Motor control pins 
#define MOTOR_PIN1 9  
#define MOTOR_PIN2 10  
#define MOTOR_PIN3 11
#define MOTOR_PIN4 12 

void control_motor(char direction) {
    switch (direction) {
        case 'F':  // Forward
            gpio_put(MOTOR_PIN1, 1);
            gpio_put(MOTOR_PIN2, 0);
            gpio_put(MOTOR_PIN3, 1);
            gpio_put(MOTOR_PIN4, 0);
            printf("Forward");
            break;
        case 'B':  // Backward
            gpio_put(MOTOR_PIN1, 0);
            gpio_put(MOTOR_PIN2, 1);
            gpio_put(MOTOR_PIN3, 0);
            gpio_put(MOTOR_PIN4, 1);
            printf("Back");
            break;
        case 'L':  // Left
            gpio_put(MOTOR_PIN1, 0);
            gpio_put(MOTOR_PIN2, 1);
            gpio_put(MOTOR_PIN3, 1);
            gpio_put(MOTOR_PIN4, 0);
            printf("Left");
            break;
        case 'R':  // Right
            gpio_put(MOTOR_PIN1, 1);
            gpio_put(MOTOR_PIN2, 0);
            gpio_put(MOTOR_PIN3, 0);
            gpio_put(MOTOR_PIN4, 1);
            printf("Right");
            break;
        case 'S':  // Stop
            gpio_put(MOTOR_PIN1, 0);
            gpio_put(MOTOR_PIN2, 0);
            gpio_put(MOTOR_PIN3, 0);
            gpio_put(MOTOR_PIN4, 0);
            printf("Stop");
            break;
        default:
            printf("Invalid direction: %c\n", direction);
            break;
    }
}

int main() {
    stdio_init_all();

    // Initialize UART
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    
    // Configure motor control pins
    gpio_init(MOTOR_PIN1);
    gpio_init(MOTOR_PIN2);
    gpio_init(MOTOR_PIN3);
    gpio_init(MOTOR_PIN4);
    gpio_set_dir(MOTOR_PIN1, GPIO_OUT);
    gpio_set_dir(MOTOR_PIN2, GPIO_OUT);
    gpio_set_dir(MOTOR_PIN3, GPIO_OUT);
    gpio_set_dir(MOTOR_PIN4, GPIO_OUT);

    printf("Car control via UART. Press 'Q' to exit.\n");

    while (1) {
        char data = uart_getc(UART_ID);
        if (data == 'Q') {
            break;
        }
        printf("Received command: %c\n", data);
        control_motor(data);
    }

    return 0;
}



