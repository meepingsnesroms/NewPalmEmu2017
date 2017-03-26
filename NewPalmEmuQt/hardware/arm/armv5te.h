#ifndef ARMV5TE
#define ARMV5TE

#include "CPU.h"
#include "types.h"

extern bool inARM;

#define ARMSTACK 13
#define ARMLR 14
#define ARMPC 15
#define ARMSR 16

//hack
//make real stack
#define ARMSTACKBEGIN 0x1000

//void pushstackARM(uint32 stackval);
//uint32 popstackARM();

void setregARM(uint8 reg,uint32 val);
uint32 getregARM(uint8 reg);

void initARM();
void callARM(uint32 function);

#endif // ARMV5TE

