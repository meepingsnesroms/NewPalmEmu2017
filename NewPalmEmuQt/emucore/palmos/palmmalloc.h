#ifndef PALMMALLOC
#define PALMMALLOC

#include "m68k.h"

//get/set current memory state
void resetmallocstate();
size_t_68k avheapmem();
size_t_68k avlinearheapmem();


//acquire memory
offset_68k getfreestorageram(size_t_68k bytes);
offset_68k getfreeheap(size_t_68k bytes);

//free relesed memory
void quickclean();
void clensememory();

bool		freememaddr(offset_68k addr);
uint32_t	getsizememaddr(offset_68k addr);
int			memisalloc(offset_68k address);
#endif // PALMMALLOC

