#ifndef ROMUTILS_H
#define ROMUTILS_H

#include "memmap.h"

void install_rom_to_memory(uint8_t* romdata,uint32_t size);
bool rom_active();
void clear_rommemory();//must be called when finished to prevent memory leaks

#endif // ROMUTILS_H
