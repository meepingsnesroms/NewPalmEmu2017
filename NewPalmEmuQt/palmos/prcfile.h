#ifndef PRCFILE
#define PRCFILE

#include "m68k.h"
#include <string>

using namespace std;

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
void printprcerror(CPTR pc);

//user functions
int loadfiletopalm(string path);
void releasefilemem();

#endif // PRCFILE

