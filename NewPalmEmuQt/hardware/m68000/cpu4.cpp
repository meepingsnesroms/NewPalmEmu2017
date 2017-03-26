#include "newcpu.h"
void op_4000(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	src += (Shptr->regs).x;
{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (dst) & 0xff;
}}}}}}
void op_4010(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4018(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	src += (Shptr->regs).x;
{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4020(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4028(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4030(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4038(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4039(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	BYTE src = get_byte(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4040(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	src += (Shptr->regs).x;
{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (dst) & 0xffff;
}}}}}}
void op_4050(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4058(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	src += (Shptr->regs).x;
{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4060(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4068(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4070(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4078(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4079(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4080(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{	src += (Shptr->regs).x;
{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}}}
void op_4090(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_4098(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	src += (Shptr->regs).x;
{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_40a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_40a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_40b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_40b8(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_40b9(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	LONG src = get_long(srca);
{	src += (Shptr->regs).x;
{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_40c0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	MakeSR();
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= ((Shptr->regs).sr) & 0xffff;
}}}
void op_40d0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_40d8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 2;
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}}
void op_40e0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}}
void op_40e8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_40f0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_40f8(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_40f9(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	MakeSR();
	put_word(srca,(Shptr->regs).sr);
}}}
void op_4180(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_4188(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_4190(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_4198(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_41b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41b8(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_41b9(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_41ba(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41bb(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}}
void op_41bc(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	WORD dst = (Shptr->regs).d[dstreg];
	if ((WORD)dst < 0) { NFLG=1; MC68000_exception(6); }
	else if ((WORD)dst > (WORD)src) { NFLG=0; MC68000_exception(6); }
}}}}
void op_41d0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41d8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
{	(Shptr->regs).a[dstreg] = (srca);
}}}}}
void op_41e0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[dstreg] = (srca);
}}}}}
void op_41e8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41f0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41f8(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41f9(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41fa(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_41fb(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[dstreg] = (srca);
}}}}
void op_4200(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (0) & 0xff;
}}}
void op_4210(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4218(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}}
void op_4220(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}}
void op_4228(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4230(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4238(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4239(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(0)) == 0;
	NFLG = ((BYTE)(0)) < 0;
	put_byte(srca,0);
}}}
void op_4240(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (0) & 0xffff;
}}}
void op_4250(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4258(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}}
void op_4260(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}}
void op_4268(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4270(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4278(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4279(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(0)) == 0;
	NFLG = ((WORD)(0)) < 0;
	put_word(srca,0);
}}}
void op_4280(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	(Shptr->regs).d[srcreg] = (0);
}}}
void op_4290(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_4298(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}}
void op_42a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}}
void op_42a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_42b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_42b8(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_42b9(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(0)) == 0;
	NFLG = ((LONG)(0)) < 0;
	put_long(srca,0);
}}}
void op_4400(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
{{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (dst) & 0xff;
}}}}}}
void op_4410(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4418(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4420(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4428(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4430(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}}
void op_4438(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4439(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	BYTE src = get_byte(srca);
{{ULONG dst = ((BYTE)(0)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(0)) < 0;
	int flgn = ((BYTE)(dst)) < 0;
	ZFLG = ((BYTE)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(0));
	NFLG = flgn != 0;
	put_byte(srca,dst);
}}}}}}
void op_4440(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (dst) & 0xffff;
}}}}}}
void op_4450(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4458(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4460(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4468(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4470(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}}
void op_4478(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4479(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
{{ULONG dst = ((WORD)(0)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(0)) < 0;
	int flgn = ((WORD)(dst)) < 0;
	ZFLG = ((WORD)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(0));
	NFLG = flgn != 0;
	put_word(srca,dst);
}}}}}}
void op_4480(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}}}
void op_4490(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_4498(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_44a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_44a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_44b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}}
void op_44b8(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_44b9(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	LONG src = get_long(srca);
{{ULONG dst = ((LONG)(0)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(0)) < 0;
	int flgn = ((LONG)(dst)) < 0;
	ZFLG = ((LONG)(dst)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(0));
	NFLG = flgn != 0;
	put_long(srca,dst);
}}}}}}
void op_44c0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44d0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44d8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44e0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44e8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44f0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44f8(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44f9(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_44fa(ULONG NUOPPRAM)
{
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44fb(ULONG NUOPPRAM)
{
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}}
void op_44fc(ULONG NUOPPRAM)
{
{{	BYTE src = nextiword();
	MakeSR();
	(Shptr->regs).sr &= 0xFF00;
	(Shptr->regs).sr |= src & 0xFF;
	MakeFromSR();
}}}
void op_4600(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (dst) & 0xff;
}}}}
void op_4610(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}
void op_4618(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}}
void op_4620(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}}
void op_4628(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}
void op_4630(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}}
void op_4638(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}
void op_4639(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	BYTE src = get_byte(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(dst)) == 0;
	NFLG = ((BYTE)(dst)) < 0;
	put_byte(srca,dst);
}}}}
void op_4640(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (dst) & 0xffff;
}}}}
void op_4650(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}
void op_4658(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}}
void op_4660(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}}
void op_4668(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}
void op_4670(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}}
void op_4678(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}
void op_4679(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	put_word(srca,dst);
}}}}
void op_4680(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}
void op_4690(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}
void op_4698(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}}
void op_46a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}}
void op_46a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}
void op_46b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}}
void op_46b8(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}
void op_46b9(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	LONG src = get_long(srca);
{	ULONG dst = ~src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	put_long(srca,dst);
}}}}
void op_46c0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	WORD src = (Shptr->regs).d[srcreg];
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46d0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46d8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46e0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46e8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46f0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46f8(ULONG NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46f9(ULONG NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_46fa(ULONG NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46fb(ULONG NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}}
void op_46fc(ULONG NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	WORD src = nextiword();
	(Shptr->regs).sr = src;
	MakeFromSR();
}}}}
void op_4800(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	UWORD newv_lo = - (src & 0xF) - (Shptr->regs).x;
	UWORD newv_hi = - (src & 0xF0);
	UWORD newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	(Shptr->regs).d[srcreg] &= ~0xff; (Shptr->regs).d[srcreg] |= (newv) & 0xff;
}}}}
void op_4810(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	UWORD newv_lo = - (src & 0xF) - (Shptr->regs).x;
	UWORD newv_hi = - (src & 0xF0);
	UWORD newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}
