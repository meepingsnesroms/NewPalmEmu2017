#include <string>
#include "minifunc.h"
#include "palmwrapper.h"
#include "biosfont.h"
#include "fbops.h"
#include "m68k.h"
#include "virtuallcd.h"

inline void set_lcd_pixel(int x, int y, uint16_t color){
	put_word(lcd_start + ((y * LCDW + x) * 2), color);
}

static void drawbioschar(int x, int y, char letter){
	for(int cury = 0;cury < 7;cury++){
		for(int curx = 0;curx <5;curx++){
			unsigned int total = (letter - 0x20) * 5;
			int thisbyte = curx;//bytes
			int thisbit = cury;//leftover
			if(Font5x7[total + thisbyte] & bit(thisbit))set_lcd_pixel(curx + x, cury + y, 0xFFFF/*white*/);
		}
	}
}

void showBSOD(std::string message){

	//make blue background
	for(uint32_t pixels = 0;pixels < LCDW * LCDH;pixels++){
		put_word(lcd_start + (pixels * 2), 0x001F/*blue*/);
	}

	int x = 0;
	int y = 0;
	uint32_t count = 0;
	while(count < message.length()){
		drawbioschar(x,y,message[count]);
		x += 5 + 1/*space between chars*/;
		if(x + 5 >= LCDW){//if the line cant fit another character move to the next line
			x = 0;
			y += 7 + 1/*space between lines*/;
		}
		count++;
	}

	//terminate execution
	throw ABORT;
}
