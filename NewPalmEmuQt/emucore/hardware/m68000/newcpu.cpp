//taken from xcopilot, mostly original at this point
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "m68k.h"
#include "newcpu.h"
#include "memmap.h"
#include "virtuallcd.h"
#include "prcfile.h"

#include "minifunc.h" //For debug functions
#include "palmwrapper.h" //hack //only used for palmabrt() function
#include "palmapi.h" //Callback to emulator for hle OS functions



int areg_byteinc[] = { 1,1,1,1,1,1,1,2 };
int imm8_table[] = { 8,1,2,3,4,5,6,7 };

uint16_t* InstructionStart_p;
shared_img* Shptr;
unsigned long specialflags;


void fatal(char* file, int line){
	if(file){
		dbgprintf("Fatal(%s,%d)\n", file, line);
		return;
	}
    Shptr->CpuReq = cpuExit;
    exit(1);
}

uint16_t nextiword(){
	uint16_t r = *(Shptr->regs).pc_p;
	(Shptr->regs).pc_p++;
	return r;
}

uint32_t nextilong(){
	uint32_t r = *(Shptr->regs).pc_p;
	(Shptr->regs).pc_p++;
	r = (r << 16) + *(Shptr->regs).pc_p;
	(Shptr->regs).pc_p++;
	return r;
}


void MC68000_setpc(offset_68k newpc){
	if(newpc == INTERCEPT){
		if((Shptr->regs).incallback){
			(Shptr->regs).incallback = false;
			return;
		}else{
			dbgprintf("\n--PC Set To INTERCEPT Outside Of Callback--\n"
				   "This is most likely the app exiting gracefuly\n"
				   "check for a call to SysAppExit.\n"
				   "-------------------------------------------\n\n");
			palmabrt();//hack
		}
	}


    if (!get_real_address(newpc)) {
		dbgprintf("FATAL: weird setpc(%08x) at %08x!\n",newpc, MC68000_getpc());
		printprcerror(MC68000_getpc());

		int i, j;
		dbgprintf("BUSERR at 0x%x\n\r", MC68000_getpc());
		dbgprintf("SR 0x%.8x\n\r", (Shptr->regs).sr);
		for (i=0;i<8;i++)
		dbgprintf("A%d[0x%.8x] ",i,(Shptr->regs).a[i]);
		dbgprintf("\n\r");
		for (i=0;i<8;i++)
		dbgprintf("D%d[0x%.8x] ",i,(Shptr->regs).d[i]);
		dbgprintf("\n\r");
		for (i = 0; i < 128; ) {
		dbgprintf("0x%8x: ", (Shptr->regs).a[7] + i);
		for (j = 0; i < 128 && j < 4; j++, i += 4)
			if (valid_address((Shptr->regs).a[7] + i, 4))
			dbgprintf("0x%8x ", get_long((Shptr->regs).a[7] + i));
			else
			dbgprintf("%10.10s ", "-");
		dbgprintf("\n\r");
		}

		abort();
    }

    (Shptr->regs).pc = newpc;

    (Shptr->regs).pc_p = get_real_address(newpc);
    (Shptr->regs).pc_oldp = get_real_address(newpc);
}

offset_68k MC68000_getpc(){
	return (Shptr->regs).pc + ((uint8_t*)(Shptr->regs).pc_p - (uint8_t*)(Shptr->regs).pc_oldp);
}

void MC68000_setstopped(int stop){
    (Shptr->regs).stopped = stop;
	if(stop)specialflags |= SPCFLAG_STOP;
}

int cctrue(int cc){
	switch(cc){
		case 0: return 1;                       /* T */
		case 1: return 0;                       /* F */
		case 2: return !CFLG && !ZFLG;          /* HI */
		case 3: return CFLG || ZFLG;            /* LS */
		case 4: return !CFLG;                   /* CC */
		case 5: return CFLG;                    /* CS */
		case 6: return !ZFLG;                   /* NE */
		case 7: return ZFLG;                    /* EQ */
		case 8: return !VFLG;                   /* VC */
		case 9: return VFLG;                    /* VS */
		case 10:return !NFLG;                   /* PL */
		case 11:return NFLG;                    /* MI */
		case 12:return NFLG == VFLG;            /* GE */
		case 13:return NFLG != VFLG;            /* LT */
		case 14:return !ZFLG && (NFLG == VFLG); /* GT */
		case 15:return ZFLG || (NFLG != VFLG);  /* LE */
	}
	fatal(nullptr, 0);
	return 0;
}

