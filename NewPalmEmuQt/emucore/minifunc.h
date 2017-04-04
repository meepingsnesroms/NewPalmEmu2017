#ifndef MINIFUNC
#define MINIFUNC

#include "types.h"


//this should be moved to the files that need it
#include "dbgmacros.h"


//meaningful words
#define UNDEFINED 0
#define ISSPECIAL(x) ((x) > 0xFFFFFF00)
#define INTERCEPT 0xFFFFFFFF



//this needs to go
#define inc_for(var,cmp) for(var = 0;var < cmp;var++)



//basic functions
#define IS_EVEN(x)		(((x) & 1) == 0)
#define IS_ODD(x)		(((x) & 1) == 1)
#define nextboundry(x)	(((x) + 1) & ~0x1)
#define bit(x)			(1 << (x))

inline long smallest(long val1,long val2){
	return val1 < val2 ? val1 : val2;
}

inline long largest(long val1,long val2){
	return val1 > val2 ? val1 : val2;
}

inline long absdiffrence(long var1,long var2){
	return largest(var1,var2) - smallest(var1,var2);
}

#endif
