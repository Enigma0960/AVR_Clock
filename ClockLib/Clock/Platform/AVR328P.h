#ifndef AVR328P_H_
#define AVR328P_H_

#include <avr/pgmspace.h>

#define SS		14
#define MOSI	15
#define MISO	16
#define SCK		17
#define SDA		22
#define SCL		23

const uint16_t PROGMEM portMode[] = {
	NOT_PORT,
	NOT_PORT,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,	
};

const uint16_t PROGMEM portOutput[] = {
	NOT_PORT,
	NOT_PORT,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM portInpute[] = {
	NOT_PORT,
	NOT_PORT,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digitalPinPort[] = {
	NOT_PIN,
	PC,
	PD,
	PD,
	PD,
	PD,
	PD,
	PB,
	PB,
	PD,
	PD,
	PD,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PC,
	PC,
	PC,
	PC,
	PC,
	PC,
};

const uint8_t PROGMEM digitalPinBitMask[] = {
	NOT_PIN,
	_BV(6),
	_BV(0),
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(6),
	_BV(7),
	_BV(5),
	_BV(6),
	_BV(7),
	_BV(0),
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
	_BV(0),
	_BV(1),
	_BV(2),
	_BV(3),
	_BV(4),
	_BV(5),
};

const uint8_t PROGMEM digitalPinToTimer[] = {
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER2B,
	NOT_ON_TIMER,
	TIMER0B,
	TIMER0A,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	TIMER1A,
	TIMER1B,
	TIMER2A,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
	NOT_ON_TIMER,
};

#endif