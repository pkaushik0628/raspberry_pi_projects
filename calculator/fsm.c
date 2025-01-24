#include "fsm.h"
#include "hardware/gpio.h"
#include "read_input.h"
#include "TFTMaster.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "ts_lcd.h"
#include "getButtonPressed.h"
#include "arrayClear.h"
#include "debouncer.h"

int result;
bool pressed;

int number1 = 0;
int number2 = 0;
char num_1[30];
int number_add;
char num_2[30];
char result1[30];
char initial_buf[30];
int opreatorPressed = 0;
static int screenvalue;
static int operatorcount;
extern int screenvalue_out;
static int stored_value;
static int screenvalue_out_1;
// extern int get_screenvalue();
static int stored_value_1;
static int stored_value_2;
static bool screenPressed;
static int at_least_one_digit_pressed;

#define ADD 10
#define SUB 11
#define MLT 12
#define DIV 13
#define EQL 14
#define CLR 15

extern uint16_t px;
extern uint16_t py;

void operation()
{
    static int operator;

    static enum FSM_STATES {
        INITIAL,
        DIGIT1,
        DIGIT2,
        RESULT
    } FSM_STATE;

    static int input_sense;

    // stored_value = screenvalue_out;
    screenPressed = debounce_pressed();

    switch (FSM_STATE)

    {

    case INITIAL:
        printf("Initial \n");
        stored_value = screenvalue_out;

        printf("%d\n", stored_value);
        if ((screenPressed) && (stored_value >= 0 && stored_value <= 9))
        {

            // printf("True \n");
            FSM_STATE = DIGIT1;
            stored_value_1 = stored_value;
            printf(" input sense = %d \n", stored_value_1);
        }

        else
        {
            FSM_STATE = INITIAL;
        }

        break;

    case DIGIT1:

        printf("DIGIT1 \n");
        stored_value = screenvalue_out;

        if ((screenPressed) && (stored_value >= 0 && stored_value <= 15))
        {
            // If an operator is pressed, it goes to digit 2
            if (stored_value >= ADD && stored_value <= DIV) // 10 t0 13 are values for operator
            {
                FSM_STATE = DIGIT2;
                operator= stored_value;

                // printf("%d", operator);
                // printf("%d", operator);
            }
            else if (stored_value == 14)
            {
                FSM_STATE = RESULT;
            }
            else if (stored_value >= 0 && stored_value <= 9)
            {
                FSM_STATE = DIGIT1;
                stored_value_1 = stored_value;
                operatorcount = 0;
            }
            else if (stored_value == CLR)
            {
                result = 0;
                number1 = 0;
                number2 = 0;
                FSM_STATE = INITIAL;
                operatorcount = 0;
            }
            else
            {
                FSM_STATE = DIGIT1;
            }
        }
        else
        {
            FSM_STATE = DIGIT1;
        }

        break;

    case DIGIT2:

        printf("Digit2 Entered \n");
        stored_value = screenvalue_out;
        if ((screenPressed) && (stored_value >= 0 && stored_value <= 15))
        {
            // If an operator is pressed, it goes to digit 2
            if ((stored_value >= 10 && stored_value <= 13) && (at_least_one_digit_pressed >= 1))
            {
                FSM_STATE = RESULT;
                operator= stored_value;
            }
            else if (stored_value == EQL)
            {
                FSM_STATE = RESULT;
            }
            else if (stored_value == CLR)
            {
                result = 0;
                number1 = 0;
                number2 = 0;
                FSM_STATE = INITIAL;
                operatorcount = 0;
            }
            else if (stored_value >= 0 && stored_value <= 9)
            {
                FSM_STATE = DIGIT2;
                stored_value_2 = stored_value;
                at_least_one_digit_pressed++;
            }
            else
            {
                FSM_STATE = DIGIT2;
                operatorcount = 0;
            }
        }
        else
        {
            FSM_STATE = DIGIT2;
            stored_value_2 = stored_value;
        }

        break;

    case RESULT:

        printf("Result State Entered \n");
        stored_value = screenvalue_out;

        if ((screenPressed) && (stored_value >= 0 && stored_value <= 15))
        {
            printf("input_sense=%d\n", stored_value);

            if (stored_value == CLR)
            {
                result = 0;
                number1 = 0;
                number2 = 0;
                opreatorPressed = 0;
                // sprintf(num_1, "%d", 0);
                // sprintf(num_2, "%d", 0);
                // sprintf(result1, "%d", 0);
                FSM_STATE = INITIAL;
            }
            else if (stored_value >= ADD && stored_value <= DIV)
            {
                FSM_STATE = DIGIT2;
                number1 = result;
                number2 = 0;
                operator= stored_value;
                opreatorPressed = 1;
            }
            else
            {
                FSM_STATE = RESULT;
            }
        }

        break;

    default:
        FSM_STATE = INITIAL;
        break;
    }

    switch (FSM_STATE)
    {

    case INITIAL:

        opreatorPressed = 0;
        // erase old result
        tft_setTextColor(ILI9340_BLACK);
        tft_setCursor(20, 24);
        tft_setTextSize(2);
        tft_writeString(result1);
        tft_setCursor(20, 24);
        tft_setTextSize(2);
        tft_writeString(num_1);
        tft_setCursor(20, 24);
        tft_setTextSize(2);
        tft_writeString(num_2);
        // reset all arrays

        arrayClear(num_1);
        arrayClear(num_2);
        arrayClear(result1);
        // sprintf(num_1, "%d", 0);
        // sprintf(num_2, "%d", 0);
        // sprintf(result1, "%d", 0);
        //  display 0
        tft_setTextColor(ILI9340_WHITE);
        tft_setCursor(20, 24);
        tft_setTextSize(2);
        sprintf(initial_buf, "%d", 0);
        tft_writeString(initial_buf);
        // printf("Test");
        break;

    case DIGIT1:

        if (!(stored_value_1 >= 0 && stored_value_1 <= 15))
        {
            printf("no digit pressed");
        }
        else if ((stored_value_1 >= 0 && stored_value_1 <= 15) && (stored_value_1 >= 0 && stored_value_1 <= 9))
        {
            // Erase old stuff
            tft_setTextColor(ILI9340_BLACK);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            // sprintf(num_1);
            // Sense the inputs
            tft_writeString(initial_buf);
            // printf("Erased");
            number_add = stored_value_1;
            // Display the number
            tft_setTextColor(ILI9340_WHITE);
            tft_setCursor(20, 24);
            tft_setTextSize(2);

            number1 = ((number1) * 10 + number_add);
            sprintf(num_1, "%d", number1);
            tft_writeString(num_1);
            result = number1;
            stored_value_1 = 16;
            at_least_one_digit_pressed = 0;
        }

        else

        {
        }
        break;

    case DIGIT2:

        printf("%d\n\n", stored_value_2);

        if (!(stored_value_2 >= 0 && stored_value_2 <= 15))
        {

            printf("no digit pressed");
        }
        else if ((at_least_one_digit_pressed >= 1) && (stored_value_2 >= 0 && stored_value_2 <= 9))
        {
            // Erase old stuff
            tft_setTextColor(ILI9340_BLACK);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            // sprintf(num_1);
            // Sense the inputs
            tft_writeString(result1);
            tft_setCursor(20, 24);
            tft_writeString(num_1);
            tft_setCursor(20, 24);
            tft_writeString(num_2);
            tft_setCursor(20, 24);
            tft_writeString(result1);
            printf("Erased");
            number_add = stored_value_2;
            // number_add = read_input(px,py) ;
            //  Display the number
            tft_setTextColor(ILI9340_WHITE);
            tft_setCursor(20, 24);
            tft_setTextSize(2);

            number2 = ((number2) * 10 + number_add);
            sprintf(num_2, "%d", number2);
            tft_writeString(num_2);
            result = number2;
            at_least_one_digit_pressed = 0;
        }

        else
        {
        }

        break;

    case RESULT:

        printf("Actual Result State");
        printf("%d \n", operator);

        if (operator== ADD)
        {
            printf("addition result\n");
            tft_setTextColor(ILI9340_BLACK);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            tft_writeString(num_2);
            result = number1 + number2;
            printf("%d", result);
            // display result
            sprintf(result1, "%d", result);
            tft_setTextColor(ILI9340_WHITE);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            tft_writeString(result1);
            operatorcount = 0;
        }

        else if (operator== SUB)
        {
            printf("Subraction result\n");
            tft_setTextColor(ILI9340_BLACK);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            tft_writeString(num_2);
            result = number1 - number2;
            // display result
            sprintf(result1, "%d", result);
            tft_setTextColor(ILI9340_WHITE);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            tft_writeString(result1);
            operatorcount = 0;
        }

        else if (operator== MLT)
        {
            printf("Multiplication result\n");
            tft_setTextColor(ILI9340_BLACK);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            tft_writeString(num_2);
            result = number1 * number2;
            // display result
            sprintf(result1, "%d", result);
            tft_setTextColor(ILI9340_WHITE);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            tft_writeString(result1);
            operatorcount = 0;
        }

        else if (operator== DIV)
        {
            printf("Divison result\n");
            tft_setTextColor(ILI9340_BLACK);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            tft_writeString(num_2);
            result = number1 / number2;
            // display result
            sprintf(result1, "%d", result);
            tft_setTextColor(ILI9340_WHITE);
            tft_setCursor(20, 24);
            tft_setTextSize(2);
            tft_writeString(result1);
            operatorcount = 0;
        }
        else
        {
            printf("else");
        }
        opreatorPressed = 0;
        break;
    }
}