#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"

#define UART_ID uart0

#define LED_PIN 25
#define TEST 4


void blink_led() {
    gpio_put(LED_PIN, 1);
    sleep_ms(500);
    gpio_put(LED_PIN, 0);
    sleep_ms(500);
}



void test()
{
gpio_put(TEST,1);
}

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_init(TEST);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    while (1) {

        test();
        while (uart_is_readable(UART_ID)) {
            
            uint8_t received_data = uart_getc(UART_ID);
            printf("Received: %c\n", received_data);
            blink_led();
        }
    }

    return 0;
}
