#include <string.h>

#include <thread>
#include <chrono>
#include <random>
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
ULONG totalticks;
//float partialticks;
ULONG keymask;
std::chrono::high_resolution_clock::time_point starttime;
bool truerandom = false;//hack

//events
CPTR appexceptionlist;

//display
WORD LCDW,LCDH;
size_t_68k LCDBYTES;
UWORD framebuffer[LCDMAXPIX * 2];//2 framebuffers of max size (the second is used for long drawing operations)
bool oldgfxmodes;

//ui
CPTR oslcdwindow,lcdbitmaptype;

//random numbers (not exposed to other files)
std::random_device seedstore;
std::mt19937 gentype(seedstore());
std::uniform_int_distribution<uint32> getrandom(0,UINT32_MAX);

//i/o thread safety
std::mutex os_data_lock;

//debug
std::string lasttrap;
//End of universal data


uint32 randomnumber(){
	return getrandom(gentype);
}

std::string directory;
shared_img palm;
std::thread palmcpu;
bool running = false,started = false;
bool hasbootableapp = false;


void get_palm_framebuffer(UWORD* copyto){
	size_t_68k total = LCDW * LCDH;

	//for old palm games that set the framebuffer address
	if(customlssa){
		//parse custom display data
		return;
	}

	//all apps start in lores mode,must be upscaled
	/*
	if(scalevideo){
		expand2x(framebuffer,copyto,160,160);
		return;
	}
	*/

	//use memcpy since it is optimized for each platform
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

	totalticks += (std::chrono::high_resolution_clock::now() - starttime) / palmTicks(1);
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

