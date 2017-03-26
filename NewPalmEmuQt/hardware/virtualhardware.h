#ifndef CUSTOMH
#define CUSTOMH

#include "m68k.h"
#include "memmap.h"

void custom_init(shared_img *shptr);
void customreset();
void setint(int num);
void unsetint(int num);
void updateisr();
int intbase();
int intlev();

void custom_lput(CPTR addr,ULONG value);
void custom_wput(CPTR addr,UWORD value);
void custom_bput(CPTR addr,UBYTE value);
ULONG custom_lget(CPTR addr);
UWORD custom_wget(CPTR addr);
UBYTE custom_bget(CPTR addr);

extern unsigned long specialflags;
extern bool updateinterrupts;

//speaker
//typedef uint16 FREQ;

extern UWORD* speakerbuffer;
void wspkctl(UWORD val);
UWORD rspkctl();

//display
extern bool customlssa;
extern CPTR activelssa;
void lcd_init(int w,int h);
extern addrbank lcd_bank;

#endif
