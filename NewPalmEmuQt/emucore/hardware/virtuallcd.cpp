#include "palmwrapper.h"

WORD LCDW,LCDH;
size_t_68k LCDBYTES;
UWORD framebuffer[LCDMAXPIX * 2];//2 framebuffers of max size (the second is used for long drawing operations)

void lcd_init(int w,int h){
	LCDBYTES = w * h * 2;
	LCDW = w;
	LCDH = h;
	memset(framebuffer,0xFF,LCDMAXBYTES * 2);//clear framebuffer to white
}

UBYTE lcd_bget(CPTR addr){
	addr -= lcd_start;
	if(addr & 1)return framebuffer[addr >> 1];
	return framebuffer[addr >> 1] >> 8;
}

UWORD lcd_wget(CPTR addr){
	addr -= lcd_start;
	return framebuffer[addr >> 1];
}

ULONG lcd_lget(CPTR addr){
	addr -= lcd_start;
	return (((ULONG)framebuffer[addr >> 1]) << 16) | framebuffer[(addr >> 1) + 1];
}

void lcd_bput(CPTR addr,UBYTE b){
	addr -= lcd_start;
	if(!(addr & 1)){
		framebuffer[addr >> 1] = (framebuffer[addr >> 1] & 0xFF) | (((UWORD)b) << 8);
	}
	else{
		framebuffer[addr >> 1] = (framebuffer[addr >> 1] & 0xFF00) | b;
	}
}

void lcd_wput(CPTR addr,UWORD w){
	addr -= lcd_start;
	framebuffer[addr >> 1] = w;
}

void lcd_lput(CPTR addr,ULONG l){
	addr -= lcd_start;
	framebuffer[addr >> 1] = l >> 16;
	framebuffer[(addr >> 1) + 1] = (UWORD)l;
}

UWORD* lcd_xlate(CPTR addr){
	return framebuffer + ((addr - lcd_start) >> 1);
}

int lcd_check(CPTR, ULONG){
	return 1;
}

addrbank lcd_bank = {
	lcd_lget, lcd_wget, lcd_bget,
	lcd_lput, lcd_wput, lcd_bput,
	lcd_xlate, lcd_check
};
