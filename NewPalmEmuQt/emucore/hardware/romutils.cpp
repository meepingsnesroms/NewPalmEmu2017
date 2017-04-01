#include <stdint.h>
#include "memmap.h"

static bool rom_writes_unlocked = false;
UWORD* rommemory = nullptr;
uint32_t rom_size = 0;


/* ROM */
ULONG rom_lget(CPTR addr)
{
	addr -= rom_start;
	return (((ULONG)rommemory[addr >> 1]) << 16) | rommemory[(addr >> 1) + 1];
}

UWORD rom_wget(CPTR addr)
{
	addr -= rom_start;
	return rommemory[addr >> 1];
}

UBYTE rom_bget(CPTR addr)
{
	addr -= rom_start;
	if(addr & 1)return rommemory[addr >> 1];
	else return rommemory[addr >> 1] >> 8;
}

void rom_lput(CPTR addr, ULONG l)
{
	if(!rom_writes_unlocked)return;

	addr -= rom_start;
	rommemory[addr >> 1] = l >> 16;
	rommemory[(addr >> 1) + 1] = (UWORD)l;
}

void rom_wput(CPTR addr, UWORD w)
{
	if(!rom_writes_unlocked)return;

	addr -= rom_start;
	rommemory[addr >> 1] = w;
}

void rom_bput(CPTR addr, UBYTE b)
{
	if(!rom_writes_unlocked)return;

	addr -= rom_start;
	if (!(addr & 1)) {
		rommemory[addr >> 1] = (rommemory[addr>>1] & 0xFF) | (((UWORD)b) << 8);
	} else {
		rommemory[addr >> 1] = (rommemory[addr >> 1] & 0xFF00) | b;
	}
}

int rom_check(CPTR addr, ULONG size)
{
	addr -= rom_start;
	return (addr + size) <= (ULONG)rom_size;
}

UWORD *rom_xlate(CPTR addr)
{
	addr -= rom_start;
	return rommemory + (addr >> 1);
}

addrbank rom_bank = {
    rom_lget, rom_wget, rom_bget,
    rom_lput, rom_wput, rom_bput,
    rom_xlate, rom_check
};

void install_rom_to_memory(uint8_t* romdata,uint32_t size){
	rom_size = size;
	rommemory = new UWORD[size / 2 + 1];

	rom_writes_unlocked = true;
	for(uint32_t count = 0;count < size;count++){
		put_byte(rom_start + count, romdata[count]);
	}
	rom_writes_unlocked = false;
}

void clear_rommemory(){
	delete[] rommemory;
}

