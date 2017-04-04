#include "newcpu.h"
void op_9000(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9010(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9018(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_9020(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_9028(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9030(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_9038(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9039(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_903a(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_903b(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_903c(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9040(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9048(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9050(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9058(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_9060(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_9068(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9070(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_9078(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9079(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_907a(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_907b(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_907c(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9080(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_9088(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_9090(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_9098(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90a0(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90a8(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_90b0(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90b8(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_90b9(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_90ba(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90bb(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90bc(uint32_t opcode)
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
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_90c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90c8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).a[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int16_t src = get_word(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = nextiword();
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_9100(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	int8_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((int8_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int8_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}
void op_9108(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int8_t src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	uint32_t newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((int8_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int8_t)(newv)) < 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_9110(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_9118(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_9120(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_9128(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_9130(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_9138(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_9139(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int8_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int8_t dst = get_byte(dsta);
{{uint32_t newv = ((int8_t)(dst)) - ((int8_t)(src));
{	int flgs = ((int8_t)(src)) < 0;
	int flgo = ((int8_t)(dst)) < 0;
	int flgn = ((int8_t)(newv)) < 0;
	ZFLG = ((int8_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_9140(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	int16_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((int16_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int16_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}
void op_9148(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int16_t src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{	uint32_t newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((int16_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int16_t)(newv)) < 0;
	put_word(dsta,newv);
}}}}}}}}
void op_9150(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_9158(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_9160(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_9168(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_9170(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_9178(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_9179(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int16_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int16_t dst = get_word(dsta);
{{uint32_t newv = ((int16_t)(dst)) - ((int16_t)(src));
{	int flgs = ((int16_t)(src)) < 0;
	int flgo = ((int16_t)(dst)) < 0;
	int flgn = ((int16_t)(newv)) < 0;
	ZFLG = ((int16_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_9180(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((int32_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int32_t)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_9188(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{	uint32_t newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((int32_t)(newv)) != 0) ZFLG = 0;
	NFLG = ((int32_t)(newv)) < 0;
	put_long(dsta,newv);
}}}}}}}}
void op_9190(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_9198(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_91a0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_91a8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_91b0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_91b8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (int32_t)(int16_t)nextiword();
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_91b9(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 3584) >> 9);
{{	int32_t src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	int32_t dst = get_long(dsta);
{{uint32_t newv = ((int32_t)(dst)) - ((int32_t)(src));
{	int flgs = ((int32_t)(src)) < 0;
	int flgo = ((int32_t)(dst)) < 0;
	int flgn = ((int32_t)(newv)) < 0;
	ZFLG = ((int32_t)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_91c0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).d[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91c8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = (Shptr->regs).a[srcreg];
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91d0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91d8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91e0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91e8(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91f0(uint32_t opcode)
{
	uint32_t srcreg = (int32_t)(int8_t)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (int32_t)(int16_t)nextiword();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (int32_t)(int16_t)nextiword();
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int32_t src = get_long(srca);
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	int32_t src = nextilong();
{	int32_t dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
