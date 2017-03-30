#ifndef RAWIMAGETOOLS
#define RAWIMAGETOOLS

#include "m68k.h"
#include "types.h"
#include "minifunc.h"
#include <vector>

//HACK remove this header
#include "palmos/graphics/bitmapcompression.h"

typedef struct{
	WORD w;
	WORD h;
}BOUNDRY;

typedef struct{
	WORD x;
	WORD y;
}COORD;

typedef struct{
	COORD start;
	COORD end;
	BOUNDRY size;
}SQUARE;

//square with ui prams,for ui bounding boxes
typedef struct{
	COORD start;
	COORD end;
	UBYTE objtype;
	UWORD objid;
	CPTR object;
}UISQUARE;

inline COORD get_coord(CPTR addr){
	COORD temp;
	temp.x = (WORD)get_word(addr);
	temp.y = (WORD)get_word(addr + 2);
	return temp;
}

inline BOUNDRY get_boundry(CPTR addr){
	BOUNDRY temp;
	temp.w = (WORD)get_word(addr);
	temp.h = (WORD)get_word(addr + 2);
	return temp;
}

inline SQUARE get_square(CPTR addr){
	SQUARE temp;
	temp.start = get_coord(addr);
	temp.size = get_boundry(addr + 4);
	temp.end.x = temp.start.x + temp.size.w;
	temp.end.y = temp.start.y + temp.size.h;
	return temp;
}

inline SQUARE get_ABSsquare(CPTR addr){
	SQUARE temp;
	temp.start = get_coord(addr);
	temp.end = get_coord(addr + 4);
	temp.size.w = temp.end.x - temp.start.x;
	temp.size.h = temp.end.y - temp.start.y;
	return temp;
}



#define THICKNESS (LCDW / 160)

//extern unsigned char Font5x7[];

//Compression Types for BitMap (for BitmapVersionTwo and >)
/*
enum{
	BitmapCompressionTypeScanLine = 0,
	BitmapCompressionTypeRLE,
	BitmapCompressionTypePackBits,
	BitmapCompressionTypeNone = 0xFF
};
*/

//font names
enum{
  stdFont = 0x00,
  boldFont,
  largeFont,
  symbolFont,
  symbol11Font,
  symbol7Font,
  ledFont,
  largeBoldFont,
  fntAppFontCustomBase = 0x80
};

typedef struct{
	std::vector<WORD> x;
	std::vector<WORD> y;
	bool fill;
	UWORD color;
}poly;

enum{
	NONE,
	NEWLINE,
	TERMINATE,
	DELETE,
	XTAB,
	YTAB,
	SPECIAL,
	WIERD
};

inline int chraction(char tst){
	switch(tst){
		case '\n':
		case '\r':
			return NEWLINE;
		case '\0':
			return TERMINATE;
		case '\b':
		case 0x7F://delete
			return DELETE;
		case '\t'://horizontal tab
			return XTAB;
		case '\v'://vertical tab
			return YTAB;
		default:
			break;
	}
	if((unsigned char)tst <= 0x1F)return WIERD;
	if((unsigned char)tst >= 0x80)return SPECIAL;
	return NONE;
}


inline uint makerowbytes(int width,int bpp){
	uint bytes = width * bpp / 8 + ((width * bpp % 8 != 0) ? 1 : 0);
	if(bytes & 1)bytes += 1;//pad
	return bytes;
}



//graphical char
class gchar {
	//adorable baby ameoba
	char value;
	CPTR start;
	offset_68k yincrement;
	offset_68k glyphoffset;
	UWORD oncolor,offcolor;
	BOUNDRY area;
	int pxbelowline;
public:
	gchar(CPTR fntbmpstart, offset_68k glyphofft, char val, UWORD oncol, UWORD offcol, BOUNDRY ar, offset_68k yinc, int lineofft);

	int aboveline();
	int belowline();
	WORD width();
	WORD height();
	UWORD getpixel(WORD x,WORD y);
};

//palm font
class RAWfnt {
	CPTR fontptr;
	offset_68k charinfotableoffset;

