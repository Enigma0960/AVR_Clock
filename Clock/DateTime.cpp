#include "DateTime.h"

Time::Time() {
	
}

void Time::init() {
	t = GetTimeRTC();
	cursor = 0;
	draw();
}

void Time::init(LCD lcd) {
	_lcd = lcd;
	t = GetTimeRTC();
	cursor = 0;
}

void Time::keyEvent(uint8_t key) {
	switch(key) {
	case KEY_UP:
		if(cursor == 0) {
			if(t.hours < 23) t.hours++;
			else t.hours = 0;
		} else if(cursor == 1){
			if(t.minutes < 59) t.minutes++;
			else t.minutes = 0;
		} else if(cursor == 2){
			if(t.seconds < 59) t.seconds++;
			else t.seconds = 0;
		}
		break;
		
	case KEY_DOWN:
		if(cursor == 0) {
			if(t.hours > 0) t.hours--;
			else t.hours = 23;
		} else if(cursor == 1){
			if(t.minutes > 0) t.minutes--;
			else t.minutes = 59;
		} else if(cursor == 2){
			if(t.seconds > 0) t.seconds--;
			else t.seconds = 59;
		}
		break;
	
	case KEY_LEFT:
		if(cursor > 0) cursor--;
		else cursor = 4;
		break;
		
	case KEY_RIGTH:
		if(cursor < 4) cursor++;
		else cursor = 0;
		break;
		
	case KEY_OK:
		if(cursor == 3) {
			GlobalEvent = SHOW_CLOCK;
		}
		if(cursor == 4) {
			//save
			GlobalEvent = SHOW_CLOCK;
		} else
			cursor = 3;
		break;
	}
}

void Time::draw() {
	_lcd.clear();
	_lcd.print("Set time");
	
	_lcd.setCursor(0, 1);
	if(cursor == 0) _lcd.print(">");
	if(t.hours < 10)
		_lcd.print("0");
	_lcd.print(t.hours);
	if(cursor == 0) _lcd.print("<");
	
	_lcd.print(":");
	
	if(cursor == 1) _lcd.print(">");
	if(t.minutes < 10)
		_lcd.print("0");
	_lcd.print(t.minutes);
	if(cursor == 1) _lcd.print("<");
	
	_lcd.print(":");
	
	if(cursor == 2) _lcd.print(">");
	if(t.seconds < 10)
		_lcd.print("0");
	_lcd.print(t.seconds);
	if(cursor == 2) _lcd.print("<");
	
	_lcd.setCursor(0, 2);
	if(cursor == 3) _lcd.print(">");
	_lcd.print("Cancel");
	if(cursor == 3) _lcd.print("<");
	_lcd.setCursor(9, 2);
	
	if(cursor == 4) _lcd.print(">");
	_lcd.print("Ok");
	if(cursor == 4) _lcd.print("<");
}

Data::Data() {
	
}

void Data::init() {
	d = GetDataRTC();
	cursor = 0;
	draw();
}

void Data::init(LCD lcd) {
	_lcd = lcd;
	d = GetDataRTC();
	cursor = 0;
}

void Data::keyEvent(uint8_t key) {
	switch(key) {
		case KEY_UP:
		if(cursor == 0) {		
			if(d.days < 31) d.days++;
			else d.days = 0;
		} else if(cursor == 1) {
			if(d.months < 12) d.months++;
			else d.months = 1;
		} else if(cursor == 2) {
			if(d.years < 99) d.years++;
			else d.years = 0;
		} else if(cursor == 3) {
			if(d.dayofwk < 7) d.dayofwk++;
			else d.dayofwk = 1;
		}
		break;
		
		case KEY_DOWN:
		if(cursor == 0) {
			if(d.days > 0) d.days--;
			else d.days = 31;
		} else if(cursor == 1) {
			if(d.months > 1) d.months--;
			else d.months = 12;
		} else if(cursor == 2) {
			if(d.years > 0) d.years--;
			else d.years = 99;
		} else if(cursor == 3) {
			if(d.dayofwk > 2) d.dayofwk--;
			else d.dayofwk = 1;
		}
		break;
		
		case KEY_LEFT:
		if(cursor > 0) cursor--;
		else cursor = 5;
		break;
		
		case KEY_RIGTH:
		if(cursor < 5) cursor++;
		else cursor = 0;
		break;
		
		case KEY_OK:
		if(cursor == 4) {
			GlobalEvent = SHOW_CLOCK;
		}
		if(cursor == 5) {
			//save
			GlobalEvent = SHOW_CLOCK;
		} else cursor = 4;
		break;
	}
}

void Data::draw() {
	_lcd.clear();
	_lcd.print("Set data");
	
	_lcd.setCursor(0, 1);
	if(cursor == 0) _lcd.print(">");
	if(d.days < 10)
	_lcd.print("0");
	_lcd.print(d.days);
	if(cursor == 0) _lcd.print("<");
	
	_lcd.print("-");
	
	if(cursor == 1) _lcd.print(">");
	if(d.months < 10)
	_lcd.print("0");
	_lcd.print(d.months);
	if(cursor == 1) _lcd.print("<");
	
	_lcd.print("-");
	
	if(cursor == 2) _lcd.print(">");
	if(d.years < 10)
	_lcd.print("0");
	_lcd.print(d.years);
	if(cursor == 2) _lcd.print("<");
	
	_lcd.print(" ");
	if(cursor == 3) _lcd.print(">");
	_lcd.print(dayofwks[d.dayofwk - 1]);
	if(cursor == 3) _lcd.print("<");
	
	_lcd.setCursor(0, 2);
	if(cursor == 4) _lcd.print(">");
	_lcd.print("Cancel");
	if(cursor == 4) _lcd.print("<");
	_lcd.setCursor(9, 2);
	
	if(cursor == 5) _lcd.print(">");
	_lcd.print("Ok");
	if(cursor == 5) _lcd.print("<");
}