uint32_t get_disp_ea(uint32_t base, uint16_t dp){
    int reg = (dp >> 12) & 7;
    LONG regd;
    
	if(dp & 0x8000)regd = (Shptr->regs).a[reg];
	else regd = (Shptr->regs).d[reg];

	if(!(dp & 0x800))regd = (LONG)(WORD)regd;
	return base + (int8_t)(dp) + regd;
}

void MC68000_init(shared_img *shptr){
  Shptr = shptr;
}

void MakeSR(){
  (Shptr->regs).sr = (((Shptr->regs).t << 15) | ((Shptr->regs).s << 13) |
		      ((Shptr->regs).intmask << 8) | ((Shptr->regs).x << 4) |
			  (NFLG << 3) | (ZFLG << 2) | (VFLG << 1) | CFLG);
}

void MakeFromSR(){
	flagtype olds = (Shptr->regs).s;

	(Shptr->regs).t = ((Shptr->regs).sr >> 15) & 1;
	(Shptr->regs).s = ((Shptr->regs).sr >> 13) & 1;
	(Shptr->regs).intmask = ((Shptr->regs).sr >> 8) & 7;
	(Shptr->regs).x = ((Shptr->regs).sr >> 4) & 1;
	NFLG = ((Shptr->regs).sr >> 3) & 1;
	ZFLG = ((Shptr->regs).sr >> 2) & 1;
	VFLG = ((Shptr->regs).sr >> 1) & 1;
	CFLG = (Shptr->regs).sr & 1;

	if (olds != (Shptr->regs).s) {
		offset_68k temp = (Shptr->regs).usp;
		(Shptr->regs).usp = (Shptr->regs).a[7];
		(Shptr->regs).a[7] = temp;
	}

	specialflags |= SPCFLAG_INT;

	if((Shptr->regs).t)specialflags |= SPCFLAG_TRACE;
	else specialflags &= ~(SPCFLAG_TRACE | SPCFLAG_DOTRACE);
}

void MC68000_exception(int nr){
  if (nr < 48 && Shptr->ExceptionFlags[nr] && InstructionStart_p) {
    (Shptr->regs).pc_p = InstructionStart_p;
    Shptr->CpuState = cpuException + nr;
    return;
  }

  if (nr == 32 + 0xF && emulateapi(*(Shptr->regs).pc_p)) {
    nextiword();
    return;
  }
  else	dbgprintf("Trap:%d err.\n",nr - 32);

  MakeSR();
  if (!(Shptr->regs).s) {
	offset_68k temp = (Shptr->regs).usp;
    (Shptr->regs).usp = (Shptr->regs).a[7];
    (Shptr->regs).a[7] = temp;
    (Shptr->regs).s = 1;
  }
#if CPU_LEVEL > 0
    (Shptr->regs).a[7] -= 2;
	put_word((Shptr->regs).a[7], nr * 4);
#endif
  (Shptr->regs).a[7] -= 4;
  put_long ((Shptr->regs).a[7], MC68000_getpc());
  (Shptr->regs).a[7] -= 2;
  put_word ((Shptr->regs).a[7], (Shptr->regs).sr);
  MC68000_setpc(get_long(4 * nr));
  (Shptr->regs).t = 0;
  specialflags &= ~(SPCFLAG_TRACE | SPCFLAG_DOTRACE);
}

void MC68000_reset(){
	for(int regnum = 0;regnum < 8;regnum++){
		AX(regnum) = 0;
		DX(regnum) = 0;
	}
	USERSP = 0;
	TFLG = false;
	SFLG = true;
	XFLG = false;
	VFLG = false;
	CFLG = false;
	NFLG = false;
	ZFLG = false;
	(Shptr->regs).stopped = false;
	specialflags = 0;
	(Shptr->regs).incallback = false;
	Shptr->CpuState = cpuStopped;
	(Shptr->regs).intmask = 7;
}

