#ifndef IMAGESCALING_H
#define IMAGESCALING_H

#include "m68k.h"

void setimageparams(int width_L,int height_L,int imagebpp_L);
//void setpalette(UBYTE**); //HACK cant read palette correctly right now
void setpalette68k(CPTR newpalette);
void upscaleimage(UBYTE* inptr,UWORD* outptr);
void upscaleimagein68k(CPTR m68kin,CPTR m68kout);
void expand2x(UWORD* input,UWORD* output,int orgwidth,int orgheight);

#endif // IMAGESCALING_H
