#include "newcpu.h"
void op_1000(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_1010(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_1018(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_1020(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_1028(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_1030(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_1038(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_1039(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_103a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_103b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_103c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_1080(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_1090(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_1098(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_10b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_10b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_10ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_10c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_10e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_10e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_10f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_10fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_10fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_10fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_1100(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_1110(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_1118(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_1120(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_1128(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_1130(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_1138(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_1139(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_113a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_113b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}}
void op_113c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_1140(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_1150(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_1158(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_1160(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_1168(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_1170(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_1178(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_1179(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_117a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_117b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_117c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_1180(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_1190(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_1198(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_11b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_11b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_11ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_11c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_11d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_11d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_11f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_11f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_11fa(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11fb(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_11fc(uint32_t NUOPPRAM)
{
{{	int8_t src = nextiword();
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_13c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_13d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_13d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_13e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_13e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_13f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_13f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_13f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_13fa(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_13fb(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_13fc(uint32_t NUOPPRAM)
{
{{	int8_t src = nextiword();
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
