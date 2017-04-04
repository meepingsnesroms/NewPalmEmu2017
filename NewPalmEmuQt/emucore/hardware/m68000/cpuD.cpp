#include "newcpu.h"
void op_d000(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d010(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d018(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d020(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d028(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d030(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d038(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d039(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d03a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d03b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int8_t src = get_byte(srca);
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d03c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = nextiword();
{	int8_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d040(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d048(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).a[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d050(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d058(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d060(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d068(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d070(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d078(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d079(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d07a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d07b(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d07c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int16_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d080(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d088(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d090(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d098(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	int32_t dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0c8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).a[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d100(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((int8_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int8_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}
void op_d108(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((int8_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int8_t)(newv)) < 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d110(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d118(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d120(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d128(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d130(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d138(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d139(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) + ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d140(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((int16_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int16_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}
void op_d148(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((int16_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int16_t)(newv)) < 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d150(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d158(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d160(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d168(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d170(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d178(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d179(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) + ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d180(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((int32_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_d188(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((int32_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int32_t)(newv)) < 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d190(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d198(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d1a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d1a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d1b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d1b8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d1b9(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) + ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d1c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1c8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
