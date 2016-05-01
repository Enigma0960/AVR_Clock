#pragma once
#ifndef IO_H
#define IO_H

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define INPUT 0x00
#define OUTPUT 0x01

void pinMode(uint8_t pin, uint8_t mode);
uint8_t digitalInput(uint8_t pin);
void digitalOutput(uint8_t pin, uint8_t val);
void turnOffPWM(uint8_t timer);

#endif