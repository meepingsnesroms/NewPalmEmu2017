#include "palmwrapper.h"
#include "virtuallcd.h"

uint16_t LCDW, LCDH;
size_t_68k LCDBYTES;
uint16_t framebuffer[LCDMAXPIX * 2];//2 framebuffers of max size (the second is used for long drawing operations)

void lcd_init(int w,int h){
	LCDBYTES = w * h * 2;
	LCDW = w;
	LCDH = h;
	memset(framebuffer,0xFF,LCDMAXBYTES * 2);//clear framebuffer to white
}

uint8_t lcd_bget(offset_68k addr){
	addr -= lcd_start;
	if(addr & 1)return framebuffer[addr >> 1];
	return framebuffer[addr >> 1] >> 8;
}

uint16_t lcd_wget(offset_68k addr){
	addr -= lcd_start;
	return framebuffer[addr >> 1];
}

uint32_t lcd_lget(offset_68k addr){
	addr -= lcd_start;
	return (((uint32_t)framebuffer[addr >> 1]) << 16) | framebuffer[(addr >> 1) + 1];
}

void lcd_bput(offset_68k addr,uint8_t b){
	addr -= lcd_start;
	if(!(addr & 1)){
		framebuffer[addr >> 1] = (framebuffer[addr >> 1] & 0xFF) | (((uint16_t)b) << 8);
	}
	else{
		framebuffer[addr >> 1] = (framebuffer[addr >> 1] & 0xFF00) | b;
	}
}

void lcd_wput(offset_68k addr,uint16_t w){
	addr -= lcd_start;
	framebuffer[addr >> 1] = w;
}

void lcd_lput(offset_68k addr,uint32_t l){
	addr -= lcd_start;
	framebuffer[addr >> 1] = l >> 16;
	framebuffer[(addr >> 1) + 1] = (uint16_t)l;
}

uint16_t* lcd_xlate(offset_68k addr){
	return framebuffer + ((addr - lcd_start) >> 1);
}

int lcd_check(offset_68k, uint32_t){
	return 1;
}

addrbank lcd_bank = {
	lcd_lget, lcd_wget, lcd_bget,
	lcd_lput, lcd_wput, lcd_bput,
	lcd_xlate, lcd_check
};
