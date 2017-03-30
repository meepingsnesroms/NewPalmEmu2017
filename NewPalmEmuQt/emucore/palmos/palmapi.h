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

extern void *apilist[0x45A];

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

extern CPTR textclipbank;
extern CPTR emulstate;

//api functions
void ftrget();
void syslibfind();

bool emulateapi(int api);

#endif // PALMAPI

