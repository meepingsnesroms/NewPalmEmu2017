#ifndef STDLIB68K
#define STDLIB68K

#include "m68k.h"

void memcpy68k(offset_68k dest,offset_68k src,size_t_68k size);
void memset68k(offset_68k dest, uint8_t value, size_t_68k size);
WORD memcmp68k(offset_68k ptr1,offset_68k ptr2,size_t_68k size);
//WORD strcmp68k(offset_68k ptr1,offset_68k ptr2,size_t_68k size);
uint16_t strlen68k(offset_68k strptr);

#endif // STDLIB68K

