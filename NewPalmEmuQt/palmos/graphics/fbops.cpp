/*
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
*/

#include "m68k.h"
#include "minifunc.h"
#include "fbops.h"

#include <stdlib.h> //needed for abs()

//HACK use memcpy for better performance

//the active framebuffers data and info
UWORD* FB_data;
int FB_width,FB_height;
int FB_linethickness;

//the bitmap to copy from if doing a bitmap operation
UWORD* FB_bitmapdata;
int FB_bitmapwidth,FB_bitmapheight;
int FB_bitmaptransparentcolor;//-1 for none

/*
//macros to read and write pixel data
#define FB_pixel(x,y) (FB_data[(y) * FB_width + (x)])
#define FB_bitmappixel(x,y) (FB_bitmapdata[(y) * FB_bitmapwidth + (x)])

#define FB_getpixel(x,y) FB_pixel((x),(y))
#define FB_setpixel(x,y,color) FB_pixel((x),(y)) = (color)
*/



void FB_line(int x,int y,int x2,int y2,UWORD color){
	//taken from rosetta code
	int dx = abs(x2 - x), sx = x < x2 ? 1 : -1;
	int dy = abs(y2 - y), sy = y < y2 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	while(true){
		FB_setpixel(x,y,color);
		if(x == x2 && y == y2) break;
		e2 = err;
		if(e2 > -dx){ err -= dy; x += sx; }
		if(e2 < dy){ err += dx; y += sy; }
	}
}

void FB_rect(int x,int y,int w,int h,UWORD color){
	FB_line(x,y,x,y + h,color);
	FB_line(x,y,x + w,y,color);
	FB_line(x + w,y,x + w,y + h,color);
	FB_line(x,y + h,x + w,y + h,color);
}

void FB_fillrect(int x,int y,int w,int h,UWORD color){
	int wcnt,hcnt;
	inc_for(hcnt,h){
		inc_for(wcnt,w){
			FB_setpixel(x + wcnt,y + hcnt,color);
		}
	}
}

void FB_copyrect(int x,int y,int w,int h,int fromx,int fromy){
	int wcnt,hcnt;
	inc_for(hcnt,h){
		inc_for(wcnt,w){
			//this function has no regard for transparency,for that use FB_drawbitmap instead
			FB_pixel(x + wcnt,y + hcnt) = FB_bitmappixel(fromx + wcnt,fromy + hcnt);
		}
	}
}

//this function just copys the raw bitmap data into the framebuffer(it ignores transparency)
void FB_copybitmap(int x,int y){
	int wcnt,hcnt;
	//dont check for transparency
	inc_for(hcnt,FB_bitmapheight){
		inc_for(wcnt,FB_bitmapwidth){
			FB_pixel(x + wcnt,y + hcnt) = FB_bitmappixel(wcnt,hcnt);
		}
	}
}

void FB_drawbitmap(int x,int y){
	int wcnt,hcnt;
	if(FB_bitmaptransparentcolor != -1){
		//check for transparency
		UWORD currentcolor;
		inc_for(hcnt,FB_bitmapheight){
			inc_for(wcnt,FB_bitmapwidth){
				currentcolor = FB_bitmappixel(wcnt,hcnt);
				if(currentcolor != FB_bitmaptransparentcolor)FB_pixel(x + wcnt,y + hcnt) = currentcolor;
			}
		}
	}
	else FB_copybitmap(x,y);//just copy raw data
}
