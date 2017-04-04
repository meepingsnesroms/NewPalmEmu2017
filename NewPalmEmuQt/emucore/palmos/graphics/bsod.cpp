#include <string>
#include "minifunc.h"
#include "palmwrapper.h"
#include "biosfont.h"
#include "fbops.h"
#include "m68k.h"
#include "virtuallcd.h"

void drawbioschar(int x,int y,char letter){
	for(int cury = 0;cury < 7;cury++){
		for(int curx = 0;curx <5;curx++){
			unsigned int total = (letter - 0x20) * 5;
			int thisbyte = curx;//bytes
			int thisbit = cury;//leftover
			if(Font5x7[total + thisbyte] & bit(thisbit))FB_setpixel(curx + x,cury + y,0xFFFF/*white*/);
		}
	}
}

void showBSOD(std::string message){
	FB_data = framebuffer;
	FB_width = LCDW;
	FB_height = LCDH;

	FB_fillrect(0,0,LCDW,LCDH,0x001F/*blue*/);

	int x = 0;
	int y = 0;
	uint count = 0;
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
