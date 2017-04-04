#include "newcpu.h"
void op_7000(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 255) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	uint32_t src = srcreg;
{	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
