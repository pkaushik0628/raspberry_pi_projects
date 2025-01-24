#include "pico/stdlib.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "sw_in.h"
#include "debounce_sw1.h"
#include "debounce_sw2.h"
#include "timer.h"
#include "led_out.h"

// set the win logic

uint32_t PONGPERIOD = 300;

static enum FSM_States {
    initial,
    SERVE1,
    serve2,
    ERROR1,
    ERROR2,
    ERROR3,
    ERROR4,
    ERROR5,
    ERROR6,
    L1,
    L2,
    L3,
    L4,
    L5,
    L6,
    L7,
    L8
} FSM_State;

// static void btn_presed = read from he button
void PlayPong_Tick()
{
    bool btn_pressed1, btn_pressed2;
    btn_pressed1 = debounce_sw1_pressed();
    btn_pressed2 = debounce_sw2_pressed();

    static bool serve1;
    static bool dir_right;
    static bool win; // left is using 0 and right is using 1 for winning case

    switch (FSM_State)
    {

    case initial:
        printf("INITIAL");
        FSM_State = SERVE1;
        serve1 = true;
        break;

    case SERVE1:
        printf("SERVE1");
        if (btn_pressed1)
        {
            FSM_State = L1;
            printf("!btnp");
        }
        else if (!serve1 && !btn_pressed1)
        {
            FSM_State = SERVE1;
        }
        else if (!serve1 && btn_pressed1)
        {
            FSM_State = L1;
        }
        else
        {
            FSM_State = SERVE1;
        }
        dir_right = true;
        serve1 = true;
        break;

    case L1:
        printf("L1");
        if (dir_right && serve1)
        {
            FSM_State = L2;
            serve1 = false;
        }
        else if (btn_pressed1 && dir_right && !serve1)

        {
            FSM_State = L2;
            if (PONGPERIOD >= 105)
            {
                PONGPERIOD = PONGPERIOD - 5;
            }
        }
        else if (!btn_pressed1 && !serve1)
        {
            FSM_State = ERROR1;
            win = 1;
        }
        else if (!btn_pressed1 && serve1)
        {
            FSM_State = L1;
        }
        else
        {
            FSM_State = L1;
        }
        break;

    case L2:
        printf("L2");

        if (dir_right && !btn_pressed2)
        {
            FSM_State = L3;
            dir_right = 1;
        }
        else if (dir_right && btn_pressed2)
        {
            FSM_State = ERROR1;
            win = 0;
        }

        else if (!dir_right && !btn_pressed1)
        {
            FSM_State = L1;
            dir_right = 1;
        }
        else if (!dir_right && btn_pressed1)
        {
            FSM_State = ERROR1;
            win = 1;
        }
        break;

    case L3:
        printf("L3");

        if (dir_right && !btn_pressed2)
        {
            FSM_State = L4;
            dir_right = 1;
        }
        else if (dir_right && btn_pressed2)
        {
            FSM_State = ERROR1;
            win = 0;
        }
        else if (!dir_right && !btn_pressed1)
        {
            FSM_State = L2;
            dir_right = 0;
        }
        else if (!dir_right && btn_pressed1)
        {
            FSM_State = ERROR1;
            win = 1;
        }
        break;

    case L4:
        printf("L4");

        if (dir_right && !btn_pressed2)
        {
            FSM_State = L5;
            dir_right = 1;
        }
        else if (dir_right && btn_pressed2)
        {
            FSM_State = ERROR1;
            win = 0;
        }
        else if (!dir_right && !btn_pressed1)
        {
            FSM_State = L3;
            dir_right = 0;
        }
        else if (!dir_right && btn_pressed1)
        {
            FSM_State = ERROR1;
            win = 1;
        }
        break;

    case L5:
        printf("L5");
        if (dir_right && !btn_pressed2)
        {
            FSM_State = L6;
            dir_right = 1;
        }
        else if (dir_right && btn_pressed2)
        {
            FSM_State = ERROR1;
            win = 0;
        }
        else if (!dir_right && !btn_pressed1)
        {
            FSM_State = L4;
            dir_right = 0;
        }
        else if (!dir_right && btn_pressed1)
        {
            FSM_State = ERROR1;
            win = 1;
        }
        break;

    case L6:
        printf("L6");

        if (dir_right && !btn_pressed2)
        {
            FSM_State = L7;
            dir_right = 1;
        }
        else if (dir_right && btn_pressed2)
        {
            FSM_State = ERROR1;
            win = 0;
        }
        else if (!dir_right && !btn_pressed1)
        {
            FSM_State = L5;
            dir_right = 0;
        }
        else if (!dir_right && btn_pressed1)
        {
            FSM_State = ERROR1;
            win = 1;
        }
        break;

    case L7:
        printf("L7");

        if (dir_right && !btn_pressed2)
        {
            FSM_State = L8;
            dir_right = 0;
        }
        else if (dir_right && btn_pressed2)
        {
            FSM_State = ERROR1;
            win = 0;
        }
        else if (!dir_right && !btn_pressed1)
        {
            FSM_State = L5;
            dir_right = 0;
        }
        else if (!dir_right && btn_pressed1)
        {
            FSM_State = ERROR1;
            win = 1;
        }
        break;

    case L8:
        printf("L8");
        if (!btn_pressed2)
        {
            FSM_State = ERROR1;
            win = 0;
        }
        else if (btn_pressed2 && !dir_right)
        {
            FSM_State = L7;
            if (PONGPERIOD >= 105)
            {
                PONGPERIOD = PONGPERIOD - 5;
            }
        }
        break;

    case ERROR1:
        printf("ERROR1");
        FSM_State = ERROR2;
        break;

    case ERROR2:
        printf("ERROR2");
        FSM_State = ERROR3;
        break;

    case ERROR3:
        printf("ERROR3");
        FSM_State = ERROR4;
        break;

    case ERROR4:
        printf("ERROR4");
        FSM_State = ERROR5;
        break;

    case ERROR5:
        printf("ERROR5");
        FSM_State = ERROR6;
        break;

    case ERROR6:
        printf("ERROR6");
        FSM_State = SERVE1;
        break;
    }

    switch (FSM_State)
    {
    case initial:
        break;

    case SERVE1:
        led_out_write(0b10000000);
        break;

    case L1:
        led_out_write(0b10000000);
        break;

    case L2:
        led_out_write(0b01000000);
        break;

    case L3:
        led_out_write(0b00100000);
        break;

    case L4:
        led_out_write(0b00010000);
        break;

    case L5:
        led_out_write(0b00001000);
        break;

    case L6:
        led_out_write(0b00000100);
        break;

    case L7:
        led_out_write(0b00000010);
        break;

    case L8:
        led_out_write(0b00000001);
        break;

    case ERROR1:
        if (win)
        {

            led_out_write(0b00000001);
            printf("Left Player Won.");
        }
        else
        {
            led_out_write(0b10000000);
            printf("Right Player Won");
        }
        break;

    case ERROR2:
        led_out_write(0b00000000);
        break;

    case ERROR3:
        if (win)
        {

            led_out_write(0b00000001);
             printf("Left Player Won.");
        }
        else
        {
            led_out_write(0b10000000);
            printf("Right Player Won");
        }
        break;

    case ERROR4:
        led_out_write(0b00000000);
        break;

    case ERROR5:

        if (win)
        {
            led_out_write(0b00000001);
             printf("Left Player Won.");
        }
        else
        {
            led_out_write(0b10000000);
            printf("Right Player Won");
        }
        break;

    case ERROR6:
        led_out_write(0b00000000);
        break;
    }
}

void main()
{
    uint32_t t1, t2, t1_debouncer, t2_debouncer;
    stdio_init_all();
    printf("Hello!\n");
    sw_in_init();
    led_out_init();
    bool led_state = true;
    static int DEBOUNCEPERIOD = 50;

    t1 = timer_read();
    t1_debouncer = timer_read();

    while (1)
    {

        t2 = timer_read();
        t2_debouncer = timer_read();

        if (timer_elapsed_ms(t1_debouncer, t2_debouncer) > DEBOUNCEPERIOD)
        {
            debounce_sw1_tick();
            debounce_sw2_tick();
            t1_debouncer = t2_debouncer;
        }

        if (timer_elapsed_ms(t1, t2) > PONGPERIOD)
        {
            PlayPong_Tick();
            t1 = t2;
        }

        // if (debounce_sw1_pressed())
        // {
        //     printf("+");
        //     PlayPong_Tick();
        // }

        // if (debounce_sw2_pressed())
        // {
        //     printf("+");
        //     PlayPong_Tick();
        // }
    }
}