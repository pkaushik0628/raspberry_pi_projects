
#include "fsm.h"
#include "hardware/gpio.h"
#include "read_input.h"
#include "TFTMaster.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "ts_lcd.h"
#include "getButtonPressed.h"
#include "arrayClear.h"
#include "fsm.h"
#include "debouncer.h"
#define ADD 10
#define SUB 11
#define MLT 12
#define DIV 13
#define EQL 14
#define CLR 15
#define NTH 16
uint16_t px;
uint16_t py;
static int screenvalue;
static bool pressed;
static int operatorcount;
int screenvalue_out;
static bool scr_pressed;

int get_screenvalue()
{

    screenvalue_out = screenvalue;
    return screenvalue_out;
}

void debouncer()
{
    static enum DB_States { NOPUSH,
                            MAYBEPUSH,
                            PUSHED,
                            MAYBENOPUSH } DB_State;

    switch (DB_State)
    {
    case NOPUSH:
        printf("No PUSH");
        printf("%d", screenvalue_out);
        screenvalue = NTH;
        get_screenvalue();
        pressed = get_ts_lcd(&px, &py);
        if (pressed)
        {
            DB_State = MAYBEPUSH;
        }
        else
            DB_State = NOPUSH;

        break;
    case MAYBEPUSH:
        printf("MAYBE PUSH");
        screenvalue = NTH;
        get_screenvalue();
        pressed = get_ts_lcd(&px, &py);
        if (pressed)
        {
            // screenvalue = read_input(px, py);
            DB_State = PUSHED;
            scr_pressed = true;
            // pressed = !pressed;
        }
        else
            DB_State = NOPUSH;

        printf("%d", screenvalue_out);

        break;
    case PUSHED:
        printf(" PUSHED");
        pressed = get_ts_lcd(&px, &py);
        if (pressed)
        {
            screenvalue = read_input(px, py);
            DB_State = PUSHED;
            // pressed = !pressed;
            get_screenvalue();
        }
        else
            DB_State = MAYBENOPUSH;

        printf("%d", screenvalue_out);

        break;

    case MAYBENOPUSH:
        printf(" MAY BE No PUSHED");
        screenvalue = NTH;
        get_screenvalue();
        pressed = get_ts_lcd(&px, &py);
        if (pressed)
        {
            // screenvalue = read_input(px, py);
            DB_State = PUSHED;
            // pressed = !pressed;
        }
        else
            DB_State = NOPUSH;

        printf("%d", screenvalue_out);

        break;
    default:
        DB_State = NOPUSH;
        break;
    }
}

bool debounce_pressed()
{
    if (scr_pressed)
    {
        pressed = false;
        return screenvalue_out;
    }
    else
        return false;
}

// static enum DEBOUNCE_STATE {

//     STATE1,
//     STATE2,

// } DEBOUNCE_STATE;

// switch (DEBOUNCE_STATE)
// {
// case STATE1:

//     pressed = get_ts_lcd(&px, &py);
//     if (pressed)
//     {
//         screenvalue = read_input(px, py);

//         if (screenvalue >= ADD && screenvalue <= DIV)
//         {
//             operatorcount++;
//         }
//         screenvalue_out = NTH;
//         DEBOUNCE_STATE = STATE2;
//     }
//     else
//     {
//         screenvalue = read_input(px, py);
//         DEBOUNCE_STATE = STATE1;
//     }
//     break;

// case STATE2:
//     pressed = get_ts_lcd(&px, &py);
//     if (!pressed)
//     {

//         DEBOUNCE_STATE = STATE1;
//     }
//     else
//     {
//         screenvalue = read_input(px, py);
//         DEBOUNCE_STATE = STATE2;
//     }
//     break;
// }

// switch (DEBOUNCE_STATE)
// {

// case STATE1:

//     printf("State1");

//     screenvalue = 16;

//     printf("%d", screenvalue);

//     break;

// case STATE2:

//     if (operatorcount > 1)
//     {
//         printf("Screenvalue is \n");
//         printf("%d", screenvalue);
//         screenvalue_out = NTH;
//         printf("Screen value is NTH");
//     }
//     else
//     {
//         screenvalue_out = screenvalue;
//         printf("The screenvalue_out is");
//         printf("%d\n", screenvalue_out);
//         operatorcount = 0;
//     }

//     break;
// }
// }