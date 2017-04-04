//taken from xcopilot
#include "m68k.h"
#include "armv5te.h"
#include "memmap.h"
#include "newcpu.h"
#include "virtuallcd.h"

#include "minifunc.h" //hack //separate 68k from palm

#include "palmwrapper.h" //hack //separate 68k from palm

#include "prcfile.h"

char* archs[3] = {"Thumb","ARM","m68k"};

char* datalengths[3] = {"BYTE","WORD","LONG"};

enum{
	BYTESIZE,
	WORDSIZE,
	LONGSIZE
};

void invalidaccess(CPTR addr,bool writing,int length){
	int arch = 2;
	/*
	if(inARM){
		if(armcpu.arm_mode == ARM7::THUMB)arch = 0;
		else arch = 1;
	}
	*/

	dbgprintf("Bus error: %s %s at undefined memory address 0x%08x\n",writing ? "READ" : "WRITE",datalengths[length],addr);
	dbgprintf("Current Arch:%s\n", archs[arch]);
	dbgprintf("m68k PC=0x%08x,ARM PC=0x%08x\n", MC68000_getpc(),getregARM(ARMPC));
}

int buserr = 0;

UWORD* dynallocedchunkptrs[TOTALBANKS];
UBYTE avchunks[TOTALBANKS];

UWORD* rammemory;
UWORD  dballregs[SIZEOFBANK / sizeof(UWORD)];

uint32_t ram_size;
extern shared_img* Shptr;
extern int exectrace;

addrbank* membanks;

enum{
	notused,
	used,
	usedmustfree
};

UWORD getnewlinearchunks(UWORD needed){
	if(needed == 0)return 0;

	int i;
	int j;

	int count = 0;
	for(i = BANKINDEX(dyn_start);i < BANKINDEX(lcd_start);i++){
		if(avchunks[i] == notused)count++;
		else count = 0;
		if(count == needed)break;
	}

	//theres no palm address space left
	if(i == BANKINDEX(lcd_start) - 1)palmabrt();

	//return i to starting bank now that we know it can provide the banks requested
	i -= (needed - 1);//change starting point from 1 to 0 based

	UWORD* realaddr = new UWORD[SIZEOFBANK / 2 * needed];
	if(realaddr == nullptr){
		palmabrt();
		return 0;
	}

	map_banks(dyn_bank, i, needed);

	avchunks[i] = usedmustfree;

	for(j = i + 1;j < i + needed;j++){
		avchunks[j] = used;
	}

	for(j = i;j < i + needed;j++){
		//dbgprintf("Bank %04x is allocated at %p!\n",j,realaddr);
		dynallocedchunkptrs[j] = realaddr;
		realaddr = (UWORD*)((UBYTE*)realaddr + SIZEOFBANK);
	}
	dbgprintf("Banks wanted:%d,Ptr:%04x\n",needed,i);
	return i;
}

void freedynchunk(int chunk){
	if(avchunks[chunk] == usedmustfree)delete[] dynallocedchunkptrs[chunk];
	avchunks[chunk] = notused;
}

void freedynchunks(){
	for(int i = 0;i < TOTALBANKS;i++){
		freedynchunk(i);
	}
}

/* Default memory access functions */
int default_check(CPTR, ULONG)
{
    return 0;
}

UWORD* default_xlate(CPTR)
{
	return nullptr;
}


