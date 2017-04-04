#ifndef PALMMEMMAP
#define PALMMEMMAP

#include "m68k.h"

#define RAMFAIL	  1
#define BANKSFAIL 2

#define NUM_BANKS(s) (((s) >> 16) + (((s) & 0xFFFF) ? 1 : 0))
#define BANKINDEX(x) ((x) >> 16)

#define SIZEOFBANK 0x10000
#define TOTALBANKS 0x10000

//cant write to odd addresses so discard 1 byte
#define STACK	    0x00010000//1mb stack
#define STACKEND    0x0010FFFE//1mb stack / Start here stack counts towards 0x0
#define HEAP	    0x00120000//~15mb heap
#define HEAPEND	    0x00DFFFFE//~15mb heap
#define SAVEDATA    0x00E00000//1mb save
#define SAVEDATAEND 0x00EFFFFE//1mb save

#define STACKSIZE	 (STACKEND - STACK)
#define HEAPSIZE	 (HEAPEND - HEAP)
#define SAVEDATASIZE (SAVEDATAEND - SAVEDATA)

#define ram_start	  0x00000000
#define dyn_start	  0x01000000
#define lcd_start	  0x1F000000
#define custom_start  0xFFFF0000

/* Default memory access functions */

uint32_t get_long(offset_68k addr);
uint16_t get_word(offset_68k addr);
uint8_t get_byte(offset_68k addr);
void  put_long(offset_68k addr,uint32_t l);
void  put_word(offset_68k addr,uint16_t w);
void  put_byte(offset_68k addr,uint8_t b);

int		valid_address(offset_68k addr, uint32_t size);
uint16_t*  get_real_address(offset_68k addr);

extern int buserr;
extern uint32_t ram_size;

typedef uint32_t	(*lget_func)(offset_68k);
typedef uint16_t	(*wget_func)(offset_68k);
typedef uint8_t	(*bget_func)(offset_68k);
typedef void	(*lput_func)(offset_68k,uint32_t);
typedef void	(*wput_func)(offset_68k,uint16_t);
typedef void	(*bput_func)(offset_68k,uint8_t);
typedef uint16_t*  (*xlate_func)(offset_68k);
typedef int		(*check_func)(offset_68k, uint32_t);

typedef struct {
	lget_func  lget;
	wget_func  wget;
	bget_func  bget;
	lput_func  lput;
	wput_func  wput;
	bput_func  bput;
    xlate_func xlateaddr;
    check_func check;
} addrbank;

extern addrbank ram_bank;
extern addrbank dyn_bank;
extern addrbank dummy_bank;

extern addrbank* membanks;

uint32_t longget(offset_68k addr);
uint16_t wordget(offset_68k addr);
uint8_t byteget(offset_68k addr);
void  longput(offset_68k addr, uint32_t l);
void  wordput(offset_68k addr, uint16_t w);
void  byteput(offset_68k addr, uint8_t b);

uint16_t getnewlinearchunks(uint16_t needed);
void  freedynchunk(int chunk);
void  freedynchunks();

void map_banks(addrbank bank, uint32_t start, uint32_t size);
int  memory_init();
void memory_deinit();
#endif
