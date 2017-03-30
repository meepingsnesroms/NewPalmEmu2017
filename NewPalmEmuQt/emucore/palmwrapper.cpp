#include <string.h>
#include <stdlib.h>

#include <thread>
#include <chrono>
#include <mutex>

#include "palmwrapper.h"

#include "prcfile.h"
#include "displaydriver.h"
#include "appselector.h"
#include "eventqueue.h"
#include "launchroutines.h"
#include "displaydriver.h"
#include "imagescaling.h"


//new list
#include "m68k.h"
#include "newcpu.h"
#include "minifunc.h"


//Universal data storage/heap/osvalues
std::vector<palmdb> apps;

//OS data
void (*TouchDriver)(int,int,bool) = nullptr;
void (*KeyDriver)(char,bool) = nullptr;
void (*ButtonDriver)(int,bool) = nullptr;

int curapp;//open app
int curoverlay;//open apps overlay(language file)
CPTR appcall;//fake data saying how and why the app was launched
std::string username;
std::string clipboard;
ULONG fullticks;
float partialticks;
ULONG keymask;
std::chrono::high_resolution_clock::time_point starttime;

//events
CPTR appexceptionlist;

//display
WORD LCDW,LCDH;
size_t_68k LCDBYTES;
UWORD framebuffer[LCDMAXPIX * 2];//2 framebuffers of max size (the second is used for long drawing operations)
bool oldgfxmodes;

//ui
CPTR oslcdwindow,lcdbitmaptype;

//i/o thread safety
std::mutex os_data_lock;

//debug
std::string lasttrap;
//End of universal data

std::string directory;
shared_img palm;
std::thread palmcpu;
bool started = false;
bool running = false;
bool hasbootableapp = false;


void get_palm_framebuffer(UWORD* copyto){
	size_t_68k total = LCDW * LCDH;

	//lssa must be fixed for old palm games that set the framebuffer address
	memcpy(copyto,framebuffer,total * sizeof(UWORD));
}

void palmabrt(){
	if(!lasttrap.empty())dbgprintf(lasttrap.c_str());
	abort();
}

void backupram(){
	//HACK need to do this!!
}

bool start(int bootfile){
	if(running)return false;

	if(!hasbootableapp)return false;
	if(apps.size() < bootfile || !apps[bootfile].exe)return false;
	bool launched = launchapp(bootfile);
	if(!launched)return false;

	palmcpu = std::thread(CPU,&palm);
    CPU_start(&palm);

	//input drivers
	TouchDriver = &appTouchDriver;
	KeyDriver = &appKeyDriver;
	ButtonDriver = nullptr;//hack

	running = true;
	started = true;
	return true;
}

bool resume(){
	if(!started)return false;

	BTNTBL = 0x00000000;
	PENX = 0x0000;
	PENY = 0x0000;
	starttime = std::chrono::high_resolution_clock::now();
    CPU_start(&palm);
	running = true;
	return true;
}

bool halt(){
	if(!running)return false;

	std::chrono::high_resolution_clock::duration timepassed = std::chrono::high_resolution_clock::now() - starttime;
	uint32 fulltickspassed = (uint32)(timepassed / palmTicks(1));//how many full ticks have passed since the last call to this function
	float partialtickspassed = (timepassed / palmTicks(1)) - fulltickspassed;
	fullticks   += fulltickspassed;
	partialticks += partialtickspassed;

	if(partialticks > 1.0){
		fullticks   += (uint32)partialticks;//reclaim any leftover time that previosly did not exceed 1 tick
		partialticks -= (uint32)partialticks;//remove any full ticks from the partial tick counter
	}

    CPU_stop(&palm);
	running = false;
	return true;
}

bool end(){
	if(started){
		started = false;
		running = false;
		palm.CpuReq = cpuExit;
		palmcpu.join();
		if(!palm.ForceExit)backupram();

		full_deinit();//clean up

		return true;
	}
	return false;
}



UWORD buttontovchr[7] = {520,0,0,516,517,518,519};

void sendbutton(int button, bool state){
	if(!running)return;

	//BTNTBL does not need a mutex since it is read only from the cpu thread

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

void sendtouch(int x, int y, bool pressed){
	if(TouchDriver)TouchDriver(x,y,pressed);
}

void sendkeyboardchar(char thiskey,bool state){
	if(KeyDriver)KeyDriver(thiskey,state);
}

std::string getclipboard(){
	std::string data;
	os_data_lock.lock();
	data = clipboard;
	os_data_lock.unlock();
	return data;
}

void setclipboard(std::string data){
	os_data_lock.lock();
	clipboard = data;
	os_data_lock.unlock();
}

