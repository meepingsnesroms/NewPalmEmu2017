#ifndef IMAGESCALING_H
#define IMAGESCALING_H

#include "m68k.h"

void setimageparams(int width_L,int height_L,int imagebpp_L);
//void setpalette(uint8_t**); //HACK cant read palette correctly right now
void setpalette68k(offset_68k newpalette);
void upscaleimage(uint8_t* inptr,uint16_t* outptr);
void upscaleimagein68k(offset_68k m68kin,offset_68k m68kout);
void expand2x(uint16_t* input,uint16_t* output,int orgwidth,int orgheight);

#endif // IMAGESCALING_H
