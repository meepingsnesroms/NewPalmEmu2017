#include "newcpu.h"
void op_b000(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b010(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b018(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b020(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b028(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b030(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b038(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b039(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b03a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b03b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b03c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b040(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b048(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).a[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b050(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b058(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b060(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b068(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b070(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b078(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b079(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b07a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b07b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b07c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b080(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b088(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b090(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b098(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0c8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).a[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b0fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b0fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b100(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_b108(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}}
void op_b110(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_b118(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_b120(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_b128(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_b130(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int8_t dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_b138(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_b139(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int8_t dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int8_t)(src)) == 0;
	NFLG = ((int8_t)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_b140(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_b148(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}}
void op_b150(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_b158(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_b160(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_b168(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_b170(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int16_t dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_b178(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_b179(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int16_t dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int16_t)(src)) == 0;
	NFLG = ((int16_t)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_b180(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_b188(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}}
void op_b190(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_b198(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_b1a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_b1a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_b1b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int32_t dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_b1b8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_b1b9(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int32_t dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((int32_t)(src)) == 0;
	NFLG = ((int32_t)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_b1c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b1c8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b1d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b1d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b1e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b1e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b1f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b1f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b1f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_b1fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b1fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_b1fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	int32_t dst = (Shptr->regs).a[dstreg];
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
