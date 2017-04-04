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

offset_68k getfreeheaphandle(size_t_68k bytes);
offset_68k getfreestorageramhandle(size_t_68k bytes);


bool ishandle(int index);
bool islocked(int index);

void quickclean();

bool lockmemaddr(offset_68k addr, bool handle);
bool unlockmemaddr(offset_68k addr, bool handle);
bool freememaddr(offset_68k addr,bool handle);
uint32_t getsizememaddr(offset_68k addr,bool handle);

bool abstractlock(offset_68k addr);
bool abstractunlock(offset_68k addr);
bool abstractfree(offset_68k addr);
uint32_t abstractgetsize(offset_68k addr);


void clensememory();
int memisalloc(offset_68k address);
#endif // PALMMALLOC

