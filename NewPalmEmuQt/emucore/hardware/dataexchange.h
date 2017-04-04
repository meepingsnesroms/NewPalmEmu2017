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


void readbytearray(offset_68k loc, uint8_t *dest, size_t_68k size);
void writebytearray(offset_68k loc, uint8_t *start, size_t_68k size);
std::string readstring(offset_68k loc);
void writestring(offset_68k loc,const std::string& str,size_t_68k forcelength = 0);


#define LINK(x) (emulink = (x))
#define UNLINK(x) ((x) = emulink)

#define stackbool(x) bool x = ((popwordlink() >> 8) != 0)
#define stackbyte(x) uint8_t x = (popwordlink() >> 8)
#define stackword(x) uint16_t x = popwordlink()
#define stacklong(x) uint32_t x = poplonglink()

#define stacklong64(x) uint64_t x;{uint32_t tmp1 = poplonglink();\
	uint32_t tmp2 = poplonglink();x = (uint64_t)tmp1 << 32 | tmp2;}

#define stackptr(x) offset_68k x = poplonglink()

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
inline void return64(offset_68k retptr,uint64_t val){
	/*
	A0 = SP;
	CPU_pushlongstack((uint32_t)val);
	CPU_pushlongstack((uint32_t)(val >> 32))
	*/
	put_long(retptr,(uint32_t)(val >> 32));
	put_long(retptr + 4,(uint32_t)val);
	return;
}


extern offset_68k emulink;

void pushlonglink(uint32_t val);
uint32_t poplonglink();
void pushwordlink(uint16_t val);
uint16_t popwordlink();
void pushbytelink(uint8_t val);
uint8_t popbytelink();

#endif // DATAEXCHANGE

