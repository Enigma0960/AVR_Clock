#pragma once
#ifndef CLOCK_H
#define CLOCK_H

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#ifndef outb
#define	outb(addr, data)	addr = (data)
#endif
#ifndef inb
#define	inb(addr)			(addr)
#endif
#ifndef outw
#define	outw(addr, data)	addr = (data)
#endif
#ifndef inw
#define	inw(addr)			(addr)
#endif
#ifndef BV
#define BV(bit)			(1<<(bit))
#endif
#ifndef cbi
#define cbi(reg,bit)	reg &= ~(BV(bit))
#endif
#ifndef sbi
#define sbi(reg,bit)	reg |= (BV(bit))
#endif
#ifndef cli
#define cli()			__asm__ __volatile__ ("cli" ::)
#endif
#ifndef sei
#define sei()			__asm__ __volatile__ ("sei" ::)
#endif

#include "Clock/Pins.h"
#include "Clock/IO.h"
#include "Clock/LCD.h"
#include "Clock/RTC.h"

#endif