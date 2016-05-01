#ifndef MENU_H
#define MENU_H

#include "../ClockLib/Clock.h"
#include "Global.h"

struct ItemMenu {
	ItemMenu* Next;
	ItemMenu* Previous;
	ItemMenu* Parent;
	ItemMenu* Child;
	uint8_t Select;
	const char* Text;
};

class Menu {
public:
	Menu();
	void init();
	void init(LCD lcd);
	void keyEvent(uint8_t key);
	void draw();
private:
	LCD _lcd;
	ItemMenu* volatile selectedItemMenu;
	
	void up(void);
	void down(void);
	void left(void);
	void rigth(void);
	void ok(void);
	
	void check(uint8_t kode);
};

#endif
