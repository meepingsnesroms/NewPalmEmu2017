#ifndef RAWIMAGETOOLS
#define RAWIMAGETOOLS

#include "m68k.h"
#include "types.h"
#include "minifunc.h"
#include <vector>

//HACK remove this header
#include "palmos/graphics/bitmapcompression.h"

typedef struct{
	int16_t w;
	int16_t h;
}BOUNDRY;

typedef struct{
	int16_t x;
	int16_t y;
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
	uint8_t objtype;
	uint16_t objid;
	offset_68k object;
}UISQUARE;

inline COORD get_coord(offset_68k addr){
	COORD temp;
	temp.x = (int16_t)get_word(addr);
	temp.y = (int16_t)get_word(addr + 2);
	return temp;
}

inline BOUNDRY get_boundry(offset_68k addr){
	BOUNDRY temp;
	temp.w = (int16_t)get_word(addr);
	temp.h = (int16_t)get_word(addr + 2);
	return temp;
}

inline SQUARE get_square(offset_68k addr){
	SQUARE temp;
	temp.start = get_coord(addr);
	temp.size = get_boundry(addr + 4);
	temp.end.x = temp.start.x + temp.size.w;
	temp.end.y = temp.start.y + temp.size.h;
	return temp;
}

inline SQUARE get_ABSsquare(offset_68k addr){
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
	std::vector<int16_t> x;
	std::vector<int16_t> y;
	bool fill;
	uint16_t color;
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


inline uint32_t makerowbytes(int width,int bpp){
	uint32_t bytes = width * bpp / 8 + ((width * bpp % 8 != 0) ? 1 : 0);
	if(bytes & 1)bytes += 1;//pad to word boundry
	return bytes;
}



//graphical char
class gchar {
	//adorable baby ameoba
	char value;
	offset_68k start;
	offset_68k yincrement;
	offset_68k glyphoffset;
	uint16_t oncolor,offcolor;
	BOUNDRY area;
	int pxbelowline;
public:
	gchar(offset_68k fntbmpstart, offset_68k glyphofft, char val, uint16_t oncol, uint16_t offcol, BOUNDRY ar, offset_68k yinc, int lineofft);

	int aboveline();
	int belowline();
	int16_t width();
	int16_t height();
	uint16_t getpixel(int16_t x,int16_t y);
};

//palm font
class RAWfnt {
	offset_68k fontptr;
	offset_68k charinfotableoffset;

	int16_t firstch,lastch;
	int16_t charwidth;
	size_t_68k chsize;
	int16_t rowwords;
	int numch;
	std::vector<uint16_t> charBMP;

	void parsefnt();
public:
	~RAWfnt();

	int16_t width,height;
	int16_t ascent,descent;
	void setactivefont(offset_68k location);
	gchar getIMG(unsigned char chnum);
	uint16_t getpixel(int16_t x,int16_t y);
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
	offset_68k m68kptr;
	bool inm68kaddrspace = false;
	bool readonly = false;
	offset_68k custompalette = 0;
	uint8_t* orgdat;
	std::vector<uint16_t> purifieddata;

	//stats
	uint8_t datatype,typeversion;
	uint8_t compression = BitmapCompressionTypeNone;

	void from68k(offset_68k m68kaddr, uint8_t type, int16_t datawidth, int16_t dataheight, uint8_t bpp, bool leaveinplace);

	void get1bitpixelarr();
	void get2bitpixelarr();
	void get4bitpixelarr();
	void get8bitpixelarr();
	uint16_t mypalettecolor(uint8_t index);

public:
	//stats
	int width = 0,height = 0;
	uint8_t pixelsize = 0;
	bool hastransparent = false;
	uint16_t transparent = 0x0000;
	size_t_68k totalsize;
	uint16_t rowbytes;

	//for width and bpp findme means get from wrapper
	RAWimg(offset_68k m68kaddr, uint8_t type);
	RAWimg(offset_68k m68kaddr, uint8_t type, int16_t datawidth, int16_t dataheight, uint8_t bpp, bool leaveinplace);
	~RAWimg();

	uint16_t getpixel(int16_t x,int16_t y);
	void setpixel(int16_t x,int16_t y,uint16_t color);

private:
	void tobuff();
};

class FBWriter{
private:
	uint16_t* test;//hack
	offset_68k location;
	uint16_t rowbytes;
	int16_t width;
	uint8_t pixelsize;

public:
	FBWriter(offset_68k addr, uint16_t buffwidth, uint8_t bpp);

	uint16_t getpixel(int16_t x,int16_t y);
	void setpixel(int16_t x,int16_t y,uint16_t color);
	void line(int16_t x, int16_t y, int16_t x2, int16_t y2, int prams, uint16_t color);
	void rect(int16_t x, int16_t y, int16_t w, int16_t h, int prams, uint16_t color, uint16_t round);
	void copyrect(RAWimg& host, int16_t startx, int16_t starty, int16_t rectw, int16_t recth, int16_t outx, int16_t outy);
	void draw(RAWimg& smlimg, int16_t x, int16_t y);
	void draw(char letter, RAWfnt& chrimgs, int16_t x, int16_t y);
	bool draw5x7(int16_t x, int16_t y, uint16_t color, char letter);//hack //remove this
};

//image type creation
offset_68k newbmp(int16_t width,int16_t height,uint8_t bpp,bool hasclearcol,uint8_t clearcolindex,bool hascoltable,offset_68k coltable);
offset_68k newdrawstate();
offset_68k newwindow(int16_t width,int16_t height,uint16_t flags,uint16_t frameflags,offset_68k winbmp,offset_68k drawstate,offset_68k nextwindowptr);
void initformwindow(offset_68k thiswindow,int16_t width,int16_t height,uint16_t flags,uint16_t frameflags,offset_68k winbmp,offset_68k drawstate,offset_68k nextwindowptr);

inline offset_68k newbmpsimple(int16_t width,int16_t height,uint8_t bpp){
	return newbmp(width,height,bpp,false,0,false,0);
}



//compression

//form
extern uint16_t frmid;
offset_68k decompressform(uint16_t id);
void releaseformmemory(offset_68k frmptr);

//bitmap
uint8_t* scanline(offset_68k addr, int16_t width, int16_t height, uint16_t rowbytes);
uint8_t* RLE(offset_68k addr,int16_t width,int16_t height,uint16_t rowbytes);
uint8_t* PackBits(offset_68k addr,int16_t width,int16_t height,uint16_t rowbytes);
#endif // RAWIMAGETOOLS

