#include "newcpu.h"
void op_8000(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_8010(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_8018(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_8020(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_8028(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_8030(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_8038(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_8039(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_803a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_803b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_803c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	int8_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_8040(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_8050(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_8058(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_8060(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_8068(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_8070(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_8078(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_8079(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_807a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_807b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_807c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int16_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_8080(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_8090(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_8098(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_80a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_80a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_80b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_80b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_80b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_80ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_80bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_80bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	int32_t dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_80c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_80d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_80d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_80e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_80e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_80f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_80f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_80f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_80fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_80fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_80fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	uint32_t newv = (uint32_t)dst / (uint16_t)src;
	uint32_t rem = (uint32_t)dst % (uint16_t)src;
	if (newv > 0xffff) { VFLG = NFLG = 1; } else
	{
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_8100(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
{	uint16_t newv_lo = (dst & 0xF) - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = (dst & 0xF0) - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (((int8_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int8_t)(newv)) < 0;
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}
void op_8108(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	uint16_t newv_lo = (dst & 0xF) - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = (dst & 0xF0) - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (((int8_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int8_t)(newv)) < 0;
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	put_byte(dsta,newv);
}}}}}}}}
void op_8110(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_8118(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_8120(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_8128(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_8130(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int8_t dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_8138(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_8139(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int8_t dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_8150(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_8158(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_8160(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_8168(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_8170(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int16_t dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_8178(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_8179(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int16_t dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_8190(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_8198(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_81a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_81a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_81b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int32_t dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_81b8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_81b9(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int32_t dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_81c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_81d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_81d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_81e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_81e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_81f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_81f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_81f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
void op_81fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_81fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}}
void op_81fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int32_t dst = (Shptr->regs).d[dstreg];
	if(src != 0){
	int32_t newv = (int32_t)dst / (int16_t)src;
	uint16_t rem = (int32_t)dst % (int16_t)src;
	if ((newv & 0xffff0000) && (newv & 0xffff0000) != 0xffff0000) { VFLG = NFLG = 1; } else
	{
	if (((int16_t)rem < 0) != ((int32_t)dst < 0)) rem = -rem;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(newv)) == 0;
	NFLG = ((int16_t)(newv)) < 0;
	newv = (newv & 0xffff) | ((uint32_t)rem << 16);
	(Shptr->regs).d[dstreg] = (newv);
	}
	}
}}}}
