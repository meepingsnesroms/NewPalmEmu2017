#ifndef PALMWRAPPER
#define PALMWRAPPER

//part of "simple functions"
#include "launchroutines.h" //globals
#include "prcfile.h" //loading apps
#include "virtuallcd.h" //framebuffer
#include "appselector.h" //home screen

//actualy needed by this header file
#include "m68k.h"
#include "palmdatatypes.h" //palm os custom structs

#include <vector>
#include <string>
#include <chrono>
#include <thread> //HACK move to files that need it



//Universal data storage/heap/osvalues
extern std::vector<palmdb> apps;

extern void (*TouchDriver)(int,int,bool);
extern void (*KeyDriver)(char,bool);
extern void (*ButtonDriver)(int,bool);

extern int curapp;
extern int curoverlay;
extern CPTR appcall;
extern std::string username;
extern ULONG totalticks;
//extern float partialticks;
extern ULONG keymask;
extern std::chrono::high_resolution_clock::time_point starttime;

//events
extern CPTR appexceptionlist;

//display
#define LCDMAXW		320
#define LCDMAXH		480
#define LCDMAXPIX	(LCDMAXW * LCDMAXH)
#define LCDMAXBPP	16
#define LCDMAXBYTES (LCDMAXPIX * 2)

extern WORD LCDW,LCDH;
#define LCDBPP 16 //hack //make varible
#define LCDHASCOLOR (LCDBPP > 4)
#define LCDDENSITY	(LCDW / 160)
extern size_t_68k LCDBYTES;
extern UWORD framebuffer[LCDMAXPIX * 2];//2 framebuffers of max size (the second is used for long drawing operations)

//ui
extern CPTR oslcdwindow,lcdbitmaptype;

//debug
extern std::string lasttrap;
//End of universal data


enum{
	Power,
	Up,
	Down,
	Calender,
	Contacts,
	Todo,
	Notes
};

//HACK above is too generic may cause conflicts,switch to "BTN_*" below
enum{
	BTN_Power,
	BTN_Up,
	BTN_Down,
	BTN_Calender,
	BTN_Contacts,
	BTN_Todo,
	BTN_Notes
};

extern std::string directory;
extern shared_img palm;
extern std::thread palmcpu;
extern bool started;
extern bool running;
extern bool hasbootableapp;


void backupram();
void palmabrt();

//simple functions
//bool loadfiletopalm(std::string path);//is in prcfile.h
//bool launchapp(int num);//is in launchroutines.h
//bool full_init(string& name,int x,int y);//is in launchroutines.h
//void full_deinit();//is in launchroutines.h
//void selectappandstart();//is in appselector.h
bool start(int bootfile);
bool resume();
bool halt();
bool end();
void sendbutton(int button, bool state);
void sendtouch(int x,int y,bool pressed);
void sendkeyboardchar(char thiskey,bool state);

//call this to get the newest framebufffer
//format is 16bit RGB565
void get_palm_framebuffer(UWORD* copyto);

//HACK add audio

std::string getclipboard();
void setclipboard(std::string data);

#endif // PALMWRAPPER

