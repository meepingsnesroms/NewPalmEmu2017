//taken from xcopilot
#ifndef NEWCPU_H
#define NEWCPU_H

#include "m68k.h"

int  intbase();
int	 intlev();

void op_illg(ULONG);

void  fatal(char *, int);
UWORD nextiword();
ULONG nextilong();
int   cctrue(int cc);
ULONG get_disp_ea (ULONG base, UWORD dp);
void MakeSR();
void MakeFromSR();
void MC68000_oldstep(UWORD opcode);
void MC68000_setpc(CPTR newpc);
CPTR MC68000_getpc();
void MC68000_setstopped(int stop);
void MC68000_exception(int);
void MC68000_init(shared_img *shptr);
void MC68000_reset();
void MC68000_run();
void MC68000_step();
void MC68000_runtilladdr(CPTR);


//pilotcpu
int   CPU(shared_img *shptr);
int   CPU_init(shared_img *shptr);
void  CPU_wait(shared_img *shptr);
void  CPU_reset(shared_img *shptr);
void  CPU_start(shared_img *shptr);
void  CPU_stop(shared_img *shptr);
void  CPU_getregs(shared_img *shptr, struct regstruct *r);
void  CPU_setregs(shared_img *shptr, struct regstruct *r);
int   CPU_setexceptionflag(shared_img *shptr, int exception, int flag);
void  CPU_pushlongstack(ULONG val);
ULONG CPU_poplongstack();
void  CPU_pushwordstack(UWORD val);
UWORD CPU_popwordstack();
//stack does not support byte ops,so no push/pop bytestack();

//call a function in 68k mode
void CPU_68kfunction(CPTR addr, CPTR from);
inline void CPU_68kfunction(CPTR addr){CPU_68kfunction(addr, 0xFFFFFFFF);}

//struct regstruct CPU_68kfunction_protect_regs(CPTR addr, CPTR from = 0xFFFFFFFF);
//inline struct regstruct CPU_68kfunction_protect_regs(CPTR addr){CPU_68kfunction_protect_regs(addr, 0xFFFFFFFF);}


//easily and quickly remove * bytes from stack,used to clean up after calling back into 68k mode
inline void CPU_cleanargsfromstack(int bytes){SP += bytes;}

//debuging
void printregs();
#endif
