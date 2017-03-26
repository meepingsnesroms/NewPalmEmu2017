#ifndef M68K
#define M68K

#include <stdint.h>
#include <stdio.h> //for the FILE* in shared_img

static_assert(sizeof(char) == 1,"char must be 1 byte!");

//fix for compiler warnings about unused parameter for some opcodes
//(if it wont compile change these)

//uae sends all opcodes themself as varibles but some opcodes dont have varibles
//the opcodes are NOP,RTS,TRAPV,RTE,RTR,STOP,ILLEGAL and RESET

//changes op_xxxx(ULONG opcode)
//to op_xxxx(ULONG) ignoreing the parameter

#define RMUP//remove unused parameters


#ifdef RMUP
#define NUOPPRAM
#else
#define NUOPPRAM opcode
#endif


//simple names
#define CPU_LEVEL 0

#define TFLG ((Shptr->regs).t)
#define XFLG ((Shptr->regs).x)
#define ZFLG ((Shptr->regs).z)
#define NFLG ((Shptr->regs).n)
#define CFLG ((Shptr->regs).c)
#define VFLG ((Shptr->regs).v)
#define SFLG ((Shptr->regs).s)

#define D0 ((Shptr->regs).d[0])
#define D1 ((Shptr->regs).d[1])
#define D2 ((Shptr->regs).d[2])
#define D3 ((Shptr->regs).d[3])
#define D4 ((Shptr->regs).d[4])
#define D5 ((Shptr->regs).d[5])
#define D6 ((Shptr->regs).d[6])
#define D7 ((Shptr->regs).d[7])
#define DX(x) ((Shptr->regs).d[(x)])

#define A0 ((Shptr->regs).a[0])
#define A1 ((Shptr->regs).a[1])
#define A2 ((Shptr->regs).a[2])
#define A3 ((Shptr->regs).a[3])
#define A4 ((Shptr->regs).a[4])
#define A5 ((Shptr->regs).a[5])
#define A6 ((Shptr->regs).a[6])
#define SP ((Shptr->regs).a[7])
#define AX(x) ((Shptr->regs).a[(x)])

#define USERSP ((Shptr->regs).usp)

#define PENX (Shptr->penx)
#define PENY (Shptr->peny)
#define PENDOWN (Shptr->pendown)
#define BTNTBL (Shptr->buttons)

#define CPUSTATE (Shptr->CpuState)
#define CPUREQ (Shptr->CpuReq)

#define SPCFLAG_STOP 2
#define SPCFLAG_INT  8
#define SPCFLAG_BRK  16
#define SPCFLAG_TRACE 64
#define SPCFLAG_DOTRACE 128
#define SPCFLAG_DOINT 256

/*
 * Cpu States
 */
#define cpuInitial    0
#define cpuLoaded     1
#define cpuRunning    2
#define cpuStopped    3
#define cpuBreakpoint 4
#define cpuException  5

/*
 * Cpu Requests
 */
#define cpuNone    0
#define cpuReset   1
#define cpuStart   2
#define cpuStop    3
#define cpuLoadApp 4
#define cpuExit    5



//type names
typedef uint8_t UBYTE;
typedef int8_t BYTE;
typedef uint16_t UWORD;
typedef int16_t WORD;
typedef uint32_t ULONG;
typedef int32_t LONG;

typedef ULONG CPTR;
typedef char flagtype;//may change to bool
typedef void cpuop_func(ULONG);

typedef ULONG size_t_68k;
typedef ULONG offset_68k;
#define nullptr_68k 0

struct regstruct{
	ULONG d[8];
	CPTR  a[8],usp;
	UWORD sr;
	flagtype t;
	flagtype s;
	flagtype x;
	flagtype v;
	flagtype c;
	flagtype n;
	flagtype z;
	flagtype stopped;
	ULONG intmask;
	ULONG pc;
	UWORD *pc_p;
	UWORD *pc_oldp;
	//custom values
	bool incallback;
};

typedef struct {
  int		CpuState;
  int		CpuReq;
  int ForceExit;

  //touchscreen
  ULONG buttons;
  UWORD penx,peny;
  bool pendown;

  bool		LcdPower;


  FILE		*logF;		/* If non-NULL, log to this file */

  /* need to remove */
  //unsigned long	lssa;		/* shadows dragonball LSSA register */
  unsigned char	PICF;           /* shadows PICF register */
  unsigned char	VPW;		/* shadows VPW register */
  unsigned char	POSR;		/* shadows POSR register */
  //int		scrnstart;	/* modified by write to LSSA */

  //cpu
  struct regstruct regs;	/* the CPU registers state */
  int		ExceptionFlags[48];
  int		ErrNo;
}shared_img;

//cpu state
extern shared_img *Shptr;

extern int ExceptionFlags[48];

extern int areg_byteinc[];
extern int imm8_table[];

struct cputbl {
	cpuop_func *handler;
	int specific;
	UWORD opcode;
};

extern struct cputbl smallcputbl[];

extern cpuop_func *cpufunctbl[65536];
extern UBYTE m68kcycles[65536];

//m68k memory access
ULONG get_long(CPTR addr);
UWORD get_word(CPTR addr);
UBYTE get_byte(CPTR addr);

void put_long(CPTR addr,ULONG l);
void put_word(CPTR addr,UWORD w);
void put_byte(CPTR addr,UBYTE b);

int valid_address(CPTR addr, ULONG size);
UWORD *get_real_address(CPTR addr);

bool killswitch();
#define KILLSWITCH if(CPUREQ)throw CPUREQ //if(killswitch())return;


#endif // M68K

