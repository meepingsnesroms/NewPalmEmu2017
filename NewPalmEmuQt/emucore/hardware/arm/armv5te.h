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

void setregARM(uint8_t reg,uint32_t val);
uint32_t getregARM(uint8_t reg);

void initARM();
void callARM(uint32_t function);

#endif // ARMV5TE

