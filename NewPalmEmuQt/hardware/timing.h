#ifndef TIMING
#define TIMING

#include "types.h"

//1 cycle = 1 opcode (this is not true for all cpus but is for this emulator)

//sleep or yield every * opcodes so the host cpu is not overloaded
//(this would slow down the emulator way worse)

void resetcycles();
void cycle();
void simulatecycles(uint32 amount);
void freecycles();

#endif // TIMING

