#include "newcpu.h"
void op_d000(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d010(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d018(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d020(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d028(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d030(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d038(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d039(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d03a(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d03b(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_d03c(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	BYTE src = nextiword();
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_d040(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d048(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d050(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d058(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d060(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d068(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d070(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d078(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d079(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d07a(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d07b(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_d07c(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_d080(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d088(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).a[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d090(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d098(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0b8(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0b9(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0ba(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0bb(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_d0bc(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_d0c0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0c8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0d0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0d8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0e0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0e8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0f0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0f8(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0f9(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d0fa(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0fb(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d0fc(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d100(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	BYTE dst = (Shptr->regs).d[dstreg];
{	ULONG newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((BYTE)(newv)) != 0) ZFLG = 0;
	NFLG = ((BYTE)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}
void op_d108(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	ULONG newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((BYTE)(newv)) != 0) ZFLG = 0;
	NFLG = ((BYTE)(newv)) < 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d110(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d118(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d120(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d128(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d130(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_d138(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d139(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = nextilong();
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) + ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(~dst)) < ((UBYTE)(src));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_d140(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
{	ULONG newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((WORD)(newv)) != 0) ZFLG = 0;
	NFLG = ((WORD)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}
void op_d148(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	CPTR dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	ULONG newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((WORD)(newv)) != 0) ZFLG = 0;
	NFLG = ((WORD)(newv)) < 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d150(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d158(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d160(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	CPTR dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d168(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d170(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_d178(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d179(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = nextilong();
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) + ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(~dst)) < ((UWORD)(src));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_d180(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
{	ULONG newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((LONG)(newv)) != 0) ZFLG = 0;
	NFLG = ((LONG)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_d188(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	CPTR dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	ULONG newv = dst + src + ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	VFLG = (flgs && flgo && !flgn) || (!flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && flgo) || (!flgn && (flgo || flgs));
	if (((LONG)(newv)) != 0) ZFLG = 0;
	NFLG = ((LONG)(newv)) < 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d190(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d198(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d1a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	CPTR dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d1a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d1b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_d1b8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d1b9(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = nextilong();
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) + ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs == flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(~dst)) < ((ULONG)(src));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_d1c0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1c8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).a[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1d0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1d8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1e0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1e8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1f0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1f8(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1f9(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_d1fa(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1fb(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_d1fc(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst + src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
