#ifndef PALMMALLOC
#define PALMMALLOC

#include "m68k.h"

//get/set current memory state
void resetmallocstate();
void clearmalloclist();
size_t_68k avheapmem();
size_t_68k avlinearheapmem();


//acquire memory
CPTR getfreestorageram(size_t_68k bytes);
CPTR getfreeheap(size_t_68k bytes);

CPTR getfreeheaphandle(size_t_68k bytes);
CPTR getfreestorageramhandle(size_t_68k bytes);


bool ishandle(int index);
bool islocked(int index);

void quickclean();

bool lockmemaddr(CPTR addr, bool handle);
bool unlockmemaddr(CPTR addr, bool handle);
bool freememaddr(CPTR addr,bool handle);
ULONG getsizememaddr(CPTR addr,bool handle);

bool abstractlock(CPTR addr);
bool abstractunlock(CPTR addr);
bool abstractfree(CPTR addr);
ULONG abstractgetsize(CPTR addr);


void clensememory();
int memisalloc(CPTR address);
#endif // PALMMALLOC

