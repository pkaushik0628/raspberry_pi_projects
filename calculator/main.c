#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TouchScreen.h"
#include "TFTMaster.h"
#include "calculator.h"
#include "fsm.h"
#include "debouncer.h"
#include "timer.h"


#define P1 100
#define P2 200

uint32_t t1,t2, t3, t4;
int main(){
calculator();
//timer_init();
stdio_init_all();
    t1 = t3 = timer_read();
    while (1) {
        t2 = t4 = timer_read();
        if (timer_elapsed_ms(t1,t2) >= P1) {
           debouncer();
           //operation();
            t1 = t2;
        }
        if (timer_elapsed_ms(t3,t4) >= P2) {
            //debouncer();
           operation();
            t3 = t4;
        }
    }
}