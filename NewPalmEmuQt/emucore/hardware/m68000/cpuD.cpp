#include "newcpu.h"
void op_d000(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d010(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d018(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d020(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d028(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d030(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d038(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d039(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d03a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
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
{	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d03c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	BYTE src = nextiword();
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d040(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d048(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d050(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d058(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d060(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d068(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d070(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d078(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d079(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d07a(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
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
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d07c(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d080(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d088(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).a[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d090(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d098(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
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
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d100(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	BYTE dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((BYTE)(newv)) != 0) ZFLG = 0;
	NFLG = ((BYTE)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}
void op_d108(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((BYTE)(newv)) != 0) ZFLG = 0;
	NFLG = ((BYTE)(newv)) < 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d110(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d118(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d120(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d128(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d130(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d138(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d139(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(~dst)) < ((uint8_t)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d140(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((WORD)(newv)) != 0) ZFLG = 0;
	NFLG = ((WORD)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}
void op_d148(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((WORD)(newv)) != 0) ZFLG = 0;
	NFLG = ((WORD)(newv)) < 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d150(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d158(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d160(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d168(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d170(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d178(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d179(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	WORD src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(~dst)) < ((uint16_t)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d180(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((LONG)(newv)) != 0) ZFLG = 0;
	NFLG = ((LONG)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_d188(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	uint32_t newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((LONG)(newv)) != 0) ZFLG = 0;
	NFLG = ((LONG)(newv)) < 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d190(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d198(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d1a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d1a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d1b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d1b8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	LONG src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d1b9(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	LONG src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(~dst)) < ((uint32_t)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d1c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).a[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1fc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
