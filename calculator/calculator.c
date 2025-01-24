#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "TouchScreen.h"
#include "TFTMaster.h"

void calculator() {
    char buffer1[30];
    char buffer2[30];
    char buffer3[30];
    
    adc_init();
    //initialize screen
    tft_init_hw();
    tft_begin();
    tft_setRotation(3); 
    tft_fillScreen(ILI9340_BLACK);  

    
    // Display 7
    tft_setCursor(0,60);
    tft_fillRoundRect(0, 60, 80, 45, 10, ILI9340_BLUE);
    tft_drawRoundRect(0, 60, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(40,82.5);
    sprintf(buffer1, "%d", 7);
    tft_writeString(buffer1);


    //Display 8
    tft_setCursor(80,60);
    tft_fillRoundRect(80, 60, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(80, 60, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(120,82.5);
    sprintf(buffer1, "%d", 8);
    tft_writeString(buffer1);

    // Display 9
    tft_setCursor(160,60);
    tft_fillRoundRect(160, 60, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(160, 60, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(200,82.5);
    sprintf(buffer1, "%d", 9);
    tft_writeString(buffer1);

    // Display +
    tft_setCursor(240,60);
    tft_fillRoundRect(240, 60, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(240, 60, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(280,82.5);
    sprintf(buffer2, "%c", '+');
    tft_writeString(buffer2);

    //Display 4
    tft_setCursor(0,105);
    tft_fillRoundRect(0, 105, 80, 45, 10, ILI9340_BLUE );
     tft_drawRoundRect(0, 105, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(40,127.5);
    sprintf(buffer1, "%d", 4);
    tft_writeString(buffer1);


    //Display 5
    tft_setCursor(80,105);
    tft_fillRoundRect(80, 105, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(80, 105, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(120,127.5);
    sprintf(buffer1, "%d", 5);
    tft_writeString(buffer1);


    //Display 6
    tft_setCursor(160,105);
    tft_fillRoundRect(160, 105, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(160, 105, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(200,127.5);
    sprintf(buffer1, "%d", 6);
    tft_writeString(buffer1);

    //Display - 
    tft_setCursor(240,105);
    tft_fillRoundRect(240, 105, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(240, 105, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(280,127.5);
    sprintf(buffer1, "%c", '-');
    tft_writeString(buffer1);

    //Display 1
    tft_setCursor(0,150);
    tft_fillRoundRect(0, 150, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(0, 150, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(40,172.5);
    sprintf(buffer1, "%d", 1);
    tft_writeString(buffer1);

    //Display 2 
    tft_setCursor(80,150);
    tft_fillRoundRect(80, 150, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(80, 150, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(120,172.5);
    sprintf(buffer1, "%d", 2);
    tft_writeString(buffer1);


    //Display 3
    tft_setCursor(160,150);
    tft_fillRoundRect(160, 150, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(160, 150, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(200,172.5);
    sprintf(buffer1, "%d", 3);
    tft_writeString(buffer1);

    //Display X
    tft_setCursor(240,150);
    tft_fillRoundRect(240, 150, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(160, 150, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(280,172.5);
    sprintf(buffer1, "%s", "x");
    tft_writeString(buffer1);


    //Display 0
    tft_setCursor(0, 195);
    tft_fillRoundRect(0, 195, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(0, 195, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(40,217.5);
    sprintf(buffer1, "%d", 0);
    tft_writeString(buffer1);


   //Display C
    tft_setCursor(0, 195);
    tft_fillRoundRect(80, 195, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(80, 195, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(120,217.5);
    sprintf(buffer1, "%s", "C");
    tft_writeString(buffer1);

    //Display =
    tft_setCursor(0, 195);
    tft_fillRoundRect(160, 195, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(160, 195, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(200,217.5);
    sprintf(buffer1, "%c", '=');
    tft_writeString(buffer1);

    //Display /
    tft_setCursor(0, 195);
    tft_fillRoundRect(240, 195, 80, 45, 10, ILI9340_BLUE );
    tft_drawRoundRect(240, 195, 80, 45, 10, ILI9340_WHITE );
    tft_setTextSize(2);
    tft_setTextColor(ILI9340_WHITE);
    tft_setCursor(280,217.5);
    sprintf(buffer1, "%c", '/');
    tft_writeString(buffer1);

    }
