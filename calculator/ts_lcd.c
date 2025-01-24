#include "ts_lcd.h"
#include "TouchScreen.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"



bool get_ts_lcd(uint16_t *px, uint16_t *py) {

struct TSPoint tpoint;

getPoint(&tpoint);

int x, y;

x = ((320)*(tpoint.y - 3600))/(700-3600);
y = ((240)*(tpoint.x - 790))/(3500-500);

*px = x;
*py = y;


if((tpoint.z<1400)){
    printf("pressed \n");
    return true;
}
else{  
    return false;
}

}



void ts_lcd_init()
{
//leave blank
}