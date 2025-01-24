#include "TouchScreen.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "TFTMaster.h"
#include "ts_lcd.h"
#include "ts_lcd.h"

static char buffer[30];
static uint16_t x_buf, y_buf;


void test()
{
  uint16_t x, y;

  if (get_ts_lcd(&x, &y))
  { 
    
    tft_drawLine(x_buf-5, y_buf, x_buf+5, y_buf, ILI9340_BLACK);
    tft_drawLine(x_buf, y_buf-5, x_buf, y_buf+5, ILI9340_BLACK);
    x_buf = x;
    y_buf = y;
    tft_setCursor(20, 200);
    tft_setTextColor(ILI9340_BLACK);
    tft_writeString(buffer);
    tft_setCursor(20, 200);
    tft_setTextColor(ILI9340_WHITE);
    sprintf(buffer, "x: %d, y: %d", x, y);
    tft_writeString(buffer);
    tft_drawLine(x-5, y, x+5, y, ILI9340_WHITE);
    tft_drawLine(x, y-5, x, y+5, ILI9340_WHITE);
  }

}
