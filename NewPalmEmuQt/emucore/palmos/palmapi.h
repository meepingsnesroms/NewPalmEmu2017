#ifndef PALMAPI
#define PALMAPI

#include "m68k.h"

#define APIFROMTP(x) ((x) & 0x0FFF)
#define SETAPIFUNCFROMTP(x,y) (apilist[(x) & 0x0FFF] = (void*)&(y))

#define API(x,y) case (x):\
	(y);\
	return true

#define SELECTOR switch(D2)

#define SELAPI(x,y) case (x):\
	(y);\
	return

//shared library traps
#define	sysLibTrapBase		0xA800
enum{
	sysLibTrapName = sysLibTrapBase,
	sysLibTrapOpen,
	sysLibTrapClose,
	sysLibTrapSleep,
	sysLibTrapWake,
	sysLibTrapCustom
};

extern offset_68k textclipbank;
extern offset_68k emulstate;

//api functions
void ftrget();
void syslibfind();

void reset_and_load_default_features();
void make_api_list_from_rom(offset_68k rom_SysGetTrapAddress);

bool emulateapi(uint16_t api);

#endif // PALMAPI

