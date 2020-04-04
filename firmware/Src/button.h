#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "main.h"

//#define KEY_MASK 0b0000000000000011
#define KEY_MASK   (BUT_SELECT_Pin | BUT_CAL_Pin)

#define KEY_NULL      0   // no key pressed
#define KEY_CAL       1   // button CAL
#define KEY_SELECT    2   // button SELECT

#define KEY_STATE_0   0   // key state 0
#define KEY_STATE_1   1   // key state 1
#define KEY_STATE_2   2   // key state 2

#define TICKS_INTERVAL 10 // read key input every 10ms

uint8_t read_key(void);
char get_key(void);

#endif /* __BUTTON_H__ */

