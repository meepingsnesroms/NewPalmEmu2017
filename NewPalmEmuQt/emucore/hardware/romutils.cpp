#include <stdint.h>
#include "memmap.h"

static const offset_68k rom_start =  0x10000000;

static bool rom_loaded = false;
static bool rom_writes_unlocked = false;
static uint16_t* rommemory = nullptr;
static uint32_t rom_size = 0;


/* ROM */
uint32_t rom_lget(offset_68k addr)
{
	addr -= rom_start;
	return (((uint32_t)rommemory[addr >> 1]) << 16) | rommemory[(addr >> 1) + 1];
}

uint16_t rom_wget(offset_68k addr)
{
	addr -= rom_start;
	return rommemory[addr >> 1];
}

uint8_t rom_bget(offset_68k addr)
{
	addr -= rom_start;
	if(addr & 1)return rommemory[addr >> 1];
	else return rommemory[addr >> 1] >> 8;
}

void rom_lput(offset_68k addr, uint32_t l)
{
	if(!rom_writes_unlocked)return;

	addr -= rom_start;
	rommemory[addr >> 1] = l >> 16;
	rommemory[(addr >> 1) + 1] = (uint16_t)l;
}

void rom_wput(offset_68k addr, uint16_t w)
{
	if(!rom_writes_unlocked)return;

	addr -= rom_start;
	rommemory[addr >> 1] = w;
}

void rom_bput(offset_68k addr, uint8_t b)
{
	if(!rom_writes_unlocked)return;

	addr -= rom_start;
	if (!(addr & 1)) {
		rommemory[addr >> 1] = (rommemory[addr>>1] & 0xFF) | (((uint16_t)b) << 8);
	} else {
		rommemory[addr >> 1] = (rommemory[addr >> 1] & 0xFF00) | b;
	}
}

int rom_check(offset_68k addr, uint32_t size)
{
	addr -= rom_start;
	return (addr + size) <= (uint32_t)rom_size;
}

uint16_t *rom_xlate(offset_68k addr)
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
	rommemory = new uint16_t[size / 2 + 1];

	map_banks(rom_bank, rom_start >> 16, NUM_BANKS(size));

	rom_writes_unlocked = true;
	for(uint32_t count = 0;count < size;count++){
		put_byte(rom_start + count, romdata[count]);
	}
	rom_writes_unlocked = false;

	rom_loaded = true;
}

bool rom_active(){
	return rom_loaded;
}

void clear_rommemory(){
	if(rom_loaded){
		delete[] rommemory;
		rom_loaded = false;
	}
}

