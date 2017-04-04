#include "newcpu.h"
void op_0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	BYTE dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_10(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_18(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_20(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_28(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_30(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_38(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_39(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_3c(uint32_t NUOPPRAM)
{
{	MakeSR();
{	WORD src = nextiword();
	src &= 0xFF;
	(Shptr->regs).sr |= src;
	MakeFromSR();
}}}
void op_40(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	WORD dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_50(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_58(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_60(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_68(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_70(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	WORD dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_78(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_79(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = nextilong();
	WORD dst = get_word(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_7c(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{	MakeSR();
{	WORD src = nextiword();
	(Shptr->regs).sr |= src;
	MakeFromSR();
}}}}
void op_80(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).d[dstreg];
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_90(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_98(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_a0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_a8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_b0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	LONG dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_b8(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_b9(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
{	offset_68k dsta = nextilong();
	LONG dst = get_long(dsta);
	src |= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_100(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
	src &= 31;
	ZFLG = !(dst & (1 << src));
}}}}
void op_108(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{	offset_68k memp = (Shptr->regs).a[srcreg] + nextiword();
{	uint16_t val = (get_byte(memp) << 8) + get_byte(memp + 2);
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (val) & 0xffff;
}}}
void op_110(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_118(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_120(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_128(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_130(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_138(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_139(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_13a(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
/*	uint32_t dstreg = (LONG)(BYTE)2; */
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = MC68000_getpc();
	dsta += (LONG)(WORD)nextiword();
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_13b(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
/*	uint32_t dstreg = (LONG)(BYTE)3; */
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = MC68000_getpc();
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_13c(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	BYTE dst = nextiword();
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_140(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
	src &= 31;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	(Shptr->regs).d[dstreg] = (dst);
}}}}
void op_148(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 7) >> 0);
	uint32_t dstreg = (opcode & 3584) >> 9;
{	offset_68k memp = (Shptr->regs).a[srcreg] + nextiword();
{	uint32_t val = (get_byte(memp) << 24) + (get_byte(memp + 2) << 16)
              + (get_byte(memp + 4) << 8) + get_byte(memp + 6);
	(Shptr->regs).d[dstreg] = (val);
}}}
void op_150(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_158(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_160(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_168(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_170(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_178(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_179(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_17a(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
/*	uint32_t dstreg = (LONG)(BYTE)2; */
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = MC68000_getpc();
	dsta += (LONG)(WORD)nextiword();
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_17b(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
/*	uint32_t dstreg = (LONG)(BYTE)3; */
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = MC68000_getpc();
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_180(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
	src &= 31;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	(Shptr->regs).d[dstreg] = (dst);
}}}}
void op_188(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = (Shptr->regs).d[srcreg];
	offset_68k memp = (Shptr->regs).a[dstreg] + nextiword();
	put_byte(memp, src >> 8); put_byte(memp + 2, src);
}}}
void op_190(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}
void op_198(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_1a0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_1a8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}
void op_1b0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_1b8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}
void op_1b9(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}
void op_1ba(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
/*	uint32_t dstreg = (LONG)(BYTE)2; */
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = MC68000_getpc();
	dsta += (LONG)(WORD)nextiword();
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_1bb(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
/*	uint32_t dstreg = (LONG)(BYTE)3; */
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = MC68000_getpc();
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_1c0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
{	LONG dst = (Shptr->regs).d[dstreg];
	src &= 31;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	(Shptr->regs).d[dstreg] = (dst);
}}}}
void op_1c8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = (Shptr->regs).d[srcreg];
	offset_68k memp = (Shptr->regs).a[dstreg] + nextiword();
	put_byte(memp, src >> 24); put_byte(memp + 2, src >> 16);
	put_byte(memp + 4, src >> 8); put_byte(memp + 6, src);
}}}
void op_1d0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_1d8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_1e0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_1e8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_1f0(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_1f8(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_1f9(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_1fa(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
/*	uint32_t dstreg = (LONG)(BYTE)2; */
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = MC68000_getpc();
	dsta += (LONG)(WORD)nextiword();
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_1fb(uint32_t opcode)
{
	uint32_t srcreg = (LONG)(BYTE)((opcode & 3584) >> 9);
/*	uint32_t dstreg = (LONG)(BYTE)3; */
{{	BYTE src = (Shptr->regs).d[srcreg];
{	offset_68k dsta = MC68000_getpc();
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_200(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	BYTE dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_210(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_218(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_220(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_228(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_230(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_238(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_239(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_23c(uint32_t NUOPPRAM)
{
{	MakeSR();
{	WORD src = nextiword();
	src |= 0xFF00;
	(Shptr->regs).sr &= src;
	MakeFromSR();
}}}
void op_240(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	WORD dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_250(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_258(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_260(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_268(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_270(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	WORD dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_278(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_279(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = nextilong();
	WORD dst = get_word(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_27c(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{	MakeSR();
{	WORD src = nextiword();
	(Shptr->regs).sr &= src;
	MakeFromSR();
}}}}
void op_280(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).d[dstreg];
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_290(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_298(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2a0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2a8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2b0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	LONG dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_2b8(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_2b9(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
{	offset_68k dsta = nextilong();
	LONG dst = get_long(dsta);
	src &= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_400(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_410(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_418(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_420(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_428(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_430(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_438(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
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
void op_439(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
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
void op_440(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_450(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_458(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_460(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_468(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_470(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_478(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
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
void op_479(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
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
void op_480(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_490(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_498(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_4a0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_4a8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_4b0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_4b8(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
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
void op_4b9(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
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
void op_600(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
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
void op_610(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_618(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_620(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_628(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_630(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
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
void op_638(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
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
void op_639(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
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
void op_640(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
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
void op_650(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_658(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_660(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_668(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_670(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
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
void op_678(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
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
void op_679(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
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
void op_680(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
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
void op_690(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_698(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_6a0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_6a8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_6b0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
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
void op_6b8(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
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
void op_6b9(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
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
void op_800(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	LONG dst = (Shptr->regs).d[dstreg];
	src &= 31;
	ZFLG = !(dst & (1 << src));
}}}}
void op_810(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_818(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_820(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_828(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_830(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_838(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_839(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_83a(uint32_t NUOPPRAM)
{
/*	uint32_t dstreg = (LONG)(BYTE)2; */
{{	WORD src = nextiword();
{	offset_68k dsta = MC68000_getpc();
	dsta += (LONG)(WORD)nextiword();
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_83b(uint32_t NUOPPRAM)
{
/*	uint32_t dstreg = (LONG)(BYTE)3; */
{{	WORD src = nextiword();
{	offset_68k dsta = MC68000_getpc();
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}}
void op_83c(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	BYTE dst = nextiword();
	src &= 7;
	ZFLG = !(dst & (1 << src));
}}}}
void op_840(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	LONG dst = (Shptr->regs).d[dstreg];
	src &= 31;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	(Shptr->regs).d[dstreg] = (dst);
}}}}
void op_850(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_858(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_860(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_868(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_870(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_878(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_879(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_87a(uint32_t NUOPPRAM)
{
/*	uint32_t dstreg = (LONG)(BYTE)2; */
{{	WORD src = nextiword();
{	offset_68k dsta = MC68000_getpc();
	dsta += (LONG)(WORD)nextiword();
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_87b(uint32_t NUOPPRAM)
{
/*	uint32_t dstreg = (LONG)(BYTE)3; */
{{	WORD src = nextiword();
{	offset_68k dsta = MC68000_getpc();
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst ^= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_880(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	LONG dst = (Shptr->regs).d[dstreg];
	src &= 31;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	(Shptr->regs).d[dstreg] = (dst);
}}}}
void op_890(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}
void op_898(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_8a0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_8a8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}
void op_8b0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_8b8(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}
void op_8b9(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}
void op_8ba(uint32_t NUOPPRAM)
{
/*	uint32_t dstreg = (LONG)(BYTE)2; */
{{	WORD src = nextiword();
{	offset_68k dsta = MC68000_getpc();
	dsta += (LONG)(WORD)nextiword();
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_8bb(uint32_t NUOPPRAM)
{
/*	uint32_t dstreg = (LONG)(BYTE)3; */
{{	WORD src = nextiword();
{	offset_68k dsta = MC68000_getpc();
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst &= ~(1 << src);
	put_byte(dsta,dst);
}}}}}
void op_8c0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	LONG dst = (Shptr->regs).d[dstreg];
	src &= 31;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	(Shptr->regs).d[dstreg] = (dst);
}}}}
void op_8d0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_8d8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_8e0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_8e8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_8f0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_8f8(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_8f9(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}
void op_8fa(uint32_t NUOPPRAM)
{
/*	uint32_t dstreg = (LONG)(BYTE)2; */
{{	WORD src = nextiword();
{	offset_68k dsta = MC68000_getpc();
	dsta += (LONG)(WORD)nextiword();
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_8fb(uint32_t NUOPPRAM)
{
/*	uint32_t dstreg = (LONG)(BYTE)3; */
{{	WORD src = nextiword();
{	offset_68k dsta = MC68000_getpc();
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src &= 7;
	ZFLG = !(dst & (1 << src));
	dst |= (1 << src);
	put_byte(dsta,dst);
}}}}}
void op_a00(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	BYTE dst = (Shptr->regs).d[dstreg];
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xff; (Shptr->regs).d[dstreg] |= (src) & 0xff;
}}}}
void op_a10(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_a18(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_a20(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_a28(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_a30(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}}
void op_a38(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_a39(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((BYTE)(src)) == 0;
	NFLG = ((BYTE)(src)) < 0;
	put_byte(dsta,src);
}}}}
void op_a3c(uint32_t NUOPPRAM)
{
{	MakeSR();
{	WORD src = nextiword();
	src &= 0xFF;
	(Shptr->regs).sr ^= src;
	MakeFromSR();
}}}
void op_a40(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	WORD dst = (Shptr->regs).d[dstreg];
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	(Shptr->regs).d[dstreg] &= ~0xffff; (Shptr->regs).d[dstreg] |= (src) & 0xffff;
}}}}
void op_a50(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_a58(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_a60(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_a68(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_a70(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	WORD dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}}
void op_a78(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_a79(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = nextilong();
	WORD dst = get_word(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((WORD)(src)) == 0;
	NFLG = ((WORD)(src)) < 0;
	put_word(dsta,src);
}}}}
void op_a7c(uint32_t NUOPPRAM)
{
{if (!(Shptr->regs).s) { (Shptr->regs).pc_p--; MC68000_exception(8); } else
{	MakeSR();
{	WORD src = nextiword();
	(Shptr->regs).sr ^= src;
	MakeFromSR();
}}}}
void op_a80(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).d[dstreg];
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	(Shptr->regs).d[dstreg] = (src);
}}}}
void op_a90(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_a98(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_aa0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_aa8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_ab0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	LONG dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}}
void op_ab8(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_ab9(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
{	offset_68k dsta = nextilong();
	LONG dst = get_long(dsta);
	src ^= dst;
	VFLG = CFLG = 0;
	ZFLG = ((LONG)(src)) == 0;
	NFLG = ((LONG)(src)) < 0;
	put_long(dsta,src);
}}}}
void op_c00(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	BYTE dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c10(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c18(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{	(Shptr->regs).a[dstreg] += areg_byteinc[dstreg];
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_c20(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	(Shptr->regs).a[dstreg] -= areg_byteinc[dstreg];
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_c28(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c30(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	BYTE src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_c38(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c39(uint32_t NUOPPRAM)
{
{{	BYTE src = nextiword();
{	offset_68k dsta = nextilong();
	BYTE dst = get_byte(dsta);
{{uint32_t newv = ((BYTE)(dst)) - ((BYTE)(src));
{	int flgs = ((BYTE)(src)) < 0;
	int flgo = ((BYTE)(dst)) < 0;
	int flgn = ((BYTE)(newv)) < 0;
	ZFLG = ((BYTE)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint8_t)(src)) > ((uint8_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c40(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	WORD dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c50(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c58(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{	(Shptr->regs).a[dstreg] += 2;
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_c60(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	(Shptr->regs).a[dstreg] -= 2;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_c68(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c70(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	WORD src = nextiword();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_c78(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c79(uint32_t NUOPPRAM)
{
{{	WORD src = nextiword();
{	offset_68k dsta = nextilong();
	WORD dst = get_word(dsta);
{{uint32_t newv = ((WORD)(dst)) - ((WORD)(src));
{	int flgs = ((WORD)(src)) < 0;
	int flgo = ((WORD)(dst)) < 0;
	int flgn = ((WORD)(newv)) < 0;
	ZFLG = ((WORD)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint16_t)(src)) > ((uint16_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c80(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	LONG dst = (Shptr->regs).d[dstreg];
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c90(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_c98(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{	(Shptr->regs).a[dstreg] += 4;
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_ca0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	(Shptr->regs).a[dstreg] -= 4;
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_ca8(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg] + (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_cb0(uint32_t opcode)
{
	uint32_t dstreg = (opcode & 7) >> 0;
{{	LONG src = nextilong();
{	offset_68k dsta = (Shptr->regs).a[dstreg];
	dsta = get_disp_ea (dsta, nextiword());
{	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}}
void op_cb8(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
{	offset_68k dsta = (LONG)(WORD)nextiword();
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
void op_cb9(uint32_t NUOPPRAM)
{
{{	LONG src = nextilong();
{	offset_68k dsta = nextilong();
	LONG dst = get_long(dsta);
{{uint32_t newv = ((LONG)(dst)) - ((LONG)(src));
{	int flgs = ((LONG)(src)) < 0;
	int flgo = ((LONG)(dst)) < 0;
	int flgn = ((LONG)(newv)) < 0;
	ZFLG = ((LONG)(newv)) == 0;
	VFLG = (flgs != flgo) && (flgn != flgo);
	CFLG = ((uint32_t)(src)) > ((uint32_t)(dst));
	NFLG = flgn != 0;
}}}}}}}
