#ifndef PALETTE_H
#define PALETTE_H

#include "m68k.h"
#include "types.h"
#include "minifunc.h"

//default color tables
extern uint8_t PalmPalette2bpp[4][3];
extern uint8_t PalmPalette4bpp[16][3];
extern uint8_t PalmPalette4bppColor[16][3];
extern uint8_t PalmPalette8bpp[256][3];

//palette functions
inline uint32_t paltorgbindex8(uint8_t color){
	uint32_t result = 0;
	result |= color << 24;
	result |= PalmPalette8bpp[color][0] << 16;
	result |= PalmPalette8bpp[color][1] << 8;
	result |= PalmPalette8bpp[color][2];
	return result;
}

inline uint16_t paltopalm(uint8_t* color){
	return ((color[0] >> 3) << 11) | ((color[1] >> 2) << 5) | (color[2] >> 3);
}

inline uint16_t get_rgb_diff(uint8_t r1,uint8_t g1,uint8_t b1,uint8_t r2,uint8_t g2,uint8_t b2){
	return absdiffrence(r1,r2) + absdiffrence(g1,g2) + absdiffrence(b1,b2);
}

//point to ColorTableType not first color index
inline uint16_t getcolortblindex(offset_68k customtable,uint8_t index){
	offset_68k indexptr = customtable + index * 4 + 2/*the first 2 bytes record the number of entrys*/;
	uint8_t minipal[3];
	//the first byte of each entry is its index,then comes actual color data
	for(int flea = 0;flea < 3;flea++)
		minipal[flea] = get_byte(indexptr + flea + 1/*skip index byte*/);
	return paltopalm(minipal);
}

//a uint should be good enough for this function (palm os dosent use 32bit color)
inline uint32_t bitstocolors(int bits){
	//2 to the power of bpp(bits per pixel)
	uint32_t colors = 1;
	while(bits > 0){
		colors *= 2;
		bits--;
	}
	return colors;
}


int getbestdefaultindex(uint8_t red, uint8_t green, uint8_t blue, int bpp);

#endif // PALETTE_H
