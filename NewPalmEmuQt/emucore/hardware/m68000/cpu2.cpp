#include "newcpu.h"
void op_2000(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_2008(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_2010(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_2018(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_2020(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_2028(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_2030(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_2038(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_2039(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_203a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_203b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_203c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_2040(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] = (src);
}}}}
void op_2048(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[dstreg] = (src);
}}}}
void op_2050(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] = (src);
}}}}
void op_2058(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	(Shptr->regs).a[dstreg] = (src);
}}}}}
void op_2060(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] = (src);
}}}}}
void op_2068(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] = (src);
}}}}
void op_2070(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] = (src);
}}}}}
void op_2078(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] = (src);
}}}}
void op_2079(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] = (src);
}}}}
void op_207a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] = (src);
}}}}}
void op_207b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] = (src);
}}}}}
void op_207c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	(Shptr->regs).a[dstreg] = (src);
}}}}
void op_2080(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2088(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2090(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2098(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_20b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_20b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_20ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_20c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20c8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_20e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_20e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_20f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_20fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_20fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_20fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2100(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2108(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2110(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2118(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_2120(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_2128(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2130(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_2138(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2139(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_213a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_213b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}}
void op_213c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2140(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2148(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2150(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2158(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2160(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2168(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2170(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2178(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2179(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_217a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_217b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_217c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2180(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2188(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2190(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2198(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21c8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	int32_t src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_21fa(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21fb(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_21fc(uint32_t NUOPPRAM)
{
{{	int32_t src = nextilong();
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_23c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_23c8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	int32_t src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_23d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_23d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_23e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_23e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_23f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_23f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_23f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_23fa(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_23fb(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_23fc(uint32_t NUOPPRAM)
{
{{	int32_t src = nextilong();
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
