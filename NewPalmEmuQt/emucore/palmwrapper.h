#ifndef PALMWRAPPER
#define PALMWRAPPER

#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include "m68k.h"
#include "palmdatatypes.h"

typedef struct{
	std::vector<std::string>	internal_files;//Prc, pdb files that are installed on the palm, put the app you want to run last in the list
	std::string					sdcard_directory;//Root directory of the sdcard
	std::string					username = "cuttlefish";//Your hotsync id
	bool						multibyte_char_support = false;//Allow UTF-16 chars
	uint32_t					screen_width  = 160;//Pixels left to right
	uint32_t					screen_height = 160;//Pixels top to bottom
	bool						confusion_is_fatal = true;//On any undefined function or error kill the emulator
}emu_config;

//App state
extern std::vector<palmdb>  apps;
extern int					curapp;
extern int					curoverlay;
extern offset_68k			appcall;

//Emulated device state
extern std::string  username;
extern std::string	sdcard_directory;
extern bool			multibyte_char_support;
extern uint32_t		keymask;

//Time
extern uint32_t											fullticks;
extern float											partialticks;
extern std::chrono::high_resolution_clock::time_point	starttime;
extern std::mutex										timer_lock;

//Events
extern offset_68k appexceptionlist;

//Ui
//extern offset_68k os_lcd_window, lcdbitmaptype;

//Debug
extern std::string	lasttrap;
extern bool			confusion_is_fatal;

enum{
	BTN_Power,
	BTN_Up,
	BTN_Down,
	BTN_Calender,
	BTN_Contacts,
	BTN_Todo,
	BTN_Notes
};

extern shared_img palm;

void palmabrt();

bool emu_start(emu_config params);
bool emu_resume();
bool emu_halt();
bool emu_end();
bool emu_started();
bool emu_paused();
void emu_sendbutton(int button, bool state);
void emu_sendtouch(int x, int y, bool pressed);
void emu_sendkeyboardchar(char thiskey, bool state);

//call this to get the newest framebufffer
//format is 16bit RGB565
void emu_get_framebuffer(uint16_t* copyto);

//HACK add audio

std::string emu_getclipboard();
void		emu_setclipboard(std::string data);

#endif // PALMWRAPPER

