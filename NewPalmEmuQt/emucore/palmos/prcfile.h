#ifndef PRCFILE
#define PRCFILE

#include "m68k.h"
#include <string>

//err codes
enum{
	WORKED = 0,
	BROKENSTAT = 1,
	TOOLARGE = 2,
	LOCKEDFILE = 3,
	FAILEDMALLOC = 4,
	NOTPALMFILE = 5
};

//internal functions
void printprcerror(offset_68k pc);

//user functions
int loadfiletopalm(std::string path);
void releasefilemem();

#endif // PRCFILE

