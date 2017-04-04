#include "newcpu.h"
void op_c000(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_c010(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_c018(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_c020(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_c028(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_c030(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_c038(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_c039(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_c03a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_c03b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}}
void op_c03c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	int8_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_c040(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_c050(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_c058(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_c060(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_c068(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_c070(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_c078(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_c079(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_c07a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_c07b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}}
void op_c07c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int16_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_c080(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_c090(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_c098(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_c0a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_c0a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_c0b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_c0b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_c0b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_c0ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_c0bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}}
void op_c0bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	int32_t dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_c0c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c0d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c0d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c0e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c0e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c0f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c0f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c0f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c0fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c0fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c0fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (uint32_t)(uint16_t)dst * (uint32_t)(uint16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c100(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
{	uint16_t newv_lo = (src & 0xF) + (dst & 0xF) + (Shptr->regs).x;
	uint16_t newv_hi = (src & 0xF0) + (dst & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo +=6; }
	newv = newv_hi + newv_lo;	CFLG = (Shptr->regs).x = (newv & 0x1F0) > 0x90;
	if (CFLG) newv += 0x60;
	if (((int8_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int8_t)(newv)) < 0;
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}
void op_c108(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	uint16_t newv_lo = (src & 0xF) + (dst & 0xF) + (Shptr->regs).x;
	uint16_t newv_hi = (src & 0xF0) + (dst & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo +=6; }
	newv = newv_hi + newv_lo;	CFLG = (Shptr->regs).x = (newv & 0x1F0) > 0x90;
	if (CFLG) newv += 0x60;
	if (((int8_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int8_t)(newv)) < 0;
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	put_byte(dsta,newv);
}}}}}}}}
void op_c110(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_c118(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_c120(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_c128(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_c130(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int8_t dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_c138(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_c139(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int8_t dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_c140(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
	(Shptr->regs).d[srcreg] = (dst);
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_c148(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
	(Shptr->regs).a[srcreg] = (dst);
	(Shptr->regs).a[dstreg] = (src);
}}}}
void op_c150(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_c158(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_c160(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_c168(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_c170(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int16_t dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_c178(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_c179(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int16_t dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_c188(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
	(Shptr->regs).d[srcreg] = (dst);
	(Shptr->regs).a[dstreg] = (src);
}}}}
void op_c190(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_c198(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_c1a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_c1a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_c1b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int32_t dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_c1b8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_c1b9(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int32_t dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_c1c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c1d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c1d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c1e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c1e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c1f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c1f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c1f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
void op_c1fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c1fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_c1fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = (int32_t)(int16_t)dst * (int32_t)(int16_t)src;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(newv)) == 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}
