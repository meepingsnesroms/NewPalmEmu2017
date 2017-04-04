#include <string.h>
#include <stdlib.h>

#include <thread>
#include <chrono>
#include <mutex>

#include "palmwrapper.h"

#include "prcfile.h"
#include "displaydriver.h"
#include "eventqueue.h"
#include "launchroutines.h"
#include "displaydriver.h"
#include "imagescaling.h"


//new list
#include "m68k.h"
#include "newcpu.h"
#include "minifunc.h"
#include "virtuallcd.h"

//App state
std::vector<palmdb> apps;
int					curapp;//open app
int					curoverlay;//open apps overlay(language file)
CPTR				appcall;//fake data saying how and why the app was launched

//Device state
std::string username;
std::string clipboard;
std::string sdcarddirectory;
bool		multibytecharsupport;
ULONG		keymask;

//Time
uint32_t fullticks;
float partialticks;
std::chrono::high_resolution_clock::time_point starttime;

//Events
CPTR appexceptionlist;

//Ui
CPTR oslcdwindow,lcdbitmaptype;

//I/o thread safety
std::mutex os_data_lock;

//Debug
std::string lasttrap;
bool		confusion_is_fatal;


shared_img  palm;
std::thread palmcpu;
bool started = false;
bool running = false;


void emu_get_framebuffer(UWORD* copyto){
	size_t_68k total = LCDW * LCDH;

	//lssa must be fixed for old palm games that set the framebuffer address
	memcpy(copyto,framebuffer,total * sizeof(UWORD));
}

void palmabrt(){
	if(!lasttrap.empty())dbgprintf("%s", lasttrap.c_str());
	abort();
}

/*
void backupram(){
	//HACK need to do this!!
}
*/

bool emu_start(emu_config params){
	if(running)return false;

	full_init(params.username, params.screen_width, params.screen_height);
	size_t xmany = params.internal_files.size();
	for(size_t count = 0;count < xmany;count++){
		int pass = loadfiletopalm(params.internal_files[count]);
		if(pass != 0)palmabrt();
	}

	bool launched = launchapp(params.internal_files.size() - 1);
	if(!launched)return false;

	palmcpu = std::thread(CPU,&palm);
    CPU_start(&palm);

	running = true;
	started = true;
	return true;
}

bool emu_resume(){
	if(!started)return false;

	BTNTBL = 0x00000000;
	PENX = 0x0000;
	PENY = 0x0000;
	starttime = std::chrono::high_resolution_clock::now();
    CPU_start(&palm);
	running = true;
	return true;
}

bool emu_halt(){
	if(!running)return false;

	std::chrono::high_resolution_clock::duration timepassed = std::chrono::high_resolution_clock::now() - starttime;
	uint32_t fulltickspassed = (uint32_t)(timepassed / palmTicks(1));//how many full ticks have passed since the last call to this function
	float partialtickspassed = (timepassed / palmTicks(1)) - fulltickspassed;
	fullticks   += fulltickspassed;
	partialticks += partialtickspassed;

	if(partialticks > 1.0){
		fullticks   += (uint32_t)partialticks;//reclaim any leftover time that previosly did not exceed 1 tick
		partialticks -= (uint32_t)partialticks;//remove any full ticks from the partial tick counter
	}

    CPU_stop(&palm);
	running = false;
	return true;
}

bool emu_end(){
	if(started){
		started = false;
		running = false;
		palm.CpuReq = cpuExit;
		palmcpu.join();

		full_deinit();//clean up

		return true;
	}
	return false;
}

bool emu_started(){
	return started;
}

bool emu_paused(){
	return !running && started;
}



UWORD buttontovchr[7] = {520,0,0,516,517,518,519};

void emu_sendbutton(int button, bool state){
	if(!running)return;

	//BTNTBL does not need a mutex since it is only written to from the gui thread

	if(state){
		BTNTBL |= bit(button);
		if(buttontovchr[button] && (bit(button) & ~keymask)){
			osevent keypress;
			keypress.type = keyDownEvent;
			keypress.data.push_back(0);//chr
			keypress.data.push_back(buttontovchr[button]);//virtual key num
			keypress.data.push_back(8);//modifiers
			addnewevent(keypress);
		}
	}
	else{
		BTNTBL &= ~bit(button);
	}
}

void emu_sendtouch(int x, int y, bool pressed){
	if(!running)return;
	appTouchDriver(x, y, pressed);
}

void emu_sendkeyboardchar(char thiskey, bool state){
	if(!running)return;
	appKeyDriver(thiskey, state);
}

std::string emu_getclipboard(){
	std::string data;
	os_data_lock.lock();
	data = clipboard;
	os_data_lock.unlock();
	return data;
}

void emu_setclipboard(std::string data){
	os_data_lock.lock();
	clipboard = data;
	os_data_lock.unlock();
}

