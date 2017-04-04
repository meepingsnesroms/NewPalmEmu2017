#include "newcpu.h"
void op_7000(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 255) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	uint32_t src = srcreg;
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
