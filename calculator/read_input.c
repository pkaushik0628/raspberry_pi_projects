

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TFTMaster.h"
#include "ts_lcd.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"

int read_input(uint16_t x, uint16_t y)
{
    
       

        if ((x > 0 && x < 80) && y > 60 && y < 105)
        {
            return 7;
        }
        else if ((x > 80 && x < 160) && y > 60 && y < 105)
        {
            return 8;
        }
        else if ((x > 160 && x < 240) && y > 60 && y < 105)
        {
            return 9;
        }
        else if ((x > 240 && x < 320) && y> 60 && y < 105)
        {
            return 10;
        }
        else if ((x > 0 && x < 80) && y > 105 && y < 150)
        {
            return 4;
        }
        else if ((x > 80 && x < 160) && y > 105 && y < 150)
        {
            return 5;
        }
        else if ((x > 160 && x < 240) && y > 105 && y < 150)
        {
            return 6;
        }
        else if ((x > 240 && x < 320) && y > 105 && y < 150)
        {
            return 11; // 11 set to sub
        }

        else if ((x > 0 && x < 80) && y > 150 && y < 195)
        {
            return 1;
        }
        else if ((x > 80 && x < 160) && y > 150 && y < 195)
        {
            return 2;
        }
        else if ((x > 160 && x < 240) && y > 150 && y < 195)
        {
            return 3;
        }
        else if ((x > 240 && x < 320) && y > 150 && y < 195)
        {
            return 12; // 12 set to x
        }

        else if ((x > 0 && x < 80) && y > 195 && y < 240)
        {
            return 0;
        }
        else if ((x > 80 && x < 160) && y > 195 && y < 240)
        {
            return 15; // clear is set to 15
        }
        else if ((x > 160 && x < 240) && y > 195 && y < 240)
        {
            return 14; // = is set to 14
        }
        else if ((x > 240 && x < 320) && y > 195 && y < 240)
        {
            return 13; // 13 is set to divide
        }
        else{
            return 0;
        }
    }

