#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TouchScreen.h"
#include "TFTMaster.h"


bool getButtonPressed()
{
struct TSPoint tpoint;

getPoint(&tpoint);

if((tpoint.z<400)){

    return true;
}
else if (tpoint.z>400){
    return false;
}
}