void op_illg(uint32_t opcode){

	palmabrt();//hack

	(Shptr->regs).pc_p--;
	if((opcode & 0xF000) == 0xF000){

		palmabrt();//hack //unsupported FPU opcode

		if((opcode & 0xE00) == 0x200)MC68000_exception(0xB);
		else
		switch(opcode & 0x1FF){
			case 0x17:
				(Shptr->regs).pc_p += 2;
				break;
			default:
				(Shptr->regs).pc_p++;
		}
		return;
	}
	if((opcode & 0xF000) == 0xA000){
		MC68000_exception(0xA);
		return;
	}
	if(opcode == 0x4AFC){ /* breakpoint */
		Shptr->CpuState = cpuBreakpoint;
		dbgprintf("I - CpuState = cpuBreakpoint\n");
		return;
	}
	dbgprintf("Illegal instruction: %04x\n", (unsigned int)opcode);
	dbgprintf("ILL at 0x%08x\n", MC68000_getpc());
	exit(1);
	MC68000_exception(4);
}

void MC68000_run(){
	uint16_t opcode;
	Shptr->CpuState = cpuRunning;       /* start running */
	for(;;) {
		if (Shptr->CpuReq != cpuNone){   /* check for a request */
			return;			      /* bail out if requested */
		}

		if(!(specialflags & SPCFLAG_STOP)){
			InstructionStart_p = (Shptr->regs).pc_p;

			//if (exectrace	dbgprintf("Traceing at %#032x\n",MC68000_getpc());


			opcode = nextiword();
			(*cpufunctbl[opcode])(opcode);


			if(buserr){ /* DAVIDM */
				int i, j;
				dbgprintf("BUSERR at 0x%x,Opcode:%04x\n\r", MC68000_getpc(),opcode);
				printprcerror(MC68000_getpc());
				dbgprintf("SR 0x%.8x\n\r", (Shptr->regs).sr);
				for (i=0;i<8;i++)
				dbgprintf("A%d[0x%.8x] ",i,(Shptr->regs).a[i]);
				dbgprintf("\n\r");
				for (i=0;i<8;i++)
				dbgprintf("D%d[0x%.8x] ",i,(Shptr->regs).d[i]);
				dbgprintf("\n\r");
				for (i = 0; i < 128; ) {
				dbgprintf("0x%8x: ", (Shptr->regs).a[7] + i);
				for (j = 0; i < 128 && j < 4; j++, i += 4)
					if (valid_address((Shptr->regs).a[7] + i, 4))
					dbgprintf("0x%8x ", get_long((Shptr->regs).a[7] + i));
					else
					dbgprintf("%10.10s ", "-");
				dbgprintf("\n\r");
				}
				//exit(1);
				palmabrt();
			}
#ifndef NO_EXCEPTION_3
			if (buserr) {
			  MC68000_exception(3);
			  buserr = 0;
			}
#endif
			InstructionStart_p = nullptr;
		}

		//if(updateinterrupts)updateisr();//any hardware interrupts

		if(specialflags){
			/*
			if(specialflags & SPCFLAG_STOP){
				dbgprintf("STOP at PC:%#08x\n",MC68000_getpc()-2);
			}
			*/

			while(specialflags & SPCFLAG_STOP){
				std::this_thread::sleep_for(std::chrono::microseconds(100));
				if(Shptr->CpuState > cpuRunning || Shptr->CpuReq != cpuNone){
					return;
				}
			}

			if(specialflags & SPCFLAG_BRK){
				specialflags &= ~SPCFLAG_BRK;
				return;
			}

		}
		//end of specialflags

		if(Shptr->CpuState > cpuRunning){
			//dbgprintf("not None 3 %d\n", Shptr->CpuState); fflush(stderr);
			return;
		}
	}
}

void MC68000_step(){
    specialflags |= SPCFLAG_BRK;
    MC68000_run();
}

void MC68000_runtilladdr(offset_68k nextpc)
{
	(Shptr->regs).incallback = true;
	do{
      MC68000_step();
	}while(MC68000_getpc() != nextpc && (Shptr->regs).incallback);
	//Shptr->CpuState = cpuStopped;//unknown
}






