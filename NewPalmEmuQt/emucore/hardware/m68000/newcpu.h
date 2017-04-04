//taken from xcopilot, mostly original at this point
#ifndef NEWCPU_H
#define NEWCPU_H

#include "m68k.h"

void op_illg(uint32_t);

void  fatal(char* , int);
uint16_t nextiword();
uint32_t nextilong();
int   cctrue(int cc);
uint32_t get_disp_ea (uint32_t base, uint16_t dp);
void MakeSR();
void MakeFromSR();
void MC68000_oldstep(uint16_t opcode);
void MC68000_setpc(offset_68k newpc);
offset_68k MC68000_getpc();
void MC68000_setstopped(int stop);
void MC68000_exception(int);
void MC68000_init(shared_img *shptr);
void MC68000_reset();
void MC68000_run();
void MC68000_step();
void MC68000_runtilladdr(offset_68k);


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
void  CPU_pushlongstack(uint32_t val);
uint32_t CPU_poplongstack();
void  CPU_pushwordstack(uint16_t val);
uint16_t CPU_popwordstack();
//stack does not support byte ops,so no push/pop bytestack();

//call a function in 68k mode
void CPU_68kfunction(offset_68k addr, offset_68k from);
inline void CPU_68kfunction(offset_68k addr){CPU_68kfunction(addr, 0xFFFFFFFF);}


//easily and quickly remove * bytes from stack,used to clean up after calling back into 68k mode
inline void CPU_cleanargsfromstack(int bytes){SP += bytes;}

//debuging
void printregs();
#endif
