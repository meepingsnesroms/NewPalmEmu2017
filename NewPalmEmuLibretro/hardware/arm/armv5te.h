#ifndef ARMV5TE
#define ARMV5TE

#include "types.h"
#include "arm7.h"

extern ARM7 armcpu;

extern bool inARM;

#define ARMSTACK 13
#define ARMPC 15
//#define ARMSR 16

//hack
//make real stack
#define ARMSTACKBEGIN 0x1000

inline uint32 getpcARM(){return armcpu.reg.r15;}

void pushstackARM(uint32 stackval);
uint32 popstackARM();

inline void setregARM(uint8 reg,uint32 val){armcpu.set_reg(reg,val);}
inline uint32 getregARM(uint8 reg){return armcpu.get_reg(reg);}

void initARM();
void callARM(uint32 function);

#endif // ARMV5TE

