#include "palmwrapper.h"
#include "palmosemulibretro.h" //needed for name mangleing
#include <vector>
#include <string>

//output framebuffer
static UWORD libretro_fb[320 * 480];

//touchscreen mouse
static int mousex = 0,mousey = 0;

//HACK make these varible
static std::vector<std::string> appstoload;
static int res_x = 160,res_y = 160;
static std::string palmname = "milkedflea";



static void drawmouse(){
	libretro_fb[mousey * res_x + mousex] = 0xF00F;//HACK pixel mouse
}



void libretro_palm_init(){
	emu_config settings;

	//HACK load varible filepath
	settings.internal_files.push_back("/Users/Hoppy/000prcs/zap2016.prc");
	settings.internal_files.push_back("/Users/Hoppy/000prcs/osdata/fonts.prc");

	bool pass = emu_start(settings);
	if(!pass)palmabrt();
}

void libretro_palm_deinit(){
	emu_end();
}

void libretro_palm_setresolution(int x,int y){
	res_x = x;
	res_y = y;
}

void libretro_palm_setbutton(int button, bool state){
	emu_sendbutton(button,state);
}

void libretro_palm_touchmouse(int relx,int rely){
	if(mousex + relx > res_x)mousex = res_x;
	else if(mousex + relx < 0)mousex = 0;
	else mousex += relx;

	if(mousey + rely > res_y)mousey = res_y;
	if(mousey + rely < 0)mousey = 0;
	else mousey += rely;
}

void libretro_palm_touchmouseclick(bool down){
	emu_sendtouch(mousex,mousey,down);
}

void* libretro_palm_getframebuffer(){
	emu_get_framebuffer(libretro_fb);
	drawmouse();
	return libretro_fb;
}
