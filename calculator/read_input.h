#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TouchScreen.h"
#include "TFTMaster.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"


int read_input(uint16_t x, uint16_t y);