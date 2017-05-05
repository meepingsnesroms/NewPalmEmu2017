#include <string>
#include "m68k.h"
#include "virtuallcd.h"
#include "ugui.h"

void set_lcd_pixel(int16_t x, int16_t y, uint16_t color){
	put_word(lcd_start + ((y * LCDW + x) * 2), color);
}

void showBSOD(std::string message){
	UG_GUI* oldgui = UG_CurrentGUI();

	UG_GUI temp;
	UG_Init(&temp, set_lcd_pixel, LCDW, LCDH);
	UG_SelectGUI(&temp);

	UG_FontSelect(&FONT_8X8);
	UG_SetForecolor(C_WHITE);
	UG_SetBackcolor(C_BLUE);
	UG_FillScreen(C_BLUE);

	UG_PutString(0, 0, (char*)message.c_str());

	UG_SelectGUI(oldgui);

	//terminate execution
	throw ABORT;
}
