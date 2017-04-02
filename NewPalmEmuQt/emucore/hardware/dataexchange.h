#ifndef DATAEXCHANGE
#define DATAEXCHANGE

#include "m68k.h"
#include "newcpu.h"
#include "minifunc.h"
#include "types.h"
#include <string>

#ifndef BIGENDIAN

#define beword(x) (((x) >> 8 & 0xFF) | ((x) << 8 & 0xFF00))
#define belong(x) (beword((x) >> 16) | beword((x)) << 16)
#define swapword(x) x = beword(x)
#define swaplong(x) x = belong(x)

#else

#define beword(x)	(x)
#define belong(x)	(x)
#define swapword(x)
#define swaplong(x)

#endif

inline float32_t rawfloat32_t(uint32_t data){return *((float32_t*)&(data));}
inline double64_t rawdouble64_t(uint64_t data){return *((double64_t*)&(data));}
inline uint32_t float32_ttoraw(float32_t data){return *((uint32_t*)&(data));}
inline uint64_t double64_ttoraw(double64_t data){return *((uint64_t*)&(data));}



#define putbyteifvptr(x,y) if((x))put_byte((x),(y))
#define putwordifvptr(x,y) if((x))put_word((x),(y))
#define putlongifvptr(x,y) if((x))put_long((x),(y))

//x == ptr,y == value to set
#define settbyteifvptr(x,y) if((x))y = get_byte((x))
#define setwordifvptr(x,y) if((x))y = get_word((x))
#define setlongifvptr(x,y) if((x))y = get_long((x))


void readbytearray(CPTR loc, UBYTE *dest, size_t_68k size);
void writebytearray(CPTR loc, UBYTE *start, size_t_68k size);
std::string readstring(CPTR loc);
void writestring(CPTR loc,const std::string& str,size_t_68k forcelength = 0);


#define LINK(x) (emulink = (x))
#define UNLINK(x) ((x) = emulink)

#define stackbool(x) bool x = ((popwordlink() >> 8) != 0)
#define stackbyte(x) UBYTE x = (popwordlink() >> 8)
#define stackword(x) UWORD x = popwordlink()
#define stacklong(x) ULONG x = poplonglink()

#define stacklong64(x) uint64_t x;{ULONG tmp1 = poplonglink();\
	ULONG tmp2 = poplonglink();x = (uint64_t)tmp1 << 32 | tmp2;}

#define stackptr(x) CPTR x = poplonglink()

#define stackskip(type) emulink += sizeof(type)
//#define stackskip(bytes) emulink += (bytes)


//when returning values > the size of one m68k register
//palm os pushes them onto the stack and sets A0 to the
//previous stack pointer.

/*
typedef struct{
	Int32 high;
	Int32 low;
} _sfpe_64_bits;
*/

//Bytes are in order 76543210
//7 is the highest 0 is the lowest


TEMPHACK
//find endian of 64bit values
inline void return64(CPTR retptr,uint64_t val){
	/*
	A0 = SP;
	CPU_pushlongstack((ULONG)val);
	CPU_pushlongstack((ULONG)(val >> 32))
	*/
	put_long(retptr,(ULONG)(val >> 32));
	put_long(retptr + 4,(ULONG)val);
	return;
}


extern CPTR emulink;

void pushlonglink(ULONG val);
ULONG poplonglink();
void pushwordlink(UWORD val);
UWORD popwordlink();
void pushbytelink(UBYTE val);
UBYTE popbytelink();

#endif // DATAEXCHANGE

