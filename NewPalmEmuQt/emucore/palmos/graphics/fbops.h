#ifndef FBOPS_H
#define FBOPS_H
#include "m68k.h"

//the active framebuffers data and info
extern uint16_t* FB_data;
extern int FB_width,FB_height;
extern int FB_linethickness;

//the bitmap to copy from if doing a bitmap operation
extern uint16_t* FB_bitmapdata;
extern int FB_bitmapwidth,FB_bitmapheight;
extern int FB_bitmaptransparentcolor;//-1 for none

//macros to read and write pixel data
#define FB_pixel(x,y) (FB_data[(y) * FB_width + (x)])
#define FB_bitmappixel(x,y) (FB_bitmapdata[(y) * FB_bitmapwidth + (x)])

#define FB_getpixel(x,y) FB_pixel((x),(y))
#define FB_setpixel(x,y,color) FB_pixel((x),(y)) = (color)

void FB_line(int x,int y,int x2,int y2,uint16_t color);

void FB_rect(int x,int y,int w,int h,uint16_t color);

void FB_fillrect(int x,int y,int w,int h,uint16_t color);

void FB_copyrect(int x,int y,int w,int h,int fromx,int fromy);

//this function just copys the raw bitmap data into the framebuffer(it ignores transparency)
void FB_copybitmap(int x,int y);

//works with transparency
void FB_drawbitmap(int x,int y);

#endif // FBOPS_H
