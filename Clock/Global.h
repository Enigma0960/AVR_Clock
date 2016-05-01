#ifndef GLOBAL_H
#define GLOBAL_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define KEY_DOWN  0x01
#define KEY_UP    0x02
#define KEY_LEFT  0x03
#define KEY_RIGTH	0x04
#define KEY_OK    0x05


#define SHOW_CLOCK		0x01
#define SHOW_MENU		  0x02
#define SHOW_SET_DATE	0x03
#define SHOW_SET_TIME	0x04

extern volatile uint8_t GlobalEvent;
extern const char* dayofwks[];

#endif
