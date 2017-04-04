#include "newcpu.h"
void op_3000(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_3008(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_3010(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_3018(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_3020(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_3028(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_3030(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_3038(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_3039(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_303a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_303b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_303c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_3040(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}
void op_3048(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}
void op_3050(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}
void op_3058(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}}
void op_3060(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}}
void op_3068(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}
void op_3070(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}}
void op_3078(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}
void op_3079(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}
void op_307a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}}
void op_307b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}}
void op_307c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] = (LONG)(WORD)(src);
}}}}
void op_3080(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3088(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3090(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3098(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_30b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_30b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_30ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_30c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_30e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_30e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_30f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_30fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_30fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_30fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
{	(Shptr->regs).a[dstreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3100(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3108(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3110(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3118(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_3120(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_3128(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3130(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_3138(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3139(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_313a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_313b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}}
void op_313c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3140(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3148(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3150(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3158(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3160(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3168(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3170(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_3178(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3179(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_317a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_317b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_317c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3180(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3188(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3190(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_3198(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_31fa(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31fb(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_31fc(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_33c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_33c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).a[srcreg];
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_33d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_33d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_33e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_33e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_33f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_33f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_33f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_33fa(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_33fb(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_33fc(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
