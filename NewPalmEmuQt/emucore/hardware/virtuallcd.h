#ifndef VIRTUALLCDH
#define VIRTUALLCDH

#include "m68k.h"
#include "memmap.h"

#define LCDMAXW		320
#define LCDMAXH		480
#define LCDMAXPIX	(LCDMAXW * LCDMAXH)
#define LCDMAXBYTES (LCDMAXPIX * 2)

#define LCDBPP		16
#define LCDMAXBPP	16
#define LCDHASCOLOR (LCDBPP > 4)
#define LCDDENSITY	(LCDW / 160)

extern uint16_t LCDW, LCDH;
extern size_t_68k LCDBYTES;
extern uint16_t framebuffer[LCDMAXPIX * 2];//2 framebuffers of max size (the second is used for long drawing operations)

void lcd_init(int w,int h);
extern addrbank lcd_bank;

#endif
