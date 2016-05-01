#include "IO.h"
#include "Pins.h"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void pinMode(uint8_t pin, uint8_t mode) {
	uint8_t bit = getPinToBitMask(pin);
	uint8_t port = getPinToPort(pin);
	volatile uint8_t *reg, *out;
	
	if (port == NOT_PORT) return;
	
	reg = getPortModeRegister(port);
	out = getPortOutputRegister(port);
	
	if(mode == INPUT) {
		uint8_t oldSREG = SREG;
		cli();
		*reg &= ~bit;
		*out &= ~bit;
		SREG = oldSREG;
	} else {
		uint8_t oldSREG = SREG;
		cli();
		*reg |= bit;
		SREG = oldSREG;
	}
};

uint8_t digitalInput(uint8_t pin) {
	uint8_t timer = getPinToTimer(pin);
	uint8_t bit = getPinToBitMask(pin);
	uint8_t port = getPinToPort(pin);
	
	if(port == NOT_PORT) return LOW;
	
	if (timer != NOT_ON_TIMER) turnOffPWM(timer);
	
	if(*getPortInputRegister(port)&bit) return HIGH;
	return LOW;
}

void digitalOutput(uint8_t pin, uint8_t val) {
	uint8_t timer = getPinToTimer(pin);
	uint8_t bit = getPinToBitMask(pin);
	uint8_t port = getPinToPort(pin);
	volatile uint8_t *out;
	
	if (port == NOT_PORT) return;
	
	if (timer != NOT_ON_TIMER) turnOffPWM(timer);
	
	out = getPortOutputRegister(port);
	
	uint8_t oldSREG = SREG;
	cli();
	if(val == LOW)
		*out &= ~bit;
	else
		*out |= bit;
	SREG = oldSREG;
}

void turnOffPWM(uint8_t timer)
{
	switch (timer)
	{
		#if defined(TCCR1A) && defined(COM1A1)
		case TIMER1A:   cbi(TCCR1A, COM1A1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1B1)
		case TIMER1B:   cbi(TCCR1A, COM1B1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1C1)
		case TIMER1C:   cbi(TCCR1A, COM1C1);    break;
		#endif
		
		#if defined(TCCR2) && defined(COM21)
		case  TIMER2:   cbi(TCCR2, COM21);      break;
		#endif
		
		#if defined(TCCR0A) && defined(COM0A1)
		case  TIMER0A:  cbi(TCCR0A, COM0A1);    break;
		#endif
		
		#if defined(TCCR0A) && defined(COM0B1)
		case  TIMER0B:  cbi(TCCR0A, COM0B1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2A1)
		case  TIMER2A:  cbi(TCCR2A, COM2A1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2B1)
		case  TIMER2B:  cbi(TCCR2A, COM2B1);    break;
		#endif
		
		#if defined(TCCR3A) && defined(COM3A1)
		case  TIMER3A:  cbi(TCCR3A, COM3A1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3B1)
		case  TIMER3B:  cbi(TCCR3A, COM3B1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3C1)
		case  TIMER3C:  cbi(TCCR3A, COM3C1);    break;
		#endif

		#if defined(TCCR4A) && defined(COM4A1)
		case  TIMER4A:  cbi(TCCR4A, COM4A1);    break;
		#endif
		#if defined(TCCR4A) && defined(COM4B1)
		case  TIMER4B:  cbi(TCCR4A, COM4B1);    break;
		#endif
		#if defined(TCCR4A) && defined(COM4C1)
		case  TIMER4C:  cbi(TCCR4A, COM4C1);    break;
		#endif
		#if defined(TCCR4C) && defined(COM4D1)
		case TIMER4D:	cbi(TCCR4C, COM4D1);	break;
		#endif
		
		#if defined(TCCR5A)
		case  TIMER5A:  cbi(TCCR5A, COM5A1);    break;
		case  TIMER5B:  cbi(TCCR5A, COM5B1);    break;
		case  TIMER5C:  cbi(TCCR5A, COM5C1);    break;
		#endif
	}
}