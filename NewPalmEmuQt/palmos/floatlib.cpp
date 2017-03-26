#include "m68k.h"
#include "types.h"
#include "floatlib.h"
#include "palmapi.h"
#include "types.h"
#include "dataexchange.h"

#include <float.h>

#include "newcpu.h"//hack //for printregs()

void palmabrt();//hack

TEMPHACK
//THIS WHOLE FILE IS A HACK RIGHT NOW

//functions that return doubles are currently broken

/*
union{
	struct{

	}flag;
	uint32 total;
}FPUscr;
*/

/*
bool FPUinvalid;
bool FPUoverflow;
bool FPUunderflow;
bool FPUdivby0;
bool FPUinexact;
int  FPUroundmode;
uint32 FPUscr;

void scrtobits(){
	FPUinvalid = FPUscr & flpInvalid;
	FPUoverflow = FPUscr & flpOverflow;
	FPUunderflow = FPUscr & flpUnderflow;
	FPUdivby0 = FPUscr & flpDivByZero;
	FPUinexact = FPUscr & flpInexact;
	FPUroundmode = (FPUscr & flpModeMask) >> flpModeShift;
}

void bitstoscr(){
	FPUscr &= 0xFFFF00FF;
	if(FPUinvalid)FPUscr |= flpInvalid;
	if(FPUoverflow)FPUscr |= flpOverflow;
	if(FPUunderflow)FPUscr |= flpUnderflow;
	if(FPUdivby0)FPUscr |= flpDivByZero;
	if(FPUinexact)FPUscr |= flpInexact;
	FPUscr |= FPUroundmode << flpModeShift;
}
*/
typedef union{
	double64 flt;
	uint64 data;
}conv64;

typedef union{
	float32 flt;
	uint32 data;
}conv32;

conv64 regs64[4];
conv32 regs32[4];

uint32 FPUscr;

void fp_set_fpscr(){
	stacklong(newreg);
	dbgprintf("New FPUscr:%d\n",newreg);
	FPUscr |= newreg & 0x0000F800;//hack //may allow modifying non flag bits
	//no return value
}

void fp_round(){
	stacklong(command);
	dbgprintf("Command:%d\n",command);
	ULONG oldround = (FPUscr >> flpModeShift) & 3;
	FPUscr &= 0xFFFFF8FF;
	FPUscr |= command << flpModeShift;
	D0 = oldround;
	if(command > 3)palmabrt();//hack //invalid command
}

void d_itod(){
	stackptr(PROTO64);//64bit are returned differently
	stacklong(intin);
	return64(PROTO64,double64toraw((double64)intin));
}

void d_div(){
	stackptr(PROTO64);//64bit are returned differently
	stacklong64(dbl1);
	stacklong64(dbl2);
	uint64 out = double64toraw(rawdouble64(dbl1) / rawdouble64(dbl2));
	return64(PROTO64,out);
}

TEMPHACK
void d_dtof(){
	stacklong64(dbl);
	//regs64[0].data = dbl;
	//D0 = (float32)regs64[0].flt;
	D0 = float32toraw((float32)rawdouble64(dbl));
}

TEMPHACK
void f_ftod(){
	stackptr(PROTO64);//64bit are returned differently
	stacklong(flt);
	//regs32[0].data = flt;
	//regs64[0].flt = (double64)regs32[0].flt;
	//return64(PROTO64,regs64[0].data);
	return64(PROTO64,double64toraw((double64)rawfloat32(flt)));
}

TEMPHACK
void d_feq(){
	stacklong64(dbl1);
	stacklong64(dbl2);

	if(rawdouble64(dbl1) == rawdouble64(dbl2)){
		D0 = 1;
	}else{
		D0 = 0;
	}

	/*
	regs64[0].data = dbl1;
	regs64[1].data = dbl2;

	D0 = (regs64[0].flt == regs64[1].flt) ? flpEqual : flpUnordered;//hack
	*/
}

void f_itof(){
	stacklong(intin);
	regs32[0].flt = (float32)intin;
	D0 = regs32[0].data;
}

void f_div(){
	stacklong(flt1);
	stacklong(flt2);
	D0 = float32toraw(rawfloat32(flt1) / rawfloat32(flt2));
}

void f_ftoi(){
	stacklong(flt);
	D0 = (int32)rawfloat32(flt);
}

void f_mul(){
	stacklong(flt1);
	stacklong(flt2);
	D0 = float32toraw(rawfloat32(flt1) * rawfloat32(flt2));
}



//float dispatch traps
void flpdispatch(){
	//This trap is just a switch statement!

	SELECTOR{
		default:
			dbgprintf("Selector Function:%d\n",D2);
			palmabrt();//hack
			break;
	}
}

void flpemdispatch(){
	//This trap is just a switch statement!

	SELECTOR{
		SELAPI(sysFloatEm_fp_set_fpscr,fp_set_fpscr());
		SELAPI(sysFloatEm_fp_round,fp_round());
		SELAPI(sysFloatEm_d_itod,d_itod());
		SELAPI(sysFloatEm_d_div,d_div());
		SELAPI(sysFloatEm_d_dtof,d_dtof());
		SELAPI(sysFloatEm_f_ftod,f_ftod());
		SELAPI(sysFloatEm_d_feq,d_feq());
		SELAPI(sysFloatEm_f_itof,f_itof());
		SELAPI(sysFloatEm_f_div,f_div());
		SELAPI(sysFloatEm_f_ftoi,f_ftoi());
		SELAPI(sysFloatEm_f_mul,f_mul());



		default:
			dbgprintf("Selector Function:%d\n",D2);
			palmabrt();//hack
			break;
	}
}

