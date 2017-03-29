#ifndef VIRTUALLCDH
#define VIRTUALLCDH

#include "m68k.h"
#include "memmap.h"

extern bool customlssa;
extern CPTR activelssa;
void lcd_init(int w,int h);
extern addrbank lcd_bank;

#endif
