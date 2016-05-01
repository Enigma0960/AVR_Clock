#include "Menu.h"

extern ItemMenu s1i0;
extern ItemMenu s1i1;
extern ItemMenu s1i2;
extern ItemMenu s2i0;

ItemMenu NullItemMenu = {(ItemMenu*)0x00, (ItemMenu*)0x00, (ItemMenu*)0x00, (ItemMenu*)0x00, 0x00, 0x00};

#define _PTR(P) (&P)

ItemMenu s1i0 = {_PTR(s2i0),		_PTR(NullItemMenu),	_PTR(NullItemMenu), _PTR(s1i1),			0x00, ("Data/Time")};
ItemMenu s1i1 = {_PTR(s1i2),		_PTR(NullItemMenu),	_PTR(s1i0),			_PTR(NullItemMenu), 0x01, ("Set data")};
ItemMenu s1i2 = {_PTR(NullItemMenu),_PTR(s1i1),			_PTR(s1i0),			_PTR(NullItemMenu), 0x02, ("Set time")};
ItemMenu s2i0 = {_PTR(NullItemMenu),_PTR(s1i0),			_PTR(NullItemMenu),	_PTR(NullItemMenu), 0x00, ("Alarm")};

Menu::Menu() {
	selectedItemMenu = &s1i0;
}

void Menu::init() {
	selectedItemMenu = &s1i0;
	draw();
}

void Menu::init(LCD lcd) {
	_lcd = lcd;
	selectedItemMenu = &s1i0;
}

void Menu::keyEvent(uint8_t key) {
	switch(key) {
	case KEY_LEFT:
		//left();
		break;
	case KEY_RIGTH:
		rigth();
		break;
	case KEY_UP:
		up();
		break;
	case KEY_DOWN:
		down();
		break;
	case KEY_OK:
		ok();
		break;
	}
	
}

void Menu::up(void) {	
	if((uint16_t)(selectedItemMenu->Next) != (uint16_t)(&NullItemMenu))
		selectedItemMenu = (selectedItemMenu->Next);
}

void Menu::down(void) {
	if((uint16_t)(selectedItemMenu->Previous) != (uint16_t)(&NullItemMenu))
		selectedItemMenu = (selectedItemMenu->Previous);
}

void Menu::left(void) {
	
}

void Menu::rigth(void) {
	if((selectedItemMenu->Parent) == (&NullItemMenu))
		GlobalEvent = SHOW_CLOCK;
	if((selectedItemMenu->Parent) != (&NullItemMenu))
		selectedItemMenu = (selectedItemMenu->Parent);
}

void Menu::ok(void) {
	if((uint16_t)(selectedItemMenu->Child) != (uint16_t)(&NullItemMenu))
		selectedItemMenu = (selectedItemMenu->Child);
	else
		check(selectedItemMenu->Select);
}

void Menu::check(uint8_t kode) {
	if(kode == 0x01) GlobalEvent = SHOW_SET_DATE;
	if(kode == 0x02) GlobalEvent = SHOW_SET_TIME;
}

void Menu::draw() {
	_lcd.clear();	
	ItemMenu* bufferMenu = selectedItemMenu;
	_lcd.setCursor(0, 0);
	if((uint16_t)(selectedItemMenu->Parent) != (uint16_t)(&NullItemMenu))
	_lcd.print(bufferMenu->Parent->Text);
	else
	_lcd.print("Settings");
	if((uint16_t)(bufferMenu->Next)!=(uint16_t)(&NullItemMenu)) {
		_lcd.setCursor(0, 1);
		_lcd.print(">");
		_lcd.print(bufferMenu->Text);
		_lcd.setCursor(1, 2);
		_lcd.print(bufferMenu->Next->Text);
		} else {
		_lcd.setCursor(1, 1);
		_lcd.print(bufferMenu->Previous->Text);
		_lcd.setCursor(0, 2);
		_lcd.print(">");
		_lcd.print(bufferMenu->Text);
	}	
}