	WORD firstch,lastch;
	WORD charwidth;
	size_t_68k chsize;
	WORD rowwords;
	int numch;
	std::vector<UWORD> charBMP;

	void parsefnt();
public:
	~RAWfnt();

	WORD width,height;
	WORD ascent,descent;
	void setactivefont(CPTR location);
	gchar getIMG(unsigned char chnum);
	UWORD getpixel(WORD x,WORD y);
};



//palm image format management
enum{
	BMP,
	WINDOW,
	ICON,
	POINTER
};

//operations
enum{
	FILL,
	OUTLINE,
	INVERT,
	PAINT,
	ERASE
};

//line types
enum{
	SOLID,
	DASHED,
	DOTTED
};

class RAWimg {
	CPTR m68kptr;
	bool inm68kaddrspace = false;
	bool readonly = false;
	CPTR custompalette = 0;
	UBYTE* orgdat;
	std::vector<UWORD> purifieddata;

	//stats
	UBYTE datatype,typeversion;
	UBYTE compression = BitmapCompressionTypeNone;

	void from68k(CPTR m68kaddr, UBYTE type, WORD datawidth, WORD dataheight, UBYTE bpp, bool leaveinplace);

	void get1bitpixelarr();
	void get2bitpixelarr();
	void get4bitpixelarr();
	void get8bitpixelarr();
	UWORD mypalettecolor(UBYTE index);

public:
	//stats
	int width = 0,height = 0;
	uint8 pixelsize = 0;
	bool hastransparent = false;
	UWORD transparent = 0x0000;
	size_t_68k totalsize;
	UWORD rowbytes;

	//for width and bpp findme means get from wrapper
	RAWimg(CPTR m68kaddr, UBYTE type);
	RAWimg(CPTR m68kaddr, UBYTE type, WORD datawidth, WORD dataheight, UBYTE bpp, bool leaveinplace);
	~RAWimg();

	UWORD getpixel(WORD x,WORD y);
	void setpixel(WORD x,WORD y,UWORD color);

private:
	void tobuff();
};

class FBWriter{
private:
	UWORD* test;//hack
	CPTR location;
	UWORD rowbytes;
	WORD width;
	UBYTE pixelsize;

public:
	FBWriter(CPTR addr, UWORD buffwidth, UBYTE bpp);

	UWORD getpixel(WORD x,WORD y);
	void setpixel(WORD x,WORD y,UWORD color);
	void line(WORD x, WORD y, WORD x2, WORD y2, int prams, UWORD color);
	void rect(WORD x, WORD y, WORD w, WORD h, int prams, UWORD color, UWORD round);
	void copyrect(RAWimg& host, WORD startx, WORD starty, WORD rectw, WORD recth, WORD outx, WORD outy);
	void draw(RAWimg& smlimg, WORD x, WORD y);
	void draw(char letter, RAWfnt& chrimgs, WORD x, WORD y);
	bool draw5x7(int16 x, int16 y, UWORD color, char letter);//hack //remove this
};

//image type creation
CPTR newbmp(int16 width,int16 height,uint8 bpp,bool hasclearcol,UBYTE clearcolindex,bool hascoltable,CPTR coltable);
CPTR newdrawstate();
CPTR newwindow(int16 width,int16 height,UWORD flags,UWORD frameflags,CPTR winbmp,CPTR drawstate,CPTR nextwindowptr);
void initformwindow(CPTR thiswindow,int16 width,int16 height,UWORD flags,UWORD frameflags,CPTR winbmp,CPTR drawstate,CPTR nextwindowptr);

inline CPTR newbmpsimple(int16 width,int16 height,uint8 bpp){
	return newbmp(width,height,bpp,false,0,false,0);
}



//compression

//form
extern UWORD frmid;
CPTR decompressform(UWORD id);
void releaseformmemory(CPTR frmptr);

//bitmap
UBYTE* scanline(CPTR addr, WORD width, WORD height, UWORD rowbytes);
UBYTE* RLE(CPTR addr,WORD width,WORD height,UWORD rowbytes);
UBYTE* PackBits(CPTR addr,WORD width,WORD height,UWORD rowbytes);
#endif // RAWIMAGETOOLS

