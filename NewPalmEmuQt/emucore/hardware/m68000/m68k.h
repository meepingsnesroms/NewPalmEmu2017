#ifndef M68K
#define M68K

#include <stdint.h>
#include <thread>
#include <chrono>

//fix for compiler warnings about unused parameter for some opcodes
//(if it wont compile change these)

//uae sends all opcodes themself as varibles but some opcodes dont have varibles
//the opcodes are NOP,RTS,TRAPV,RTE,RTR,STOP,ILLEGAL and RESET

//changes op_xxxx(uint32_t opcode)
//to op_xxxx(uint32_t) ignoreing the parameter

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

#define PENX	(Shptr->penx)
#define PENY	(Shptr->peny)
#define PENDOWN (Shptr->pendown)
#define BTNTBL	(Shptr->buttons)

#define CPUSTATE	(Shptr->CpuState)
#define CPUREQ		(Shptr->CpuReq)

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
#define cpuExit    4

typedef uint8_t flagtype;//Some flags have more that 2 values so this must remain an 8bit int
typedef void cpuop_func(uint32_t);

typedef uint32_t size_t_68k;
typedef uint32_t offset_68k;
#define nullptr_68k 0

struct regstruct{
	uint32_t d[8];
	offset_68k  a[8],usp;
	uint16_t sr;
	flagtype t;
	flagtype s;
	flagtype x;
	flagtype v;
	flagtype c;
	flagtype n;
	flagtype z;
	flagtype stopped;
	uint32_t intmask;
	uint32_t pc;
	uint16_t *pc_p;
	uint16_t *pc_oldp;
	//custom values
	bool incallback;
};

typedef struct {
  int		CpuState;
  int		CpuReq;
  int ForceExit;

  //touchscreen
  uint32_t buttons;
  uint16_t penx,peny;
  bool pendown;

  //bool		LcdPower;

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
	uint16_t opcode;
};

extern struct cputbl smallcputbl[];

extern cpuop_func *cpufunctbl[65536];
extern uint8_t m68kcycles[65536];

//m68k memory access
uint32_t get_long(offset_68k addr);
uint16_t get_word(offset_68k addr);
uint8_t  get_byte(offset_68k addr);

void put_long(offset_68k addr,uint32_t l);
void put_word(offset_68k addr,uint16_t w);
void put_byte(offset_68k addr,uint8_t b);

int valid_address(offset_68k addr, uint32_t size);
uint16_t *get_real_address(offset_68k addr);

#define STATECHANGE 1
#define ABORT		2

inline void m68k_handle_changes(){
    check_again:
	switch(Shptr->CpuReq){
		case cpuStart:
		case cpuNone:
			break;
		case cpuExit:
		case cpuReset:
			throw STATECHANGE;
		case cpuStop:
			while(Shptr->CpuReq == cpuStop){
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
			goto check_again;
	}
}


#endif // M68K