void op_4818(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	UWORD newv_lo = - (src & 0xF) - (Shptr->regs).x;
	UWORD newv_hi = - (src & 0xF0);
	UWORD newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}}
void op_4820(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	UWORD newv_lo = - (src & 0xF) - (Shptr->regs).x;
	UWORD newv_hi = - (src & 0xF0);
	UWORD newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}}
void op_4828(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	UWORD newv_lo = - (src & 0xF) - (Shptr->regs).x;
	UWORD newv_hi = - (src & 0xF0);
	UWORD newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}
void op_4830(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	UWORD newv_lo = - (src & 0xF) - (Shptr->regs).x;
	UWORD newv_hi = - (src & 0xF0);
	UWORD newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}}
void op_4838(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	UWORD newv_lo = - (src & 0xF) - (Shptr->regs).x;
	UWORD newv_hi = - (src & 0xF0);
	UWORD newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}
void op_4839(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	BYTE src = get_byte(srca);
{	UWORD newv_lo = - (src & 0xF) - (Shptr->regs).x;
	UWORD newv_hi = - (src & 0xF0);
	UWORD newv;
	if (newv_lo > 9) { newv_lo-=6; newv_hi-=0x10; }
	newv = newv_hi + (newv_lo & 0xF);	CFLG = (Shptr->regs).x = (newv_hi & 0x1F0) > 0x90;
	if (CFLG) newv -= 0x60;
	if (newv != 0) ZFLG = 0;
	put_byte(srca,newv);
}}}}
void op_4840(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{	ULONG dst = ((src >> 16)&0xFFFF) | ((src&0xFFFF)<<16);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}
void op_4850(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[7] -= 4;
{	CPTR dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4858(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
{	(Shptr->regs).a[7] -= 4;
{	CPTR dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}}
void op_4860(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[7] -= 4;
{	CPTR dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}}
void op_4868(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	CPTR dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4870(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[7] -= 4;
{	CPTR dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4878(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	CPTR dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4879(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
{	(Shptr->regs).a[7] -= 4;
{	CPTR dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_487a(ULONG NUOPPRAM)
{
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	CPTR dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_487b(ULONG NUOPPRAM)
{
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[7] -= 4;
{	CPTR dsta = (Shptr->regs).a[7];
	put_long(dsta,srca);
}}}}}
void op_4880(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
{	ULONG dst = (LONG)(BYTE)src;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(dst)) == 0;
	NFLG = ((WORD)(dst)) < 0;
	(Shptr->regs).d[srcreg] &= ~0xffff; (Shptr->regs).d[srcreg] |= (dst) & 0xffff;
}}}}
void op_4890(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_4898(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	srca -= 2*bitcnt;
	(Shptr->regs).a[srcreg] = srca;
	for(i=0;i<8;i++) { if (mask & 32768) { put_word(srca, rd[i]); srca += 2; } mask <<= 1; }
	for(i=0;i<8;i++) { if (mask & 32768) { put_word(srca, ra[i]); srca += 2; } mask <<= 1; }
}}}}}
void op_48a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48b8(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48b9(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = nextilong();
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, rd[i]); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_word(srca, ra[i]); srca += 2; } mask >>= 1; }
}}}}
void op_48c0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
{	ULONG dst = (LONG)(WORD)src;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(dst)) == 0;
	NFLG = ((LONG)(dst)) < 0;
	(Shptr->regs).d[srcreg] = (dst);
}}}}
void op_48d0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48d8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48e0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	srca -= 4*bitcnt;
	(Shptr->regs).a[srcreg] = srca;
	for(i=0;i<8;i++) { if (mask & 32768) { put_long(srca, rd[i]); srca += 4; } mask <<= 1; }
	for(i=0;i<8;i++) { if (mask & 32768) { put_long(srca, ra[i]); srca += 4; } mask <<= 1; }
}}}}}
void op_48e8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48f0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48f8(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_48f9(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = nextilong();
{	int i, bitcnt = 0;
	ULONG rd[8], ra[8];
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { rd[i] = (Shptr->regs).d[i]; ra[i] = (Shptr->regs).a[i]; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, rd[i]); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { put_long(srca, ra[i]); srca += 4; } mask >>= 1; }
}}}}
void op_4a00(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	BYTE src = (Shptr->regs).d[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a10(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a18(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}}
void op_4a20(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}}
void op_4a28(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a30(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}}
void op_4a38(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a39(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	BYTE src = get_byte(srca);
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
}}}
void op_4a40(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).d[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a48(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	WORD src = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a50(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a58(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}}
void op_4a60(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}}
void op_4a68(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a70(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}}
void op_4a78(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a79(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
}}}
void op_4a80(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).d[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4a88(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).a[srcreg];
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4a90(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4a98(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}}
void op_4aa0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}}
void op_4aa8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4ab0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}}
void op_4ab8(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4ab9(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	LONG src = get_long(srca);
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
}}}
void op_4c90(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4c98(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	(Shptr->regs).a[srcreg] = srca;
}}}}
void op_4ca0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}}
void op_4ca8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cb0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cb8(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cb9(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = nextilong();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cba(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cbb(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = (LONG)(WORD)get_word(srca); srca += 2; } mask >>= 1; }
}}}}
void op_4cd0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cd8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
	(Shptr->regs).a[srcreg] = srca;
}}}}
void op_4ce0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}}
void op_4ce8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cf0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cf8(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cf9(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = nextilong();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cfa(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4cfb(ULONG NUOPPRAM)
{
{	UWORD mask = nextiword(), bitmask = mask;
{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	int i, bitcnt = 0;
	for(i=0;i<16;i++) { bitcnt += bitmask & 1; bitmask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).d[i] = get_long(srca); srca += 4; } mask >>= 1; }
	for(i=0;i<8;i++) { if (mask & 1) { (Shptr->regs).a[i] = get_long(srca); srca += 4; } mask >>= 1; }
}}}}
void op_4e40(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 15) >> 0);
{{	ULONG src = srcreg;
	MC68000_exception(src+32);
}}}
void op_4e50(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[7] -= 4;
{	CPTR olda = (Shptr->regs).a[7];
{	LONG src = (Shptr->regs).a[srcreg];
	put_long(olda,src);
	(Shptr->regs).a[srcreg] = ((Shptr->regs).a[7]);
{	WORD offs = nextiword();
	(Shptr->regs).a[7] += offs;
}}}}}}
void op_4e58(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	LONG src = (Shptr->regs).a[srcreg];
	(Shptr->regs).a[7] = src;
{	CPTR olda = (Shptr->regs).a[7];
	LONG old = get_long(olda);
{	(Shptr->regs).a[7] += 4;
	(Shptr->regs).a[srcreg] = (old);
}}}}}
void op_4e60(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	LONG src = (Shptr->regs).a[srcreg];
	(Shptr->regs).usp = src;
}}}}
void op_4e68(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	(Shptr->regs).a[srcreg] = ((Shptr->regs).usp);
}}}}
void op_4e70(ULONG NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{	customreset();
}}}
void op_4e71(ULONG NUOPPRAM)
{
{}}
void op_4e72(ULONG NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	WORD src = nextiword();
	(Shptr->regs).sr = src;
	MakeFromSR();
	MC68000_setstopped(1);
}}}}
void op_4e73(ULONG NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{{	CPTR sra = (Shptr->regs).a[7];
	WORD sr = get_word(sra);
{	(Shptr->regs).a[7] += 2;
{	CPTR pca = (Shptr->regs).a[7];
	LONG pc = get_long(pca);
{	(Shptr->regs).a[7] += 4;
	(Shptr->regs).sr = sr; MC68000_setpc(pc);
	MakeFromSR();
}}}}}}}
void op_4e74(ULONG NUOPPRAM)//nop
{
{}}
void op_4e75(ULONG NUOPPRAM)
{
{{	CPTR pca = (Shptr->regs).a[7];
	LONG pc = get_long(pca);
{	(Shptr->regs).a[7] += 4;
	MC68000_setpc(pc);
}}}}
void op_4e76(ULONG NUOPPRAM)
{
{	if(VFLG) MC68000_exception(7);
}}
void op_4e77(ULONG NUOPPRAM)
{
{	MakeSR();
{	CPTR sra = (Shptr->regs).a[7];
	WORD sr = get_word(sra);
{	(Shptr->regs).a[7] += 2;
{	CPTR pca = (Shptr->regs).a[7];
	LONG pc = get_long(pca);
{	(Shptr->regs).a[7] += 4;
	(Shptr->regs).sr &= 0xFF00; sr &= 0xFF;
	(Shptr->regs).sr |= sr; MC68000_setpc(pc);
	MakeFromSR();
}}}}}}
void op_4e90(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4e98(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}}
void op_4ea0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}}
void op_4ea8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4eb0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4eb8(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4eb9(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4eba(ULONG NUOPPRAM)
{
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4ebb(ULONG NUOPPRAM)
{
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	(Shptr->regs).a[7] -= 4;
{	CPTR spa = (Shptr->regs).a[7];
	put_long(spa,MC68000_getpc());
	MC68000_setpc(srca);
}}}}}
void op_4ed0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	MC68000_setpc(srca);
}}}
void op_4ed8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
{	(Shptr->regs).a[srcreg] += 4;
	MC68000_setpc(srca);
}}}}
void op_4ee0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	MC68000_setpc(srca);
}}}}
void op_4ee8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	MC68000_setpc(srca);
}}}
void op_4ef0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
	MC68000_setpc(srca);
}}}
void op_4ef8(ULONG NUOPPRAM)
{
{{	CPTR srca = (LONG)(WORD)nextiword();
	MC68000_setpc(srca);
}}}
void op_4ef9(ULONG NUOPPRAM)
{
{{	CPTR srca = nextilong();
	MC68000_setpc(srca);
}}}
void op_4efa(ULONG NUOPPRAM)
{
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
	MC68000_setpc(srca);
}}}
void op_4efb(ULONG NUOPPRAM)
{
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
	MC68000_setpc(srca);
}}}
