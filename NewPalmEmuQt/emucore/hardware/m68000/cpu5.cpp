#include "newcpu.h"
void op_5000(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5010(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5018(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5020(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5028(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5030(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5038(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
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
void op_5039(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
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
void op_5040(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5048(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_5050(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5058(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5060(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5068(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5070(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5078(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
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
void op_5079(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
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
void op_5080(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5088(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_5090(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_5098(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_50a0(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_50a8(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_50b0(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
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
void op_50b8(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
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
void op_50b9(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
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
void op_50c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(0) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_50c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(0)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_50d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(0) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_50d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(0) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_50e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(0) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_50e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(0) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_50f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(0) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_50f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(0) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_50f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(0) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5100(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_5110(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_5118(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_5120(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_5128(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_5130(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_5138(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_5139(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_5140(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_5148(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_5150(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_5158(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_5160(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_5168(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_5170(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_5178(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
{	offset_68k dsta = (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_5179(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
{	offset_68k dsta = nextilong();
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_5180(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_5188(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	LONG dst = (Shptr->regs).a[dstreg];
{	uint32_t newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_5190(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_5198(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_51a0(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_51a8(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_51b0(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
	uint32_t dstreg = (opcode & 7) >> 0;
{{	uint32_t src = srcreg;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_51b8(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
{	offset_68k dsta = (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_51b9(uint32_t opcode)
{
	uint32_t srcreg = imm8_table[(opcode & 3584) >> 9];
{{	uint32_t src = srcreg;
{	offset_68k dsta = nextilong();
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_51c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(1) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_51c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(1)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_51d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(1) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_51d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(1) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_51e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(1) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_51e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(1) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_51f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(1) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_51f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(1) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_51f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(1) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_52c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(2) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_52c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(2)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_52d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(2) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_52d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(2) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_52e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(2) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_52e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(2) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_52f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(2) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_52f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(2) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_52f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(2) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_53c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(3) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_53c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(3)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_53d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(3) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_53d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(3) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_53e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(3) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_53e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(3) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_53f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(3) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_53f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(3) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_53f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(3) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_54c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(4) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_54c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(4)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_54d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(4) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_54d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(4) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_54e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(4) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_54e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(4) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_54f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(4) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_54f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(4) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_54f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(4) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_55c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(5) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_55c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(5)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_55d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(5) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_55d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(5) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_55e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(5) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_55e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(5) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_55f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(5) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_55f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(5) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_55f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(5) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_56c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(6) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_56c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(6)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_56d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(6) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_56d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(6) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_56e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(6) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_56e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(6) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_56f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(6) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_56f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(6) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_56f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(6) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_57c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(7) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_57c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(7)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_57d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(7) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_57d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(7) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_57e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(7) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_57e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(7) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_57f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(7) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_57f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(7) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_57f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(7) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_58c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(8) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_58c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(8)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_58d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(8) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_58d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(8) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_58e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(8) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_58e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(8) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_58f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(8) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_58f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(8) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_58f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(8) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_59c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(9) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_59c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(9)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_59d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(9) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_59d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(9) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_59e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(9) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_59e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(9) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_59f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(9) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_59f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(9) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_59f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(9) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ac0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(10) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_5ac8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(10)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_5ad0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(10) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ad8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(10) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5ae0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(10) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5ae8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(10) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5af0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(10) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5af8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(10) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5af9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(10) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5bc0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(11) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_5bc8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(11)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_5bd0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(11) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5bd8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(11) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5be0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(11) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5be8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(11) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5bf0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(11) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5bf8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(11) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5bf9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(11) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5cc0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(12) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_5cc8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(12)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_5cd0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(12) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5cd8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(12) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5ce0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(12) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5ce8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(12) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5cf0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(12) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5cf8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(12) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5cf9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(12) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5dc0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(13) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_5dc8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(13)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_5dd0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(13) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5dd8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(13) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5de0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(13) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5de8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(13) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5df0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(13) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5df8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(13) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5df9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(13) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ec0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(14) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_5ec8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(14)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_5ed0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(14) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ed8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(14) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5ee0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(14) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5ee8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(14) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ef0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(14) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ef8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(14) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ef9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(14) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5fc0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{{	int val = cctrue(15) ? 0xff : 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (val) & 0xff;
}}}}
void op_5fc8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD offs = nextiword();
	if (!cctrue(15)) {
	if (src--) (Shptr->regs).pc_p = (uint16_t *)((char *)(Shptr->regs).pc_p + (LONG)offs - 2);
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (src) & 0xffff;
	}
}}}}
void op_5fd0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(15) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5fd8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	int val = cctrue(15) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5fe0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int val = cctrue(15) ? 0xff : 0;
	put_byte(srca,val);
}}}}}
void op_5fe8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int val = cctrue(15) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ff0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int val = cctrue(15) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ff8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	int val = cctrue(15) ? 0xff : 0;
	put_byte(srca,val);
}}}}
void op_5ff9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	int val = cctrue(15) ? 0xff : 0;
	put_byte(srca,val);
}}}}
