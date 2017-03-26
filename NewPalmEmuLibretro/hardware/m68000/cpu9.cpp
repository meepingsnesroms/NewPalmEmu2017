#include "newcpu.h"
void op_9000(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9010(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9018(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[srcreg] += areg_byteinc[srcreg];
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_9020(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_9028(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9030(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_9038(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9039(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_903a(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_903b(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	BYTE src = get_byte(srca);
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}}
void op_903c(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	BYTE src = nextiword();
{	BYTE dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}}
void op_9040(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9048(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9050(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9058(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_9060(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_9068(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9070(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_9078(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9079(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_907a(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_907b(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}}
void op_907c(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	WORD dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}}
void op_9080(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_9088(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).a[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_9090(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_9098(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_90b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90b8(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_90b9(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_90ba(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90bb(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}}
void op_90bc(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).d[dstreg];
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}}
void op_90c0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90c8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).a[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90d0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90d8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[srcreg] += 2;
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90e0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90e8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90f0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90f8(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90f9(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_90fa(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90fb(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	WORD src = get_word(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_90fc(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = nextiword();
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_9100(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	BYTE dst = (Shptr->regs).d[dstreg];
{	ULONG newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((BYTE)(newv)) != 0) ZFLG = 0;
	NFLG = ((BYTE)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (newv) & 0xff;
}}}}}}
void op_9108(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= areg_byteinc[srcreg];
{	CPTR srca = (Shptr->regs).a[srcreg];
	BYTE src = get_byte(srca);
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	ULONG newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((BYTE)(newv)) != 0) ZFLG = 0;
	NFLG = ((BYTE)(newv)) < 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_9110(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_9118(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_9120(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_9128(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_9130(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}}
void op_9138(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_9139(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	CPTR dsta = nextilong();
	BYTE dst = get_byte(dsta);
{{ULONG newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UBYTE)(src)) > ((UBYTE)(dst));
	NFLG = flgn != 0;
	put_byte(dsta,newv);
}}}}}}}
void op_9140(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	WORD src = (Shptr->regs).d[srcreg];
{	WORD dst = (Shptr->regs).d[dstreg];
{	ULONG newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((WORD)(newv)) != 0) ZFLG = 0;
	NFLG = ((WORD)(newv)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (newv) & 0xffff;
}}}}}}
void op_9148(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 2;
{	CPTR srca = (Shptr->regs).a[srcreg];
	WORD src = get_word(srca);
{	(Shptr->regs).a[dstreg] -= 2;
{	CPTR dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	ULONG newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((WORD)(newv)) != 0) ZFLG = 0;
	NFLG = ((WORD)(newv)) < 0;
	put_word(dsta,newv);
}}}}}}}}
void op_9150(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_9158(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_9160(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 2;
{	CPTR dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_9168(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_9170(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}}
void op_9178(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_9179(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	WORD src = (Shptr->regs).d[srcreg];
{	CPTR dsta = nextilong();
	WORD dst = get_word(dsta);
{{ULONG newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((UWORD)(src)) > ((UWORD)(dst));
	NFLG = flgn != 0;
	put_word(dsta,newv);
}}}}}}}
void op_9180(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
{	ULONG newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((LONG)(newv)) != 0) ZFLG = 0;
	NFLG = ((LONG)(newv)) < 0;
	(Shptr->regs).d[dstreg] = (newv);
}}}}}}
void op_9188(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[dstreg] -= 4;
{	CPTR dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	ULONG newv = dst - src - ((Shptr->regs).x ? 1 : 0);
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	VFLG = (!flgs && flgo && !flgn) || (flgs && !flgo && flgn);
	(Shptr->regs).x = CFLG = (flgs && !flgo) || (flgn && (!flgo || flgs));
	if (((LONG)(newv)) != 0) ZFLG = 0;
	NFLG = ((LONG)(newv)) < 0;
	put_long(dsta,newv);
}}}}}}}}
void op_9190(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_9198(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_91a0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= 4;
{	CPTR dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_91a8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_91b0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	ULONG dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}}
void op_91b8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_91b9(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	LONG src = (Shptr->regs).d[srcreg];
{	CPTR dsta = nextilong();
	LONG dst = get_long(dsta);
{{ULONG newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = (Shptr->regs).x = ((ULONG)(src)) > ((ULONG)(dst));
	NFLG = flgn != 0;
	put_long(dsta,newv);
}}}}}}}
void op_91c0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91c8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = (Shptr->regs).a[srcreg];
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91d0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91d8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	(Shptr->regs).a[srcreg] += 4;
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91e0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	(Shptr->regs).a[srcreg] -= 4;
{	CPTR srca = (Shptr->regs).a[srcreg];
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91e8(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg] + (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91f0(ULONG opcode)
{
	ULONG srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (Shptr->regs).a[srcreg];
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91f8(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = (LONG)(WORD)nextiword();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91f9(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = nextilong();
	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
void op_91fa(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca += (LONG)(WORD)nextiword();
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91fb(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	CPTR srca = MC68000_getpc();
	srca = get_disp_ea (srca, nextiword());
{	LONG src = get_long(srca);
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}}
void op_91fc(ULONG opcode)
{
	ULONG dstreg = (opcode & 3584) >> 9;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).a[dstreg];
{	ULONG newv = dst - src;
	(Shptr->regs).a[dstreg] = (newv);
}}}}}