/* A dummy bank that only contains zeros */
ULONG dummy_lget(CPTR addr)
{
	dbgprintf("Bus error: read a long from undefined memory address 0x%08x\n",addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
    buserr = 1;
	palmabrt();//hack
    return 0;
}

UWORD dummy_wget(CPTR addr)
{
	dbgprintf("Bus error: read a word from undefined memory address 0x%08x\n",addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
	buserr = 1;
	palmabrt();//hack
    return 0;
}

UBYTE dummy_bget(CPTR addr)
{
	dbgprintf("Bus error: read a byte from undefined memory address 0x%08x\n",addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
    buserr = 1;
	palmabrt();//hack
    return 0;
}

void dummy_lput(CPTR addr, ULONG)
{
	dbgprintf("Bus error: wrote a long to undefined memory address 0x%08x\n",addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
    buserr = 1;
	palmabrt();//hack
}

void dummy_wput(CPTR addr, UWORD)
{
	dbgprintf("Bus error: wrote a word to undefined memory address 0x%08x\n",addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
	buserr = 1;
	palmabrt();//hack
}

void dummy_bput(CPTR addr, UBYTE)
{
	dbgprintf("Bus error: wrote a byte to undefined memory address 0x%08x\n",addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
    buserr = 1;
	palmabrt();//hack
}

int dummy_check(CPTR, ULONG)
{
    return 0;
}

UWORD* dummy_xlate(CPTR)
{
	dbgprintf("uhhg");
	return nullptr;
}


/* RAM */
ULONG ram_lget(CPTR addr)
{
	addr -= ram_start;
	return (((ULONG)rammemory[addr >> 1]) << 16) | rammemory[(addr >> 1) + 1];
}

UWORD ram_wget(CPTR addr)
{
	addr -= ram_start;
    return rammemory[addr >> 1];
}

UBYTE ram_bget(CPTR addr)
{
	addr -= ram_start;
	if(addr & 1)return rammemory[addr >> 1];
	else return rammemory[addr >> 1] >> 8;
}

void ram_lput(CPTR addr, ULONG l)
{
	addr -= ram_start;
    rammemory[addr >> 1] = l >> 16;
	rammemory[(addr >> 1) + 1] = (UWORD)l;
}

void ram_wput(CPTR addr, UWORD w)
{
	addr -= ram_start;
    rammemory[addr >> 1] = w;
}

void ram_bput(CPTR addr, UBYTE b)
{
	addr -= ram_start;
	if (!(addr & 1)) {
		rammemory[addr >> 1] = (rammemory[addr>>1] & 0xFF) | (((UWORD)b) << 8);
    } else {
		rammemory[addr >> 1] = (rammemory[addr >> 1] & 0xFF00) | b;
    }
}

int ram_check(CPTR addr, ULONG size)
{
	addr -= ram_start;
    return (addr + size) <= (ULONG)ram_size;
}

UWORD* ram_xlate(CPTR addr)
{
	addr -= ram_start;
    return rammemory + (addr >> 1);
}

ULONG dyn_lget(CPTR addr)
{
	//dbgprintf("DynBank:%16p,long addr:%08x\n",dynallocedchunkptrs[addr >> 16],addr);
	ULONG temp = ((ULONG)dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1]) << 16;
	return temp | dynallocedchunkptrs[addr >> 16][((addr & 0xFFFF) >> 1) + 1];
}

UWORD dyn_wget(CPTR addr)//(default format)
{
	return dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1];
}

UBYTE dyn_bget(CPTR addr)
{
	if(addr & 1)return dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1];
	return dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1] >> 8;
}

void dyn_lput(CPTR addr, ULONG l)
{
	dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1] = l >> 16;
	dynallocedchunkptrs[addr >> 16][((addr & 0xFFFF) >> 1) + 1] = (UWORD)l;
}

void dyn_wput(CPTR addr, UWORD w)//(default format)
{
	dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1] = w;
}

void dyn_bput(CPTR addr, UBYTE b)
{
	if (!(addr & 1)){
		dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1] = (dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1] & 0xFF) | (((UWORD)b) << 8);
	}
	else{
		dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1] = (dynallocedchunkptrs[addr >> 16][(addr & 0xFFFF) >> 1] & 0xFF00) | b;
	}
}

int dyn_check(CPTR addr, ULONG)
{
	if(dynallocedchunkptrs[addr >> 16] != 0)return 1;
	return 0;
}

UWORD* dyn_xlate(CPTR addr)
{
	return dynallocedchunkptrs[addr >> 16] + ((addr & 0xFFFF) >> 1);
}


/* Dragonball register area */
ULONG reg_lget(CPTR addr)
{
	addr &= 0xFFFF;
	return (((ULONG)dballregs[addr >> 1]) << 16) | dballregs[(addr >> 1) + 1];
}

UWORD reg_wget(CPTR addr)
{
	addr &= 0xFFFF;
	return dballregs[addr >> 1];
}

UBYTE reg_bget(CPTR addr)
{
	addr &= 0xFFFF;
	if(addr & 1)return dballregs[addr >> 1];
	else return dballregs[addr >> 1] >> 8;
}

void reg_lput(CPTR addr, ULONG l)
{
	addr &= 0xFFFF;
	dballregs[addr >> 1] = l >> 16;
	dballregs[(addr >> 1) + 1] = (UWORD)l;
}

void reg_wput(CPTR addr, UWORD w)
{
	addr &= 0xFFFF;
	dballregs[addr >> 1] = w;
}

void reg_bput(CPTR addr, UBYTE b)
{
	addr &= 0xFFFF;
	if (!(addr & 1)) {
		dballregs[addr >> 1] = (dballregs[addr>>1] & 0xFF) | (((UWORD)b) << 8);
	} else {
		dballregs[addr >> 1] = (dballregs[addr >> 1] & 0xFF00) | b;
	}
}

int reg_check(CPTR addr, ULONG size)
{
	addr &= 0xFFFF;
	return (addr + size) <= 0xFFFF;
}

UWORD* reg_xlate(CPTR addr)
{
	addr &= 0xFFFF;
	return dballregs + (addr >> 1);
}

