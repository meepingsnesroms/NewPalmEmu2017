#ifndef DBGMACROS
#define DBGMACROS

#include <stdio.h>//for printf

#ifdef _DBGMODE
#define DEBUG(x) x
#define dbgprintf	printf
#else
#define DEBUG(x)
#define dbgprintf(x,...)
#endif

#define TEMPHACK

#endif
