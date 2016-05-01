#pragma once
#ifndef __PINS_H__
#define __PINS_H__

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define HIGH 0x1
#define LOW  0x0

#define NOT_PORT 0
#define NOT_PIN 0


#define NOT_ON_TIMER 0
#define TIMER0A 1
#define TIMER0B 2
#define TIMER1A 3
#define TIMER1B 4
#define TIMER1C 5
#define TIMER2  6
#define TIMER2A 7
#define TIMER2B 8
#define TIMER3A 9
#define TIMER3B 10
#define TIMER3C 11
#define TIMER4A 12
#define TIMER4B 13
#define TIMER4C 14
#define TIMER4D 15
#define TIMER5A 16
#define TIMER5B 17
#define TIMER5C 18

#define PA 1
#define PB 2
#define PC 3
#define PD 4
#define PE 5
#define PF 6
#define PG 7
#define PH 8
#define PJ 9
#define PK 10
#define PL 11

#ifdef __AVR_ATmega328P__
#include "Platform/avr328p.h"
#endif

//extern const uint16_t PROGMEM portMode[];
//extern const uint16_t PROGMEM portOutput[];
//extern const uint16_t PROGMEM portInpute[];
//extern const uint8_t PROGMEM digitalPinPort[];
//extern const uint8_t PROGMEM digitalPinBitMask[];

#define getPinToPort(P) (pgm_read_byte(digitalPinPort + (P)))
#define getPinToBitMask(P) (pgm_read_byte(digitalPinBitMask + (P)))
#define getPinToTimer(P) ( pgm_read_byte( digitalPinToTimer + (P) ) )
#define getPortModeRegister(P) ((volatile uint8_t *)(pgm_read_word(portMode + (P))))
#define getPortInputRegister(P) ((volatile uint8_t *)(pgm_read_word(portInpute + (P))))
#define getPortOutputRegister(P) ((volatile uint8_t *)(pgm_read_word(portOutput + (P))))



//#ifdef __AVR_ATmega328P__
//#include "Platform/avr328p.h"
//#endif 

#endif