/* Address banks */

addrbank dummy_bank = {
    dummy_lget, dummy_wget, dummy_bget,
    dummy_lput, dummy_wput, dummy_bput,
    dummy_xlate, dummy_check
};

addrbank ram_bank = {
    ram_lget, ram_wget, ram_bget,
    ram_lput, ram_wput, ram_bput,
    ram_xlate, ram_check
};

addrbank dyn_bank = {
	dyn_lget, dyn_wget, dyn_bget,
	dyn_lput, dyn_wput, dyn_bput,
	dyn_xlate, dyn_check
};

addrbank reg_bank = {
    reg_lget, reg_wget, reg_bget,
    reg_lput, reg_wput, reg_bput,
    reg_xlate, reg_check
};

void map_banks(addrbank bank, uint32_t start, uint32_t size)
{
	//must use uint32_t because start+size can overflow a uint16_t
	for (uint32_t bnr = start; bnr < start+size; bnr++)
       membanks[bnr] = bank;
}



int memory_init(){
	buserr = 0;

	//ram
	ram_size = (SIZEOFBANK / 2) * 0x100;
	rammemory = new UWORD[ram_size];

	//banks
	membanks = new addrbank[0xFFFF];
	for(offset_68k fluff = 0;fluff < TOTALBANKS;fluff++){
		avchunks[fluff] = notused;
		dynallocedchunkptrs[fluff] = nullptr;
		membanks[fluff] = dummy_bank;
	}

	//no rom segment,in palms with rom 0x0 and 0x010a0000 where rom
	map_banks(ram_bank, ram_start >> 16, 0x100 + 1);//16mb ram + 1 page that used to be rom

	//dynamicly set lcd banks size
	map_banks(lcd_bank, lcd_start >> 16, NUM_BANKS(LCDBYTES * 2));

	map_banks(reg_bank, 0xFFFF0000 >> 16, 1);

	return 0;
}

void memory_deinit(){
	freedynchunks();
	delete[] rammemory;
	delete[] membanks;
}

ULONG longget(CPTR addr)
{
    return membanks[BANKINDEX(addr)].lget(addr);
}
UWORD wordget(CPTR addr)
{
    return membanks[BANKINDEX(addr)].wget(addr);
}
UBYTE byteget(CPTR addr) 
{
    return membanks[BANKINDEX(addr)].bget(addr);
}
void longput(CPTR addr, ULONG l)
{
    membanks[BANKINDEX(addr)].lput(addr, l);
}
void wordput(CPTR addr, UWORD w)
{
    membanks[BANKINDEX(addr)].wput(addr, w);
}
void byteput(CPTR addr, UBYTE b)
{
    membanks[BANKINDEX(addr)].bput(addr, b);
}

ULONG get_long(CPTR addr) 
{
	if(IS_EVEN(addr))return longget(addr);
	dbgprintf("Bus error: read a long from odd address 0x%08x\n", addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
    buserr = 1;
	palmabrt();//hack
    return 0;
}

UWORD get_word(CPTR addr) 
{
	if(IS_EVEN(addr))return wordget(addr);
	dbgprintf("Bus error: read a word from odd address 0x%08x\n", addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
    buserr = 1;
	palmabrt();//hack
    return 0;
}

UBYTE get_byte(CPTR addr) 
{
    return byteget(addr); 
}

void put_long(CPTR addr, ULONG l) 
{
	if(IS_EVEN(addr)){
		longput(addr, l);
		return;
	}

	dbgprintf("Bus error: wrote a long to odd address 0x%08x\n", addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
	buserr = 1;
	palmabrt();//hack

}

void put_word(CPTR addr, UWORD w) 
{
	if(IS_EVEN(addr)){
		wordput(addr, w);
		return;
	}

	dbgprintf("Bus error: wrote a word to odd address 0x%08x\n", addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
	buserr = 1;
	palmabrt();//hack

}

void put_byte(CPTR addr, UBYTE b) 
{
    byteput(addr, b);
}

UWORD* get_real_address(CPTR addr)
{
	if (!IS_EVEN(addr)) {
		dbgprintf("Bus error: attempted translation of odd address 0x%08x\n", addr);
		dbgprintf("PC=0x%08x\n", MC68000_getpc());
		printprcerror(MC68000_getpc());
		buserr = 1;
    }
    return membanks[BANKINDEX(addr)].xlateaddr(addr);
}

int valid_address(CPTR addr, ULONG size)
{
	if (!IS_EVEN(addr)) {
	dbgprintf("Bus error: attempted validation of odd address 0x%08x\n", addr);
	dbgprintf("PC=0x%08x\n", MC68000_getpc());
	buserr = 1;
    }
    return membanks[BANKINDEX(addr)].check(addr, size);
}
