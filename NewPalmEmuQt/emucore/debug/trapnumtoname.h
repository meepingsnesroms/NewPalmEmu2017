#ifndef TRAPNUMTONAME_H
#define TRAPNUMTONAME_H

#include "m68k.h"

const char *lookup_trap(uint16_t opcode);

#endif // TRAPNUMTONAME_H
