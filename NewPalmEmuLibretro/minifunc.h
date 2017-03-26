#ifndef MINIFUNC
#define MINIFUNC

#include "types.h"

/*
#define TEMPHACK _Pragma("message \"This is a hack, it works but not correctly!\n\"")

#define STUCK _Pragma("message \"Stuck here wait for more information.\n\"")
*/

#ifdef _GLIBCXX_HAVE_BROKEN_VSWPRINTF

#endif

#ifdef _DBGMODE
#define DEBUG(x) x
#define dbgprintf	printf
#else
#define DEBUG(x)
#define dbgprintf(x,...) //(0)
#endif

#define TEMPHACK
#define STUCK

//meaningful words
#define findme 0
#define notrequired 0
#define ISSPECIAL(x) ((x) > 0xFFFFFF00)
#define INTERCEPT 0xFFFFFFFF


//basic misc functions
//hack //multithread this
#define async_for(var,start,end) for(var = 0;var < cmp;var++)

#define inc_for(var,cmp) for(var = 0;var < cmp;var++)

#define dec_for(var,cmp) for(var = 0;var > cmp;var--)

#define for_2D(x,y,w,h) for(y = 0;y < h;y++)\
	for(x = 0;x < w;x++)

#define nextboundry(x) (((x) + 1) & ~0x1)

#define check_addr(x) (((x) & 1) == 0)

#define bit(x) (1 << (x))

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
