#include "newcpu.h"
void op_4000(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	src += (Shptr->regs).x;
{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (dst) & 0xff;
}}}}}}
void op_4010(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4018(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	src += (Shptr->regs).x;
{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4020(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4028(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4030(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4038(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4039(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4040(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	src += (Shptr->regs).x;
{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (dst) & 0xffff;
}}}}}}
void op_4050(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4058(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	src += (Shptr->regs).x;
{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4060(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4068(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4070(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4078(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4079(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4080(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{	src += (Shptr->regs).x;
{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}}}
void op_4090(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_4098(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	src += (Shptr->regs).x;
{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_40a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_40a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_40b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_40b8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_40b9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_40c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	MakeSR();
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= ((Shptr->regs).sr) & 0xffff;
}}}
void op_40d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_40d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 2;
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}}
void op_40e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}}
void op_40e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_40f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_40f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_40f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_4180(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_4188(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_4190(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_4198(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_41b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41b8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_41b9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_41ba(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41bb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41bc(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_41d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
{	(Shptr->regs).a[dstreg] = (srca);
}}}}}
void op_41e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[dstreg] = (srca);
}}}}}
void op_41e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41f8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41f9(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = nextilong();
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41fa(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41fb(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 3584) >> 9;
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_4200(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (0) & 0xff;
}}}
void op_4210(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4218(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}}
void op_4220(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}}
void op_4228(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4230(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4238(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4239(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4240(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (0) & 0xffff;
}}}
void op_4250(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4258(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}}
void op_4260(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}}
void op_4268(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4270(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4278(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4279(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4280(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	(Shptr->regs).d[srcreg] = (0);
}}}
void op_4290(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_4298(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}}
void op_42a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}}
void op_42a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_42b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_42b8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_42b9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_4400(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
{{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (dst) & 0xff;
}}}}}}
void op_4410(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4418(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4420(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4428(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4430(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4438(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4439(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	BYTE src = get_byte(srca);
{{uint32_t dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint8_t)(src)) > ((uint8_t)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4440(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (dst) & 0xffff;
}}}}}}
void op_4450(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4458(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4460(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4468(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4470(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4478(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4479(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{{uint32_t dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint16_t)(src)) > ((uint16_t)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4480(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}}}
void op_4490(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_4498(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_44a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_44a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_44b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_44b8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_44b9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	LONG src = get_long(srca);
{{uint32_t dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((uint32_t)(src)) > ((uint32_t)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_44c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44f8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44f9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44fa(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44fb(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44fc(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_4600(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (dst) & 0xff;
}}}}
void op_4610(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}
void op_4618(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}}
void op_4620(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}}
void op_4628(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}
void op_4630(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}}
void op_4638(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}
void op_4639(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	BYTE src = get_byte(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}
void op_4640(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (dst) & 0xffff;
}}}}
void op_4650(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}
void op_4658(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}}
void op_4660(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}}
void op_4668(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}
void op_4670(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}}
void op_4678(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}
void op_4679(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}
void op_4680(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}
void op_4690(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}
void op_4698(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}}
void op_46a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}}
void op_46a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}
void op_46b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}}
void op_46b8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}
void op_46b9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	LONG src = get_long(srca);
{	uint32_t dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}
void op_46c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	WORD src = (Shptr->regs).d[srcreg];
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46f8(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46f9(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46fa(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46fb(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46fc(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	WORD src = nextiword();
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_4800(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	uint16_t newv_lo = - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (newv) & 0xff;
}}}}
void op_4810(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	uint16_t newv_lo = - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}
void op_4818(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	uint16_t newv_lo = - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}}
void op_4820(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	uint16_t newv_lo = - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}}
void op_4828(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	uint16_t newv_lo = - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}
void op_4830(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	uint16_t newv_lo = - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}}
void op_4838(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	uint16_t newv_lo = - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}
void op_4839(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	BYTE src = get_byte(srca);
{	uint16_t newv_lo = - (src & 0xF) - (Shptr->regs).x;
	uint16_t newv_hi = - (src & 0xF0);
	uint16_t newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}
void op_4840(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{	uint32_t dst = ((src >> 16)&0xFFFF) | ((src&0xFFFF)<<16);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}
void op_4850(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[7] -= 4;
{	offset_68k dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4858(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
{	(Shptr->regs).a[7] -= 4;
{	offset_68k dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}}
void op_4860(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[7] -= 4;
{	offset_68k dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}}
void op_4868(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	offset_68k dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4870(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[7] -= 4;
{	offset_68k dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4878(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	offset_68k dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4879(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	(Shptr->regs).a[7] -= 4;
{	offset_68k dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_487a(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	offset_68k dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_487b(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[7] -= 4;
{	offset_68k dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4880(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	uint32_t dst = (LONG)(BYTE)src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (dst) & 0xffff;
}}}}
void op_4890(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_4898(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	srca -= 2*bitcnt;
	(Shptr->regs).a[srcreg] = srca;
	for(i=0;i<8;i++) { if (mask & 32768) { put_word(srca, rd[i]); srca += 2; } mask <<= 1; }
	for(i=0;i<8;i++) { if (mask & 32768) { put_word(srca, ra[i]); srca += 2; } mask <<= 1; }
}}}}}
void op_48a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48b8(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48b9(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = nextilong();
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{	uint32_t dst = (LONG)(WORD)src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}
void op_48d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	srca -= 4*bitcnt;
	(Shptr->regs).a[srcreg] = srca;
	for(i=0;i<8;i++) { if (mask & 32768) { put_long(srca, rd[i]); srca += 4; } mask <<= 1; }
	for(i=0;i<8;i++) { if (mask & 32768) { put_long(srca, ra[i]); srca += 4; } mask <<= 1; }
}}}}}
void op_48e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48f8(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48f9(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = nextilong();
{	int i, bitcnt = 0;
	uint32_t rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_4a00(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a10(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a18(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}}
void op_4a20(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	offset_68k srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}}
void op_4a28(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a30(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}}
void op_4a38(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a39(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a40(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a48(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a50(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a58(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}}
void op_4a60(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}}
void op_4a68(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a70(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}}
void op_4a78(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a79(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a80(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4a88(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4a90(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4a98(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}}
void op_4aa0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}}
void op_4aa8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4ab0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}}
void op_4ab8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4ab9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4c90(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4c98(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	(Shptr->regs).a[srcreg] = srca;
}}}}
void op_4ca0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}}
void op_4ca8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cb0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cb8(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cb9(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = nextilong();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cba(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cbb(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cd0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cd8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
	(Shptr->regs).a[srcreg] = srca;
}}}}
void op_4ce0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}}
void op_4ce8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cf0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cf8(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cf9(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = nextilong();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cfa(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cfb(uint32_t NUOPPRAM)
{
{	uint16_t mask = nextiword(), bitmask = mask;
{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4e40(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 15) >> 0);
{{	uint32_t src = srcreg;
	MC68000_exception(src+32);
}}}
void op_4e50(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[7] -= 4;
{	offset_68k olda = (Shptr->regs).a[7];
{	LONG src = (Shptr->regs).a[srcreg];
	put_long(olda,src);
	(Shptr->regs).a[srcreg] = ((Shptr->regs).a[7]);
{	WORD offs = nextiword();
	(Shptr->regs).a[7] += offs;
}}}}}}
void op_4e58(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).a[srcreg];
	(Shptr->regs).a[7] = src;
{	offset_68k olda = (Shptr->regs).a[7];
	LONG old = get_long(olda);
{	(Shptr->regs).a[7] += 4;
	(Shptr->regs).a[srcreg] = (old);
}}}}}
void op_4e60(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	LONG src = (Shptr->regs).a[srcreg];
	(Shptr->regs).usp = src;
}}}}
void op_4e68(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	(Shptr->regs).a[srcreg] = ((Shptr->regs).usp);
}}}}
void op_4e70(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{
}}}
void op_4e71(uint32_t NUOPPRAM)
{
{}}
void op_4e72(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	WORD src = nextiword();
	(Shptr->regs).sr = src;
	MakeFromSR();
	MC68000_setstopped(1);
}}}}
void op_4e73(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	offset_68k sra = (Shptr->regs).a[7];
	WORD sr = get_word(sra);
{	(Shptr->regs).a[7] += 2;
{	offset_68k pca = (Shptr->regs).a[7];
	LONG pc = get_long(pca);
{	(Shptr->regs).a[7] += 4;
	(Shptr->regs).sr = sr; MC68000_setpc(pc);
	MakeFromSR();
}}}}}}}
void op_4e74(uint32_t NUOPPRAM)//nop
{
{}}
void op_4e75(uint32_t NUOPPRAM)
{
{{	offset_68k pca = (Shptr->regs).a[7];
	LONG pc = get_long(pca);
{	(Shptr->regs).a[7] += 4;
	MC68000_setpc(pc);
}}}}
void op_4e76(uint32_t NUOPPRAM)
{
{	if(VFLG) MC68000_exception(7);
}}
void op_4e77(uint32_t NUOPPRAM)
{
{	MakeSR();
{	offset_68k sra = (Shptr->regs).a[7];
	WORD sr = get_word(sra);
{	(Shptr->regs).a[7] += 2;
{	offset_68k pca = (Shptr->regs).a[7];
	LONG pc = get_long(pca);
{	(Shptr->regs).a[7] += 4;
	(Shptr->regs).sr &= 0xFF00; sr &= 0xFF;
	(Shptr->regs).sr |= sr; MC68000_setpc(pc);
	MakeFromSR();
}}}}}}
void op_4e90(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4e98(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}}
void op_4ea0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}}
void op_4ea8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4eb0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4eb8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4eb9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4eba(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4ebb(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[7] -= 4;
{	offset_68k spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4ed0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	MC68000_setpc(srca);
}}}
void op_4ed8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
	MC68000_setpc(srca);
}}}}
void op_4ee0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	offset_68k srca = (Shptr->regs).a[srcreg];
	MC68000_setpc(srca);
}}}}
void op_4ee8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	MC68000_setpc(srca);
}}}
void op_4ef0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	offset_68k srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	MC68000_setpc(srca);
}}}
void op_4ef8(uint32_t NUOPPRAM)
{
{{	offset_68k srca = (LONG)(WORD)nextiword();
	MC68000_setpc(srca);
}}}
void op_4ef9(uint32_t NUOPPRAM)
{
{{	offset_68k srca = nextilong();
	MC68000_setpc(srca);
}}}
void op_4efa(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
	MC68000_setpc(srca);
}}}
void op_4efb(uint32_t NUOPPRAM)
{
{{	offset_68k srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
	MC68000_setpc(srca);
}}}
