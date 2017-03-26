#ifndef PALETTE_H
#define PALETTE_H

#include "m68k.h"
#include "types.h"

//default color tables
extern UBYTE PalmPalette2bpp[4][3];
extern UBYTE PalmPalette4bpp[16][3];
extern UBYTE PalmPalette4bppColor[16][3];
extern UBYTE PalmPalette8bpp[256][3];

//palette functions
inline ULONG paltorgbindex8(UBYTE color){
	ULONG result = 0;
	result |= color << 24;
	result |= PalmPalette8bpp[color][0] << 16;
	result |= PalmPalette8bpp[color][1] << 8;
	result |= PalmPalette8bpp[color][2];
	return result;
}

inline UWORD paltopalm(UBYTE* color){
	return ((color[0] >> 3) << 11) | ((color[1] >> 2) << 5) | (color[2] >> 3);
}

inline uint16 getrgbdiff(uint8 r1,uint8 g1,uint8 b1,uint8 r2,uint8 g2,uint8 b2){
	return absdiffrence(r1,r2) + absdiffrence(g1,g2) + absdiffrence(b1,b2);
}

//point to ColorTableType not first color index
inline UWORD getcolortblindex(CPTR customtable,UBYTE index){
	CPTR indexptr = customtable + index * 4 + 2/*the first 2 bytes record the number of entrys*/;
	UBYTE minipal[3];
	//the first byte of each entry is its index,then comes actual color data
	for(int flea = 0;flea < 3;flea++)
		minipal[flea] = get_byte(indexptr + flea + 1/*skip index byte*/);
	return paltopalm(minipal);
}

//a uint should be good enough for this function (palm os dosent use 32bit color)
inline uint bitstocolors(int bits){
	//2 to the power of bpp(bits per pixel)
	uint colors = 1;
	while(bits > 0){
		colors *= 2;
		bits--;
	}
	return colors;
}


int getbestdefaultindex(UBYTE red, UBYTE green, UBYTE blue, int bpp);

#endif // PALETTE_H
