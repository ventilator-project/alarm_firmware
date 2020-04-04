#include "button.h"
#include "main.h"

// global var
volatile char KEY = KEY_NULL;
volatile char KEY_VALID = FALSE;


/******************************************************************
 * key scan state machine
 *****************************************************************/
uint8_t read_key(void)
{
    static char key_state = 0;
    static uint16_t key_press;
    static uint16_t key_old;
    unsigned char key_return = KEY_NULL;

/*
    Read the buttons:
    Bit        15  14  13  12  11  10  9  8  7  6  5  4  3  2  1   0
    ------------------------------------------------------------------
    GPIOA                                                      SEL CAL
    ==================================================================
*/

    // read pushbutton's input level
    key_press =  GPIOA->IDR & KEY_MASK;

    switch (key_state)
    {
        case KEY_STATE_0:    // init state
            if (key_press != KEY_MASK) { // key pressed!
                key_state = KEY_STATE_1; // next time switch to STATE_1
                key_old = key_press;     // record the value
            }
            break;
        case KEY_STATE_1:    // now, to confirm
            if (key_press == key_old) // if not released
            {
                if (~key_press & BUT_CAL_Pin)
                    key_return = KEY_CAL;               // CAL
                else if (~key_press & BUT_SELECT_Pin)
                    key_return = KEY_SELECT;            // SELECT
                else
                    key_return = KEY_NULL;

                key_state = KEY_STATE_2;    // 
            }
            else
                key_state = KEY_STATE_0;    // bouncing/released, to init state

            break;
        case KEY_STATE_2:
            if (key_press == KEY_MASK)      // released, switch to init state
                key_state = KEY_STATE_0;

            break;
    }

    return key_return;
}


/*****************************************************************************
*
*   Function name : get_key
*
*   Returns :       The valid key
*
*   Parameters :    None
*
*   Purpose :       Get the valid key
*
*****************************************************************************/
char get_key(void)
{
    char k;

    if (KEY_VALID)              // Check for unread key in buffer
    {
        k = KEY;
        KEY_VALID = FALSE;
    }
    else
        k = KEY_NULL;           // No key stroke available

    return k;
}