//pilotcpu
int CPU(shared_img *shptr){
	shptr->CpuState = cpuStopped;
	do{
		switch(shptr->CpuReq){
		case cpuStart:
			shptr->CpuReq = cpuNone;
			dbgprintf("I - CPU Started\n");
			try{
				MC68000_run();
			}catch(int request){
				if(request == ABORT){
					//tell the control thread that the cpu is now off
					//shptr->CpuState = cpuStopped;
					//it already stopped executing so just let the cpu
					//idle until killed or user restarts it
				}
				//hack //backup state and exit
			};
			break;
		case cpuStop:
			shptr->CpuReq = cpuNone;
			shptr->CpuState = cpuStopped;
			dbgprintf("I - CPU Stopped\n");
			break;
		case cpuReset:
			shptr->CpuReq = cpuNone;
			MC68000_reset();
			dbgprintf("I - CPU Reset\n");
			break;
		case cpuExit:
			dbgprintf("I - CPU Exit\n");
			break;
		default:
			std::this_thread::sleep_for(std::chrono::milliseconds(1)); /* sleep for 1 ms */
			break;
		}
	}
	while(shptr->CpuReq != cpuExit);

	return 0;
}

int CPU_init(shared_img *shptr){
  int r = memory_init();
  if(r != 0)return r;

  MC68000_init(shptr);
  MC68000_reset();

  return 0;
}

void CPU_reset(shared_img *shptr){
  shptr->CpuReq = cpuReset;
  while(shptr->CpuState != cpuStopped){
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void CPU_start(shared_img *shptr){
  shptr->CpuReq = cpuStart;
  while(shptr->CpuState != cpuRunning){
	  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void CPU_stop(shared_img *shptr){
  shptr->CpuReq = cpuStop;
  while(shptr->CpuState != cpuStopped){
	  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void CPU_wait(shared_img *shptr){
  while(shptr->CpuState == cpuRunning){
	  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void CPU_getregs(shared_img *shptr, struct regstruct *r){
	*r = shptr->regs;
	r->pc = MC68000_getpc();
}

void CPU_setregs(shared_img *shptr, struct regstruct *r){
	shptr->regs = *r;
	MakeFromSR();
	MC68000_setpc(r->pc);
}

int CPU_setexceptionflag(shared_img *shptr, int exception, int flag){
	int r;
	if(exception < 0 || exception >= 48){
		return 0;
	}
	r = shptr->ExceptionFlags[exception];
	shptr->ExceptionFlags[exception] = flag;
	return r;
}

//68k stack access
void CPU_pushlongstack(uint32_t val){
	SP -= 4;
	put_long(SP,val);
}

uint32_t CPU_poplongstack(){
	uint32_t retval;
	retval = get_long(SP);
	SP += 4;
	return retval;
}

void CPU_pushwordstack(uint16_t val){
	SP -= 2;
	put_word(SP,val);
}

uint16_t CPU_popwordstack(){
	uint16_t retval;
	retval = get_word(SP);
	SP += 2;
	return retval;
}

//call a function in 68k mode
void CPU_68kfunction(offset_68k addr,offset_68k from){
	//save old pc
	offset_68k oldpc = MC68000_getpc();

	//push caller pc to stack, will be popped off and called on rts opcode
	CPU_pushlongstack(from);

	//set destination pc
	MC68000_setpc(addr);

	//run until rts is called with caller pc
	MC68000_runtilladdr(from);

	//restore old(correct) pc
	MC68000_setpc(oldpc);
}

//debuging
void printregs(){
	int i, j;
	dbgprintf("SR 0x%.8x\n\r", (Shptr->regs).sr);
	for (i=0;i<8;i++)
	dbgprintf("A%d[0x%.8x] ",i,(Shptr->regs).a[i]);
	dbgprintf("\n\r");
	for (i=0;i<8;i++)
	dbgprintf("D%d[0x%.8x] ",i,(Shptr->regs).d[i]);
	dbgprintf("\n\r");
	for (i = 0; i < 128; ) {
	dbgprintf("0x%8x: ", (Shptr->regs).a[7] + i);
	for (j = 0; i < 128 && j < 4; j++, i += 4)
		if (valid_address((Shptr->regs).a[7] + i, 4))
		dbgprintf("0x%8x ", get_long((Shptr->regs).a[7] + i));
		else
		dbgprintf("%10.10s ", "-");
	dbgprintf("\n\r");
	}
}
