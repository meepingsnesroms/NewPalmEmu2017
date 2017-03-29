#include "palmwrapper.h"

#include "m68k.h"
#include "minifunc.h"
#include "memmap.h"
#include "virtualhardware.h"
#include "rawimagetools.h"
#include "resourcelocator.h"
#include "displaydriver.h" //hack move coord into rawimagetools.h

#define SELECTORBCKGRNDCOLOR 0x0

#define ICONID 1000

bool selectingapp = false;

COORD drawingcoord;

void nextdrawingarea(){
	drawingcoord.x += 32;//hack //do based on display width
}

static void cleanupandlaunch(int app){
	selectingapp = false;
	start(app);
}

void selectortouchintercept(int x,int y,bool down){
	if(down){
		//animate selection
		//hack
	}else{
		//launch selected app
		size_t app = x / 32 + (y / 32) * 10;
		if(app < apps.size()){
			if(apps[app].exe == true)cleanupandlaunch(app);
		}
	}
}

void selectappandstart(){
	//disable input
	TouchDriver = nullptr;
	KeyDriver = nullptr;
	ButtonDriver = nullptr;

	//start running
	running = true;
	started = true;

	FBWriter display(lcd_start,LCDW,LCDBPP);

	for(int cnty = 0;cnty < LCDH;cnty++){
		for(int cntx = 0;cntx < LCDW;cntx++){
			display.setpixel(cntx,cnty,SELECTORBCKGRNDCOLOR);
		}
	}

	drawingcoord.x = 0;
	drawingcoord.y = 0;

	//an icon is 32*32 pixels + text height

	TEMPHACK;
	//may need to check for icons in app overlays

	size_t appvectorsize = apps.size();
	for(size_t bunfluff = 0;bunfluff < appvectorsize;bunfluff++){
		//draw icon
		CPTR iconptr = nullptr_68k;
		if(apps[bunfluff].resdb){
			iconptr = getresource(bunfluff,ICONID,'tAIB');
		}
		if(iconptr){
			RAWimg icon(iconptr,BMP);
			display.draw(icon,drawingcoord.x,drawingcoord.y);
		}

		//draw text
		//display.draw5x7(x,y,0xFFFF,'G');

		//allocate screen space for next name/icon
		nextdrawingarea();
	}

	//set flag for touchscreen
	selectingapp = true;
	TouchDriver = selectortouchintercept;
}
