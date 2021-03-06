#ifndef LCD_H
#define LCD_H

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "Pins.h"
#include "IO.h"

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

//Print
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

class LCD {
public:
	LCD(){}
	LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	LCD(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	LCD(uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
	LCD(uint8_t rs, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

	void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
	
	void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

	void clear();
	void home();

	void noDisplay();
	void display();
	void noBlink();
	void blink();
	void noCursor();
	void cursor();
	void scrollDisplayLeft();
	void scrollDisplayRight();
	void leftToRight();
	void rightToLeft();
	void autoscroll();
	void noAutoscroll();

	void setRowOffsets(int row0, int row1, int row2, int row3);
	void createChar(uint8_t location, uint8_t charmap[]);
	void setCursor(uint8_t cols, uint8_t rows);
	size_t write(uint8_t value);
	void command(uint8_t value);
	
	size_t write(const char* str);
	size_t write(const char* buffer, size_t size);
	size_t write(const uint8_t* buffer, size_t size);
	
	size_t print(const char str[]);
	size_t print(char c);
	size_t print(unsigned char b, int base = DEC);
	size_t print(int n, int base = DEC);
	size_t print(unsigned int n, int base = DEC);
	size_t print(long n, int base = DEC);
	size_t print(unsigned long n, int base = DEC);
	size_t print(double n, int digits = 2);
	
private:
	void send(uint8_t value, uint8_t mode);
	void write4bits(uint8_t value);
	void write8bits(uint8_t value);
	void pulseEnable();

	size_t printNumber(unsigned long number, uint8_t base);
	size_t printFloat(double number, uint8_t digits);

	uint8_t pinRS;
	uint8_t pinRW;
	uint8_t pinE;
	uint8_t pinData[8];

	uint8_t displayFunction;
	uint8_t displayControl;
	uint8_t displayMode;

	uint8_t numLines;
	uint8_t rowOffsets[4];
};

#endif //LCD_H_
