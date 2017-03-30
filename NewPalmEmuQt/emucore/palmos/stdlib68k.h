#ifndef STDLIB68K
#define STDLIB68K

#include "m68k.h"

void memcpy68k(CPTR dest,CPTR src,size_t_68k size);
void memset68k(CPTR dest, UBYTE value, size_t_68k size);
WORD memcmp68k(CPTR ptr1,CPTR ptr2,size_t_68k size);
//WORD strcmp68k(CPTR ptr1,CPTR ptr2,size_t_68k size);
UWORD strlen68k(CPTR strptr);

#endif // STDLIB68K

