#include "Global.h"
#include "../ClockLib/Clock.h"
#include "Menu.h"
#include "DateTime.h"

#include <util/atomic.h>

volatile uint8_t GlobalEvent = SHOW_CLOCK;
volatile uint8_t portHistory = 0xFF;
const char* dayofwks[] = {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};

LCD lcd(2, 3, 4, 5, 6, 9, 10);
Menu menu;
Time time;
Data data;

int main(void) {
	InitRTC();
	
	lcd.begin(20, 4);
	menu.init(lcd);
	time.init(lcd);
	data.init(lcd);
	
	
	
	TIMSK1 |= (1<<TOIE1);
	TCCR1B = (1<<CS12)|(0<<CS11)|(0<<CS10);
	TCNT1 = 500;
	
	PCICR |= (1<<PCIE0);
	PCMSK0 |= (1<<PCINT0)|(1<<PCINT1)|(1<<PCINT2)|(1<<PCINT3)|(1<<PCINT4);
	
	sei();
	
	uint8_t volatile historyEvent;
	
	while (1) {
		if(historyEvent != GlobalEvent) {
			historyEvent = GlobalEvent;
			switch(GlobalEvent) {
			case SHOW_MENU:
				menu.init();
				break;
			case SHOW_SET_TIME:
				time.init();
				break;
			case SHOW_SET_DATE:
				data.init();
				break;
			}
		}
		
		
		if(GlobalEvent == SHOW_CLOCK) {
			if(!(TCCR1B & 0x04)) TCCR1B = (1<<CS12)|(0<<CS11)|(0<<CS10);
		} else {
			if(!(TCCR1B & 0x00)) TCCR1B = (0<<CS12)|(0<<CS11)|(0<<CS10);
		}		
//////////////////////////////////////////////////////////////////////////
		//cli();
		//lcd.setCursor(5, 3);
		//lcd.print(GlobalEvent, HEX);
		//sei();
//////////////////////////////////////////////////////////////////////////
	}
}

ISR(PCINT0_vect) {
	uint8_t key = 0x00;
	
	if(!(PINB & (1<<PINB0)))
		key = KEY_DOWN;
	else if(!(PINB & (1<<PINB1)))
		key = KEY_UP;
	else if(!(PINB & (1<<PINB2)))
		key = KEY_LEFT;
	else if(!(PINB & (1<<PINB3)))
		key = KEY_RIGTH;
	else if(!(PINB & (1<<PINB4)))
		key = KEY_OK;
	else return;
	
	switch(GlobalEvent) {
	case SHOW_CLOCK:
		if(key == KEY_OK) {
			GlobalEvent = SHOW_MENU;
		}
		break;
		
	case SHOW_MENU:
		menu.keyEvent(key);
		menu.draw();
		break;
		
	case SHOW_SET_DATE:
		data.keyEvent(key);
		data.draw();
		break;
		
	case SHOW_SET_TIME:
		time.keyEvent(key);
		time.draw();
		break;
	}
}

ISR(TIMER1_OVF_vect) {
	TCNT1 = 5000;
	lcd.clear();
	lcd.setCursor(5, 1);
	lcd.print(GetValueRTC(HOURS_REGISTER)>>4);
	lcd.print(GetValueRTC(HOURS_REGISTER)&0xf);
	lcd.print(":");
	lcd.print(GetValueRTC(MINUTES_REGISTER)>>4);
	lcd.print(GetValueRTC(MINUTES_REGISTER)&0xf);
	lcd.print(":");
	lcd.print(GetValueRTC(SECONDS_REGISTER)>>4);
	lcd.print(GetValueRTC(SECONDS_REGISTER)&0xf);
	//lcd.print(" ");
	lcd.setCursor(4, 2);
	lcd.print(dayofwks[GetValueRTC(DAYOFWK_REGISTER, true)-1]);
	lcd.print(" ");
	lcd.print(GetValueRTC(DAYS_REGISTER)>>4);
	lcd.print(GetValueRTC(DAYS_REGISTER)&0xf);
	lcd.print("-");
	lcd.print(GetValueRTC(MONTHS_REGISTER)>>4);
	lcd.print(GetValueRTC(MONTHS_REGISTER)&0xf);
	lcd.print("-");
	lcd.print(GetValueRTC(YEARS_REGISTER)>>4);
	lcd.print(GetValueRTC(YEARS_REGISTER)&0xf);
}