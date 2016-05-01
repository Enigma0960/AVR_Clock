#ifndef DATETIME_H
#define DATETIME_H

#include "../ClockLib/Clock.h"
#include "Global.h"

class Time {
public:
	Time();
	void init();
	void init(LCD lcd);
	void keyEvent(uint8_t key);
	void draw();
private:
	LCD _lcd;
	TimeRTC t;
	uint8_t cursor;	
};

class Data {
	public:
	Data();
	void init();
	void init(LCD lcd);
	void keyEvent(uint8_t key);
	void draw();
	private:
	LCD _lcd;
	DataRTC d;
	uint8_t cursor;
};

#endif
