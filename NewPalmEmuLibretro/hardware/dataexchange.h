#ifndef DATAEXCHANGE
#define DATAEXCHANGE

#include "m68k.h"
#include "newcpu.h"
#include "minifunc.h"
#include "types.h"
#include <string>

using std::string;//HACK //this should be universal(possibly in "types.h")

#define UNIVERSAL

#ifdef FASTASM

//hardware endian swap

#else

#define beword(x) (((x) >> 8 & 0xFF) | ((x) << 8 & 0xFF00))
#define belong(x) (beword((x) >> 16) | beword((x)) << 16)

#endif

inline float32 rawfloat32(uint32 data){return *((float32*)&(data));}
inline double64 rawdouble64(uint64 data){return *((double64*)&(data));}
inline uint32 float32toraw(float32 data){return *((uint32*)&(data));}
inline uint64 double64toraw(double64 data){return *((uint64*)&(data));}

#define swapword(x) x = beword(x)
#define swaplong(x) x = belong(x)

#define putbyteifvptr(x,y) if((x))put_byte((x),(y))
#define putwordifvptr(x,y) if((x))put_word((x),(y))
#define putlongifvptr(x,y) if((x))put_long((x),(y))

//x == ptr,y == value to set
#define settbyteifvptr(x,y) if((x))y = get_byte((x))
#define setwordifvptr(x,y) if((x))y = get_word((x))
#define setlongifvptr(x,y) if((x))y = get_long((x))

//HACK retain compatibility with functions that use m68kstr
#define m68kstr(x) readstring(x)
//std::string m68kstr(CPTR strptr);

void membyteswap(UBYTE *start, size_t_68k size);

void readbytearray(CPTR loc, UBYTE *dest, size_t_68k size);
void writebytearray(CPTR loc, UBYTE *start, size_t_68k size);
string readstring(CPTR loc);
void writestring(CPTR loc,const string& str,size_t_68k forcelength = 0);



#define LINK(x) (emulink = (x))
#define UNLINK(x) ((x) = emulink)

#define stackbool(x) bool x = ((popwordlink() >> 8) != 0)
#define stackbyte(x) UBYTE x = (popwordlink() >> 8)
#define stackword(x) UWORD x = popwordlink()
#define stacklong(x) ULONG x = poplonglink()

#define stacklong64(x) uint64 x;{ULONG tmp1 = poplonglink();\
	ULONG tmp2 = poplonglink();x = (uint64)tmp1 << 32 | tmp2;}

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
inline void return64(CPTR retptr,uint64 val){
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

