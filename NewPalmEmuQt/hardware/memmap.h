#ifndef COPILOTMEM
#define COPILOTMEM

//taken from xcopilot
#include "m68k.h"

#define RAMFAIL 1
#define BANKSFAIL 2

#define NUM_BANKS(s) (((s) >> 16) + (((s) & 0xFFFF) ? 1 : 0))
#define bankindex(x) ((x) >> 16)

#define SIZEOFBANK 0x10000
#define TOTALBANKS 0x10000

//cant write to odd addresses so discard 1 byte
#define STACK	   0x00010000//1mb stack
#define STACKEND   0x0010FFFE//1mb stack / Start here stack counts towards 0x0
#define HEAP	   0x00120000//~15mb heap
#define HEAPEND	   0x00DFFFFE//~15mb heap
#define SAVEDATA    0x00E00000//1mb save
#define SAVEDATAEND 0x00EFFFFE//1mb save

#define STACKSIZE (STACKEND - STACK)
#define HEAPSIZE (HEAPEND - HEAP)
#define SAVEDATASIZE (SAVEDATAEND - SAVEDATA)

#define ram_start	  0x00000000
#define dyn_start	  0x01000000
#define lcd_start	  0x1F000000
#define custom_start  0xFFFF0000

/* Default memory access functions */

ULONG get_long(CPTR addr);
UWORD get_word(CPTR addr);
UBYTE get_byte(CPTR addr);
void put_long(CPTR addr,ULONG l);
void put_word(CPTR addr,UWORD w);
void put_byte(CPTR addr,UBYTE b);

int valid_address(CPTR addr, ULONG size);
UWORD *get_real_address(CPTR addr);


extern int buserr;
extern int ram_size;

extern UWORD *rammemory;


UWORD *default_xlate(CPTR);
int default_check(CPTR, ULONG);


typedef ULONG (*lget_func)(CPTR);
typedef UWORD (*wget_func)(CPTR);
typedef UBYTE (*bget_func)(CPTR);
typedef void (*lput_func)(CPTR,ULONG);
typedef void (*wput_func)(CPTR,UWORD);
typedef void (*bput_func)(CPTR,UBYTE);
typedef UWORD *(*xlate_func)(CPTR);
typedef int (*check_func)(CPTR, ULONG);

typedef struct {
    lget_func lget;
    wget_func wget;
    bget_func bget;
    lput_func lput;
    wput_func wput;
    bput_func bput;
    xlate_func xlateaddr;
    check_func check;
} addrbank;

//Dynamicly allocated
ULONG dyn_lget(CPTR);
UWORD dyn_wget(CPTR);
UBYTE dyn_bget(CPTR);
void  dyn_lput(CPTR, ULONG);
void  dyn_wput(CPTR, UWORD);
void  dyn_bput(CPTR, UBYTE);
int   dyn_check(CPTR addr, ULONG);
UWORD *dyn_xlate(CPTR addr);

//RAM
ULONG ram_lget(CPTR);
UWORD ram_wget(CPTR);
UBYTE ram_bget(CPTR);
void  ram_lput(CPTR, ULONG);
void  ram_wput(CPTR, UWORD);
void  ram_bput(CPTR, UBYTE);
int   ram_check(CPTR addr, ULONG size);
UWORD *ram_xlate(CPTR addr);

//extern addrbank rom_bank;
extern addrbank ram_bank;
extern addrbank dyn_bank;
extern addrbank custom_bank;

//dummy
ULONG dummy_lget(CPTR);
UWORD dummy_wget(CPTR);
UBYTE dummy_bget(CPTR);
void  dummy_lput(CPTR, ULONG);
void  dummy_wput(CPTR, UWORD);
void  dummy_bput(CPTR, UBYTE);
int   dummy_check(CPTR addr, ULONG size);
UWORD *dummy_xlate(CPTR addr);

extern addrbank dummy_bank;

extern addrbank *membanks;

ULONG longget(CPTR addr);
UWORD wordget(CPTR addr);
UBYTE byteget(CPTR addr);
void longput(CPTR addr, ULONG l);
void wordput(CPTR addr, UWORD w);
void byteput(CPTR addr, UBYTE b);

UWORD getnewlinearchunks(UWORD needed);
void freedynchunk(int chunk);
void freedynchunks();

void map_banks(addrbank bank, int start, int size);
int memory_init();
void memory_deinit();
#endif
